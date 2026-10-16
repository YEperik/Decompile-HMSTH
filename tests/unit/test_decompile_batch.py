import json
import threading
import unittest
import contextlib
import io
from pathlib import Path
from unittest.mock import patch

from tests.unit import test_decompile as fixture
from app.application.decompile import GhidraExportError
from app.application.decompile_batch import decompile_batch
from app.application.workspaces import rename
from app.domain.workspace.model import ValidationError, ConflictError
from app.domain.binary.elf import Cancelled
from app.cli import main
from app.presentation import compact


class BatchTests(unittest.TestCase):
    def setUp(self):
        self.f = fixture.DecompileTests()
        self.f.setUp()
        self.addCleanup(self.f.doCleanups)

    def call(self, ids=None, **kw):
        f = self.f
        return decompile_batch(f.store, f.iid, ids or ['3:2'], str(f.home), str(f.jdk), **kw)

    def saved(self):
        files = list((self.f.store.root / 'decompile-batches').glob('*/batch.json'))
        self.assertEqual(len(files), 1)
        return json.loads(files[0].read_text())

    def test_actual_adapter_and_durable_result(self):
        with patch('app.application.decompile.run', side_effect=self.f.fake_export):
            result = self.call()
        self.assertEqual(result, self.saved())
        self.assertEqual(result['status'], 'COMPLETED_UNVERIFIED')
        self.assertEqual(result['counts']['DECOMPILED_UNVERIFIED'], 1)
        self.assertTrue(Path(result['functions'][0]['code_file']).is_file())
        self.assertFalse(result['semantics_verified'])

    def test_failed_export_continues_with_logs(self):
        error = GhidraExportError('TEST missing export')
        error.artifact_dir = 'TEST_JOB'; error.run_dir = 'TEST_LOG'
        success = {'status': 'DECOMPILED_UNVERIFIED', 'semantics_verified': False}
        with patch('app.application.decompile_batch.decompile_function', side_effect=[error, success]):
            result = self.call(['3:2', '3:3'])
        self.assertEqual(result['status'], 'PARTIAL')
        self.assertEqual(result['functions'][0]['run_dir'], 'TEST_LOG')
        self.assertEqual(result, self.saved())

    def test_zero_exit_missing_output_is_failed_batch(self):
        with patch('app.application.decompile.run', return_value={'status': 'succeeded', 'artifact_dir': 'TEST_LOG'}):
            result = self.call()
        self.assertEqual(result['status'], 'FAILED')
        row = result['functions'][0]
        self.assertEqual(row['run_dir'], 'TEST_LOG')
        self.assertTrue((Path(row['artifact_dir']) / 'request.json').is_file())
        self.assertFalse((Path(row['artifact_dir']) / 'receipt.json').exists())

    def test_runner_cancel_stops_remaining_functions(self):
        with patch('app.application.decompile_batch.decompile_function', return_value={
                'status': 'GHIDRA_RUN_FAILED', 'run_status': 'cancelled'}) as runner:
            result = self.call(['3:2', '3:3'])
        self.assertEqual(runner.call_count, 1)
        self.assertEqual(result['status'], 'CANCELLED')
        self.assertEqual(result['functions'][1]['status'], 'NOT_RUN')

    def test_timeout_continues_but_not_success(self):
        with patch('app.application.decompile_batch.decompile_function', return_value={
                'status': 'GHIDRA_RUN_FAILED', 'run_status': 'timed_out'}) as runner:
            result = self.call(['3:2', '3:3'])
        self.assertEqual(runner.call_count, 2)
        self.assertEqual(result['status'], 'FAILED')

    def test_manifest_change_aborts_remaining(self):
        def change(*args):
            rename(self.f.store, 'Changed')
            return {'status': 'DECOMPILED_UNVERIFIED'}
        with patch('app.application.decompile_batch.decompile_function', side_effect=change) as runner:
            with self.assertRaises(ConflictError):
                self.call(['3:2', '3:3'])
        self.assertEqual(runner.call_count, 1)
        self.assertEqual(self.saved()['status'], 'ABORTED')
        self.assertEqual(self.saved()['functions'][1]['status'], 'NOT_RUN')

    def test_preflight_error_stops_batch(self):
        (self.f.jdk / 'bin/java').unlink()
        with self.assertRaises(ValidationError):
            self.call(['3:2', '3:3'])
        result = self.saved()
        self.assertEqual(result['status'], 'ABORTED')
        self.assertEqual(result['functions'][1]['status'], 'NOT_RUN')
        self.assertFalse((self.f.store.root / 'decompilations').exists())

    def test_interrupt_preserves_progress(self):
        with patch('app.application.decompile_batch.decompile_function', side_effect=KeyboardInterrupt):
            with self.assertRaises(KeyboardInterrupt):
                self.call(['3:2', '3:3'])
        self.assertEqual(self.saved()['status'], 'CANCELLED')
        self.assertEqual(self.saved()['functions'][0]['status'], 'ABORTED')

    def test_invalid_selections_and_early_cancel(self):
        for ids in (['3:2', '3:2'], ['../bad'], [None], ['3:' + str(i) for i in range(101)]):
            with self.assertRaises(ValidationError):
                self.call(ids)
        token = threading.Event(); token.set()
        with self.assertRaises(Cancelled):
            self.call(cancel=token)
        self.assertFalse((self.f.store.root / 'decompile-batches').exists())

    def test_cli_partial_returns_nonzero_and_summary_stays_short(self):
        result = {'status': 'PARTIAL', 'report_file': 'batch.json', 'semantics_verified': False,
                  'counts': {'EXPORT_FAILED': 1}, 'functions': [{'status': 'EXPORT_FAILED'}] * 100}
        output = io.StringIO()
        with contextlib.redirect_stdout(output), patch(
                'app.application.decompile_batch.decompile_batch', return_value=result) as batch:
            code = main(['--json', 'ghidra-batch', str(self.f.store.root), '--input-id', self.f.iid,
                         '--symbol-id', '3:2', '--symbol-id', '3:3',
                         '--ghidra-home', str(self.f.home), '--jdk-home', str(self.f.jdk)])
        self.assertEqual(code, 1)
        self.assertEqual(batch.call_args.args[2], ['3:2', '3:3'])
        self.assertEqual(json.loads(output.getvalue()), result)
        summary = compact(result)
        self.assertIn('EXPORT_FAILED: 1', summary)
        self.assertIn('batch.json', summary)
        self.assertLess(len(summary.splitlines()), 10)

    def test_invalid_timeout_and_profile_create_no_batch(self):
        for timeout in (0, float('nan'), 3601, True):
            with self.assertRaises(ValidationError):
                self.call(timeout=timeout)
        with self.assertRaises(ValidationError):
            self.call(analysis='generic')
        self.assertFalse((self.f.store.root / 'decompile-batches').exists())
