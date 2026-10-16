import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_build_plans as fixture
from app.domain.workspace.model import ValidationError,ConflictError,WorkspaceError,PathError
from app.domain.binary.elf import Cancelled

class BuildStageTests(unittest.TestCase):
    call=fixture.BuildPlanTests.call
    add=fixture.BuildPlanTests.add
    material=fixture.BuildPlanTests.material
    plan=fixture.BuildPlanTests.plan
    snapshot=fixture.BuildPlanTests.snapshot
    def setUp(self):
        fixture.BuildPlanTests.setUp(self)
        self.saved_plan=self.plan();self.pid=self.saved_plan['plan_id']
    def stage(self,action='create',sid=None,**kw):
        return self.call(revision=self.revision,material_action='build-stage',bundle_id=self.bundle_id,
                         build_options={'plan_id':self.pid},stage_action=action,stage_id=sid,**kw)
    def test_copies_and_no_process_or_object(self):
        before=self.snapshot()
        with patch('subprocess.Popen',side_effect=AssertionError('No process allowed')):r=self.stage()
        folder=Path(r['stage_dir']);plan=Path(self.saved_plan['plan_dir'])
        for name in ('source.c','assembly.s','context.h','plan.json'):
            self.assertEqual((folder/'inputs'/name).read_bytes(),(plan/name).read_bytes())
            self.assertEqual((folder/'inputs'/name).stat().st_nlink,1)
        self.assertEqual(list((folder/'outputs').iterdir()),[])
        self.assertEqual(r['manifest']['argv_proposal'][-4:],['-c','inputs/source.c','-o','outputs/candidate.o'])
        for path,data in before.items():self.assertEqual((self.store.root/path).read_bytes(),data)
        self.assertFalse(r['build_execution_verified']);self.assertEqual(self.elf.read_bytes(),self.raw)
    def test_verify_list_readonly(self):
        a=self.stage();before=self.snapshot()
        self.assertEqual(a,self.stage('verify',a['stage_id']))
        self.assertEqual(self.stage('list')['verified_input_stages'],[a['stage_id']]);self.assertEqual(before,self.snapshot())
    def test_new_stage_each_time_no_overwrite(self):
        a=self.stage();b=self.stage();self.assertNotEqual(a['stage_id'],b['stage_id'])
        self.assertEqual(len(self.stage('list')['verified_input_stages']),2)
    def test_edit_staged_input_does_not_change_plan(self):
        a=self.stage();p=Path(a['stage_dir'],'inputs/source.c');p.write_text('modified')
        self.assertEqual(Path(self.saved_plan['plan_dir'],'source.c').read_bytes(),self.source.read_bytes())
        with self.assertRaises(ConflictError):self.stage('verify',a['stage_id'])
        with self.assertRaises(ConflictError):self.stage('list')
    def test_tamper_manifest_refused(self):
        a=self.stage();p=Path(a['stage_dir'],'stage.json');p.write_text('{}')
        with self.assertRaises(ConflictError):self.stage('verify',a['stage_id'])
    def test_partial_failure_reported(self):
        original=self.store.atomic
        def fail(relative,data):
            if relative.endswith('stage.json'):raise OSError('injected')
            return original(relative,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.stage()
        info=self.stage('list');self.assertEqual(len(info['incomplete_stages']),1);self.assertEqual(info['verified_input_stages'],[])
        a=self.stage();self.assertNotEqual(a['stage_id'],info['incomplete_stages'][0])
    def test_output_is_not_build_proof(self):
        a=self.stage();Path(a['stage_dir'],'outputs/candidate.o').write_bytes(b'not-an-elf')
        r=self.stage('verify',a['stage_id']);self.assertFalse(r['output_files_inspected']);self.assertFalse(r['build_execution_verified'])
    def test_context_paths_opt_in(self):
        r=self.plan({**self.options,'use_context':True});self.pid=r['plan_id'];s=self.stage()
        argv=s['manifest']['argv_proposal'];self.assertEqual(argv[argv.index('-include')+1],'inputs/context.h')
    def test_invalid_ids_and_modes(self):
        for sid in ('../x','BAD'):
            with self.assertRaises(ValidationError):self.stage('verify',sid)
        with self.assertRaises(ValidationError):self.stage('wrong')
        with self.assertRaises(ValidationError):self.stage('list','unused')
    def test_limit_and_collision(self):
        a=self.stage()
        with patch('app.application.build_stages.MAX_STAGES',1):
            with self.assertRaises(ValidationError):self.stage()
        with patch('app.application.build_stages.uuid4',return_value=a['stage_id']):
            with self.assertRaises(ConflictError):self.stage()
    def test_cancel_and_corrupt_plan(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.stage(cancel=event)
        Path(self.saved_plan['plan_dir'],'source.c').write_text('bad')
        with self.assertRaises(ConflictError):self.stage()
        self.assertFalse((self.store.root/'build-stages').exists())
    def test_symlink_output_root(self):
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'build-stages').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.stage()
        self.assertEqual(list(outside.iterdir()),[])
    def test_missing_input_and_output_dir(self):
        a=self.stage();root=Path(a['stage_dir']);data=(root/'inputs/context.h').read_bytes();(root/'inputs/context.h').unlink()
        with self.assertRaises((WorkspaceError,OSError)):self.stage('verify',a['stage_id'])
        (root/'inputs/context.h').write_bytes(data);(root/'outputs').rmdir()
        with self.assertRaises(ValidationError):self.stage('verify',a['stage_id'])
    def test_cli(self):
        root=fixture.fixture.fixture.ROOT
        args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--revision',self.revision,'--bundle-id',self.bundle_id,'--plan-id',self.pid]
        r=subprocess.run([sys.executable,'-m','app','stage-build']+args,cwd=root,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);sid=json.loads(r.stdout)['stage_id']
        for command,extra in [('verify-build-stage',['--stage-id',sid]),('list-build-stages',[])]:
            r=subprocess.run([sys.executable,'-m','app',command]+args+extra,cwd=root,capture_output=True,text=True)
            self.assertEqual(r.returncode,0,r.stderr)
