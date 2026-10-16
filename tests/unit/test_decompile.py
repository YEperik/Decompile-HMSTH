import hashlib
import json
from pathlib import Path
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_ghidra as fixture
from app.application.decompile import decompile_function,validate_export,_inspect_file,analysis_contract,validate_analysis_log
from app.application.workspaces import rename
from app.domain.binary.elf import Cancelled
from app.domain.workspace.model import ValidationError,ConflictError

class DecompileTests(unittest.TestCase):
    def setUp(self):
        fixture.GhidraTests.setUp(self)
        self.ldefs.write_text(self.ldefs.read_text().replace('MIPS:LE:32:test','r5900:LE:32:default').replace('processor="MIPS"','processor="MIPS-R5900"').replace('variant="test"','variant="PS2"'))
        self.jdk=self.root/'jdk';(self.jdk/'bin').mkdir(parents=True)
        java=self.jdk/'bin/java';java.write_text('FIXTURE_NOT_EXECUTED');java.chmod(0o700)
        self.native=self.home/'GPL/DemanglerGnu/os/linux_x86_64';self.native.mkdir(parents=True)
        for name in ('demangler_gnu_v2_24','demangler_gnu_v2_41'):
            p=self.native/name;p.write_text('FIXTURE_NOT_EXECUTED');p.chmod(0o700)
    def call(self,**kw):
        return decompile_function(self.store,self.iid,'3:2',str(self.home),str(self.jdk),**kw)
    def fake_export(self,store,command,cancel):
        args=command.argv;i=args.index('-postScript');start=int(args[i+2],16);size=int(args[i+3]);out=Path(args[i+4]);out.mkdir()
        payload=self.source.read_bytes()[0x108:0x110]
        rows=[{'address':hex(start+n),'bytes':payload[n:n+4].hex(),'assembly':'FIXTURE','pcode_ops':0} for n in range(0,size,4)]
        result={'analysis':analysis_contract(args[i+6]),'status':'DECOMPILED_UNVERIFIED','language':'r5900:LE:32:default','compiler_spec':'default','ghidra_version':'TEST_ONLY','java_version':'21-test','start':hex(start),'size':size,'mapped_bytes_sha256':args[i+5],'instructions':rows,'pcode_origins_within_selected_range':True,'recompiled':False,'semantics_verified':False}
        (out/'result.json').write_text(json.dumps(result));(out/'decompiled.c').write_text('/* TEST DOUBLE, NOT A DECOMPILER RESULT */')
        log=out.parent/'fake-run';log.mkdir();(log/'stdout.txt').write_text('INFO PS2_WORKBENCH_PROFILE_CONFIGURED\n')
        return {'status':'succeeded','artifact_dir':str(log)}
    def test_adapter_contract_with_test_double(self):
        original=self.source.read_bytes()
        with patch('app.application.decompile.run',side_effect=self.fake_export) as runner:
            result=self.call()
        self.assertEqual(result['status'],'DECOMPILED_UNVERIFIED');self.assertEqual(result['instructions'],2)
        self.assertEqual(self.source.read_bytes(),original);self.assertFalse(result['semantics_verified'])
        self.assertTrue((Path(result['artifact_dir'])/'receipt.json').is_file())
        argv=runner.call_args.args[1].argv
        self.assertIn('-noanalysis',argv);self.assertIn('r5900:LE:32:default',argv)
        self.assertNotIn(str(self.source),argv)
    def test_generic_processor_rejected(self):
        self.ldefs.write_text(self.ldefs.read_text().replace('MIPS-R5900','MIPS'))
        with patch('app.application.decompile.run',side_effect=AssertionError('must not run')):
            with self.assertRaises(ValidationError):self.call()
    def test_recommended_profile_runs_analysis(self):
        with patch('app.application.decompile.run',side_effect=self.fake_export) as runner:
            result=self.call(analysis='recommended',timeout=600)
        argv=runner.call_args.args[1].argv
        self.assertNotIn('-noanalysis',argv)
        self.assertEqual(argv[argv.index('-preScript')+1],'ConfigureR5900.java')
        self.assertEqual(argv[argv.index('-analysisTimeoutPerFile')+1],'450')
        self.assertEqual(result['analysis'],analysis_contract('recommended'))
        request=json.loads((Path(result['artifact_dir'])/'request.json').read_text())
        self.assertEqual(request['analysis'],result['analysis'])
        self.assertEqual(len(request['profile_script_sha256']),64)
    def test_wrong_or_incomplete_analysis_rejected(self):
        for value in (analysis_contract('bounded'),
                      {'profile':'recommended','auto_analysis_completed':False,'settings':{}},
                      {'profile':'recommended','auto_analysis_completed':True,'settings':{}}):
            def fake(store,command,cancel):
                result=self.fake_export(store,command,cancel)
                out=Path(command.argv[command.argv.index('-postScript')+4])
                p=out/'result.json';data=json.loads(p.read_text());data['analysis']=value
                p.write_text(json.dumps(data));return result
            with patch('app.application.decompile.run',side_effect=fake):
                with self.assertRaises(ValidationError):self.call(analysis='recommended')
    def test_invalid_profile_creates_no_job(self):
        with self.assertRaises(ValidationError):self.call(analysis='generic-mips')
        self.assertFalse((self.store.root/'decompilations').exists())
    def test_demangler_not_executable_rejected_before_run(self):
        (self.native/'demangler_gnu_v2_24').chmod(0o600)
        with patch('app.application.decompile.run',side_effect=AssertionError('must not run')):
            with self.assertRaises(ValidationError):self.call(analysis='recommended')
        self.assertFalse((self.store.root/'decompilations').exists())
    def test_missing_assets_and_jdk(self):
        (self.jdk/'bin/java').unlink()
        with self.assertRaises(ValidationError):self.call()
        self.assertFalse((self.store.root/'decompilations').exists())
    def test_zero_exit_without_output_not_success(self):
        with patch('app.application.decompile.run',return_value={'status':'succeeded','artifact_dir':'TEST_RUN'}):
            with self.assertRaises(ValidationError):self.call()
    def test_timeout_not_success(self):
        with patch('app.application.decompile.run',return_value={'status':'timed_out','artifact_dir':'TEST_RUN'}):
            self.assertEqual(self.call()['status'],'GHIDRA_RUN_FAILED')
    def test_export_mismatch_rejected(self):
        for field,value in (('language','MIPS:LE:32:default'),('size',4),('mapped_bytes_sha256','0'*64),('ghidra_version','OTHER'),('pcode_origins_within_selected_range',False)):
            def fake(store,command,cancel):
                result=self.fake_export(store,command,cancel);out=Path(command.argv[command.argv.index('-postScript')+4]);p=out/'result.json';data=json.loads(p.read_text());data[field]=value;p.write_text(json.dumps(data));return result
            with patch('app.application.decompile.run',side_effect=fake):
                with self.assertRaises(ValidationError):self.call()
    def test_instruction_bytes_rejected(self):
        def fake(store,command,cancel):
            result=self.fake_export(store,command,cancel);out=Path(command.argv[command.argv.index('-postScript')+4]);p=out/'result.json';data=json.loads(p.read_text());data['instructions'][0]['bytes']='00000000';p.write_text(json.dumps(data));return result
        with patch('app.application.decompile.run',side_effect=fake):
            with self.assertRaises(ValidationError):self.call()
    def test_changed_source_and_manifest(self):
        original=self.source.read_bytes();self.source.write_bytes(original+b'x')
        with self.assertRaises(ConflictError):self.call()
        self.source.write_bytes(original)
        def change(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.decompile._inspect_file',side_effect=change):
            with self.assertRaises(ConflictError):self.call()
    def test_input_snapshot_change_rejected(self):
        def fake(store,command,cancel):
            result=self.fake_export(store,command,cancel);p=Path(command.argv[command.argv.index('-import')+1]);p.write_bytes(b'changed');return result
        with patch('app.application.decompile.run',side_effect=fake):
            with self.assertRaises(ConflictError):self.call()
    def test_cancel_and_timeout_validation(self):
        token=threading.Event();token.set()
        with self.assertRaises(Cancelled):self.call(cancel=token)
        with self.assertRaises(ValidationError):self.call(timeout=0)
        self.assertFalse((self.store.root/'decompilations').exists())

    def test_analyzer_errors_cannot_produce_success_receipt(self):
        for content in ('INFO ordinary startup', 'INFO PS2_WORKBENCH_PROFILE_CONFIGURED\nERROR analyzer failed'):
            def fake(store,command,cancel):
                result=self.fake_export(store,command,cancel)
                (Path(result['artifact_dir'])/'stdout.txt').write_text(content)
                return result
            with patch('app.application.decompile.run',side_effect=fake):
                with self.assertRaises(ValidationError):self.call(analysis='recommended')
        self.assertFalse(list((self.store.root/'decompilations').glob('*/receipt.json')))
