import json
from pathlib import Path
import unittest
from unittest.mock import patch

from tests.unit import test_decompile as fixture
from app.application.export_checks import check_export, verify_allocated
from app.domain.workspace.model import ValidationError, ConflictError


class ExportCheckTests(unittest.TestCase):
    def setUp(self):
        self.fx = fixture.DecompileTests()
        self.fx.setUp()
        self.addCleanup(self.fx.doCleanups)
        with patch('app.application.decompile.run', side_effect=self.fx.fake_export):
            self.export = self.fx.call()
        self.job = Path(self.export['artifact_dir'])
        self.compiler = str(self.fx.jdk / 'bin/java')  # test double only; never executed

    def call(self, **kw):
        return check_export(self.fx.store, self.job.name, self.compiler, **kw)

    def result(self, status='succeeded', code=0):
        return {'status': status, 'exit_code': code, 'artifact_dir': 'TEST_DOUBLE_RUN'}

    def test_syntax_acceptance_never_claims_runtime_or_matching(self):
        original = (self.job / 'export/decompiled.c').read_bytes()
        with patch('app.application.export_checks.run', return_value=self.result()) as runner:
            result = self.call()
        self.assertEqual(result['status'], 'SYNTAX_ACCEPTED_UNVERIFIED')
        for flag in ('linked', 'runtime_tested', 'semantics_verified', 'ps2_binary_match_verified'):
            self.assertIs(result[flag], False)
        self.assertEqual((Path(result['report_dir']) / 'source.txt').read_bytes(), original)
        argv = runner.call_args.args[1].argv
        self.assertIn('-fsyntax-only', argv)
        self.assertNotIn('-o', argv)
        self.assertEqual((self.job / 'export/decompiled.c').read_bytes(), original)

    def test_rejected_syntax_timeout_and_cancel_are_not_passes(self):
        for status, code, expected in [('failed', 1, 'BLOCKED_SYNTAX'),
                                       ('timed_out', None, 'CHECK_FAILED'),
                                       ('cancelled', None, 'CHECK_FAILED'),
                                       ('failed', 2, 'CHECK_FAILED')]:
            with patch('app.application.export_checks.run', return_value=self.result(status, code)):
                result = self.call()
            self.assertEqual(result['status'], expected)
            self.assertFalse(result['syntax_accepted'])

    def test_tampered_export_rejected_before_compiler(self):
        (self.job / 'export/decompiled.c').write_text('changed')
        with patch('app.application.export_checks.run', side_effect=AssertionError('must not run')):
            with self.assertRaises(ConflictError): self.call()

    def test_changed_original_elf_rejected(self):
        self.fx.source.write_bytes(self.fx.source.read_bytes() + b'changed')
        with self.assertRaises(ConflictError): self.call()

    def test_missing_receipt_rejected(self):
        (self.job / 'receipt.json').unlink()
        with self.assertRaises(FileNotFoundError): self.call()

    def test_changed_snapshot_or_receipt_rejected_after_compiler(self):
        for change in ('snapshot', 'receipt'):
            original = (self.job / 'receipt.json').read_bytes()
            def fake(store, command, cancel):
                path = Path(command.argv[-1]) if change == 'snapshot' else self.job / 'receipt.json'
                path.write_bytes(b'changed')
                return self.result()
            with patch('app.application.export_checks.run', side_effect=fake):
                with self.assertRaises(ConflictError): self.call()
            (self.job / 'receipt.json').write_bytes(original)
        self.assertFalse(list((self.fx.store.root / 'export-checks').glob('*/report.json')))

    def test_invalid_parameters_create_no_check(self):
        with self.assertRaises(ValidationError): self.call(language='assembly')
        with self.assertRaises(ValidationError): self.call(timeout=0)
        with self.assertRaises(ValidationError):
            check_export(self.fx.store, '../escape', self.compiler)
        self.assertFalse((self.fx.store.root / 'export-checks').exists())

    def test_zero_exit_without_object_is_not_build_success(self):
        with patch('app.application.export_checks.run', return_value=self.result()):
            with self.assertRaises(FileNotFoundError): self.call(emit_object=True)
        self.assertFalse(list((self.fx.store.root / 'export-checks').glob('*/report.json')))

    def test_storage_header_tampering_is_rejected(self):
        def fake(store, command, cancel):
            header = Path(command.argv[command.argv.index('-include') + 1])
            header.write_text('#define sfuo_IsTerm() 1')
            return self.result()
        with patch('app.application.export_checks.run', side_effect=fake):
            with self.assertRaises(ConflictError): self.call(storage_types=True)
        self.assertFalse(list((self.fx.store.root / 'export-checks').glob('*/report.json')))

    def test_ee_rejects_host_target_before_compilation(self):
        probe = self.fx.root / 'probe';probe.mkdir()
        (probe / 'stdout.txt').write_text('x86_64-linux-gnu\n')
        with patch('app.application.export_checks.run', return_value={
                'status':'succeeded','artifact_dir':str(probe)}) as runner:
            with self.assertRaises(ValidationError): self.call(target='ps2-ee')
        self.assertEqual(runner.call_count, 1)
        self.assertEqual(runner.call_args.args[1].argv[-1], '-dumpmachine')
        self.assertFalse((self.fx.store.root / 'export-checks').exists())

    def test_strip_debug_cannot_change_allocated_bytes(self):
        raw = self.fx.source.read_bytes()
        changed = bytearray(raw);changed[0x108] ^= 1
        with self.assertRaises(ConflictError): verify_allocated(raw, bytes(changed))
        verify_allocated(raw, raw + b'non-allocated trailing data')

    def test_invalid_target_and_strip_combinations(self):
        with self.assertRaises(ValidationError): self.call(target='mips-generic')
        with self.assertRaises(ValidationError): self.call(strip_debug=True)
        with self.assertRaises(ValidationError): self.call(target='ps2-ee',strip_debug=True)
