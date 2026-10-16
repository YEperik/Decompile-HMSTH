import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_build_stages as fixture
from tests.relocation_fixture import make_relocations
from tests.elf_fixture import edit
from app.domain.workspace.model import WorkspaceError,ValidationError,ConflictError,PathError
from app.domain.binary.elf import Cancelled

class CandidateTests(unittest.TestCase):
    call=fixture.BuildStageTests.call
    add=fixture.BuildStageTests.add
    material=fixture.BuildStageTests.material
    plan=fixture.BuildStageTests.plan
    stage=fixture.BuildStageTests.stage
    snapshot=fixture.BuildStageTests.snapshot
    def setUp(self):
        fixture.BuildStageTests.setUp(self);self.staged=self.stage()
        self.object=self.parent/'candidate.o';self.object.write_bytes(make_relocations(1))
    def candidate(self,options=None,**kw):
        return self.call(revision=self.revision,material_action='build-stage',bundle_id=self.bundle_id,
                         build_options={'plan_id':self.pid},stage_action='verify',stage_id=self.staged['stage_id'],
                         candidate_options={'path':str(self.object),'symbol_id':'3:2'} if options is None else options,**kw)
    def test_import_roundtrip_exact_snapshot_and_no_process(self):
        original=self.object.read_bytes()
        with patch('subprocess.Popen',side_effect=AssertionError('No process allowed')):a=self.candidate()
        self.assertEqual(Path(a['candidate_dir'],'candidate.o').read_bytes(),original)
        self.assertEqual(a['report']['candidate']['elf_type'],'REL')
        self.assertEqual(a['report']['comparison']['status'],'RAW_RANGE_IDENTICAL')
        self.assertFalse(a['report']['build_provenance_verified']);self.assertFalse(a['report']['compiler_executed_by_importer'])
        self.assertEqual(self.object.read_bytes(),original);self.assertEqual(self.elf.read_bytes(),self.raw)
    def test_show_readonly_after_external_object_removed(self):
        a=self.candidate();self.object.unlink();before=self.snapshot()
        self.assertEqual(a,self.candidate({'candidate_id':a['candidate_id']}));self.assertEqual(before,self.snapshot())
    def test_difference_and_changed_object_new_snapshot(self):
        a=self.candidate();raw=bytearray(self.object.read_bytes());raw[0x109]^=1;self.object.write_bytes(raw);b=self.candidate()
        self.assertNotEqual(a['candidate_id'],b['candidate_id']);self.assertEqual(b['report']['comparison']['differing_byte_positions'],1)
        self.assertEqual(b['report']['comparison']['differences'][0]['candidate_file_offset'],0x109)
        self.assertEqual(Path(a['candidate_dir'],'candidate.o').read_bytes(),make_relocations(1))
    def test_exec_dyn_host_and_truncated_refused(self):
        for raw in (make_relocations(2),make_relocations(3),edit(make_relocations(1),18,62,'H'),make_relocations(1)[:40],b'not ELF'):
            self.object.write_bytes(raw)
            with self.assertRaises(WorkspaceError):self.candidate()
        self.assertFalse((self.store.root/'build-candidates').exists())
    def test_unknown_function_and_invalid_id(self):
        for sid in ('3:5','../x','3:02','3:999'):
            with self.assertRaises(WorkspaceError):self.candidate({'path':str(self.object),'symbol_id':sid})
    def test_unknown_relocation_preserved(self):
        self.object.write_bytes(edit(make_relocations(1),0x504,(3<<8)|123));r=self.candidate()['report']
        self.assertEqual(r['candidate']['references']['unknown_type_counts'],{'123':1});self.assertFalse(r['relocations_applied'])
    def test_size_and_report_limits(self):
        self.object.write_bytes(make_relocations(1)+b'x'*(1024*1024))
        with self.assertRaises(ValidationError):self.candidate()
        self.object.write_bytes(make_relocations(1))
        # Enough for object, too small for provenance report.
        with patch('app.application.build_candidates.MAX_MANIFEST',2000):
            with self.assertRaises(ValidationError):self.candidate()
        self.assertFalse((self.store.root/'build-candidates').exists())
    def test_corrupt_snapshot_or_report_not_overwritten(self):
        a=self.candidate()
        for name in ('candidate.o','report.json'):
            p=Path(a['candidate_dir'],name);original=p.read_bytes();p.write_bytes(b'bad');before=self.snapshot()
            with self.assertRaises(WorkspaceError):self.candidate({'candidate_id':a['candidate_id']})
            with self.assertRaises(ConflictError):self.candidate()
            self.assertEqual(before,self.snapshot());p.write_bytes(original)
    def test_stage_changed_refused(self):
        Path(self.staged['stage_dir'],'inputs/source.c').write_text('changed')
        with self.assertRaises(ConflictError):self.candidate()
        self.assertFalse((self.store.root/'build-candidates').exists())
    def test_cancel_symlink_input_and_output(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.candidate(cancel=event)
        link=self.parent/'linked.o';link.symlink_to(self.object)
        with self.assertRaises(WorkspaceError):self.candidate({'path':str(link),'symbol_id':'3:2'})
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'build-candidates').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.candidate()
        self.assertEqual(list(outside.iterdir()),[])
    def test_partial_save_retry(self):
        original=self.store.atomic
        def fail(relative,data):
            if relative.endswith('report.json'):raise OSError('injected')
            return original(relative,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.candidate()
        a=self.candidate();self.assertEqual(a,self.candidate({'candidate_id':a['candidate_id']}))
    def test_invalid_candidate_ids(self):
        for cid in ('../x','A'*64,'0'*64):
            with self.assertRaises((WorkspaceError,OSError)):self.candidate({'candidate_id':cid})
    def test_cli_import_and_show(self):
        root=fixture.fixture.fixture.fixture.ROOT
        args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--revision',self.revision,'--bundle-id',self.bundle_id,'--plan-id',self.pid,'--stage-id',self.staged['stage_id']]
        r=subprocess.run([sys.executable,'-m','app','import-build-candidate']+args+['--candidate',str(self.object),'--candidate-symbol','3:2'],cwd=root,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);cid=json.loads(r.stdout)['candidate_id']
        r=subprocess.run([sys.executable,'-m','app','show-build-candidate']+args+['--candidate-id',cid],cwd=root,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr)
