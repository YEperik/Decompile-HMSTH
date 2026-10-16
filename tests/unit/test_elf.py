import hashlib
import io
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch

from app.application.baselines import create_baseline, inspect_file
from app.application.workspaces import add_input, rename
from app.domain.binary.elf import Cancelled, InvalidELF, UnsupportedELF, parse
from app.domain.workspace.model import ConflictError, PathError, ValidationError
from app.infrastructure.persistence.store import Store
from tests.elf_fixture import edit, make_elf


class ELFTests(unittest.TestCase):
    def parse(self, data):
        return parse(io.BytesIO(data), len(data))

    def test_header_segments_sections_and_unknown_target(self):
        report = self.parse(make_elf())
        self.assertEqual(report['entry_point'], '0x00100000')
        self.assertEqual(report['architecture'], 'MIPS')
        self.assertEqual(report['entry_load_segments'], [0])
        self.assertEqual([x['name'] for x in report['sections']], ['', '.text', '.bss', '.shstrtab'])
        self.assertFalse(report['sections'][2]['file_backed'])
        self.assertEqual(report['target']['evidence_status'], 'UNRESOLVED')

    def test_truncated_at_header_and_table(self):
        for size in (4, 15, 51, 60, 340, len(make_elf())-1):
            with self.subTest(size=size), self.assertRaises(InvalidELF):
                self.parse(make_elf()[:size])

    def test_unsupported_not_mislabelled_invalid(self):
        for raw in (b'CD001 ISO data', edit(make_elf(), 4, 2, 'B'), edit(make_elf(), 5, 2, 'B'),
                    edit(make_elf(), 18, 62, 'H'), edit(make_elf(), 16, 0xff80, 'H'),
                    edit(make_elf(), 48, 0, 'H'), edit(make_elf(), 50, 0xffff, 'H')):
            with self.subTest(raw=raw[:20]), self.assertRaises(UnsupportedELF):
                self.parse(raw)

    def test_bad_header_and_huge_table_offsets(self):
        for offset, val, fmt in [(4,0,'B'),(6,0,'B'),(20,0,'I'),(40,51,'H'),(42,31,'H'),
                                  (28,0xfffffff0,'I'),(32,0xfffffff0,'I'),(50,9,'H')]:
            with self.subTest(offset=offset), self.assertRaises(InvalidELF):
                self.parse(edit(make_elf(),offset,val,fmt))

    def test_segment_bounds_alignment_and_overflow(self):
        for offset,val in [(56,0xfffffff0),(68,49),(80,3),(60,0xfffffff0),(60,0x100001)]:
            with self.subTest(offset=offset), self.assertRaises(InvalidELF):
                self.parse(edit(make_elf(),offset,val))

    def test_nobits_not_read_as_file_bytes(self):
        raw=edit(make_elf(),0x140+80+16,0xfffffff0)
        self.assertEqual(self.parse(raw)['sections'][2]['offset'],0xfffffff0)

    def test_null_segment_fields_not_dereferenced(self):
        raw=edit(edit(make_elf(),52,0),56,0xfffffff0)
        self.assertFalse(self.parse(raw)['segments'][0]['interpreted'])

    def test_section_names_and_sizes_rejected(self):
        for offset,val in [(0x140+40,9999),(0x140+40+16,0xfffffff0),
                           (0x140+40+32,3),(0x140+40+36,7),(0x140+120+4,1)]:
            with self.subTest(offset=offset), self.assertRaises(InvalidELF):
                self.parse(edit(make_elf(),offset,val))

    def test_string_table_terminator_rejected(self):
        raw=bytearray(make_elf());raw[0x110]=65
        with self.assertRaises(InvalidELF):self.parse(bytes(raw))

    def test_sectionless_elf_supported_with_warning(self):
        raw=edit(edit(edit(make_elf(),32,0),48,0,'H'),50,0,'H')
        report=self.parse(raw)
        self.assertEqual(report['sections'],[])
        self.assertTrue(report['warnings'])

    def test_unmapped_entry_is_warning(self):
        report=self.parse(edit(make_elf(),24,0x200000))
        self.assertEqual(report['entry_load_segments'],[])
        self.assertTrue(report['warnings'])

    def test_rel_type_without_load_table(self):
        raw=edit(edit(edit(make_elf(),16,1,'H'),28,0),44,0,'H')
        self.assertEqual(self.parse(raw)['elf_type_name'],'REL')

    def test_budget_guard(self):
        with self.assertRaises(UnsupportedELF):self.parse(edit(make_elf(),48,513,'H'))

    @unittest.skipUnless(shutil.which('readelf'), 'GNU readelf unavailable')
    def test_independent_readelf_matches_fixture(self):
        with tempfile.TemporaryDirectory() as t:
            path=Path(t)/'synthetic.elf';path.write_bytes(make_elf())
            result=subprocess.run(['readelf','-W','-h','-l','-S',str(path)],capture_output=True,text=True,env={'LC_ALL':'C'})
            self.assertEqual(result.returncode,0,result.stderr)
            self.assertIn('0x100000',result.stdout)
            self.assertRegex(result.stdout,r'Number of section headers:\s+4')
            self.assertRegex(result.stdout,r'Number of program headers:\s+1')
            self.assertRegex(result.stdout,r'\.text\s+PROGBITS\s+00100000\s+000100\s+000010')
            self.assertRegex(result.stdout,r'\.bss\s+NOBITS\s+00100010\s+000110\s+000020')
            self.assertRegex(result.stdout,r'LOAD\s+0x000100\s+0x00100000\s+0x00100000\s+0x00010\s+0x00030')


class BaselineTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name)
        self.store=Store(self.parent/'Workspace 日本');self.store.create('test')
        self.path=self.parent/'synthetic 日本.elf';self.path.write_bytes(make_elf())
        snapshot=add_input(self.store,str(self.path))
        self.input_id=snapshot.data['inputs'][0]['id']

    def test_roundtrip_immutable_hash_and_original_untouched(self):
        before=self.path.read_bytes();snapshot=self.store.load()
        result=create_baseline(self.store,self.input_id)
        report_path=Path(result['report_file']);raw=report_path.read_bytes();mtime=report_path.stat().st_mtime_ns
        again=create_baseline(self.store,self.input_id)
        self.assertEqual(result['baseline'],again['baseline'])
        self.assertEqual(report_path.stat().st_mtime_ns,mtime)
        self.assertEqual(result['receipt']['report_sha256'],hashlib.sha256(raw).hexdigest())
        self.assertEqual(self.path.read_bytes(),before)
        self.assertEqual(self.store.load(),snapshot)
        self.assertEqual(len(list((self.store.root/'baselines/records').glob('*.json'))),2)

    def test_changed_registered_input_refused(self):
        self.path.write_bytes(edit(make_elf(),36,1))
        with self.assertRaises(ConflictError):create_baseline(self.store,self.input_id)
        self.assertFalse((self.store.root/'baselines').exists())

    def test_cancel_before_and_during_hash(self):
        cancel=threading.Event();cancel.set()
        with self.assertRaises(Cancelled):create_baseline(self.store,self.input_id,cancel)
        cancel.clear()
        with self.assertRaises(Cancelled):
            create_baseline(self.store,self.input_id,cancel,lambda event:cancel.set())
        self.assertFalse((self.store.root/'baselines').exists())

    def test_mutation_during_hash_refused(self):
        with self.assertRaises(ValidationError):
            create_baseline(self.store,self.input_id,progress=lambda e:self.path.write_bytes(edit(make_elf(),36,1)))
        self.assertFalse((self.store.root/'baselines').exists())

    def test_workspace_changed_during_parse_refused(self):
        with self.assertRaises(ConflictError):
            create_baseline(self.store,self.input_id,progress=lambda e:rename(self.store,'changed'))

    def test_report_tamper_refused(self):
        first=create_baseline(self.store,self.input_id)
        Path(first['report_file']).write_text('tampered')
        with self.assertRaises(ConflictError):create_baseline(self.store,self.input_id)
        self.assertEqual(Path(first['report_file']).read_text(),'tampered')

    def test_missing_input_and_unknown_id(self):
        with self.assertRaises(ValidationError):create_baseline(self.store,'unknown')
        self.path.unlink()
        with self.assertRaises(FileNotFoundError):create_baseline(self.store,self.input_id)

    def test_output_symlink_refused(self):
        try:(self.store.root/'baselines').symlink_to(self.parent,target_is_directory=True)
        except OSError:self.skipTest('Symlink permission not available')
        with self.assertRaises(PathError):create_baseline(self.store,self.input_id)

    def test_save_failure_never_changes_input(self):
        with patch.object(self.store,'atomic',side_effect=OSError('injected full disk')):
            with self.assertRaises(OSError):create_baseline(self.store,self.input_id)
        self.assertEqual(self.path.read_bytes(),make_elf())
        self.assertEqual(list((self.store.root/'baselines/records').glob('*.json')),[])

    def test_multiple_executables_have_separate_reports(self):
        other=self.parent/'other.elf';other.write_bytes(edit(make_elf(),36,1))
        snapshot=add_input(self.store,str(other));other_id=snapshot.data['inputs'][1]['id']
        a=create_baseline(self.store,self.input_id);b=create_baseline(self.store,other_id)
        self.assertNotEqual(a['report_file'],b['report_file'])
        self.assertEqual(a['baseline']['metadata']['target']['value'],'UNKNOWN')

    def test_baseline_cli(self):
        result=subprocess.run([sys.executable,'-m','app.cli','baseline',str(self.store.root),'--input-id',self.input_id],capture_output=True,text=True)
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(json.loads(result.stdout)['baseline']['source_sha256'],hashlib.sha256(make_elf()).hexdigest())
