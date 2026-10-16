import json
import os
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

from app.application.ghidra import check_install, create_plan
from app.application.workspaces import add_input
from app.domain.workspace.model import ValidationError, ConflictError
from app.infrastructure.persistence.store import Store
from tests.symbol_fixture import make_symbols


class GhidraTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.root=Path(self.tmp.name);self.home=self.root/'ghidra fixture'
        (self.home/'Ghidra').mkdir(parents=True);(self.home/'support').mkdir()
        (self.home/'Ghidra/application.properties').write_text('application.version=TEST_ONLY\napplication.java.min=21\n')
        name='analyzeHeadless.bat' if os.name=='nt' else 'analyzeHeadless'
        (self.home/'support'/name).write_text('TEST FIXTURE ONLY; never executed')
        (self.home/'support'/name).chmod(0o700)
        self.ldefs=self.home/'Ghidra/Processors/MIPS/data/languages/mips.ldefs'
        self.ldefs.parent.mkdir(parents=True)
        self.ldefs.write_text('<language_definitions><language id="MIPS:LE:32:test" processor="MIPS" endian="little" size="32" variant="test" slafile="test.sla" processorspec="test.pspec"><compiler id="default" spec="test.cspec"/></language></language_definitions>')
        for asset in ('test.sla','test.pspec','test.cspec'):
            (self.ldefs.parent/asset).write_bytes(b'TEST_ONLY_NOT_VALID_GHIDRA_DATA')
        self.store=Store(self.root/'workspace');self.store.create('Ghidra tests')
        self.source=self.root/'input.elf';self.source.write_bytes(make_symbols())
        add_input(self.store,str(self.source));self.iid=self.store.load().data['inputs'][0]['id']

    def plan(self,**kwargs):
        args=dict(store=self.store,input_id=self.iid,home=str(self.home),language='MIPS:LE:32:test',cspec='default');args.update(kwargs)
        return create_plan(**args)

    def test_missing_installation_is_not_success(self):
        with patch.dict(os.environ,{},clear=True),patch('app.application.ghidra.shutil.which',return_value=None):
            result=check_install()
        self.assertEqual(result['status'],'NOT_FOUND');self.assertFalse(result['executed'])

    def test_incomplete_installation(self):
        self.assertEqual(check_install(str(self.root))['status'],'INCOMPLETE')

    def test_catalog_reports_declarations_not_runtime_verification(self):
        result=check_install(str(self.home))
        self.assertEqual(result['declared_version'],'TEST_ONLY');self.assertFalse(result['runtime_verified'])
        self.assertEqual(result['languages'][0]['compiler_specs'],['default'])

    def test_plan_is_saved_without_execution_or_overwrite_flags(self):
        with patch('subprocess.Popen',side_effect=AssertionError('must not execute')):
            result=self.plan()
        self.assertEqual(result['status'],'PLAN_ONLY');self.assertFalse(result['executed'])
        self.assertIn('-noanalysis',result['argv']);self.assertNotIn('-overwrite',result['argv'])
        self.assertEqual(json.loads(Path(result['plan_path']).read_text()),result)
        self.assertFalse((self.store.root/'runs').exists())
        self.assertNotEqual(result['id'],self.plan()['id'])

    def test_wrong_language_cspec_or_endian_rejected(self):
        for args in ({'language':'guessed-r5900'},{'cspec':'missing'}):
            with self.assertRaises(ValidationError):self.plan(**args)
        self.ldefs.write_text(self.ldefs.read_text().replace('little','big'))
        with self.assertRaises(ValidationError):self.plan()
        self.assertFalse((self.store.root/'ghidra').exists())

    def test_corrupt_xml_and_entities_rejected(self):
        for raw in ('<bad','<!DOCTYPE x><language_definitions/>'):
            self.ldefs.write_text(raw)
            with self.assertRaises(ValidationError):check_install(str(self.home))

    def test_changed_registered_input_rejected(self):
        self.source.write_bytes(make_symbols(1))
        with self.assertRaises(ConflictError):self.plan()
        self.assertFalse((self.store.root/'ghidra').exists())

    def test_duplicate_language_is_ambiguous(self):
        (self.ldefs.parent/'duplicate.ldefs').write_bytes(self.ldefs.read_bytes())
        with self.assertRaises(ValidationError):self.plan()

    def test_missing_assets_reported_and_plan_rejected(self):
        (self.ldefs.parent/'test.sla').unlink()
        result=check_install(str(self.home))
        self.assertEqual(result['languages'][0]['language_assets']['sla']['status'],'NOT_FOUND')
        with self.assertRaises(ValidationError):self.plan()
        self.assertFalse((self.store.root/'ghidra').exists())

    def test_traversal_asset_is_not_read(self):
        self.ldefs.write_text(self.ldefs.read_text().replace('test.sla','../../outside.sla'))
        result=check_install(str(self.home))
        self.assertEqual(result['languages'][0]['language_assets']['sla']['status'],'UNSAFE_REFERENCE')
        with self.assertRaises(ValidationError):self.plan()

    def test_r5900_extension_catalog_and_hashes(self):
        ext=self.home/'Ghidra/Extensions/PS2/data/languages';ext.mkdir(parents=True)
        text=self.ldefs.read_text().replace('MIPS:LE:32:test','r5900:LE:32:fixture').replace('processor="MIPS"','processor="MIPS-R5900"')
        (ext/'ps2.ldefs').write_text(text)
        for asset in ('test.sla','test.pspec','test.cspec'):(ext/asset).write_bytes(b'FIXTURE')
        report=check_install(str(self.home));self.assertEqual(len(report['languages']),2)
        result=self.plan(language='r5900:LE:32:fixture')
        self.assertEqual(result['selected_language']['processor'],'MIPS-R5900')
        self.assertEqual(len(result['selected_language']['language_assets']['sla']['sha256']),64)
        self.assertFalse(result['installation']['runtime_verified'])

    def test_external_catalog_auditable_but_not_assumed_installed(self):
        ext=self.root/'external';ext.mkdir()
        (ext/'ps2.ldefs').write_text(self.ldefs.read_text().replace('MIPS:LE:32:test','MIPS:LE:32:external'))
        for asset in ('test.sla','test.pspec','test.cspec'):(ext/asset).write_bytes(b'FIXTURE')
        report=check_install(str(self.home),[str(ext)])
        self.assertEqual(len(report['languages']),2)
        with self.assertRaises(ValidationError):
            self.plan(language='MIPS:LE:32:external',language_dirs=[str(ext)])

    def test_duplicate_cspec_and_empty_asset_rejected(self):
        text=self.ldefs.read_text()
        self.ldefs.write_text(text.replace('</language>','<compiler id="default" spec="test.cspec"/></language>'))
        with self.assertRaises(ValidationError):self.plan()
        self.ldefs.write_text(text);(self.ldefs.parent/'test.cspec').write_bytes(b'')
        with self.assertRaises(ValidationError):self.plan()

    @unittest.skipUnless(os.name=='posix','POSIX executable mode')
    def test_non_executable_launcher_rejected(self):
        (self.home/'support/analyzeHeadless').chmod(0o600)
        with self.assertRaises(ValidationError):self.plan()
