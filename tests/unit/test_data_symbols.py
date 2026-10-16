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
from tests.symbol_fixture import make_symbols
from app.application.data_symbols import data_bundle,list_data_symbols,_inspect_file
from app.application.workspaces import add_input,rename
from app.domain.binary.elf import Cancelled
from app.domain.workspace.model import ValidationError,ConflictError,PathError
from app.infrastructure.persistence.store import Store

class DataTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.store=Store(self.parent/'workspace');self.store.create('Data')
        self.register(make_symbols())
    def register(self,raw):
        self.raw=raw;self.path=self.parent/(hashlib.sha256(raw).hexdigest()+'.elf');self.path.write_bytes(raw)
        add_input(self.store,str(self.path));self.iid=self.store.load().data['inputs'][-1]['id']
    def run_data(self,sid='3:4',**kw):return data_bundle(self.store,self.iid,sid,**kw)
    def changed(self,offset,value,fmt='<I'):
        raw=bytearray(make_symbols());struct.pack_into(fmt,raw,offset,value);self.register(bytes(raw))
    def test_exact_bytes_verify_and_idempotent(self):
        a=self.run_data();folder=Path(a['bundle_dir']);self.assertEqual((folder/'bytes.bin').read_bytes(),self.raw[0x118:0x11c])
        before={p.name:p.read_bytes() for p in folder.iterdir()};self.assertEqual(self.run_data(),a)
        self.assertEqual(self.run_data(verify=True)['status'],'VERIFIED_SOURCE_RANGE')
        self.assertEqual(before,{p.name:p.read_bytes() for p in folder.iterdir()});self.assertEqual(self.raw,self.path.read_bytes())
    def test_rel_and_dyn_address_mapping(self):
        for typ in (1,3):
            self.register(make_symbols(typ));a=self.run_data();self.assertEqual(a['metadata']['range']['file_offset'],0x118)
            self.assertEqual(a['metadata']['elf_type'],{1:'REL',3:'DYN'}[typ])
    def test_list_pagination_and_common(self):
        a=list_data_symbols(self.path,limit=1);self.assertEqual(a['total_objects'],2);self.assertEqual(a['next_offset'],1)
        self.assertTrue(a['objects'][0]['extractable']);b=list_data_symbols(self.path,offset=1)
        self.assertFalse(b['objects'][0]['extractable']);self.assertEqual(b['objects'][0]['definition'],'COMMON')
        for kw in ({'limit':0},{'limit':True},{'offset':-1}):
            with self.assertRaises(ValidationError):list_data_symbols(self.path,**kw)
    def test_nobits_metadata_only(self):
        self.changed(0x400+40+4,8);a=self.run_data()
        self.assertEqual(a['storage'],'NOBITS_NO_FILE_PAYLOAD');self.assertEqual(a['payload_size'],0)
        self.assertIsNone(a['metadata']['payload_sha256']);self.assertEqual([p.name for p in Path(a['bundle_dir']).iterdir()],['object.json'])
        self.run_data(verify=True)
    def test_invalid_and_wrong_type(self):
        for sid in ('3:2','3:7','3:999','../x','03:4',None):
            with self.assertRaises(ValidationError):self.run_data(sid)
        with self.assertRaises(ValidationError):data_bundle(self.store,'missing','3:4')
    def test_zero_size_overflow_and_special_flags(self):
        for off,value,fmt in ((0x200+4*16+8,0,'<I'),(0x200+4*16+4,0xffffffff,'<I'),(0x200+4*16+13,128,'<B'),(0x400+40+8,0x406,'<I'),(0x400+40+8,0x806,'<I')):
            self.changed(off,value,fmt)
            with self.assertRaises(ValidationError):self.run_data()
    def test_corruption_and_missing_verify(self):
        with self.assertRaises(FileNotFoundError):self.run_data(verify=True)
        a=self.run_data();p=Path(a['bundle_dir'])/'bytes.bin';p.write_bytes(b'bad')
        for verify in (True,False):
            with self.assertRaises(ConflictError):self.run_data(verify=verify)
        self.assertEqual(p.read_bytes(),b'bad')
    def test_partial_write_retry(self):
        original=self.store.atomic
        def fail(path,data):
            if path.endswith('object.json'):raise OSError('injected')
            original(path,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.run_data()
        self.run_data();self.run_data(verify=True)
    def test_changed_source_and_manifest(self):
        self.path.write_bytes(self.raw+b'changed')
        with self.assertRaises(ConflictError):self.run_data()
        self.path.write_bytes(self.raw)
        def change(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.data_symbols._inspect_file',side_effect=change):
            with self.assertRaises(ConflictError):self.run_data()
        self.assertFalse((self.store.root/'data').exists())
    def test_cancel_symlink_and_unexpected(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.run_data(cancel=event)
        a=self.run_data();folder=Path(a['bundle_dir']);p=folder/'bytes.bin';p.unlink();p.symlink_to(self.path)
        with self.assertRaises(PathError):self.run_data()
        p.unlink();p.write_bytes(self.raw[0x118:0x11c]);(folder/'extra').write_bytes(b'x')
        with self.assertRaises(ConflictError):self.run_data()
    def test_cli(self):
        for args in (['list-data-symbols',str(self.path)],*[ [command,str(self.store.root),'--input-id',self.iid,'--symbol-id','3:4'] for command in ('extract-data','verify-data')]):
            p=subprocess.run([sys.executable,'-m','app',*args],capture_output=True,text=True)
            self.assertEqual(p.returncode,0,p.stderr);json.loads(p.stdout)
