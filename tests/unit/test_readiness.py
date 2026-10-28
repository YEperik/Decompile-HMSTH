import json
import platform
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_materials as fixture
from app.application.readiness import assess,runtime_report
from app.domain.workspace.model import WorkspaceError,ConflictError
from app.domain.binary.elf import Cancelled

class ReadinessTests(unittest.TestCase):
    setUp=fixture.MaterialTests.setUp
    call=fixture.MaterialTests.call
    add=fixture.MaterialTests.add
    material=fixture.MaterialTests.material
    snapshot=fixture.MaterialTests.snapshot
    def check(self,bundle,**kw):return self.material('check',bundle_id=bundle['bundle_id'],**kw)
    def test_clean_text_still_manual_and_no_writes(self):
        a=self.material();before=self.snapshot();r=self.check(a)
        self.assertEqual(before,self.snapshot());self.assertTrue(r['integrity_verified'])
        self.assertFalse(r['automatic_execution_ready']);self.assertFalse(r['syntax_verified'])
        self.assertEqual(r['status'],'MANUAL_REVIEW_REQUIRED');self.assertEqual(r['lexical_findings']['total'],0)
        self.assertEqual(self.elf.read_bytes(),self.raw)
    def test_external_directives_not_resolved(self):
        self.asm.write_text('.include "missing.s"\n.incbin "does-not-exist.bin"\n.macro test\n')
        self.header.write_text('#include "missing.h"\n#if FLAG\n#endif\n')
        r=self.check(self.material())
        self.assertEqual(r['lexical_findings']['counts'],{'ASM_EXTERNAL_FILE':2,'ASM_MACRO':1,'CONTEXT_INCLUDE':1,'CONTEXT_CONDITIONAL':1})
        self.assertFalse(r['external_files_opened']);self.assertFalse(r['tools_executed'])
    def test_detail_limit_counts_all(self):
        self.asm.write_text('.include "missing"\n'*100)
        r=self.check(self.material())['lexical_findings']
        self.assertEqual(r['total'],100);self.assertEqual(len(r['details']),64);self.assertEqual(r['details_omitted'],36)
    def test_comments_and_conditionals_not_semantically_parsed(self):
        self.header.write_text('/*\n#include "inside-comment.h"\n*/\n')
        r=self.check(self.material())
        self.assertEqual(r['lexical_findings']['counts']['CONTEXT_INCLUDE'],1)
        self.assertFalse(r['context_verified'])
    def test_preprocessor_and_crlf_statistics(self):
        self.asm.write_bytes(b'# include "a.h"\r\n.word 0')
        r=self.check(self.material());s=r['statistics']['assembly.s']
        self.assertEqual(s['crlf_count'],1);self.assertEqual(s['lf_lines'],2);self.assertFalse(s['ends_with_lf'])
        self.assertEqual(r['lexical_findings']['counts']['ASM_PREPROCESSOR'],1)
    def test_corrupt_bundle_or_target_never_ready(self):
        a=self.material();p=Path(a['bundle_dir'],'assembly.s');before=p.read_bytes();p.write_text('changed')
        with self.assertRaises(ConflictError):self.check(a)
        p.write_bytes(before);(self.bundle/'bytes.bin').write_bytes(b'changed')
        with self.assertRaises(ConflictError):self.check(a)
    def test_bad_bundle_and_cancel(self):
        with self.assertRaises(WorkspaceError):self.material('check',bundle_id='../x')
        a=self.material();event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.check(a,cancel=event)
    def test_windows_diagnostic_is_not_certification(self):
        with patch('app.application.readiness.os.name','nt'),patch('app.application.readiness.sys.version_info',(3,14,8)),patch('app.application.readiness.platform.system',return_value='Windows'),patch('app.application.readiness.platform.python_version',return_value='3.14.8'):
            r=runtime_report()
        self.assertEqual(r['process_runner'],'UNSUPPORTED_WINDOWS');self.assertTrue(r['python_minimum_met'])
        self.assertEqual(r['file_workflow'],'REQUIRES_LOCAL_VERIFICATION');self.assertFalse(r['external_tools_probed'])
    def test_old_python_and_unknown_platform(self):
        with patch('app.application.readiness.os.name','other'),patch('app.application.readiness.sys.version_info',(3,11,9)):
            r=runtime_report()
        self.assertFalse(r['python_minimum_met']);self.assertEqual(r['file_workflow'],'PYTHON_TOO_OLD')
        self.assertEqual(r['process_runner'],'UNSUPPORTED_PLATFORM')
    def test_posix_diagnostic(self):
        with patch('app.application.readiness.os.name','posix'),patch('app.application.readiness.sys.version_info',(3,12,0)):
            r=runtime_report()
        self.assertEqual(r['process_runner'],'IMPLEMENTED_POSIX');self.assertTrue(r['python_minimum_met'])
    def test_runtime_observation_is_dynamic_not_a_fake_ci_claim(self):
        r=runtime_report()
        evidence=r['runtime_test_evidence']
        self.assertIn(platform.system(), evidence)
        self.assertIn(platform.python_version(), evidence)
        self.assertIn('not CI test evidence', evidence)
    def test_cli_doctor_and_check(self):
        a=self.material();root=fixture.fixture.ROOT
        r=subprocess.run([sys.executable,'-m','app','doctor'],cwd=root,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);self.assertFalse(json.loads(r.stdout)['external_tools_executed'])
        r=subprocess.run([sys.executable,'-m','app','draft-materials-check',str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--revision',self.revision,'--bundle-id',a['bundle_id']],cwd=root,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);self.assertEqual(json.loads(r.stdout)['status'],'MANUAL_REVIEW_REQUIRED')
