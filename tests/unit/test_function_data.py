import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch
from tests.relocation_fixture import make_relocations
from app.application.function_data import function_data,_inspect_file
from app.application.workspaces import add_input,rename
from app.domain.binary.elf import Cancelled
from app.domain.workspace.model import ValidationError,ConflictError,PathError
from app.infrastructure.persistence.store import Store

class FunctionDataTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.store=Store(self.parent/'workspace');self.store.create('Function data')
        self.register(make_relocations())
    def register(self,raw):
        self.raw=raw;self.path=self.parent/(hashlib.sha256(raw).hexdigest()+'.elf');self.path.write_bytes(raw)
        add_input(self.store,str(self.path));self.iid=self.store.load().data['inputs'][-1]['id']
    def run_bundle(self,**kw):return function_data(self.store,self.iid,'3:2',**kw)
    def report(self,result):return json.loads(Path(result['report_file']).read_bytes())
    def test_exact_function_and_data_verify_idempotent(self):
        a=self.run_bundle();folder=Path(a['bundle_dir']);r=self.report(a)
        self.assertEqual((folder/'function.bin').read_bytes(),self.raw[0x108:0x110])
        self.assertEqual((folder/'object-3-4.bin').read_bytes(),self.raw[0x118:0x11c])
        self.assertEqual(r['counts'],{'EXTRACTED':1,'NOBITS':0,'UNRESOLVED':0,'NOT_OBJECT':1})
        self.assertEqual(r['dependency_completeness'],'UNVERIFIED');self.assertFalse(r['recursive'])
        before={p.name:p.read_bytes() for p in folder.iterdir()}
        self.assertEqual(self.run_bundle(),a);self.run_bundle(verify=True)
        self.assertEqual(before,{p.name:p.read_bytes() for p in folder.iterdir()});self.assertEqual(self.raw,self.path.read_bytes())
    def test_rel_and_rela(self):
        for typ,rela in ((1,False),(1,True),(3,True)):
            self.register(make_relocations(typ,rela));a=self.run_bundle();self.run_bundle(verify=True)
            self.assertEqual(a['counts']['EXTRACTED'],1)
    def test_duplicate_references_copy_once(self):
        raw=bytearray(make_relocations());struct.pack_into('<I',raw,0x504,(4<<8)|2);self.register(bytes(raw))
        r=self.report(self.run_bundle());self.assertEqual(r['counts']['EXTRACTED'],1)
        self.assertEqual(len(r['references'][0]['relocation_ids']),2)
    def test_unresolved_size_is_reported_not_guessed(self):
        raw=bytearray(make_relocations());struct.pack_into('<I',raw,0x200+4*16+8,0);self.register(bytes(raw))
        a=self.run_bundle();self.assertEqual(a['counts']['UNRESOLVED'],1)
        self.assertFalse((Path(a['bundle_dir'])/'object-3-4.bin').exists());self.run_bundle(verify=True)
    def test_nobits_metadata_only(self):
        raw=bytearray(make_relocations());raw.extend(struct.pack('<IIIIIIIIII',0,8,3,0x200000,0,32,0,0,4,0))
        struct.pack_into('<H',raw,48,7);struct.pack_into('<H',raw,0x200+4*16+14,6);struct.pack_into('<I',raw,0x200+4*16+4,0x200000)
        self.register(bytes(raw));a=self.run_bundle();self.assertEqual(a['counts']['NOBITS'],1)
        self.assertFalse((Path(a['bundle_dir'])/'object-3-4.bin').exists());self.run_bundle(verify=True)
    def test_no_outgoing_objects_does_not_claim_complete(self):
        a=function_data(self.store,self.iid,'3:1');self.assertEqual(a['counts']['EXTRACTED'],0)
        self.assertEqual(a['dependency_completeness'],'UNVERIFIED')
    def test_limits_cancel_and_selection(self):
        for target,value in (('MAX_OBJECTS',0),('MAX_PAYLOAD',8)):
            with patch('app.application.function_data.'+target,value):
                with self.assertRaises(ValidationError):self.run_bundle()
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.run_bundle(cancel=event)
        for sid in ('../x',True,'03:2'):
            with self.assertRaises(ValidationError):function_data(self.store,self.iid,sid)
        self.assertFalse((self.store.root/'function-data').exists())
    def test_changed_source_and_manifest(self):
        self.path.write_bytes(self.raw+b'x')
        with self.assertRaises(ConflictError):self.run_bundle()
        self.path.write_bytes(self.raw)
        def change(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.function_data._inspect_file',side_effect=change):
            with self.assertRaises(ConflictError):self.run_bundle()
    def test_corruption_never_overwritten(self):
        a=self.run_bundle();p=Path(a['bundle_dir'])/'object-3-4.bin';p.write_bytes(b'bad')
        for verify in (False,True):
            with self.assertRaises(ConflictError):self.run_bundle(verify=verify)
        self.assertEqual(p.read_bytes(),b'bad')
    def test_partial_commit_retry_and_missing_verify(self):
        with self.assertRaises(FileNotFoundError):self.run_bundle(verify=True)
        original=self.store.atomic
        def fail(path,data):
            if path.endswith('report.json'):raise OSError('injected')
            original(path,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.run_bundle()
        self.assertFalse(list((self.store.root/'function-data').rglob('report.json')))
        self.run_bundle();self.run_bundle(verify=True)
    def test_symlink_and_unexpected_file(self):
        a=self.run_bundle();folder=Path(a['bundle_dir']);p=folder/'function.bin';p.unlink();p.symlink_to(self.path)
        with self.assertRaises(PathError):self.run_bundle()
        p.unlink();p.write_bytes(self.raw[0x108:0x110]);(folder/'extra').write_bytes(b'x')
        with self.assertRaises(ConflictError):self.run_bundle()
    def test_cli(self):
        for command in ('extract-function-data','verify-function-data'):
            p=subprocess.run([sys.executable,'-m','app',command,str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2'],capture_output=True,text=True)
            self.assertEqual(p.returncode,0,p.stderr);self.assertEqual(json.loads(p.stdout)['counts']['EXTRACTED'],1)
