import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_targets as fixture
from app.application.queue import queue_list,mutate,prepare
from app.application.targets import target_bundle
from app.application.workspaces import rename
from app.infrastructure.persistence.store import Store
from app.domain.workspace.model import ConflictError,ValidationError,PathError
from app.domain.binary.elf import Cancelled

class QueueTests(unittest.TestCase):
    def setUp(self):
        fixture.TargetTests.setUp(self)
        target_bundle(self.store,self.iid,'3:2');target_bundle(self.store,self.iid,'3:1')
    def add(self,sid='3:2',**kw):return mutate(self.store,'add',input_id=self.iid,symbol_id=sid,**kw)
    def update(self,item,token,**kw):return mutate(self.store,'update',item_id=item,expected_token=token,**kw)
    def test_add_list_priority_filter_and_counts(self):
        a=self.add(priority=20,note='Inspect function');b=self.add('3:1',priority=90)
        self.assertEqual([x['priority'] for x in b['items']],[90,20])
        self.assertEqual(b['counts']['TODO'],2);self.assertEqual(queue_list(self.store,min_priority=50)['returned'],1)
        self.assertFalse(b['automatic_execution']);self.assertFalse(b['binary_matching_claimed'])
        self.assertEqual(self.path.read_bytes(),self.raw)
    def test_pause_resume_after_reopen(self):
        a=self.add();iid=a['items'][0]['id'];b=self.update(iid,a['queue_token'],status='ACTIVE')
        c=self.update(iid,b['queue_token'],status='PAUSED',note='Continue later')
        self.store=Store(self.store.root);reopened=queue_list(self.store)
        self.assertEqual(reopened,c);d=self.update(iid,c['queue_token'],status='ACTIVE')
        self.assertEqual(d['counts']['ACTIVE'],1)
        e=self.update(iid,d['queue_token'],status='REVIEWED');self.assertFalse(e['binary_matching_claimed'])
    def test_only_one_active(self):
        a=self.add();first=a['items'][0]['id'];b=self.add('3:1');second=next(x['id'] for x in b['items'] if x['id']!=first)
        c=self.update(first,b['queue_token'],status='ACTIVE');before=(self.store.root/'queue/state.json').read_bytes()
        with self.assertRaises(ConflictError):self.update(second,c['queue_token'],status='ACTIVE')
        self.assertEqual((self.store.root/'queue/state.json').read_bytes(),before)
    def test_stale_token_refused(self):
        a=self.add();iid=a['items'][0]['id'];self.update(iid,a['queue_token'],note='first')
        with self.assertRaises(ConflictError):self.update(iid,a['queue_token'],note='stale')
        self.assertEqual(queue_list(self.store)['items'][0]['note'],'first')
    def test_duplicate_invalid_priority_note_status(self):
        a=self.add()
        with self.assertRaises(ValidationError):self.add()
        for value in (-1,101,True,'1'):
            with self.assertRaises(ValidationError):queue_list(self.store,min_priority=value)
        for kw in ({'priority':101},{'note':'x'*501},{'note':'x\x00'},{'status':'MATCHED'},{}):
            with self.assertRaises(ValidationError):self.update(a['items'][0]['id'],a['queue_token'],**kw)
    def test_history_previous_state_exact(self):
        a=self.add();old=(self.store.root/'queue/state.json').read_bytes();self.update(a['items'][0]['id'],a['queue_token'],priority=70)
        archived=self.store.root/('queue/history/000001-'+a['queue_token']+'.json')
        self.assertEqual(archived.read_bytes(),old)
    def test_atomic_failure_old_state_survives_retry(self):
        a=self.add();old=(self.store.root/'queue/state.json').read_bytes();original=self.store.atomic
        def fail(path,data):
            if path=='queue/state.json':raise OSError('injected')
            return original(path,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.update(a['items'][0]['id'],a['queue_token'],note='new')
        self.assertEqual((self.store.root/'queue/state.json').read_bytes(),old)
        b=self.update(a['items'][0]['id'],a['queue_token'],note='new');self.assertEqual(b['items'][0]['note'],'new')
    def test_list_available_source_missing_update_refused(self):
        a=self.add();self.path.unlink()
        self.assertEqual(queue_list(self.store),a)
        with self.assertRaises(FileNotFoundError):self.update(a['items'][0]['id'],a['queue_token'],status='ACTIVE')
    def test_source_changed_refused(self):
        a=self.add();self.path.write_bytes(self.raw+b'changed')
        with self.assertRaises(ConflictError):self.update(a['items'][0]['id'],a['queue_token'],status='ACTIVE')
    def test_corrupt_state_and_duplicate_schema_refused(self):
        self.add();path=self.store.root/'queue/state.json';original=path.read_bytes();path.write_text('{}')
        with self.assertRaises(ValidationError):queue_list(self.store)
        data=json.loads(original);data['items'].append(data['items'][0]);path.write_text(json.dumps(data))
        with self.assertRaises(ValidationError):queue_list(self.store)
    def test_manifest_conflict(self):
        def change(*args):
            result=prepare(*args);rename(self.store,'Changed');return result
        with patch('app.application.queue.prepare',side_effect=change):
            with self.assertRaises(ConflictError):self.add()
        self.assertFalse((self.store.root/'queue').exists())
    def test_cancel_symlink_and_limit(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.add(cancel=event)
        self.add()
        with patch('app.application.queue.MAX_ITEMS',1):
            with self.assertRaises(ValidationError):self.add('3:1')
        # Use a clean root to exercise output path guard.
        other=Store(self.parent/'other');other.create('Other');outside=self.parent/'outside';outside.mkdir();(other.root/'queue').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):queue_list(other)
    def test_empty_list_no_queue_files(self):
        result=queue_list(self.store);self.assertEqual(result['total_items'],0);self.assertEqual(result['queue_revision'],0)
        self.assertFalse((self.store.root/'queue').exists())
    def test_cli_add_update_list(self):
        r=subprocess.run([sys.executable,'-m','app','queue-add',str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2'],cwd=fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);a=json.loads(r.stdout)
        r=subprocess.run([sys.executable,'-m','app','queue-update',str(self.store.root),'--item-id',a['items'][0]['id'],'--expected-token',a['queue_token'],'--status','ACTIVE'],cwd=fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr)
        r=subprocess.run([sys.executable,'-m','app','queue-list',str(self.store.root),'--status','ACTIVE'],cwd=fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);self.assertEqual(json.loads(r.stdout)['returned'],1)
