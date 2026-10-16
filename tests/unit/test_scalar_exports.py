import copy
import hashlib
import json
from pathlib import Path
import unittest
from unittest.mock import patch

from app.application.decompile import SCALAR_SIZES
from app.application.export_checks import storage_header, STORAGE_TYPES, native_scalar_probe
from app.domain.workspace.model import ConflictError, ValidationError
from tests.unit import test_export_checks as fixture


class ScalarExportTests(unittest.TestCase):
    def setUp(self):
        self.fx = fixture.ExportCheckTests()
        self.fx.setUp()
        self.addCleanup(self.fx.doCleanups)
        path = self.fx.job / 'export/result.json'
        result = json.loads(path.read_text())
        result.update(export_schema=2, scalar_sizes=dict(SCALAR_SIZES), pcode_userop_counts={'_vmul': 1})
        for row in result['instructions']:
            row['userops'] = []
        result['instructions'][0]['userops'] = [{'name': '_vmul', 'inputs': [
            {'space': 'register', 'offset': '1000', 'size': 16}],
            'output': {'space': 'register', 'offset': '1010', 'size': 16}}]
        self.result = result
        self.write(result)
        probe = patch('app.application.export_checks.native_scalar_probe', return_value={
            'scalar_widths_match': False, 'abi_verified': False, 'mismatches': {
                'long': {'compiler': 4, 'ghidra': 8}}})
        probe.start(); self.addCleanup(probe.stop)

    def write(self, result, bind=True):
        raw = json.dumps(result).encode()
        (self.fx.job / 'export/result.json').write_bytes(raw)
        if bind:
            p = self.fx.job / 'receipt.json'; receipt = json.loads(p.read_text())
            receipt['export_sha256'] = hashlib.sha256(raw).hexdigest()
            p.write_text(json.dumps(receipt))

    def test_aliases_use_ghidra_widths_and_keep_source(self):
        original = (self.fx.job / 'export/decompiled.c').read_bytes()
        with patch('app.application.export_checks.run', return_value=self.fx.result()):
            result = self.fx.call(storage_types=True)
        header = (Path(result['report_dir']) / 'storage_types.h').read_bytes()
        self.assertIn(b'typedef uint32_t uint;', header)
        self.assertIn(b'typedef uint64_t ulong;', header)
        self.assertNotIn(b'unsigned long ulong', header)
        self.assertEqual(result['storage_header_sha256'], hashlib.sha256(header).hexdigest())
        self.assertEqual(result['pcode_userop_counts'], {'_vmul': 1})
        self.assertFalse(result['userop_semantics_implemented'])
        self.assertFalse(result['native_scalar_probe']['scalar_widths_match'])
        self.assertIn('compiler 4 byte, Ghidra 8 byte', result['warnings'][0])
        self.assertEqual((Path(result['report_dir']) / 'source.txt').read_bytes(), original)

    def test_legacy_export_retains_old_explicit_width_header(self):
        self.assertEqual(storage_header({}), STORAGE_TYPES)

    def test_invalid_scalar_sizes_rejected(self):
        for width in (4, True, '8'):
            result = copy.deepcopy(self.result); result['scalar_sizes']['long'] = width
            self.write(result)
            with patch('app.application.export_checks.run', side_effect=AssertionError('must not run')):
                with self.assertRaises(ValidationError): self.fx.call(storage_types=True)

    def test_invalid_userop_counts_or_operands_rejected(self):
        for change in ('count', 'size', 'offset', 'name'):
            result = copy.deepcopy(self.result)
            op = result['instructions'][0]['userops'][0]
            if change == 'count': result['pcode_userop_counts']['_vmul'] = 2
            elif change == 'size': op['inputs'][0]['size'] = 0
            elif change == 'offset': op['inputs'][0]['offset'] = '../bad'
            else: op['name'] = 'bad name'
            self.write(result)
            with self.assertRaises(ValidationError): self.fx.call()

    def test_changed_valid_metadata_rejected_by_receipt(self):
        result = copy.deepcopy(self.result)
        result['instructions'][0]['userops'][0]['inputs'][0]['offset'] = '2000'
        self.write(result, bind=False)
        with self.assertRaises(ConflictError): self.fx.call()

    def test_schema2_requires_metadata_hash(self):
        p = self.fx.job / 'receipt.json'; receipt = json.loads(p.read_text())
        del receipt['export_sha256']; p.write_text(json.dumps(receipt))
        with self.assertRaises(ValidationError): self.fx.call()

    def test_metadata_change_during_compile_rejected(self):
        def change(*args):
            (self.fx.job / 'export/result.json').write_text('{}')
            return self.fx.result()
        with patch('app.application.export_checks.run', side_effect=change):
            with self.assertRaises(ConflictError): self.fx.call()

    def test_native_probe_records_mismatch_without_claiming_abi(self):
        folder = self.fx.fx.store.root / 'probe'; folder.mkdir()
        output = folder / 'stdout.txt'
        macros = '#define __CHAR_BIT__ 8\n' + ''.join(
            f'#define __SIZEOF_{name.upper()}__ {size}\n'
            for name, size in {'short':2, 'int':4, 'long':4, 'long_long':8, 'pointer':4}.items())
        output.write_text(macros)
        with patch('app.application.export_checks.run', return_value={
                'status':'succeeded', 'artifact_dir':str(folder)}):
            result = native_scalar_probe(self.fx.fx.store, self.fx.compiler, folder, SCALAR_SIZES, 30, None)
        self.assertEqual(result['mismatches'], {'long': {'compiler': 4, 'ghidra': 8}})
        self.assertFalse(result['abi_verified'])
        output.write_text('#define __CHAR_BIT__ 16\n')
        with patch('app.application.export_checks.run', return_value={
                'status':'succeeded', 'artifact_dir':str(folder)}):
            with self.assertRaises(ValidationError):
                native_scalar_probe(self.fx.fx.store, self.fx.compiler, folder, SCALAR_SIZES, 30, None)
