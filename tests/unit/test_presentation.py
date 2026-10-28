import contextlib
import io
import json
from pathlib import Path
import unittest
from unittest.mock import patch
from app.cli import main
from app.presentation import compact,root_help

class PresentationTests(unittest.TestCase):
    def run_cli(self,args,tty=False):
        output=io.StringIO();errors=io.StringIO()
        with contextlib.redirect_stdout(output),contextlib.redirect_stderr(errors),patch.object(output,'isatty',return_value=tty):
            try:code=main(args)
            except SystemExit as exc:code=exc.code
        return code,output.getvalue(),errors.getvalue()
    def test_default_and_help_are_short(self):
        for args in ([],['--help'],['-h']):
            code,out,err=self.run_cli(args)
            self.assertEqual(code,0);self.assertLessEqual(len(out.splitlines()),15);self.assertEqual(err,'')
    def test_advertised_commands_exist(self):
        for line in root_help().splitlines():
            if ' : ' in line:
                for command in line.split(' : ',1)[1].split(', '):
                    self.assertEqual(self.run_cli([command,'--help'])[0],0,command)
    def test_all_help_retains_advanced_commands(self):
        code,out,err=self.run_cli(['--help-all'])
        self.assertEqual(code,0);self.assertIn('plan-build',out);self.assertNotIn('demo-run',out)
    def test_demo_removed_and_error_short(self):
        code,out,err=self.run_cli(['demo-run'])
        self.assertEqual(code,2);self.assertNotIn('choose from',err);self.assertLess(len(err),400)
        self.assertFalse((Path(__file__).resolve().parents[2]/'app/application/tasks.py').exists())
    def test_piped_json_and_explicit_json_identical(self):
        a=self.run_cli(['tools-detect']);b=self.run_cli(['--json','tools-detect'],tty=True)
        self.assertEqual(a[0],0);self.assertEqual(json.loads(a[1]),json.loads(b[1]))
    def test_terminal_compact_and_explicit_text(self):
        with patch('app.application.toolchains.detect',return_value={'status':'OK','limitations':['Long explanation']*40,'items':list(range(100))}):
            for args,tty in ((['tools-detect'],True),(['--text','tools-detect'],False)):
                code,out,err=self.run_cli(args,tty)
                self.assertEqual(code,0);self.assertIn('status: OK',out);self.assertNotIn('Long explanation',out);self.assertLessEqual(len(out.splitlines()),19)
    def test_compact_preserves_status_and_controls(self):
        output=compact({'items':list(range(1000)),'status':'FAILED','message':'bad\x1b[2J\nname'})
        self.assertIn('status: FAILED',output);self.assertNotIn('\x1b',output);self.assertIn('Full details',output)
    def test_incompatible_output_flags_rejected(self):
        self.assertEqual(self.run_cli(['--json','--text','tools-detect'])[0],2)

    def test_section_summary_keeps_result_and_warnings(self):
        result=compact({'status':'VERIFIED_SOURCE_BYTES','bundle_dir':'out','metadata':{
            'section':{'index':5,'name':'main'},'payload_size':3155840,'storage':'FILE_BYTES',
            'elf_warnings':['Check mapping'],'chunks':[{}]*100}})
        self.assertIn('section: main',result);self.assertIn('bytes: 3155840',result)
        self.assertIn('Check mapping',result);self.assertNotIn('chunks',result)
        self.assertLessEqual(len(result.splitlines()),9)
