import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_targets as fixture
from tests.relocation_fixture import make_relocations
from tests.elf_fixture import edit
from app.application.targets import target_bundle
from app.application.workspaces import add_input,rename
from app.application.comparisons import compare_functions,byte_diff,prepare
from app.domain.workspace.model import ConflictError,ValidationError,WorkspaceError,PathError
from app.domain.binary.elf import Cancelled

class ComparisonTests(unittest.TestCase):
    def setUp(self):
        fixture.TargetTests.setUp(self)
        self.reference=self.iid
        target_bundle(self.store,self.reference,'3:2')
        self.candidate_path=self.parent/'candidate.elf';self.register_candidate(self.raw)
    def register_candidate(self,raw):
        self.candidate_path=self.parent/('candidate-'+str(len(self.store.load().data['inputs']))+'.elf')
        self.candidate_path.write_bytes(raw);add_input(self.store,str(self.candidate_path))
        self.candidate=self.store.load().data['inputs'][-1]['id']
        self.candidate_bundle=Path(target_bundle(self.store,self.candidate,'3:2')['bundle_dir'])
    def compare(self,**kw):return compare_functions(self.store,self.reference,'3:2',self.candidate,'3:2',**kw)
    def snapshot(self):return {str(p.relative_to(self.store.root)):p.read_bytes() for p in self.store.root.rglob('*') if p.is_file()}
    def test_identical_readonly_and_no_build_claim(self):
        before=self.snapshot();r=self.compare()['comparison'];self.assertEqual(before,self.snapshot())
        self.assertEqual(r['status'],'RAW_RANGE_IDENTICAL');self.assertTrue(r['same_selection'])
        self.assertFalse(r['build_verified']);self.assertFalse(r['source_to_candidate_link_verified'])
        self.assertFalse(r['whole_binary_comparison_performed']);self.assertGreater(r['reference']['relocations_starting_in_range'],0)
        self.assertEqual(self.path.read_bytes(),self.raw)
    def test_difference_offsets(self):
        raw=bytearray(self.raw);raw[0x109]^=255;self.register_candidate(bytes(raw))
        r=self.compare()['comparison'];self.assertEqual(r['differing_byte_positions'],1)
        self.assertEqual(r['differences'][0]['relative_offset'],1)
        self.assertEqual(r['differences'][0]['reference_file_offset'],0x109)
        self.assertEqual(r['differences'][0]['candidate_file_offset'],0x109)
    def test_shorter_candidate(self):
        self.register_candidate(edit(self.raw,0x228,4))
        r=self.compare()['comparison'];self.assertEqual(r['differing_byte_positions'],4)
        self.assertIsNone(r['differences'][0]['candidate_byte']);self.assertIsNone(r['differences'][0]['candidate_file_offset'])
    def test_identical_range_different_input_not_whole_binary(self):
        raw=bytearray(self.raw);raw[0x100]^=255;self.register_candidate(bytes(raw))
        r=self.compare()['comparison'];self.assertEqual(r['status'],'RAW_RANGE_IDENTICAL')
        self.assertFalse(r['source_files_have_same_hash']);self.assertFalse(r['same_selection'])
        self.assertFalse(r['program_semantics_verified'])
    def test_rel_exec_layout_difference_explicit(self):
        self.register_candidate(make_relocations(1));r=self.compare()['comparison']
        self.assertFalse(r['elf_types_equal']);self.assertFalse(r['symbol_layout_fields_equal'])
        self.assertFalse(r['abi_compatibility_verified']);self.assertFalse(r['relocations_normalized'])
    def test_difference_limit(self):
        count,details=byte_diff(b'\x00'*100,b'\xff'*120)
        self.assertEqual(count,120);self.assertEqual(len(details),64)
    def test_saved_report_stable_and_corruption_rejected(self):
        a=self.compare(save=True);b=self.compare(save=True);self.assertEqual(a,b)
        path=Path(a['report_file']);self.assertEqual(json.loads(path.read_bytes()),a['comparison']);path.write_text('bad')
        with self.assertRaises(ConflictError):self.compare(save=True)
        self.assertEqual(path.read_text(),'bad')
    def test_candidate_changed_since_registration(self):
        self.candidate_path.write_bytes(self.raw+b'changed')
        with self.assertRaises(ConflictError):self.compare(save=True)
        self.assertFalse((self.store.root/'comparisons').exists())
    def test_missing_or_corrupt_bundle(self):
        path=self.candidate_bundle/'metadata.json';original=path.read_bytes();path.unlink()
        with self.assertRaises((WorkspaceError,OSError)):self.compare()
        path.write_bytes(b'bad')
        with self.assertRaises(ConflictError):self.compare()
        path.write_bytes(original)
    def test_manifest_conflict_between_reads(self):
        counter=0
        def mutate(*args):
            nonlocal counter
            result=prepare(*args);counter+=1
            if counter==1:rename(self.store,'Changed')
            return result
        with patch('app.application.comparisons.prepare',side_effect=mutate):
            with self.assertRaises(ConflictError):self.compare(save=True)
        self.assertFalse((self.store.root/'comparisons').exists())
    def test_cancel_invalid_ids_and_limit(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.compare(cancel=event)
        with self.assertRaises(ValidationError):compare_functions(self.store,self.reference,'../x',self.candidate,'3:2')
        with patch('app.application.comparisons.MAX_MANIFEST',10):
            with self.assertRaises(ValidationError):self.compare(save=True)
        self.assertFalse((self.store.root/'comparisons').exists())
    def test_output_symlink(self):
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'comparisons').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.compare(save=True)
        self.assertEqual(list(outside.iterdir()),[])
    def test_cli_exit_codes(self):
        args=[sys.executable,'-m','app','compare-functions',str(self.store.root),'--reference-input',self.reference,'--reference-symbol','3:2','--candidate-symbol','3:2','--candidate-input']
        r=subprocess.run(args+[self.candidate],cwd=fixture.ROOT,capture_output=True,text=True);self.assertEqual(r.returncode,0,r.stderr)
        raw=bytearray(self.raw);raw[0x108]^=1;self.register_candidate(bytes(raw))
        r=subprocess.run(args+[self.candidate,'--save'],cwd=fixture.ROOT,capture_output=True,text=True);self.assertEqual(r.returncode,1,r.stderr)
        self.assertEqual(json.loads(r.stdout)['comparison']['status'],'RAW_RANGE_DIFFERENT')
        r=subprocess.run(args+['missing'],cwd=fixture.ROOT,capture_output=True,text=True);self.assertEqual(r.returncode,2)
