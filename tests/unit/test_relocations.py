import io
import json
from pathlib import Path
import shutil
import struct
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch

from app.domain.binary.relocations import function_refs
from app.domain.binary.elf import InvalidELF,UnsupportedELF,Cancelled
from app.application.relocations import create_references
from app.application.workspaces import add_input,rename
from app.infrastructure.persistence.store import Store
from app.domain.workspace.model import ConflictError,ValidationError,PathError
from tests.relocation_fixture import make_relocations
from tests.symbol_fixture import make_symbols
from tests.elf_fixture import edit

ROOT=Path(__file__).resolve().parents[2]


class RelocationTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.path=self.parent/'reloc 日本.elf';self.path.write_bytes(make_relocations())
        self.store=Store(self.parent/'workspace');self.store.create('Relocs');add_input(self.store,str(self.path))
        self.iid=self.store.load().data['inputs'][0]['id']

    def parse(self,raw,sid='3:2'):return function_refs(io.BytesIO(raw),len(raw),sid)
    def save(self):return create_references(self.store,self.iid,'3:2')

    def test_rel_outgoing_incoming_and_unresolved_addends(self):
        report=self.parse(make_relocations())
        self.assertEqual(report['counts'],{'matches':3,'inside_range':2,'references_selected':1,'referenced_symbols':2})
        first=report['matches'][0]
        self.assertEqual(first['type_name'],'R_MIPS_26');self.assertEqual(first['symbol_id'],'3:3')
        self.assertIsNone(first['addend']);self.assertEqual(first['location_file_offset'],0x108)
        self.assertEqual(report['referenced_symbols'][0]['definition'],'UNDEFINED')
        self.assertFalse(report['relocations_applied'])

    def test_rela_signed_explicit_addend(self):
        report=self.parse(make_relocations(rela=True))
        self.assertEqual(report['matches'][0]['addend'],-4)
        self.assertEqual(report['matches'][0]['addend_source'],'EXPLICIT')

    def test_relocatable_section_offset_and_dyn_virtual_address(self):
        self.assertEqual(self.parse(make_relocations(1))['matches'][0]['r_offset'],8)
        self.assertEqual(self.parse(make_relocations(3))['matches'][0]['r_offset'],0x100008)

    def test_unknown_type_preserved_without_semantic_claim(self):
        report=self.parse(edit(make_relocations(),0x504,(3<<8)|255))
        self.assertEqual(report['matches'][0]['type'],255)
        self.assertEqual(report['matches'][0]['type_name'],'UNKNOWN')
        self.assertFalse(report['matches'][0]['semantics_verified'])

    def test_none_and_null_symbol_do_not_create_dependencies(self):
        report=self.parse(edit(make_relocations(),0x504,0))
        self.assertEqual(report['counts']['referenced_symbols'],1)

    def test_no_relocations_not_proof_of_no_dependencies(self):
        report=self.parse(make_symbols())
        self.assertEqual(report['total_relocations_scanned'],0)
        self.assertEqual(report['matches'],[]);self.assertTrue(report['warnings'])

    def test_malformed_link_size_index_location_and_truncation(self):
        raw=make_relocations();shoff=struct.unpack_from('<I',raw,32)[0];tab=shoff+5*40
        for sample in (edit(raw,tab+24,1),edit(raw,tab+36,16),edit(raw,0x504,(999<<8)|4),
                       edit(raw,0x500,0xfffffffc),raw[:-1]):
            with self.assertRaises(InvalidELF):self.parse(sample)

    def test_limits_and_unknown_function_size(self):
        with patch('app.domain.binary.relocations.MAX_RELOCATIONS',2):
            with self.assertRaises(UnsupportedELF):self.parse(make_relocations())
        with patch('app.domain.binary.relocations.MAX_MATCHES',2):
            with self.assertRaises(UnsupportedELF):self.parse(make_relocations())
        with self.assertRaises(UnsupportedELF):self.parse(make_relocations(),'3:5')

    def test_report_repeatable_immutable_and_source_unchanged(self):
        original=self.path.read_bytes();first=self.save();second=self.save()
        self.assertEqual(first['report'],second['report']);self.assertNotEqual(first['receipt'],second['receipt'])
        self.assertEqual(self.path.read_bytes(),original)
        Path(first['report_file']).write_text('corrupt')
        with self.assertRaises(ConflictError):self.save()

    def test_input_change_and_invalid_ids_rejected(self):
        for sid in ('../x','3:02'):
            with self.assertRaises(ValidationError):create_references(self.store,self.iid,sid)
        self.path.write_bytes(make_relocations(rela=True))
        with self.assertRaises(ConflictError):self.save()
        self.assertFalse((self.store.root/'references').exists())

    def test_cancel_and_manifest_conflict(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):create_references(self.store,self.iid,'3:2',event)
        from app.application.relocations import _inspect_file
        def mutate(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.relocations._inspect_file',side_effect=mutate):
            with self.assertRaises(ConflictError):self.save()

    def test_symlink_output_refused(self):
        outside=self.parent/'outside';outside.mkdir()
        try:(self.store.root/'references').symlink_to(outside,target_is_directory=True)
        except OSError:self.skipTest('Symlink privilege unavailable')
        with self.assertRaises(PathError):self.save()
        self.assertEqual(list(outside.iterdir()),[])

    def test_cli_report_and_missing_arguments(self):
        result=subprocess.run([sys.executable,'-m','app','function-refs',str(self.store.root),
                               '--input-id',self.iid,'--symbol-id','3:2'],cwd=ROOT,capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(json.loads(result.stdout)['report']['references']['counts']['matches'],3)

    @unittest.skipUnless(shutil.which('readelf'),'readelf unavailable')
    def test_independent_readelf_raw_offset_info_comparison(self):
        p=subprocess.run([shutil.which('readelf'),'--wide','--relocs',str(self.path)],capture_output=True,text=True,check=True)
        rows=[]
        for line in p.stdout.splitlines():
            parts=line.split()
            if len(parts)>=3 and parts[2].startswith('R_MIPS_'):
                rows.append((int(parts[0],16),int(parts[1],16),parts[2]))
        report=self.parse(self.path.read_bytes())
        self.assertEqual(rows,[(x['r_offset'],x['r_info'],x['type_name']) for x in report['matches']])
