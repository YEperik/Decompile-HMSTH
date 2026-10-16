import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch
from tests.elf_fixture import make_elf,edit
from app.application.sections import section_bundle,MAX_MANIFEST,_inspect_file
from app.application.workspaces import add_input,rename
from app.domain.binary.elf import Cancelled,InvalidELF
from app.domain.workspace.model import ValidationError,ConflictError,PathError
from app.infrastructure.persistence.store import Store

class SectionTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.path=self.parent/'input.elf'
        self.store=Store(self.parent/'workspace');self.store.create('Sections')
        self.register(make_elf())
    def register(self,raw):
        self.raw=raw;self.path=self.parent/f'input-{hashlib.sha256(raw).hexdigest()}.elf';self.path.write_bytes(raw)
        add_input(self.store,str(self.path));self.iid=self.store.load().data['inputs'][-1]['id']
    def run_section(self,index=1,**kw):return section_bundle(self.store,self.iid,index,**kw)
    def test_export_verify_exact_and_repeat(self):
        a=self.run_section();m=a['metadata'];folder=Path(a['bundle_dir'])
        payload=b''.join((folder/x['file']).read_bytes() for x in m['chunks'])
        self.assertEqual(payload,self.raw[m['section']['offset']:m['section']['offset']+m['section']['size']])
        self.assertEqual(hashlib.sha256(payload).hexdigest(),m['payload_sha256'])
        before={p.name:p.read_bytes() for p in folder.iterdir()}
        self.assertEqual(self.run_section(),a);self.assertEqual(self.run_section(verify=True)['status'],'VERIFIED_SOURCE_BYTES')
        self.assertEqual(before,{p.name:p.read_bytes() for p in folder.iterdir()});self.assertEqual(self.path.read_bytes(),self.raw)
    def test_nobits_without_fabricated_bytes(self):
        self.register(edit(make_elf(),0x140+80+16,0xfffffff0))
        a=self.run_section(2);m=a['metadata']
        self.assertEqual(m['storage'],'NOBITS_NO_FILE_PAYLOAD');self.assertEqual(m['payload_size'],0);self.assertIsNone(m['payload_sha256'])
        self.assertEqual(m['chunks'],[]);self.assertGreater(m['section']['size'],0)
        self.assertEqual([p.name for p in Path(a['bundle_dir']).iterdir()],['section.json'])
        self.run_section(2,verify=True)
    def test_large_section_chunking(self):
        raw=make_elf();payload=bytes(range(256))*(MAX_MANIFEST//256+3)
        raw=edit(edit(raw,0x140+40+16,len(raw)),0x140+40+20,len(payload))+payload;self.register(raw)
        a=self.run_section();folder=Path(a['bundle_dir']);chunks=a['metadata']['chunks']
        self.assertEqual(len(chunks),2);self.assertEqual(chunks[1]['section_offset'],MAX_MANIFEST)
        self.assertEqual(b''.join((folder/x['file']).read_bytes() for x in chunks),payload);self.run_section(verify=True)
    def test_empty_file_backed(self):
        self.register(edit(make_elf(),0x140+40+20,0));m=self.run_section()['metadata']
        self.assertEqual(m['storage'],'FILE_BYTES');self.assertEqual(m['payload_sha256'],hashlib.sha256(b'').hexdigest());self.assertEqual(m['chunks'],[])
    def test_invalid_selection_and_limit(self):
        for value in (0,-1,True,'1',512,10):
            with self.assertRaises(ValidationError):self.run_section(value)
        with patch('app.application.sections.MAX_SECTION',1):
            with self.assertRaises(ValidationError):self.run_section()
        with self.assertRaises(ValidationError):section_bundle(self.store,'missing',1)
        self.assertFalse((self.store.root/'sections').exists())
    def test_changed_source_rejected(self):
        self.path.write_bytes(self.raw+b'changed')
        with self.assertRaises(ConflictError):self.run_section()
        self.assertFalse((self.store.root/'sections').exists())
    def test_bad_bounds_rejected(self):
        self.register(edit(make_elf(),0x140+40+16,0xfffffff0))
        with self.assertRaises(InvalidELF):self.run_section()
    def test_corrupt_bundle_not_overwritten(self):
        a=self.run_section();p=Path(a['bundle_dir'])/'chunk-0000.bin';p.write_bytes(b'bad')
        for verify in (False,True):
            with self.assertRaises(ConflictError):self.run_section(verify=verify)
        self.assertEqual(p.read_bytes(),b'bad')
    def test_missing_verify_and_partial_retry(self):
        with self.assertRaises(FileNotFoundError):self.run_section(verify=True)
        original=self.store.atomic
        def fail(path,data):
            if path.endswith('section.json'):raise OSError('injected')
            original(path,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.run_section()
        self.assertFalse(list((self.store.root/'sections').rglob('section.json')))
        self.run_section();self.run_section(verify=True)
    def test_cancel_and_manifest_conflict(self):
        token=threading.Event();token.set()
        with self.assertRaises(Cancelled):self.run_section(cancel=token)
        def change(*args):
            result=_inspect_file(*args);rename(self.store,'changed');return result
        with patch('app.application.sections._inspect_file',side_effect=change):
            with self.assertRaises(ConflictError):self.run_section()
        self.assertFalse((self.store.root/'sections').exists())
    def test_symlink_and_unexpected_files(self):
        a=self.run_section();folder=Path(a['bundle_dir']);p=folder/'chunk-0000.bin';raw=p.read_bytes();p.unlink();outside=self.parent/'outside';outside.write_bytes(raw);p.symlink_to(outside)
        with self.assertRaises(PathError):self.run_section()
        p.unlink();p.write_bytes(raw);(folder/'extra.bin').write_bytes(b'x')
        with self.assertRaises(ConflictError):self.run_section(verify=True)
    def test_cli(self):
        for command in ('extract-section','verify-section'):
            p=subprocess.run([sys.executable,'-m','app',command,str(self.store.root),'--input-id',self.iid,'--section-index','1'],capture_output=True,text=True)
            self.assertEqual(p.returncode,0,p.stderr);self.assertFalse(json.loads(p.stdout)['metadata']['executed'])
