import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_materials as fixture
from app.domain.workspace.model import ValidationError,ConflictError,WorkspaceError,PathError
from app.domain.binary.elf import Cancelled

class BuildPlanTests(unittest.TestCase):
    call=fixture.MaterialTests.call
    add=fixture.MaterialTests.add
    material=fixture.MaterialTests.material
    snapshot=fixture.MaterialTests.snapshot
    def setUp(self):
        fixture.MaterialTests.setUp(self)
        self.bundle_id=self.material()['bundle_id']
        self.options={'compiler':r'C:\Toolchain Example\ee-gcc.exe','optimization':'2','use_context':False}
    def plan(self,options=None,**kw):
        return self.call(revision=self.revision,material_action='build-plan',bundle_id=self.bundle_id,build_options=self.options if options is None else options,**kw)
    def test_plan_snapshots_and_no_process(self):
        with patch('subprocess.Popen',side_effect=AssertionError('No process allowed')):r=self.plan()
        plan=r['plan'];folder=Path(r['plan_dir'])
        self.assertEqual((folder/'source.c').read_bytes(),self.source.read_bytes())
        self.assertEqual((folder/'assembly.s').read_bytes(),self.asm.read_bytes())
        self.assertEqual((folder/'context.h').read_bytes(),self.header.read_bytes())
        self.assertFalse((folder/'candidate.o').exists());self.assertFalse(plan['executed']);self.assertFalse(plan['build_verified'])
        self.assertEqual(plan['argv_proposal'],[self.options['compiler'],'-x','c','-O2','-c','source.c','-o','candidate.o'])
        self.assertFalse(plan['compiler']['exists_verified']);self.assertEqual(self.elf.read_bytes(),self.raw)
    def test_repeatable_and_show_readonly(self):
        a=self.plan();self.assertEqual(a,self.plan());before=self.snapshot()
        self.assertEqual(a,self.plan({'plan_id':a['plan_id']}));self.assertEqual(before,self.snapshot())
    def test_context_opt_in_separate_plan(self):
        a=self.plan();b=self.plan({**self.options,'use_context':True})
        self.assertNotEqual(a['plan_id'],b['plan_id']);self.assertNotIn('-include',a['plan']['argv_proposal'])
        self.assertIn('-include',b['plan']['argv_proposal']);self.assertIn('UNVERIFIED',b['plan']['context_mode'])
    def test_cpp_source_language(self):
        self.revision=self.add(language='cpp')['record']['revision'];self.bundle_id=self.material()['bundle_id'];r=self.plan()
        self.assertEqual(r['plan']['argv_proposal'][2],'c++');self.assertTrue(Path(r['plan_dir'],'source.cpp').is_file())
    def test_invalid_paths_and_options(self):
        for path in ('gcc','C:relative.exe','/a/../gcc','/gcc\nrun'):
            with self.assertRaises(ValidationError):self.plan({**self.options,'compiler':path})
        for options in ({**self.options,'optimization':'fast'},{**self.options,'use_context':'yes'},{**self.options,'extra':True}):
            with self.assertRaises(ValidationError):self.plan(options)
        self.assertFalse((self.store.root/'build-plans').exists())
    def test_posix_path_is_only_declared(self):
        r=self.plan({**self.options,'compiler':'/does/not/exist/gcc'})
        self.assertFalse(r['plan']['compiler']['exists_verified'])
    def test_corrupt_each_file_not_overwritten(self):
        a=self.plan();folder=Path(a['plan_dir'])
        for name in ('source.c','context.h','assembly.s','plan.json'):
            path=folder/name;original=path.read_bytes();path.write_text('corrupt');before=self.snapshot()
            for options in (self.options,{'plan_id':a['plan_id']}):
                with self.assertRaises(WorkspaceError):self.plan(options)
                self.assertEqual(before,self.snapshot())
            path.write_bytes(original)
    def test_binding_different_revision(self):
        a=self.plan();self.revision=self.add()['record']['revision'];self.bundle_id=self.material()['bundle_id']
        with self.assertRaises((WorkspaceError,OSError)):self.plan({'plan_id':a['plan_id']})
    def test_partial_save_retry_and_no_output(self):
        original=self.store.atomic
        def fail(relative,data):
            if relative.endswith('plan.json'):raise OSError('injected')
            return original(relative,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.plan()
        a=self.plan();self.assertEqual(a,self.plan({'plan_id':a['plan_id']}))
        self.assertEqual(list((self.store.root/'build-plans').rglob('candidate.o')),[])
    def test_source_target_corruption_and_cancel(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.plan(cancel=event)
        (self.bundle/'bytes.bin').write_bytes(b'bad')
        with self.assertRaises(ConflictError):self.plan()
        self.assertFalse((self.store.root/'build-plans').exists())
    def test_output_symlink(self):
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'build-plans').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.plan()
        self.assertEqual(list(outside.iterdir()),[])
    def test_invalid_plan_id(self):
        for pid in ('../x','A'*64,'0'*64):
            with self.assertRaises((WorkspaceError,OSError)):self.plan({'plan_id':pid})
    def test_cli(self):
        args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--revision',self.revision,'--bundle-id',self.bundle_id]
        r=subprocess.run([sys.executable,'-m','app','plan-build']+args+['--compiler',self.options['compiler'],'--optimization','2'],cwd=fixture.fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);pid=json.loads(r.stdout)['plan_id']
        r=subprocess.run([sys.executable,'-m','app','show-build-plan']+args+['--plan-id',pid],cwd=fixture.fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);self.assertFalse(json.loads(r.stdout)['plan']['executed'])
