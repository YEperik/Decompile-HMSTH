"""Check an unchanged decompiler export with an explicitly selected compiler."""
import hashlib
import json
from pathlib import Path
from uuid import UUID, uuid4
import platform
import io
import re

from app.application.baselines import _inspect_file
from app.application.decompile import validate_export, SCALAR_SIZES
from app.application.targets import encoded
from app.application.toolchains import _hash_file, _artifact, PS2_TARGET
from app.application.workspaces import resolve_input
from app.domain.binary.symbols import parse_symbols
from app.domain.binary.elf import parse
from app.domain.workspace.model import ValidationError, ConflictError
from app.infrastructure.persistence.store import read_bytes
from app.infrastructure.process_runner.runner import Command, run


STORAGE_TYPES = b'''/* Ghidra storage widths; original signedness/types are unverified. */
#include <stdint.h>
typedef uint8_t undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;
'''


def storage_header(result):
    if result.get('export_schema', 1) == 1:
        return STORAGE_TYPES
    sizes = result.get('scalar_sizes')
    if sizes != SCALAR_SIZES or any(type(v) is not int for v in sizes.values()):
        raise ValidationError('Ukuran scalar R5900 tidak cocok.')
    aliases = [('uchar', 'char'), ('ushort', 'short'), ('uint', 'int'), ('ulong', 'long')]
    return STORAGE_TYPES + b'/* Alias widths from verified Ghidra data organization, not compiler long. */\n' + ''.join(
        f'typedef uint{sizes[native] * 8}_t {alias};\n' for alias, native in aliases).encode()


def native_scalar_probe(store, compiler, folder, expected, timeout, cancel):
    source = folder / 'scalar_probe.c'
    raw = b'/* Compiler native widths; no game code. */\n'
    store.atomic(str(source.relative_to(store.root)), raw)
    execution = run(store, Command((str(compiler), '-dM', '-E', '-x', 'c', str(source)), timeout=timeout), cancel)
    if execution['status'] != 'succeeded':
        raise ValidationError('Probe tipe compiler gagal. Log: ' + execution['artifact_dir'])
    text = read_bytes(Path(execution['artifact_dir']) / 'stdout.txt').decode('utf-8')
    if read_bytes(source) != raw:
        raise ConflictError('Input probe tipe berubah.')
    macros = dict(re.findall(r'^#define (__[A-Z_]+__) ([0-9]+)$', text, re.M))
    try:
        if macros['__CHAR_BIT__'] != '8':
            raise ValueError()
        actual = {'char': 1, **{name: int(macros['__SIZEOF_' + name.upper() + '__'])
                                for name in ('short', 'int', 'long', 'long_long', 'pointer')}}
        if any(not 1 <= size <= 16 for size in actual.values()):
            raise ValueError()
    except (KeyError, ValueError):
        raise ValidationError('Compiler tidak menyediakan ukuran scalar GCC yang didukung.')
    return {'compiler_sizes': actual, 'ghidra_sizes': expected,
            'mismatches': {name: {'compiler': actual[name], 'ghidra': size}
                           for name, size in expected.items() if actual[name] != size},
            'scalar_widths_match': actual == expected, 'abi_verified': False,
            'run_dir': execution['artifact_dir']}


def verify_allocated(original, normalized, cancel=None):
    def allocated(raw):
        metadata = parse(io.BytesIO(raw), len(raw), cancel)
        return [(s['name'], s['type'], s['flags'], s['size'], s['address'], s['alignment'],
                 raw[s['offset']:s['offset']+s['size']] if s['file_backed'] else None)
                for s in metadata['sections'] if s['flags'] & 2]
    if allocated(original) != allocated(normalized):
        raise ConflictError('objcopy mengubah section ALLOC; hasil ditolak.')


def check_export(store, job_id, compiler, language='c++', timeout=30, cancel=None,
                 storage_types=False, emit_object=False, target='host', strip_debug=False):
    try:
        if str(UUID(job_id)) != job_id:
            raise ValueError()
    except (ValueError, TypeError, AttributeError):
        raise ValidationError('job-id harus UUID kanonik.')
    if language not in ('c', 'c++'):
        raise ValidationError('Bahasa harus c atau c++.')
    if target not in ('host', 'ps2-ee'):
        raise ValidationError('Target harus host atau ps2-ee.')
    if type(strip_debug) is not bool or (strip_debug and not (emit_object and target == 'ps2-ee')):
        raise ValidationError('strip-debug memerlukan object ps2-ee.')
    if type(storage_types) is not bool or type(emit_object) is not bool:
        raise ValidationError('Opsi storage-types dan emit-object harus boolean.')
    machine = {'x86_64': 62, 'aarch64': 183}.get(platform.machine())
    if emit_object and target == 'host' and (platform.system() != 'Linux' or machine is None):
        raise ValidationError('Build object host memerlukan Linux x86_64/aarch64.')
    Command((compiler,), timeout=timeout).validate()
    exe = Path(compiler).resolve()
    if exe.is_relative_to(store.root.resolve()):
        raise ValidationError('Compiler harus di luar workspace data.')
    snapshot = store.load()
    job = store.managed('decompilations/' + job_id)
    request_raw = read_bytes(job / 'request.json')
    receipt_raw = read_bytes(job / 'receipt.json')
    try:
        request, receipt = json.loads(request_raw), json.loads(receipt_raw)
        item = next(x for x in snapshot.data['inputs'] if x['id'] == request['input_id'])
        sid = request['symbol_id']
        if receipt['status'] != 'DECOMPILED_UNVERIFIED' or receipt['symbol_id'] != sid:
            raise ValueError()
    except (ValueError, KeyError, TypeError, StopIteration):
        raise ValidationError('Receipt/request dekompilasi invalid.')

    def reader(stream, size, token):
        if size > 32 * 1024**2:
            raise ValidationError('ELF melebihi 32 MiB.')
        symbols = parse_symbols(stream, size, token)
        symbol = next((x for x in symbols['symbols'] if x['id'] == sid), None)
        if symbol is None or symbol['file_offset'] is None or not 0 < symbol['size'] <= 16384:
            raise ValidationError('Simbol target tidak valid.')
        stream.seek(symbol['file_offset'])
        return symbol, stream.read(symbol['size'])

    (symbol, payload), digest, size = _inspect_file(resolve_input(store, item), reader, cancel)
    if digest != item['sha256'] or size != item['size_bytes'] or any(
            x.get('source_sha256') != digest for x in (request, receipt)):
        raise ConflictError('Sumber ELF/receipt berubah.')
    try:
        profile = receipt['analysis']['profile']
        if profile not in ('bounded', 'recommended'):
            raise ValidationError('Profil analisis export tidak dikenal.')
        result, code_hash = validate_export(job / 'export', symbol, payload, receipt['ghidra_version'], profile)
        if result['analysis'] != request['analysis'] or code_hash != receipt['code_sha256']:
            raise ConflictError('Export tidak cocok dengan receipt.')
    except (KeyError, TypeError):
        raise ValidationError('Metadata export tidak lengkap.')
    code = read_bytes(job / 'export/decompiled.c')
    export_raw = read_bytes(job / 'export/result.json')
    if 'export_sha256' in receipt and hashlib.sha256(export_raw).hexdigest() != receipt['export_sha256']:
        raise ConflictError('Metadata export berubah sejak dekompilasi.')
    if result.get('export_schema', 1) == 2 and 'export_sha256' not in receipt:
        raise ValidationError('Export schema 2 memerlukan hash metadata dalam receipt.')
    header = storage_header(result) if storage_types else None
    if hashlib.sha256(code).hexdigest() != code_hash:
        raise ConflictError('Kode export berubah selama persiapan.')
    compiler_hash = _hash_file(exe)
    objcopy = exe.parent / (PS2_TARGET + '-objcopy')
    objcopy_hash = None
    if strip_debug:
        Command((str(objcopy),), timeout=timeout).validate()
        objcopy_hash = _hash_file(objcopy)
    target_probe = None
    if target == 'ps2-ee':
        target_probe = run(store, Command((str(exe), '-dumpmachine'), timeout=timeout), cancel)
        if target_probe['status'] != 'succeeded' or read_bytes(
                Path(target_probe['artifact_dir']) / 'stdout.txt').decode().strip() != PS2_TARGET:
            raise ValidationError('Compiler bukan target mips64r5900el-ps2-elf.')
    relative = 'export-checks/' + str(uuid4())
    with store.lock():
        if store.load().token != snapshot.token:
            raise ConflictError('Manifest berubah selama persiapan.')
        store.managed('export-checks').mkdir(exist_ok=True)
        folder = store.managed(relative)
        folder.mkdir()
        store.atomic(relative + '/source.txt', code)
        if storage_types:
            store.atomic(relative + '/storage_types.h', header)
        binding = {'job_id': job_id, 'source_sha256': digest, 'code_sha256': code_hash,
                   'request_sha256': hashlib.sha256(request_raw).hexdigest(),
                   'receipt_sha256': hashlib.sha256(receipt_raw).hexdigest(),
                   'compiler': str(exe), 'compiler_sha256': compiler_hash, 'language': language,
                   'storage_types': storage_types, 'object_requested': emit_object,
                   'storage_header_sha256': hashlib.sha256(header).hexdigest() if header else None,
                   'scalar_sizes': result.get('scalar_sizes'),
                   'pcode_userop_counts': result.get('pcode_userop_counts'),
                   'userop_semantics_implemented': False,
                   'target': target, 'target_probe': target_probe,
                   'strip_debug': strip_debug, 'objcopy_sha256': objcopy_hash}
        store.atomic(relative + '/request.json', encoded(binding))
    scalar_probe = (native_scalar_probe(store, exe, folder, result['scalar_sizes'], timeout, cancel)
                    if result.get('export_schema', 1) == 2 else None)
    # No helper implementations, source rewriting, link step, or execution of produced code.
    options = ('-include', str(folder / 'storage_types.h')) if storage_types else ()
    output = ('-c', '-o', str(folder / 'candidate.o')) if emit_object else ('-fsyntax-only',)
    flags = ('-O2', '-G0') if target == 'ps2-ee' else ()
    execution = run(store, Command((str(exe), *output, *flags, '-fmax-errors=20', *options, '-x', language,
                                   str(folder / 'source.txt')), timeout=timeout), cancel)
    if (_hash_file(exe) != compiler_hash or read_bytes(folder / 'source.txt') != code
            or read_bytes(job / 'request.json') != request_raw
            or read_bytes(job / 'receipt.json') != receipt_raw
            or read_bytes(job / 'export/decompiled.c') != code):
        raise ConflictError('Input/compiler berubah selama pemeriksaan.')
    if read_bytes(job / 'export/result.json') != export_raw:
        raise ConflictError('Metadata export berubah selama pemeriksaan.')
    if storage_types and read_bytes(folder / 'storage_types.h') != header:
        raise ConflictError('Header tipe berubah selama pemeriksaan.')
    accepted = execution['status'] == 'succeeded'
    shape = (1, 8) if target == 'ps2-ee' else (2, machine)
    obj = _artifact(folder / 'candidate.o', 1, shape) if accepted and emit_object else None
    raw_object = obj
    normalization = None
    object_path = folder / 'candidate.o'
    if obj and strip_debug:
        original = read_bytes(object_path)
        normalized_path = folder / 'normalized.o'
        normalization = run(store, Command((str(objcopy), '--strip-debug', str(object_path),
                                            str(normalized_path)), timeout=timeout), cancel)
        if normalization['status'] != 'succeeded':
            raise ValidationError('objcopy gagal; periksa log run: ' + normalization['artifact_dir'])
        if _hash_file(objcopy) != objcopy_hash or read_bytes(object_path) != original:
            raise ConflictError('objcopy/object asli berubah.')
        verify_allocated(original, read_bytes(normalized_path), cancel)
        obj = _artifact(normalized_path, 1, shape)
        object_path = normalized_path
    comparison = None
    if obj and target == 'ps2-ee':
        from app.domain.binary.relocations import function_refs
        with object_path.open('rb') as stream:
            candidates = parse_symbols(stream, obj['size'], cancel)['symbols']
            matches = [s for s in candidates if s['name'] == result['function_name']
                       and s['type_name'] == 'FUNC' and s.get('file_offset') is not None and s['size'] > 0]
            comparison = {'status': 'SYMBOL_NOT_UNIQUE_OR_MISSING'}
            if len(matches) == 1:
                candidate = matches[0]
                stream.seek(candidate['file_offset'])
                actual = stream.read(candidate['size'])
                references = function_refs(stream, obj['size'], candidate['id'], cancel)
                comparison = {'status': 'RAW_RANGE_IDENTICAL' if actual == payload else 'RAW_RANGE_DIFFERENT',
                              'reference_size': len(payload), 'candidate_size': len(actual),
                              'candidate_bytes_sha256': hashlib.sha256(actual).hexdigest(),
                              'candidate_symbol': candidate, 'references': references,
                              'relocations_applied': False, 'whole_binary_match': False}
    built_status = 'EE_OBJECT_BUILT_UNVERIFIED' if target == 'ps2-ee' else 'HOST_OBJECT_BUILT_UNVERIFIED'
    status = ((built_status if emit_object else 'SYNTAX_ACCEPTED_UNVERIFIED') if accepted else
              'BLOCKED_SYNTAX' if execution['status'] == 'failed' and execution['exit_code'] == 1
              else 'CHECK_FAILED')
    warnings = ([f"Ukuran native {name}: compiler {sizes['compiler']} byte, Ghidra {sizes['ghidra']} byte; ABI belum diverifikasi."
                 for name, sizes in scalar_probe['mismatches'].items()] if scalar_probe else [])
    report = {**binding, 'status': status, 'syntax_accepted': accepted,
              'warnings': warnings,
              'native_scalar_probe': scalar_probe,
              'run_status': execution['status'], 'exit_code': execution['exit_code'],
              'run_dir': execution['artifact_dir'], 'report_dir': str(folder),
              'object': obj, 'raw_compiler_object': raw_object, 'normalization_run': normalization,
              'function_comparison': comparison,
              'linked': False, 'runtime_tested': False, 'semantics_verified': False,
              'ps2_binary_match_verified': False}
    store.atomic(relative + '/report.json', encoded(report))
    return report
