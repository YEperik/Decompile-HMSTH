import json
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import unittest
from uuid import uuid4
from unittest.mock import patch
from app.application.drafts import drafts, prepare
from app.application.targets import target_bundle
from app.application.workspaces import add_input,rename
from app.infrastructure.persistence.store import Store
from app.domain.workspace.model import WorkspaceError,ConflictError,ValidationError,PathError
from app.domain.binary.elf import Cancelled
from tests.relocation_fixture import make_relocations
ROOT=Path(__file__).resolve().parents[2]

class DraftTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.elf=self.parent/'input.elf';self.raw=make_relocations();self.elf.write_bytes(self.raw)
        self.store=Store(self.parent/'ws');self.store.create('Drafts');add_input(self.store,str(self.elf))
        self.iid=self.store.load().data['inputs'][0]['id']
        self.bundle=Path(target_bundle(self.store,self.iid,'3:2')['bundle_dir'])
        self.source=self.parent/'candidate.c';self.source.write_bytes(b'int candidate(void) { return 1; }\r\n')
    def call(self,**kw):return drafts(self.store,self.iid,'3:2',**kw)
    def add(self,**kw):return self.call(source=str(self.source),**kw)
    def test_roundtrip_preserves_source_and_target(self):
        before=self.source.read_bytes();r=self.add();record=r['record']
        self.assertEqual(Path(r['source_file']).read_bytes(),before)
        self.assertEqual(record['status'],'DRAFT');self.assertFalse(record['built']);self.assertFalse(record['matched'])
        self.assertEqual(self.call(revision=record['revision'])['source_text'],before.decode())
        self.assertEqual(self.source.read_bytes(),before);self.assertEqual(self.elf.read_bytes(),self.raw)
        self.assertEqual(len(self.call()['revisions']),1)
    def test_revisions_parent_and_branch_no_overwrite(self):
        a=self.add();self.source.write_text('int candidate(void) { return 2; }\n')
        b=self.add(parent=a['record']['revision'],language='cpp');c=self.add(parent=a['record']['revision'])
        self.assertNotEqual(b['record']['revision'],c['record']['revision'])
        self.assertIn('return 1',Path(a['source_file']).read_text())
        self.assertEqual(b['record']['parent'],a['record']['revision'])
        self.assertEqual(len(self.call()['revisions']),3)
    def test_invalid_source(self):
        for content in (b'',b'  \n',b'\xff',b'x\x00',b'x'*(256*1024+1)):
            self.source.write_bytes(content)
            with self.assertRaises(ValidationError):self.add()
        self.assertFalse((self.store.root/'drafts').exists())
    def test_invalid_ids_and_parent(self):
        for rid in ('../x','BAD',str(uuid4())):
            with self.assertRaises(ValidationError):self.call(revision=rid)
            with self.assertRaises(ValidationError):self.add(parent=rid)
    def test_missing_and_corrupt_target(self):
        p=self.bundle/'bytes.bin';original=p.read_bytes();p.unlink()
        with self.assertRaises((WorkspaceError,OSError)):self.add()
        p.write_bytes(b'bad')
        with self.assertRaises(ConflictError):self.add()
        self.assertFalse((self.store.root/'drafts').exists());p.write_bytes(original)
    def test_corrupt_source_and_record(self):
        a=self.add();p=Path(a['source_file']);p.write_text('changed')
        with self.assertRaises(ConflictError):self.call()
        p.write_bytes(self.source.read_bytes());record=p.parent/'record.json';record.write_text('[]')
        with self.assertRaises(ValidationError):self.call()
    def test_record_path_traversal_refused(self):
        a=self.add();p=Path(a['source_file']).parent/'record.json';r=a['record'];r['source_file']='../../other.c';p.write_text(json.dumps(r))
        with self.assertRaises(ValidationError):self.call()
    def test_parent_cycle_refused(self):
        a=self.add();p=Path(a['source_file']).parent/'record.json';r=a['record'];r['parent']=r['revision'];p.write_text(json.dumps(r))
        with self.assertRaises(ValidationError):self.call()
    def test_changed_elf_and_manifest(self):
        self.elf.write_bytes(self.raw+b'x')
        with self.assertRaises(ConflictError):self.add()
        self.elf.write_bytes(self.raw)
        def mutate(*args):
            value=prepare(*args);rename(self.store,'Changed');return value
        with patch('app.application.drafts.prepare',side_effect=mutate):
            with self.assertRaises(ConflictError):self.add()
    def test_cancel(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.add(cancel=event)
        self.assertFalse((self.store.root/'drafts').exists())
    def test_symlinks(self):
        link=self.parent/'source-link.c';link.symlink_to(self.source)
        with self.assertRaises(WorkspaceError):self.call(source=str(link))
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'drafts').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.add()
        self.assertEqual(list(outside.iterdir()),[])
    def test_partial_publication_reported_and_old_revision_preserved(self):
        first=self.add();original=self.store.atomic
        def fail(relative,data):
            if relative.endswith('record.json'):raise OSError('simulated failure')
            return original(relative,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.add(parent=first['record']['revision'])
        h=self.call();self.assertEqual(len(h['revisions']),1);self.assertEqual(len(h['incomplete_revisions']),1)
        self.assertEqual(Path(first['source_file']).read_bytes(),self.source.read_bytes())
    def test_revision_limit_and_collision(self):
        first=self.add()
        with patch('app.application.drafts.MAX_REVISIONS',1):
            with self.assertRaises(ValidationError):self.add()
        with patch('app.application.drafts.uuid4',return_value=first['record']['revision']):
            with self.assertRaises(ConflictError):self.add()
    def test_cli_add_show_history(self):
        args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2']
        r=subprocess.run([sys.executable,'-m','app','draft-add']+args+['--source',str(self.source)],cwd=ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);rid=json.loads(r.stdout)['record']['revision']
        for command,extra in [('draft-show',['--revision',rid]),('draft-history',[])]:
            r=subprocess.run([sys.executable,'-m','app',command]+args+extra,cwd=ROOT,capture_output=True,text=True)
            self.assertEqual(r.returncode,0,r.stderr)
