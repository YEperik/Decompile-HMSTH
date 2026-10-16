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
from app.application.relocation_preview import calculate, create_preview, _inspect_file
from app.application.workspaces import add_input, rename
from app.infrastructure.persistence.store import Store
from app.domain.workspace.model import ValidationError, ConflictError, PathError
from app.domain.binary.elf import UnsupportedELF, Cancelled
from tests.hi_lo_fixture import make_hi_lo
from tests.elf_fixture import edit

ROOT = Path(__file__).resolve().parents[2]


class ArithmeticTests(unittest.TestCase):
    def test_known_vectors_and_reconstructed_value(self):
        # Independent expected resulting values and immediate fields.
        vectors = [(0,0,0,0,0,0), (0,0,0x7fff,0x7fff,0,0x7fff),
                   (0,0,0x8000,0x8000,1,0x8000),
                   (1,0x8000,0x12348000,0x12350000,0x1235,0),
                   (0,0xffff,0,0xffffffff,0,0xffff),
                   (0xffff,0x7fff,0x10000,0x7fff,0,0x7fff)]
        for hi,lo,s,value,expected_hi,expected_lo in vectors:
            with self.subTest(hi=hi,lo=lo,s=s):
                result=calculate(0x3c080000|hi,0x25080000|lo,s)
                a,b=result['preview_words']
                self.assertEqual(result['value32'],value)
                self.assertEqual((a&0xffff,b&0xffff),(expected_hi,expected_lo))
                signed=(b&0xffff) if b&0x8000==0 else (b&0xffff)-65536
                self.assertEqual((((a&0xffff)*65536)+signed)&0xffffffff,value)
                self.assertEqual((a>>16,b>>16),(0x3c08,0x2508))

    def test_invalid_operands(self):
        for operand in (-1,2**32,True,'0'):
            with self.assertRaises(ValidationError):calculate(0x3c080000,0x25080000,operand)

    def test_unsupported_instruction_patterns(self):
        for hi,lo in [(0x3c000000,0x24000000),(0x3c280000,0x25080000),
                      (0x3c080000,0x35080000),(0x3c080000,0x25280000),
                      (0x3c080000,0x25090000),(0,0x25080000)]:
            with self.assertRaises(UnsupportedELF):calculate(hi,lo,0)


class PreviewTests(unittest.TestCase):
    def setUp(self):
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.parent=Path(self.temp.name);self.path=self.parent/'pair.o'
        self.store=Store(self.parent/'workspace');self.store.create('Preview')
        self.register(make_hi_lo())

    def register(self,raw):
        self.path.write_bytes(raw);add_input(self.store,str(self.path))
        self.iid=self.store.load().data['inputs'][-1]['id']

    def save(self,**kwargs):
        return create_preview(self.store,self.iid,'3:2','5:0',0x12348000,**kwargs)

    def reject(self,raw):
        # Each modified fixture gets its own registered file identity.
        self.path=self.parent/(hashlib.sha256(raw).hexdigest()+'.o');self.register(raw)
        with self.assertRaises((UnsupportedELF,ValidationError)):self.save()
        self.assertFalse((self.store.root/'previews').exists())

    def test_repeatable_report_and_unchanged_input(self):
        before=self.path.read_bytes();a=self.save();b=self.save()
        self.assertEqual(a['report'],b['report']);self.assertNotEqual(a['receipt'],b['receipt'])
        self.assertEqual(before,self.path.read_bytes())
        r=a['report'];self.assertFalse(r['input_modified']);self.assertFalse(r['relocations_applied'])
        self.assertFalse(r['symbol_value_verified']);self.assertEqual(r['preview']['calculation']['value32'],0x12350000)
        self.assertEqual(r['source_sha256'],hashlib.sha256(before).hexdigest())

    def test_corrupt_report_not_overwritten(self):
        path=Path(self.save()['report_file']);path.write_text('corrupt')
        with self.assertRaises(ConflictError):self.save()
        self.assertEqual(path.read_text(),'corrupt')

    def test_exec_and_dyn_refused(self):
        for etype in (2,3):self.reject(edit(make_hi_lo(),16,etype,'H'))

    def test_rela_refused(self):self.reject(make_hi_lo(True))

    def test_missing_or_different_symbol_pair(self):
        for info in ((4<<8)|5,(3<<8)|6):self.reject(edit(make_hi_lo(),0x50c,info))

    def test_nonadjacent_unaligned_or_partial_fields(self):
        for offset in (8,10,14,16):self.reject(edit(make_hi_lo(),0x508,offset))

    def test_stacked_relocation_refused(self):self.reject(edit(make_hi_lo(),0x510,8))

    def test_local_and_special_symbol_attributes_refused(self):
        for info in (0x13,0x16):self.reject(edit(make_hi_lo(),0x24c,info,'B'))
        self.reject(edit(make_hi_lo(),0x24d,2,'B'))
        self.reject(edit(edit(make_hi_lo(),0x504,(1<<8)|5),0x50c,(1<<8)|6))

    def test_gp_disp_refused(self):
        raw=bytearray(make_hi_lo());name_offset=struct.unpack_from('<I',raw,0x240)[0]
        raw[0x180+name_offset:0x180+name_offset+9]=b'_gp_disp\0'
        self.reject(bytes(raw))

    def test_changed_registered_input_refused(self):
        self.path.write_bytes(edit(make_hi_lo(),0x108,0x3c080002))
        with self.assertRaises(ConflictError):self.save()
        self.assertFalse((self.store.root/'previews').exists())

    def test_cancel(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.save(cancel=event)
        self.assertFalse((self.store.root/'previews').exists())

    def test_manifest_conflict(self):
        def mutate(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.relocation_preview._inspect_file',side_effect=mutate):
            with self.assertRaises(ConflictError):self.save()
        self.assertFalse((self.store.root/'previews').exists())

    def test_output_symlink_refused(self):
        outside=self.parent/'outside';outside.mkdir()
        (self.store.root/'previews').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.save()
        self.assertEqual(list(outside.iterdir()),[])

    def test_invalid_identifiers_and_values(self):
        for fid,hid,value in [('../x','5:0',0),('3:02','5:0',0),('3:2','5:00',0),('3:2','5:0',-1),('3:2','5:0',True)]:
            with self.assertRaises(ValidationError):create_preview(self.store,self.iid,fid,hid,value)

    def test_cli_success_and_invalid_value(self):
        args=[sys.executable,'-m','app','preview-hi-lo',str(self.store.root),'--input-id',self.iid,'--function-id','3:2','--hi-reloc-id','5:0','--symbol-value']
        good=subprocess.run(args+['0x12348000'],cwd=ROOT,capture_output=True,text=True)
        self.assertEqual(good.returncode,0,good.stderr)
        self.assertFalse(json.loads(good.stdout)['report']['input_modified'])
        bad=subprocess.run(args+['-1'],cwd=ROOT,capture_output=True,text=True)
        self.assertEqual(bad.returncode,2)
