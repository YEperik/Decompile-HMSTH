"""Bounded POSIX runner. No shell, no implicit version probing, no input execution."""
from dataclasses import dataclass, field
import hashlib
import json
import math
import os
from pathlib import Path
import selectors
import signal
import subprocess
import threading
import time
from uuid import UUID, uuid4

from app.domain.workspace.model import PathError, ValidationError, WorkspaceError, now
from app.infrastructure.logging.events import EventLog, Redactor
from app.infrastructure.persistence.store import Store, read_bytes


class UnsupportedPlatform(WorkspaceError):
    code = "unsupported_platform"


@dataclass(frozen=True)
class Command:
    argv: tuple[str, ...]
    timeout: float = 30.0
    max_output_bytes: int = 262144  # aggregate raw stdout + stderr cap
    secrets: tuple[str, ...] = field(default=(), repr=False)

    def validate(self):
        if os.name != 'posix':
            raise UnsupportedPlatform("Runner Tahap 1B hanya POSIX; penghentian pohon proses Windows belum diimplementasikan.")
        if not self.argv or len(self.argv) > 256 or any(not isinstance(a, str) or '\0' in a for a in self.argv):
            raise ValidationError("argv harus daftar string valid, maksimum 256 argumen.")
        if sum(len(a) for a in self.argv) > 32768:
            raise ValidationError("Command terlalu panjang.")
        try:
            for arg in self.argv:
                arg.encode('utf-8')
        except UnicodeError as exc:
            raise ValidationError('argv mengandung Unicode invalid.') from exc
        exe = Path(self.argv[0])
        if not exe.is_absolute() or not exe.is_file() or not os.access(exe, os.X_OK):
            raise PathError("Executable harus absolute, tersedia dan executable; tidak mencari melalui PATH.")
        if isinstance(self.timeout, bool) or not isinstance(self.timeout, (int, float)) \
                or not math.isfinite(self.timeout) or not 0 < self.timeout <= 3600:
            raise ValidationError("Timeout harus > 0 dan <= 3600 detik.")
        if type(self.max_output_bytes) is not int or not 1 <= self.max_output_bytes <= 262144:
            raise ValidationError("Batas output harus 1–262144 byte gabungan.")
        return self


def _write(store, name, data):
    raw = (json.dumps(data, ensure_ascii=False, indent=2) + '\n').encode('utf-8')
    store.atomic(name, raw)


def _group_signal(proc, sig):
    try:
        os.killpg(proc.pid, sig)
    except ProcessLookupError:
        pass


def _collect(proc, command, cancel):
    """Drain both nonblocking pipes. TERM then KILL the process group on every exit."""
    started = time.monotonic()
    output = {'stdout': bytearray(), 'stderr': bytearray()}
    used = 0
    reason = None
    stopping = None
    killed = False
    selector = selectors.DefaultSelector()
    try:
        for name, pipe in [('stdout', proc.stdout), ('stderr', proc.stderr)]:
            os.set_blocking(pipe.fileno(), False)
            selector.register(pipe, selectors.EVENT_READ, name)
        while True:
            current = time.monotonic()
            if reason is None:
                if cancel.is_set():
                    reason = 'cancelled'
                elif current - started >= command.timeout:
                    reason = 'timed_out'
            if stopping is None and (reason is not None or proc.poll() is not None):
                stopping = current
                _group_signal(proc, signal.SIGTERM)
            if stopping is not None and not killed and current - stopping >= 0.25:
                _group_signal(proc, signal.SIGKILL)
                killed = True
            if proc.poll() is not None and not selector.get_map() and killed:
                break
            if stopping is not None and current - stopping >= 2:
                reason = reason or 'cleanup_incomplete'
                break
            try:
                events = selector.select(0.03)
            except KeyboardInterrupt:
                cancel.set()
                continue
            for key, _ in events:
                try:
                    block = os.read(key.fileobj.fileno(), 16384)
                except BlockingIOError:
                    continue
                if not block:
                    selector.unregister(key.fileobj)
                    continue
                remaining = command.max_output_bytes - used
                kept = block[:remaining]
                output[key.data].extend(kept)
                used += len(kept)
                if len(block) > remaining:
                    reason = reason or 'output_limit'
        return output, reason
    finally:
        selector.close()
        _group_signal(proc, signal.SIGKILL)
        try:
            proc.wait(timeout=2)
        finally:
            proc.stdout.close()
            proc.stderr.close()


def run(store, command, cancel=None, on_event=None):
    """Run an explicitly chosen trusted tool. Call from a worker thread in GUI."""
    command.validate()
    store.load()  # must be an actual valid workspace before any tool runs
    # Never execute a file inside the data workspace, including a registered input.
    executable = Path(command.argv[0]).resolve()
    if executable.is_relative_to(store.root):
        raise PathError("Executable dalam workspace data ditolak; pilih instalasi tool tepercaya.")
    cancel = cancel or threading.Event()
    with store.lock():
        runs = store.managed('runs')
        runs.mkdir(exist_ok=True)
    # Separate workspace-wide runner lease: concurrency is exactly one, even across processes.
    with Store(runs).lock():
        return _run_one(store, command, cancel, on_event)


def _run_one(store, command, cancel, on_event):
    redactor = Redactor(command.secrets)
    run_id = str(uuid4())
    folder = store.managed(f'runs/{run_id}')
    folder.mkdir()
    record = Store(folder)
    log = EventLog(record.managed('events.jsonl'), run_id, redactor)
    began = time.monotonic()
    result = dict(run_id=run_id, status='queued', reason=None, argv=redactor.argv(command.argv),
                  tool_version='UNVERIFIED', started_at=now(), ended_at=None, duration_seconds=None,
                  exit_code=None, pid=None, timeout_seconds=command.timeout,
                  max_output_bytes=command.max_output_bytes, output_hashes={}, artifact_dir=str(folder))

    def notify(event, **fields):
        log.emit(event, **fields)
        if on_event:
            try:
                on_event(redactor.value(dict(event=event, run_id=run_id, **fields)))
            except Exception:
                # A view callback must not change tool execution or leave children running.
                log.emit('observer_error', message='View callback failed; run continues.')

    with record.lock():
        _write(record, 'result.json', result)
        _write(record, 'request.json', {k: result[k] for k in ('run_id', 'argv', 'timeout_seconds', 'max_output_bytes', 'tool_version')})
        notify('queued', argv=result['argv'])
        streams = {'stdout': b'', 'stderr': b''}
        proc = None
        try:
            if cancel.is_set():
                result.update(status='cancelled', reason='cancelled_before_start')
            else:
                proc = subprocess.Popen(command.argv, cwd=folder, stdin=subprocess.DEVNULL,
                                        stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=0,
                                        shell=False, start_new_session=True, close_fds=True)
                result.update(status='running', pid=proc.pid)
                _write(record, 'result.json', result)
                notify('running', pid=proc.pid)
                streams, reason = _collect(proc, command, cancel)
                exit_code = proc.poll()
                status = ('cancelled' if reason == 'cancelled' else 'timed_out' if reason == 'timed_out'
                          else 'failed' if reason or exit_code != 0 else 'succeeded')
                result.update(status=status, reason=reason or ('exit_nonzero' if exit_code else None), exit_code=exit_code)
        except (OSError, subprocess.SubprocessError) as exc:
            result.update(status='failed', reason='process_error', message=redactor.text(str(exc)))
        except KeyboardInterrupt:
            result.update(status='cancelled', reason='keyboard_interrupt')
        finally:
            # Covers log/write exceptions immediately after spawn as well as normal collection.
            if proc is not None:
                _group_signal(proc, signal.SIGKILL)
                try:
                    proc.wait(timeout=2)
                except subprocess.TimeoutExpired:
                    result.update(status='failed', reason='cleanup_incomplete')
                for pipe in (proc.stdout, proc.stderr):
                    if pipe and not pipe.closed:
                        pipe.close()
                if result['exit_code'] is None:
                    result['exit_code'] = proc.poll()
        for name, raw in streams.items():
            sanitized = redactor.text(bytes(raw).decode('utf-8', errors='replace')).encode('utf-8')
            if len(sanitized) > 786432:
                sanitized = sanitized[:786432].decode('utf-8', errors='ignore').encode('utf-8')
                result['redacted_output_truncated'] = True
            record.atomic(f'{name}.txt', sanitized)
            result['output_hashes'][f'{name}.txt'] = hashlib.sha256(sanitized).hexdigest()
        result.update(ended_at=now(), duration_seconds=round(time.monotonic() - began, 6))
        _write(record, 'result.json', redactor.value(result))
        notify('finished', status=result['status'], reason=result['reason'], exit_code=result['exit_code'])
        return redactor.value(result)


def recover_interrupted(store):
    """Mark abandoned metadata, never signal a persisted PID (PID reuse is unsafe)."""
    from app.domain.workspace.model import ConflictError
    store.load()
    recovered = []
    runs = store.managed('runs')
    if not runs.exists():
        return recovered
    for folder in sorted(runs.iterdir()):
        try:
            if str(UUID(folder.name)) != folder.name:
                continue
        except ValueError:
            continue
        folder = store.managed(f'runs/{folder.name}')
        record = Store(folder)
        try:
            with record.lock():
                path = record.managed('result.json')
                if not path.exists():
                    continue
                try:
                    result = json.loads(read_bytes(path))
                except (ValueError, UnicodeError, RecursionError):
                    recovered.append({'run_id': folder.name, 'status': 'unreadable'})
                    continue
                if not isinstance(result, dict) or result.get('run_id') != folder.name:
                    recovered.append({'run_id': folder.name, 'status': 'unreadable'})
                    continue
                if result.get('status') in ('queued', 'running'):
                    result.update(status='failed', reason='interrupted', ended_at=now(),
                                  cleanup='UNKNOWN: inspect orphan processes manually; no PID was signalled')
                    _write(record, 'result.json', result)
                    EventLog(record.managed('events.jsonl'), folder.name, Redactor()).emit('recovered', reason='interrupted')
                    recovered.append({'run_id': folder.name, 'status': 'failed', 'reason': 'interrupted'})
        except ConflictError:
            continue  # active runner owns this lease; do not mislabel it as abandoned
    return recovered
