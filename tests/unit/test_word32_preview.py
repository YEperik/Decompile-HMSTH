import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch
from app.application.word32_preview import calculate, create_preview, _inspect_file
from app.application.workspaces import add_input, rename
from app.infrastructure.persistence.store import Store
from app.domain.workspace.model import ValidationError, ConflictError, PathError
from app.domain.binary.elf import UnsupportedELF, Cancelled
from tests.word32_fixture import make_word32
from tests.elf_fixture import edit

ROOT=Path(__file__).resolve().parents[2]


class Word32ArithmeticTests(unittest.TestCase):
    def test_boundary_vectors_and_byte_encoding(self):
        for a,s,v,wrapped in [(0,0,0,False),(0xffffffff,0,0xffffffff,False),
                              (0x7fffffff,1,0x80000000,False),
                              (0xffffffff,1,0,True),(0xfffffff0,0x30,0x20,True),
                              (0xffffffff,0xffffffff,0xfffffffe,True)]:
            with self.subTest(a=a,s=s):
                r=calculate(a,s)
                self.assertEqual(r['value32'],v)
                self.assertEqual(r['wrapped_to_32_bits'],wrapped)
                self.assertEqual(int.from_bytes(bytes.fromhex(r['preview_bytes_le']),'little'),v)
                self.assertEqual(int.from_bytes(bytes.fromhex(r['before_bytes_le']),'little'),a)
        self.assertEqual(calculate(0x12345678,0)['preview_bytes_le'],'78563412')

    def test_invalid_operands(self):
        for bad in (-1,2**32,True,1.0,'3',None):
            for args in ((bad,0),(0,bad)):
                with self.assertRaises(ValidationError):calculate(*args)


class Word32PreviewTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.path=self.parent/'word.o'
        self.store=Store(self.parent/'workspace');self.store.create('Word32')
        self.register(make_word32())

    def register(self,raw):
        self.path.write_bytes(raw);add_input(self.store,str(self.path))
        self.iid=self.store.load().data['inputs'][-1]['id']

    def save(self,**kwargs):
        return create_preview(self.store,self.iid,'3:2','5:0',0x30,**kwargs)

    def reject(self,raw):
        self.path=self.parent/(hashlib.sha256(raw).hexdigest()+'.o');self.register(raw)
        with self.assertRaises((UnsupportedELF,ValidationError)):self.save()
        self.assertFalse((self.store.root/'previews').exists())

    def test_immutable_report_and_input_unchanged(self):
        before=self.path.read_bytes();first=self.save();second=self.save()
        self.assertEqual(first['report'],second['report'])
        self.assertNotEqual(first['receipt'],second['receipt'])
        self.assertEqual(before,self.path.read_bytes())
        r=first['report'];self.assertEqual(r['preview']['calculation']['value32'],0x20)
        self.assertFalse(r['input_modified']);self.assertFalse(r['relocations_applied'])
        self.assertFalse(r['symbol_value_verified'])
        self.assertEqual(r['source_sha256'],hashlib.sha256(before).hexdigest())

    def test_corrupt_report_not_overwritten(self):
        path=Path(self.save()['report_file']);path.write_text('corrupt')
        with self.assertRaises(ConflictError):self.save()
        self.assertEqual(path.read_text(),'corrupt')

    def test_exec_dyn_rela_refused(self):
        for etype in (2,3):self.reject(edit(make_word32(),16,etype,'H'))
        self.reject(make_word32(True))

    def test_wrong_type_and_outside_range(self):
        self.reject(edit(make_word32(),0x504,(4<<8)|5))
        self.reject(edit(make_word32(),0x500,0))

    def test_unaligned_or_partial_word(self):
        for off in (9,10,14):self.reject(edit(make_word32(),0x500,off))
        # Shorten function to 2 bytes while retaining aligned relocation start.
        self.reject(edit(make_word32(),0x228,2))

    def test_additional_relocation_refused(self):
        for type_number in (2,5,123):self.reject(edit(make_word32(),0x50c,(4<<8)|type_number))

    def test_special_symbols_refused(self):
        for info in (0x13,0x16):self.reject(edit(make_word32(),0x24c,info,'B'))
        self.reject(edit(make_word32(),0x24d,2,'B'))
        self.reject(edit(make_word32(),0x504,(1<<8)|2))
        self.reject(edit(make_word32(),0x504,(7<<8)|2))

    def test_undefined_symbol_is_explicit_assumption(self):
        self.path=self.parent/'undefined.o';self.register(edit(make_word32(),0x504,(3<<8)|2))
        r=self.save()['report']
        self.assertEqual(r['preview']['referenced_symbol']['definition'],'UNDEFINED')
        self.assertFalse(r['symbol_value_verified'])

    def test_changed_input_refused(self):
        self.path.write_bytes(edit(make_word32(),0x108,1))
        with self.assertRaises(ConflictError):self.save()
        self.assertFalse((self.store.root/'previews').exists())

    def test_cancel(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.save(cancel=event)
        self.assertFalse((self.store.root/'previews').exists())

    def test_manifest_conflict(self):
        def mutate(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.word32_preview._inspect_file',side_effect=mutate):
            with self.assertRaises(ConflictError):self.save()
        self.assertFalse((self.store.root/'previews').exists())

    def test_output_symlink(self):
        outside=self.parent/'outside';outside.mkdir()
        (self.store.root/'previews').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.save()
        self.assertEqual(list(outside.iterdir()),[])

    def test_ids_and_values(self):
        for fid,rid,s in [('../x','5:0',0),('3:02','5:0',0),('3:2','5:00',0),('3:2','5:0',2**32),('3:2','5:0',True)]:
            with self.assertRaises(ValidationError):create_preview(self.store,self.iid,fid,rid,s)
        with self.assertRaises(ValidationError):create_preview(self.store,'missing','3:2','5:0',0)

    def test_cli(self):
        args=[sys.executable,'-m','app','preview-word32',str(self.store.root),'--input-id',self.iid,'--function-id','3:2','--reloc-id','5:0','--symbol-value']
        result=subprocess.run(args+['0x30'],cwd=ROOT,capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(json.loads(result.stdout)['report']['preview']['calculation']['preview_bytes_le'],'20000000')
        for value in ('-1','0x100000000','invalid'):
            result=subprocess.run(args+[value],cwd=ROOT,capture_output=True,text=True)
            self.assertEqual(result.returncode,2)
