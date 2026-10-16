import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

from app.application.toolchains import detect, examine, exit_status, _artifact, _target_shape
from app.domain.workspace.model import ValidationError, PathError
from app.infrastructure.persistence.store import Store
from app.infrastructure.process_runner.runner import UnsupportedPlatform
from tests.elf_fixture import make_elf

ROOT = Path(__file__).resolve().parents[2]


class ToolchainTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.store = Store(Path(self.tmp.name) / 'space 日本')
        self.store.create('Toolchain')

    def test_detect_does_not_execute_or_claim_verification(self):
        with patch('app.application.toolchains.shutil.which', side_effect=[None, None, '/trusted/gcc']), \
             patch('app.application.toolchains.run', side_effect=AssertionError('must not execute')):
            result = detect()
        self.assertFalse(result['executed'])
        self.assertEqual([x['status'] for x in result['candidates']],
                         ['NOT_FOUND', 'NOT_FOUND', 'FOUND_UNVERIFIED'])

    def test_profile_never_accepts_host_as_ps2(self):
        with self.assertRaises(ValidationError): _target_shape('x86_64-linux-gnu', 'ps2-ee')
        with self.assertRaises(ValidationError): _target_shape('mips-linux-gnu', 'ps2-ee')
        self.assertEqual(_target_shape('mips64r5900el-ps2-elf', 'ps2-ee'), (1, 8))

    def test_bad_artifacts_rejected(self):
        path = Path(self.tmp.name) / 'bad.o'
        for raw in (b'', b'not ELF', make_elf()):
            path.write_bytes(raw)
            with self.assertRaises(ValidationError): _artifact(path, 1, (2, 62))

    def test_exit_statuses(self):
        for name, code in [('checked',0),('succeeded',0),('failed',1),
                           ('non_reproducible',1),('cancelled',130),('timed_out',124)]:
            self.assertEqual(exit_status({'status':name}),code)

    def test_cli_help_and_missing_configuration(self):
        for command in ('tools-detect','toolchain-check','build-smoke'):
            r=subprocess.run([sys.executable,'-m','app',command,'--help'],cwd=ROOT,capture_output=True)
            self.assertEqual(r.returncode,0)
        r=subprocess.run([sys.executable,'-m','app','build-smoke',str(self.store.root)],cwd=ROOT,capture_output=True)
        self.assertEqual(r.returncode,2)

    @unittest.skipUnless(os.name == 'posix', 'POSIX runner')
    def test_missing_compiler_creates_no_report(self):
        with self.assertRaises(PathError): examine(self.store, '/missing/compiler')
        self.assertFalse((self.store.root/'toolchains').exists())

    def test_unsupported_platform_fails_before_mutation(self):
        with patch('app.infrastructure.process_runner.runner.os.name','nt'):
            with self.assertRaises(UnsupportedPlatform): examine(self.store,sys.executable)
        self.assertFalse((self.store.root/'toolchains').exists())

    @unittest.skipUnless(os.name == 'posix', 'POSIX runner')
    def test_failure_timeout_cancel_are_persisted_and_stop_pipeline(self):
        for status in ('failed','timed_out','cancelled'):
            with patch('app.application.toolchains.run',return_value={
                    'status':status,'run_id':'controlled-fault','argv':[], 'artifact_dir':'unused'}) as run:
                report=examine(self.store,sys.executable,build=True)
            self.assertEqual(report['status'],status)
            self.assertIsNone(report['repeatable'])
            self.assertEqual(run.call_count,1)
            self.assertEqual(json.loads(Path(report['report_path']).read_text())['status'],status)

    @unittest.skipUnless(os.name == 'posix', 'POSIX runner')
    def test_real_non_compiler_does_not_report_success(self):
        report=examine(self.store,sys.executable)
        self.assertEqual(report['status'],'failed')
        self.assertIn('error',report)

    @unittest.skipUnless(os.name == 'posix' and shutil.which('gcc'), 'Real GCC unavailable')
    def test_real_host_compile_link_twice_and_target_rejection(self):
        gcc=str(Path(shutil.which('gcc')).absolute())
        target=subprocess.check_output([gcc,'-dumpmachine'],text=True).strip()
        if not (target.startswith(('x86_64-','aarch64-')) and 'linux' in target):
            self.skipTest('Host target outside explicit ELF smoke subset')
        before=(self.store.root/'workspace.json').read_bytes()
        report=examine(self.store,gcc,'host-elf',build=True)
        self.assertEqual(report['status'],'succeeded',report)
        self.assertTrue(report['repeatable'])
        self.assertFalse(report['runtime_tested'])
        self.assertEqual(len(report['steps']),10)
        for output in report['outputs']:
            for kind in ('object','elf'):
                item=output[kind]
                self.assertEqual(hashlib.sha256(Path(item['path']).read_bytes()).hexdigest(),item['sha256'])
        self.assertEqual((self.store.root/'workspace.json').read_bytes(),before)
        rejected=examine(self.store,gcc,'ps2-ee',build=True)
        self.assertEqual(rejected['status'],'failed')
        self.assertNotIn('outputs',rejected)
        self.assertNotEqual(report['id'],rejected['id'])
