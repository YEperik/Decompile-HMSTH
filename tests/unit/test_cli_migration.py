import ast
import contextlib
import hashlib
import io
import json
import os
from pathlib import Path
import subprocess
import signal
import sys
import tempfile
import time
import unittest
import tomllib
from unittest.mock import patch
from uuid import uuid4

from app.application.baselines import inspect_file
from app.application.run_history import latest_run
from app.cli import main
from app.domain.workspace.model import PathError
from app.infrastructure.persistence.store import Store
from tests.elf_fixture import edit, make_elf

ROOT = Path(__file__).resolve().parents[2]
NO_GUI = '''
import importlib.abc, runpy, sys
class BlockGUI(importlib.abc.MetaPathFinder):
    def find_spec(self, fullname, path=None, target=None):
        if fullname.split('.')[0] in ('tkinter','_tkinter','PySide6','PyQt6') or fullname.startswith('app.ui'):
            raise ModuleNotFoundError('GUI import prohibited during CLI test: '+fullname)
sys.meta_path.insert(0, BlockGUI())
sys.argv = ['app'] + sys.argv[1:]
runpy.run_module('app', run_name='__main__')
'''


class CLIMigrationTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.parent = Path(self.tmp.name)
        self.input = self.parent/'input 日本 spasi.elf'
        self.input.write_bytes(make_elf())
        self.store = Store(self.parent/'workspace spasi')
        self.store.create('Migration')

    def cli(self, *args):
        return subprocess.run([sys.executable,'-c',NO_GUI,*map(str,args)],cwd=ROOT,
                              capture_output=True,text=True,timeout=10)

    def test_help_root_and_subcommands_without_gui(self):
        for args in [('--help',),('inspect-elf','--help'),('baseline','--help'),('run-history','--help')]:
            with self.subTest(args=args):
                r=self.cli(*args);self.assertEqual(r.returncode,0,r.stderr)
                self.assertIn('usage:',r.stdout)

    def test_inspect_json_equals_existing_service_and_writes_nothing(self):
        before={str(p.relative_to(self.parent)):hashlib.sha256(p.read_bytes()).hexdigest()
                for p in self.parent.rglob('*') if p.is_file()}
        r=self.cli('inspect-elf',self.input,'--format','json')
        self.assertEqual(r.returncode,0,r.stderr)
        self.assertEqual(json.loads(r.stdout),inspect_file(self.input))
        after={str(p.relative_to(self.parent)):hashlib.sha256(p.read_bytes()).hexdigest()
               for p in self.parent.rglob('*') if p.is_file()}
        self.assertEqual(before,after)

    def test_inspect_text_summary(self):
        r=self.cli('inspect-elf',self.input)
        self.assertEqual(r.returncode,0,r.stderr)
        self.assertIn('Entry: 0x00100000',r.stdout)
        self.assertIn('UNKNOWN (UNRESOLVED)',r.stdout)
        self.assertIn(hashlib.sha256(make_elf()).hexdigest(),r.stdout)

    def test_missing_args_command_and_bad_format(self):
        for args in [('inspect-elf',),('inspect-elf',str(self.input),'--format','xml'),('not-a-command',)]:
            with self.subTest(args=args):
                r=self.cli(*args);self.assertEqual(r.returncode,2)
                self.assertIn('usage:',r.stderr)

    def test_invalid_empty_truncated_corrupt_unsupported_and_missing_paths(self):
        samples=[(b'','unsupported_elf'),(b'not an ELF','unsupported_elf'),
                 (make_elf()[:20],'invalid_elf'),(edit(make_elf(),28,0xfffffff0),'invalid_elf'),
                 (edit(make_elf(),18,62,'H'),'unsupported_elf')]
        for data,expected in samples:
            with self.subTest(expected=expected,size=len(data)):
                self.input.write_bytes(data)
                r=self.cli('inspect-elf',self.input,'--format','json')
                self.assertEqual(r.returncode,2,r.stderr)
                self.assertEqual(json.loads(r.stderr)['error'],expected)
                self.assertEqual(r.stdout,'')
                self.assertEqual(self.input.read_bytes(),data)
        r=self.cli('inspect-elf',self.parent/'absent.elf')
        self.assertEqual(r.returncode,2)
        self.assertIn('Path tidak ditemukan',json.loads(r.stderr)['hint'])

    def test_unreadable_input_has_actionable_error_controlled_fault(self):
        output,errors=io.StringIO(),io.StringIO()
        with patch.object(Path,'open',side_effect=PermissionError('read denied')):
            with contextlib.redirect_stdout(output),contextlib.redirect_stderr(errors):
                code=main(['inspect-elf',str(self.input)])
        self.assertEqual(code,2)
        self.assertEqual(output.getvalue(),'')
        self.assertIn('izin baca',json.loads(errors.getvalue())['hint'])

    def test_full_workspace_baseline_flow_without_gui(self):
        r=self.cli('add-input',self.store.root,self.input)
        self.assertEqual(r.returncode,0,r.stderr)
        iid=json.loads(r.stdout)['inputs'][0]['id']
        r=self.cli('baseline',self.store.root,'--input-id',iid)
        self.assertEqual(r.returncode,0,r.stderr)
        first=json.loads(r.stdout)
        second=json.loads(self.cli('baseline',self.store.root,'--input-id',iid).stdout)
        self.assertEqual(first['baseline'],second['baseline'])
        self.assertEqual(self.input.read_bytes(),make_elf())
        self.assertEqual(self.cli('open',self.store.root).returncode,0)
        self.assertEqual(self.cli('create',self.store.root,'--name','exists').returncode,2)

    def test_history_empty_is_read_only_and_json(self):
        self.assertEqual(latest_run(self.store),{'found':False,'run_id':None,'history':'Belum ada run nyata.'})
        r=self.cli('run-history',self.store.root)
        self.assertEqual(r.returncode,0,r.stderr)
        self.assertFalse(json.loads(r.stdout)['found'])
        self.assertFalse((self.store.root/'runs').exists())

    def test_history_cli_matches_service_and_artifact_format(self):
        run_id=str(uuid4());folder=self.store.root/'runs'/run_id;folder.mkdir(parents=True)
        artifacts={'result.json':json.dumps({'run_id':run_id,'status':'succeeded'}),
                   'events.jsonl':'{"event":"finished"}\n','stdout.txt':'actual bytes\n','stderr.txt':''}
        for name,value in artifacts.items():(folder/name).write_text(value)
        expected='\n\n'.join(name+'\n'+value for name,value in artifacts.items())
        actual=latest_run(self.store)
        self.assertEqual(actual['history'],expected)
        r=self.cli('run-history',self.store.root)
        self.assertEqual(json.loads(r.stdout),actual)

    def test_history_latest_selection_and_non_uuid_ignored(self):
        runs=self.store.root/'runs';runs.mkdir()
        for n,mtime in [('not-a-uuid',99999),(str(uuid4()),100),(str(uuid4()),200)]:
            folder=runs/n;folder.mkdir();p=folder/'result.json';p.write_text(n);os.utime(p,ns=(mtime,mtime))
            if mtime==200:expected=n
        self.assertEqual(latest_run(self.store)['run_id'],expected)

    def test_history_symlink_escape_refused(self):
        try:(self.store.root/'runs').symlink_to(self.parent,target_is_directory=True)
        except OSError:self.skipTest('symlink privilege unavailable')
        with self.assertRaises(PathError):latest_run(self.store)

    def test_missing_external_tool_is_not_faked(self):
        r=self.cli('run-tool',self.store.root,'--argv-json',json.dumps(['/nonexistent/tool']))
        self.assertEqual(r.returncode,2)
        self.assertIn(json.loads(r.stderr)['error'],('unsafe_path','unsupported_platform'))
        self.assertFalse((self.store.root/'runs').exists())

    @unittest.skipUnless(os.name == 'posix', 'Native Windows runner remains unsupported')
    def test_terminal_ctrl_c_cancels_real_child_and_saves_result(self):
        proc=subprocess.Popen([sys.executable,'-m','app','run-tool',str(self.store.root),
                               '--argv-json',json.dumps([sys.executable,'-c','import time; time.sleep(30)']),'--timeout','40'],cwd=ROOT,
                              stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True)
        running=None
        try:
            deadline=time.monotonic()+5
            while time.monotonic()<deadline and proc.poll() is None:
                for path in (self.store.root/'runs').glob('*/result.json'):
                    data=json.loads(path.read_text())
                    if data['status']=='running':
                        running=data
                        break
                if running:break
                time.sleep(0.01)
            self.assertIsNotNone(running,'CLI did not publish a running child')
            proc.send_signal(signal.SIGINT)
            stdout,stderr=proc.communicate(timeout=12)
            self.assertEqual(proc.returncode,130,stderr)
            result=json.loads(stdout)
            self.assertEqual(result['status'],'cancelled')
            saved=json.loads((Path(result['artifact_dir'])/'result.json').read_text())
            self.assertEqual(saved['status'],'cancelled')
            self.assertIsNotNone(saved['exit_code'])
            with self.assertRaises(ProcessLookupError):os.kill(running['pid'],0)
        finally:
            if proc.poll() is None:
                proc.kill()
            proc.communicate(timeout=5)
            if running:
                try:os.killpg(running['pid'],signal.SIGKILL)
                except ProcessLookupError:pass

    def test_production_has_no_gui_and_package_entrypoint_is_intact(self):
        self.assertFalse((ROOT/'app/ui').exists())
        blocked=('tkinter','_tkinter','PySide6','PyQt6','app.ui')
        for path in (ROOT/'app').rglob('*.py'):
            for node in ast.walk(ast.parse(path.read_text())):
                names=([n.name for n in node.names] if isinstance(node,ast.Import)
                       else [node.module or ''] if isinstance(node,ast.ImportFrom) else [])
                for name in names:
                    self.assertFalse(any(name==b or name.startswith(b+'.') for b in blocked),path)
        metadata=tomllib.loads((ROOT/'pyproject.toml').read_text())
        self.assertEqual(metadata['project']['scripts'],{'ps2-workbench':'app.cli:main'})
