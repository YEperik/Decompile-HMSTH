"""Explicit Linux/POSIX R5900 headless export; no build or semantic-match claims."""
import hashlib
import json
import os
import platform
from pathlib import Path
import re
import shutil
from uuid import uuid4

from app.application.baselines import _inspect_file
from app.application.extractions import rejection
from app.application.ghidra import check_install
from app.application.targets import encoded
from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint
from app.domain.binary.symbols import parse_symbols
from app.domain.workspace.model import ValidationError, ConflictError
from app.infrastructure.persistence.store import read_bytes
from app.infrastructure.process_runner.runner import Command, run

LANGUAGE = 'r5900:LE:32:default'
SCALAR_SIZES = {'char': 1, 'short': 2, 'int': 4, 'long': 8, 'long_long': 8, 'pointer': 4}


class GhidraExportError(ValidationError):
    code = 'ghidra_export_failed'


def validate_export(folder, symbol, payload, version, analysis="bounded"):
    try:
        result = json.loads(read_bytes(folder / 'result.json'))
        code = read_bytes(folder / 'decompiled.c').decode('utf-8')
        instructions = result['instructions']
        schema = result.get('export_schema', 1)
        if type(schema) is not int or schema not in (1, 2):
            raise ValueError('Unsupported export schema')
        if schema == 2:
            sizes = result['scalar_sizes']
            if sizes != SCALAR_SIZES or any(type(v) is not int for v in sizes.values()):
                raise ValueError('Unexpected R5900 scalar sizes')
            counts = {}
            for instruction in instructions:
                if not isinstance(instruction['userops'], list):
                    raise ValueError('Invalid userops')
                for op in instruction['userops']:
                    name = op['name']
                    if not isinstance(name, str) or not re.fullmatch(r'[A-Za-z_][A-Za-z_0-9]{0,127}', name):
                        raise ValueError('Invalid userop name')
                    if not isinstance(op['inputs'], list):
                        raise ValueError('Invalid userop inputs')
                    for node in op['inputs'] + ([op['output']] if 'output' in op else []):
                        if (type(node['size']) is not int or not 1 <= node['size'] <= 32
                                or not isinstance(node['space'], str) or not node['space']
                                or not re.fullmatch(r'[0-9a-f]{1,16}', node['offset'])):
                            raise ValueError('Invalid userop operand')
                    counts[name] = counts.get(name, 0) + 1
            if result['pcode_userop_counts'] != counts:
                raise ValueError('Userop counts mismatch')
        valid = (result['status'] == 'DECOMPILED_UNVERIFIED' and result['language'] == LANGUAGE
                 and result['compiler_spec'] == 'default' and result['ghidra_version'] == version
                 and int(result['start'], 16) == symbol['start'] and result['size'] == len(payload)
                 and result['mapped_bytes_sha256'] == hashlib.sha256(payload).hexdigest()
                 and len(instructions) == len(payload) // 4 and bool(code.strip())
                 and result['pcode_origins_within_selected_range'] is True
                 and result['analysis'] == analysis_contract(analysis)
                 and result['recompiled'] is False and result['semantics_verified'] is False)
        for index, instruction in enumerate(instructions):
            valid = valid and (int(instruction['address'], 16) == symbol['start'] + index * 4
                               and bytes.fromhex(instruction['bytes']) == payload[index*4:index*4+4]
                               and isinstance(instruction['assembly'], str) and bool(instruction['assembly']))
        if not valid:
            raise ValueError('Output does not match selected function')
    except (ValueError, KeyError, TypeError, UnicodeError) as exc:
        raise GhidraExportError('Keluaran Ghidra invalid/tidak cocok dengan target.') from exc
    return result, hashlib.sha256(code.encode()).hexdigest()


def analysis_contract(profile):
    return {'profile': profile, 'auto_analysis_completed': profile == 'recommended',
            'settings': {'Decompiler Parameter ID': False, 'Demangler GNU': True,
                         'Demangler GNU.Use Deprecated Demangler': True} if profile == 'recommended' else {}}


def validate_analysis_log(run_dir):
    text = read_bytes(Path(run_dir) / 'stdout.txt').decode('utf-8')
    if 'PS2_WORKBENCH_PROFILE_CONFIGURED' not in text or re.search(r'^\s*(?:ERROR|FATAL)\s', text, re.M):
        raise GhidraExportError('Analisis Ghidra tidak bersih atau profil tidak diterapkan. Log: ' + str(run_dir))


def decompile_function(store, input_id, symbol_id, ghidra_home, jdk_home, timeout=180, cancel=None, analysis='bounded'):
    if analysis not in ('bounded', 'recommended'):
        raise ValidationError('Profil analisis harus bounded atau recommended.')
    if not isinstance(symbol_id, str) or not re.fullmatch(r'[0-9]{1,6}:[0-9]{1,6}', symbol_id):
        raise ValidationError('symbol-id harus table:index.')
    install = check_install(ghidra_home)
    choices = [x for x in install['languages'] if x['id'] == LANGUAGE
               and x['processor'] == 'MIPS-R5900' and x['variant'] == 'PS2'
               and x['endian'] == 'little' and x['size'] == '32' and x['catalog_in_installation']]
    if install['status'] != 'DECLARED' or len(choices) != 1:
        raise ValidationError('Ekstensi R5900 PS2 yang unik wajib tersedia; MIPS generik ditolak.')
    selected = choices[0]
    specs = [x for x in selected['compiler_assets'] if x['id'] == 'default']
    if (len(specs) != 1 or specs[0]['asset']['status'] != 'PRESENT'
            or any(x['status'] != 'PRESENT' for x in selected['language_assets'].values())):
        raise ValidationError('Asset R5900/default tidak lengkap.')
    jdk = Path(jdk_home).resolve()
    java = jdk / 'bin/java'
    launcher = Path(install['launcher']).resolve()
    env_executable = shutil.which('env')
    if not java.is_file() or not os.access(java, os.X_OK) or not env_executable:
        raise ValidationError('JDK executable dan env POSIX diperlukan.')
    if not launcher.is_file() or not os.access(launcher, os.X_OK):
        raise ValidationError('Launcher headless tidak executable.')
    if analysis == 'recommended':
        if platform.system() != 'Linux' or platform.machine() not in ('x86_64', 'amd64'):
            raise ValidationError('Profil recommended saat ini memerlukan Linux x86_64.')
        native_dir = launcher.parent.parent / 'GPL/DemanglerGnu/os/linux_x86_64'
        for name in ('demangler_gnu_v2_24', 'demangler_gnu_v2_41'):
            native = native_dir / name
            if not native.is_file() or not os.access(native, os.X_OK):
                raise ValidationError('Demangler GNU tidak tersedia/executable: ' + str(native))
    if any(p.is_relative_to(store.root.resolve()) for p in (java, launcher)):
        raise ValidationError('Instalasi tool harus di luar workspace data.')
    Command((env_executable,), timeout=timeout).validate()
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id'] == input_id), None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan.')

    def reader(stream, size, token):
        if size > 32 * 1024**2:
            raise ValidationError('Uji headless dibatasi ELF 32 MiB.')
        symbols = parse_symbols(stream, size, token)
        symbol = next((s for s in symbols['symbols'] if s['id'] == symbol_id), None)
        if symbol is None:
            raise ValidationError('Simbol tidak ditemukan.')
        reason = rejection(symbol)
        if reason or symbol['size'] > 16384 or symbol['size'] % 4 or symbol['start'] % 4:
            raise ValidationError(reason or 'Fungsi harus aligned, maksimal 16 KiB.')
        stream.seek(0)
        raw = stream.read(size)
        return symbol, raw

    (symbol, raw), digest, size = _inspect_file(resolve_input(store, item), reader, cancel)
    if (digest, size) != (item['sha256'], item['size_bytes']):
        raise ConflictError('ELF berubah sejak registrasi.')
    payload = raw[symbol['file_offset']:symbol['file_offset'] + symbol['size']]
    script = Path(__file__).resolve().parents[1] / 'ghidra_scripts/ExportR5900Function.java'
    job = 'decompilations/' + str(uuid4())
    with store.lock():
        checkpoint(cancel)
        if store.load().token != snapshot.token:
            raise ConflictError('Manifest berubah selama persiapan.')
        store.managed('decompilations').mkdir(exist_ok=True)
        folder = store.managed(job)
        folder.mkdir()
        (folder / 'projects').mkdir()
        with (folder / 'input.elf').open('xb') as stream:
            stream.write(raw)
        request = {'input_id': input_id, 'symbol_id': symbol_id, 'source_sha256': digest,
                   'language': LANGUAGE, 'ghidra_version': install['declared_version'],
                   'script_sha256': hashlib.sha256(read_bytes(script)).hexdigest(),
                   'profile_script_sha256': hashlib.sha256(read_bytes(script.parent / 'ConfigureR5900.java')).hexdigest(),
                   'analysis': analysis_contract(analysis),
                   'language_assets': selected, 'jdk_home': str(jdk)}
        store.atomic(job + '/request.json', encoded(request))
    analysis_args = ('-noanalysis',) if analysis == 'bounded' else (
        '-preScript', 'ConfigureR5900.java', '-analysisTimeoutPerFile', str(max(1, int(timeout * 0.75))))
    argv = (env_executable, 'JAVA_HOME=' + str(jdk), 'PATH=' + str(jdk / 'bin') + os.pathsep + os.environ.get('PATH', ''),
            str(launcher), str(folder / 'projects'), 'target', '-import', str(folder / 'input.elf'),
            '-processor', LANGUAGE, '-cspec', 'default', '-max-cpu', '2', *analysis_args,
            '-scriptPath', str(script.parent), '-postScript', script.name, hex(symbol['start']),
            str(symbol['size']), str(folder / 'export'), hashlib.sha256(payload).hexdigest(), analysis, '-deleteProject')
    execution = run(store, Command(argv, timeout=timeout), cancel)
    if execution['status'] != 'succeeded':
        return {'status': 'GHIDRA_RUN_FAILED', 'run_status': execution['status'],
                'artifact_dir': str(folder), 'run_dir': execution['artifact_dir']}
    try:
        if analysis == 'recommended':
            validate_analysis_log(execution['artifact_dir'])
        # A zero exit code does not establish a successful script export.
        if not (folder / 'export/result.json').is_file():
            raise GhidraExportError('Ghidra tidak menghasilkan export lengkap. Log: ' + execution['artifact_dir'])
        result, code_hash = validate_export(folder / 'export', symbol, payload, install['declared_version'], analysis)
    except GhidraExportError as exc:
        exc.artifact_dir = str(folder)
        exc.run_dir = execution['artifact_dir']
        raise
    if hashlib.sha256((folder / 'input.elf').read_bytes()).hexdigest() != digest:
        raise ConflictError('Snapshot input berubah selama Ghidra berjalan.')
    receipt = {'status': 'DECOMPILED_UNVERIFIED', 'source_sha256': digest,
               'symbol_id': symbol_id, 'language': LANGUAGE, 'ghidra_version': result['ghidra_version'],
               'analysis': result['analysis'],
               'java_version': result['java_version'], 'instructions': len(result['instructions']),
               'code_sha256': code_hash, 'run_dir': execution['artifact_dir'],
               'export_sha256': hashlib.sha256(read_bytes(folder / 'export/result.json')).hexdigest(),
               'artifact_dir': str(folder), 'code_file': str(folder / 'export/decompiled.c'),
               'recompiled': False, 'semantics_verified': False}
    store.atomic(job + '/receipt.json', encoded(receipt))
    return receipt
