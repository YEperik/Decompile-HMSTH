import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import time
import unittest
from unittest.mock import patch
from uuid import uuid4

from tests.support.task_controller import TaskController
from app.domain.workspace.model import ConflictError, PathError, ValidationError
from app.infrastructure.persistence.store import Store
from app.infrastructure.process_runner.runner import Command, recover_interrupted, run


@unittest.skipUnless(os.name == 'posix', 'Runner is explicitly POSIX-only in stage 1B')
class RunnerTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.store = Store(Path(self.tmp.name) / 'Runner 日本')
        self.store.create('Test')

    def command(self, source, **kwargs):
        return Command((sys.executable, '-u', '-c', source), **kwargs)

    def output(self, result, name):
        return (Path(result['artifact_dir']) / name).read_text()

    def test_real_success_streams_logs_and_hashes(self):
        result = run(self.store, self.command("import sys; print('hello 日本'); print('warning',file=sys.stderr)"))
        self.assertEqual(result['status'], 'succeeded')
        self.assertEqual(result['exit_code'], 0)
        self.assertIn('hello 日本', self.output(result, 'stdout.txt'))
        self.assertIn('warning', self.output(result, 'stderr.txt'))
        import hashlib
        self.assertEqual(result['output_hashes']['stdout.txt'], hashlib.sha256(self.output(result, 'stdout.txt').encode()).hexdigest())
        events = [json.loads(line) for line in self.output(result, 'events.jsonl').splitlines()]
        self.assertEqual([e['event'] for e in events], ['queued', 'running', 'finished'])
        self.assertTrue(all(e['run_id'] == result['run_id'] for e in events))
        self.assertEqual(json.loads(self.output(result, 'result.json'))['status'], 'succeeded')

    def test_nonzero_real_exit(self):
        result = run(self.store, self.command("import sys; sys.exit(7)"))
        self.assertEqual((result['status'], result['exit_code'], result['reason']), ('failed', 7, 'exit_nonzero'))

    def test_missing_tool_and_invalid_request_create_no_runs(self):
        for command in [Command(('/nonexistent/tool',)), self.command('pass', timeout=float('nan')),
                        self.command('pass', timeout=0), self.command('pass', max_output_bytes=0),
                        Command((sys.executable, '\ud800'))]:
            with self.subTest(command=command), self.assertRaises((PathError, ValidationError)):
                run(self.store, command)
        self.assertFalse((self.store.root/'runs').exists())

    def test_tool_in_workspace_is_not_executed(self):
        script = self.store.root/'inputs/tool'
        script.write_text('#!/bin/sh\necho bad\n')
        script.chmod(0o755)
        with self.assertRaises(PathError):
            run(self.store, Command((str(script),)))

    def test_spawn_exec_format_error_logged(self):
        script = Path(self.tmp.name)/'bad-tool'
        script.write_text('not an executable format')
        script.chmod(0o755)
        result = run(self.store, Command((str(script),)))
        self.assertEqual((result['status'],result['reason']), ('failed','process_error'))
        self.assertIsNone(result['exit_code'])

    def test_timeout_kills_term_ignoring_child(self):
        result = run(self.store, self.command("import signal,time; signal.signal(signal.SIGTERM,signal.SIG_IGN); print('ready',flush=True); time.sleep(60)", timeout=0.2))
        self.assertEqual(result['status'], 'timed_out')
        self.assertLess(result['duration_seconds'], 4)
        self.assertIsNotNone(result['exit_code'])

    def test_cancel_running_and_prestart(self):
        cancel = threading.Event()
        result = run(self.store, self.command('import time; time.sleep(60)'), cancel,
                     lambda e: cancel.set() if e['event']=='running' else None)
        self.assertEqual(result['status'], 'cancelled')
        self.assertIsNotNone(result['pid'])
        result = run(self.store, self.command("print('must not run')"), cancel)
        self.assertEqual(result['reason'], 'cancelled_before_start')
        self.assertIsNone(result['pid'])
        self.assertEqual(self.output(result, 'stdout.txt'), '')

    def test_both_streams_large_output_bounded_without_deadlock(self):
        result = run(self.store, self.command("import os;\nfor i in range(10000):\n os.write(1,b'a'*1024); os.write(2,b'b'*1024)\n", max_output_bytes=8192))
        self.assertEqual((result['status'],result['reason']), ('failed','output_limit'))
        self.assertLessEqual(len(self.output(result,'stdout.txt'))+len(self.output(result,'stderr.txt')),8192)

    def test_invalid_utf8_is_replaced_not_crash(self):
        result = run(self.store, self.command("import os;os.write(1,bytes([255,254]))"))
        self.assertEqual(result['status'], 'succeeded')
        self.assertEqual(self.output(result,'stdout.txt'), '\ufffd\ufffd')

    def test_redaction_across_stream_chunks_and_argv(self):
        secret = 'PRIVATE-KEY-VALUE-123'
        source = "import os,time; s=os.environ['RUNNER_TEST_SECRET'].encode();os.write(1,s[:12]);time.sleep(.05);os.write(1,s[12:]);print(' token=abc123')"
        request = Command((sys.executable,'-u','-c',source,'--token',secret), secrets=(secret,))
        with patch.dict(os.environ, {'RUNNER_TEST_SECRET':secret}):
            result = run(self.store,request)
        for p in Path(result['artifact_dir']).iterdir():
            if p.is_file():
                self.assertNotIn(secret.encode(),p.read_bytes(),p.name)
        self.assertIn('[REDACTED]', self.output(result,'stdout.txt'))
        self.assertNotIn('abc123', self.output(result,'stdout.txt'))

    def test_callback_error_does_not_break_process(self):
        def bad(event): raise ValueError('view failed')
        result = run(self.store,self.command("print('ok')"),on_event=bad)
        self.assertEqual(result['status'],'succeeded')
        self.assertIn('observer_error',self.output(result,'events.jsonl'))

    def test_descendant_cleanup_after_parent_exit(self):
        marker=Path(self.tmp.name)/'escaped-marker'
        child=f"import time,pathlib;time.sleep(1);pathlib.Path({str(marker)!r}).write_text('should not exist')"
        source=f"import subprocess,sys;subprocess.Popen([sys.executable,'-c',{child!r}]);print('parent exits')"
        result=run(self.store,self.command(source))
        self.assertEqual(result['status'],'succeeded')
        time.sleep(1.1)
        self.assertFalse(marker.exists())

    def test_concurrency_and_recovery_do_not_touch_active_job(self):
        checked=[]
        def active(event):
            if event['event']=='running':
                with self.assertRaises(ConflictError):
                    run(self.store,self.command('pass'))
                self.assertEqual(recover_interrupted(self.store),[])
                checked.append(True)
        result=run(self.store,self.command('pass'),on_event=active)
        self.assertEqual(result['status'],'succeeded')
        self.assertTrue(checked)  # callback exceptions would otherwise be contained by runner

    def test_recovery_abandoned_job_and_malformed_result(self):
        runs=self.store.root/'runs';runs.mkdir()
        rid=str(uuid4());folder=runs/rid;folder.mkdir()
        (folder/'result.json').write_text(json.dumps({'run_id':rid,'status':'running','pid':999999999}))
        bad=str(uuid4());other=runs/bad;other.mkdir();(other/'result.json').write_text('{bad')
        with patch('app.infrastructure.process_runner.runner.os.killpg') as kill:
            result=recover_interrupted(self.store)
        kill.assert_not_called()
        self.assertEqual({x['status'] for x in result},{'failed','unreadable'})
        self.assertEqual(json.loads((folder/'result.json').read_text())['reason'],'interrupted')

    def test_symlink_runs_directory_refused(self):
        (self.store.root/'runs').symlink_to(self.tmp.name,target_is_directory=True)
        with self.assertRaises(PathError):run(self.store,self.command('pass'))

    def test_disk_failure_after_spawn_still_cleans_process(self):
        from app.infrastructure.process_runner import runner
        original=runner._write
        pid=[]
        def fail(store,name,data):
            if name=='result.json' and data.get('status')=='running':
                pid.append(data['pid'])
                raise OSError('injected disk failure')
            return original(store,name,data)
        with patch.object(runner,'_write',side_effect=fail):
            result=run(self.store,self.command('import time;time.sleep(60)'))
        self.assertEqual(result['status'],'failed')
        with self.assertRaises(ProcessLookupError):os.kill(pid[0],0)


class ControllerTests(unittest.TestCase):
    def test_ui_task_result_queue_cancel_and_busy(self):
        tasks=TaskController()
        entered=threading.Event()
        def job(cancel,emit):
            emit({'event':'actual worker'})
            entered.set()
            cancel.wait(3)
            return {'cancelled':cancel.is_set()}
        tasks.submit(job)
        self.assertTrue(entered.wait(2))
        with self.assertRaises(ConflictError):tasks.submit(job)
        tasks.cancel();tasks.thread.join(3)
        events=tasks.poll()
        self.assertIn(('done',{'cancelled':True}),events)
        self.assertFalse(tasks.busy)

    def test_ui_task_failure_is_visible(self):
        tasks=TaskController()
        def fail(cancel,emit):raise ValueError('visible failure')
        tasks.submit(fail);tasks.thread.join(2)
        events=tasks.poll()
        self.assertTrue(any(k=='error' and v['message']=='visible failure' for k,v in events))
        self.assertFalse(tasks.busy)
