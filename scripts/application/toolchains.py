"""Explicit GCC adapter; detection never executes discovered files.

Build only the embedded freestanding fixture; never run its output.
Two identical local builds are evidence of repeatability, not game matching.
"""
import hashlib
import json
import os
from pathlib import Path
import platform
import re
import shutil
import struct
from uuid import uuid4

from app.domain.workspace.model import ValidationError, WorkspaceError, now
from app.infrastructure.persistence.store import Store, read_bytes
from app.infrastructure.process_runner.runner import Command, run

PS2_TARGET = 'mips64r5900el-ps2-elf'
SOURCE = b'unsigned workbench_add(unsigned a, unsigned b) { return a + b; }\nvoid workbench_entry(void) { for (;;) {} }\n'
NAMES = ('mips64r5900el-ps2-elf-gcc', 'ee-gcc', 'gcc')


def detect():
    candidates = []
    for name in NAMES:
        path = shutil.which(name)
        candidates.append({'name': name, 'path': str(Path(path).absolute()) if path else None,
                           'status': 'FOUND_UNVERIFIED' if path else 'NOT_FOUND'})
    return {'schema_version': 1, 'candidates': candidates,
            'runner_supported': os.name == 'posix', 'executed': False,
            'hint': 'Pilih executable tepercaya secara eksplisit dengan --compiler; deteksi bukan verifikasi.'}


def _hash_file(path):
    digest = hashlib.sha256()
    with path.open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(chunk)
    return digest.hexdigest()


def _target_shape(target, profile):
    if profile == 'ps2-ee' and target == PS2_TARGET:
        return (1, 8)
    if profile == 'host-elf' and 'linux' in target:
        if target.startswith('x86_64-'):
            return (2, 62)
        if target.startswith('aarch64-'):
            return (2, 183)
    raise ValidationError('Target compiler tidak sesuai profil: ' + target)


def _artifact(path, expected_type, shape):
    raw = read_bytes(path)  # bounded, rejects symlinks and hardlinks
    cls, machine = shape
    minimum = 52 if cls == 1 else 64
    if len(raw) < minimum or raw[:7] != b'\x7fELF' + bytes((cls, 1, 1)):
        raise ValidationError('Output bukan ELF little-endian dengan class yang diharapkan.')
    elf_type, actual_machine, version = struct.unpack_from('<HHI', raw, 16)
    if (elf_type, actual_machine, version) != (expected_type, machine, 1):
        raise ValidationError('Type/machine/version output ELF tidak sesuai target.')
    if cls == 1:
        # Reuse the full Stage 2 parser for the PS2 structural subset.
        from app.application.baselines import inspect_file
        inspect_file(path)
    return {'path': str(path), 'size': len(raw), 'sha256': hashlib.sha256(raw).hexdigest(),
            'elf_class': cls, 'machine': machine, 'elf_type': elf_type,
            'validation': 'stage2_parser' if cls == 1 else 'header_identity_only'}


def examine(store, compiler, profile='ps2-ee', build=False, timeout=30):
    if profile not in ('ps2-ee', 'host-elf'):
        raise ValidationError('Profil toolchain tidak dikenal.')
    # Validation precedes any report directory creation. No implicit PATH execution.
    Command((compiler, '--version'), timeout=timeout).validate()
    store.load()
    exe = Path(compiler)
    before = _hash_file(exe)
    identity = str(uuid4())
    parent = store.managed('toolchains')
    parent.mkdir(exist_ok=True)
    folder = store.managed('toolchains/' + identity)
    folder.mkdir()
    record = Store(folder)
    report = {'schema_version': 1, 'id': identity, 'created_at': now(), 'status': 'running',
              'profile': profile, 'compiler': str(exe), 'compiler_sha256': before,
              'report_path': str(folder / 'report.json'), 'probes': {}, 'steps': [],
              'build_requested': build, 'repeatable': None,
              'runtime_tested': False, 'game_matching_tested': False,
              'environment': {'system': platform.system(), 'machine': platform.machine(),
                              'python': platform.python_version(), 'policy': 'inherited; values not dumped'},
              'scope': 'local freestanding smoke; no SDK, libc, ABI or game compatibility guarantee'}

    def save():
        record.atomic('report.json', (json.dumps(report, indent=2) + '\n').encode())

    def invoke(label, arguments):
        result = run(store, Command(tuple(arguments), timeout=timeout, max_output_bytes=32768))
        report['steps'].append({'label': label, 'run_id': result['run_id'],
                                'status': result['status'], 'argv': result['argv'],
                                'artifact_dir': result['artifact_dir']})
        if result['status'] != 'succeeded':
            report['status'] = result['status']
            raise ValidationError('Langkah toolchain gagal: ' + label + '; periksa log run.')
        return read_bytes(Path(result['artifact_dir']) / 'stdout.txt').decode('utf-8').strip()

    save()
    try:
        for key, option in [('version', '--version'), ('target', '-dumpmachine'),
                            ('full_version', '-dumpfullversion'), ('linker', '-print-prog-name=ld'),
                            ('libc', '-print-file-name=libc.a')]:
            value = invoke(key, (compiler, option))
            if not value:
                raise ValidationError('Probe kosong: ' + key)
            report['probes'][key] = value
            save()
        target = report['probes']['target']
        shape = _target_shape(target, profile)
        if not re.fullmatch(r'[0-9]+(?:\.[0-9]+){0,3}', report['probes']['full_version']):
            raise ValidationError('Versi GCC tidak dikenali; adapter hanya mendukung GCC.')
        report['libc_status'] = 'NOT_FOUND' if report['probes']['libc'] == 'libc.a' else 'REPORTED_UNVERIFIED'
        report['linker_status'] = 'REPORTED_UNVERIFIED'
        linker_name = report['probes']['linker']
        linker = (linker_name if Path(linker_name).is_absolute() else
                  shutil.which(linker_name) if '/' not in linker_name else None)
        if linker:
            report['linker_candidate'] = {'path': linker, 'sha256': _hash_file(Path(linker)),
                                          'version': invoke('linker_version', (linker, '--version'))}
        else:
            report['linker_candidate'] = {'path': None, 'status': 'NOT_RESOLVED'}
        # This candidate is diagnostic; the driver may select another linker via specs.
        if build:
            outputs = []
            for iteration in ('a', 'b'):
                directory = folder / iteration
                directory.mkdir()
                source = directory / 'smoke.c'
                source.write_bytes(SOURCE)
                obj, elf = directory / 'smoke.o', directory / 'smoke.elf'
                invoke('compile_' + iteration, (compiler, '-std=c99', '-O2', '-g0', '-ffreestanding',
                       '-fno-pic', '-fno-pie', '-fno-stack-protector', '-c', str(source), '-o', str(obj)))
                object_record = _artifact(obj, 1, shape)
                invoke('link_' + iteration, (compiler, '-nostdlib', '-static', '-Wl,--build-id=none',
                       '-Wl,-e,workbench_entry', str(obj), '-o', str(elf)))
                outputs.append({'iteration': iteration, 'object': object_record,
                                'elf': _artifact(elf, 2, shape)})
                report['outputs'] = outputs
                save()
            report['source_sha256'] = hashlib.sha256(SOURCE).hexdigest()
            report['repeatable'] = all(outputs[0][kind]['sha256'] == outputs[1][kind]['sha256']
                                       for kind in ('object', 'elf'))
            report['linker_status'] = 'DRIVER_LINK_VERIFIED'
            report['status'] = 'succeeded' if report['repeatable'] else 'non_reproducible'
        else:
            report['status'] = 'checked'
        if _hash_file(exe) != before:
            report['status'] = 'failed'
            report['error'] = 'Compiler berubah selama pemeriksaan; hasil tidak dipercaya.'
    except (WorkspaceError, OSError) as exc:
        if report['status'] == 'running':
            report['status'] = 'failed'
        report['error'] = str(exc)
    except KeyboardInterrupt:
        report['status'] = 'cancelled'
        report['error'] = 'Dihentikan pengguna.'
    finally:
        report['ended_at'] = now()
        save()
    return report


def exit_status(report):
    return {'checked': 0, 'succeeded': 0, 'timed_out': 124, 'cancelled': 130}.get(report['status'], 1)
