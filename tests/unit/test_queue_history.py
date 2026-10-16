import hashlib
import json
import subprocess
import sys
import unittest
from unittest.mock import patch
from tests.unit import test_queue as fixture
from app.application.queue import mutate,queue_list
from app.application.queue_history import history_list,history_show
from app.domain.workspace.model import ValidationError,ConflictError

class HistoryTests(unittest.TestCase):
    setUp=fixture.QueueTests.setUp
    def seed(self):
        a=mutate(self.store,'add',input_id=self.iid,symbol_id='3:2',note='First')
        b=mutate(self.store,'update',item_id=a['items'][0]['id'],expected_token=a['queue_token'],status='ACTIVE',priority=80)
        mutate(self.store,'update',item_id=a['items'][0]['id'],expected_token=b['queue_token'],status='PAUSED',note='Later')
        return a,b
    def files(self):return {str(p.relative_to(self.store.root)):p.read_bytes() for p in self.store.root.rglob('*') if p.is_file()}
    def test_empty_no_creation(self):
        self.assertEqual(history_list(self.store)['returned'],0)
        self.assertFalse((self.store.root/'queue').exists())
    def test_order_pagination_and_full_snapshot(self):
        a,b=self.seed();before=self.files();page=history_list(self.store,limit=2)
        self.assertEqual([x['revision'] for x in page['snapshots']],[2,1])
        self.assertEqual(page['next_before_revision'],1)
        self.assertEqual([x['revision'] for x in history_list(self.store,1)['snapshots']],[0])
        self.assertEqual(history_show(self.store,1)['snapshot'],a)
        self.assertEqual(history_show(self.store,2)['snapshot'],b)
        self.assertTrue(page['archive_revisions_complete']);self.assertFalse(page['history_authenticity_proven'])
        self.assertEqual(self.files(),before)
    def test_missing_source_still_readable(self):
        self.seed();self.path.unlink();self.assertEqual(history_show(self.store,2)['snapshot']['counts']['ACTIVE'],1)
    def test_missing_revision_reported(self):
        a,b=self.seed();next((self.store.root/'queue/history').glob('000001-*')).unlink()
        self.assertFalse(history_list(self.store)['archive_revisions_complete'])
        with self.assertRaises(ValidationError):history_show(self.store,1)
    def test_corrupt_payload_hash(self):
        self.seed();p=next((self.store.root/'queue/history').glob('000002-*'));p.write_bytes(p.read_bytes()+b' ')
        with self.assertRaises(ConflictError):history_list(self.store)
    def test_schema_and_revision_mismatch(self):
        self.seed();p=next((self.store.root/'queue/history').glob('000002-*'));data=json.loads(p.read_bytes());data['revision']=1
        raw=json.dumps(data).encode();p.unlink();q=p.with_name('000002-'+hashlib.sha256(raw).hexdigest()+'.json');q.write_bytes(raw)
        with self.assertRaises(ConflictError):history_show(self.store,2)
        q.write_text('{}')
        with self.assertRaises(ValidationError):history_show(self.store,2)
    def test_duplicate_and_future_rejected(self):
        self.seed();folder=self.store.root/'queue/history';p=next(folder.glob('000001-*'));other=folder/('000001-'+'0'*64+'.json');other.write_bytes(p.read_bytes())
        with self.assertRaises(ConflictError):history_list(self.store)
        other.unlink();other=folder/('000004-'+'0'*64+'.json');other.write_bytes(p.read_bytes())
        with self.assertRaises(ConflictError):history_list(self.store)
    def test_failed_commit_checkpoint_excluded(self):
        a,b=self.seed();current=queue_list(self.store);original=self.store.atomic
        def fail(path,data):
            if path=='queue/state.json':raise OSError('injected')
            return original(path,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):mutate(self.store,'update',item_id=a['items'][0]['id'],expected_token=current['queue_token'],note='failed')
        self.assertEqual(history_list(self.store)['total_archived_snapshots'],3)
        self.assertEqual(queue_list(self.store),current)
    def test_invalid_options_and_missing(self):
        for value in (-1,True,'2',1000001):
            with self.assertRaises(ValidationError):history_show(self.store,value)
        for value in (0,51,True,'2'):
            with self.assertRaises(ValidationError):history_list(self.store,limit=value)
        with self.assertRaises(ValidationError):history_show(self.store,0)
    def test_symlink_and_scan_limit(self):
        self.seed();p=next((self.store.root/'queue/history').glob('000002-*'));raw=p.read_bytes();p.unlink();external=self.parent/'outside-history';external.write_bytes(raw);p.symlink_to(external)
        with self.assertRaises(ValidationError):history_list(self.store)
        p.unlink();p.write_bytes(raw)
        with patch('app.application.queue_history.MAX_ENTRIES',1):
            with self.assertRaises(ValidationError):history_list(self.store)
    def test_current_corruption_not_hidden(self):
        self.seed();(self.store.root/'queue/state.json').write_text('{}')
        with self.assertRaises(ValidationError):history_list(self.store)
    def test_cli(self):
        self.seed()
        for args in (['queue-history',str(self.store.root),'--limit','1'],['show-queue-history',str(self.store.root),'--revision','2']):
            p=subprocess.run([sys.executable,'-m','app',*args],capture_output=True,text=True)
            self.assertEqual(p.returncode,0,p.stderr);self.assertTrue(json.loads(p.stdout)['read_only'])
