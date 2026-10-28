"""Extract one ELF-declared function's file bytes, without executing or relocating it."""
import hashlib
import json
import re
from uuid import uuid4

from app.application.baselines import _inspect_file
from app.application.symbols import inspect_symbols
from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint
from app.domain.binary.symbols import parse_symbols, VERSION as SYMBOL_VERSION
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.persistence.store import read_bytes

VERSION = 'function-bytes-1'
MAX_EXTRACT = 1024 * 1024


def rejection(symbol):
    if symbol['type'] != 2 or symbol['definition'] != 'SECTION':
        return 'Bukan simbol FUNC yang didefinisikan dalam section.'
    if not 0 < symbol['size'] <= MAX_EXTRACT:
        return 'Ukuran harus diketahui, positif dan maksimum 1 MiB.'
    if symbol['file_offset'] is None or symbol['end_exclusive'] is None:
        return 'Rentang byte file belum diketahui/valid.'
    if symbol['warnings']:
        return 'Simbol memiliki peringatan; periksa manual sebelum ekstraksi.'
    return None


def list_functions(path, offset=0, limit=20):
    if type(offset) is not int or offset < 0 or type(limit) is not int or not 1 <= limit <= 200:
        raise ValidationError('offset harus >= 0; limit harus 1–200.')
    report = inspect_symbols(path)
    functions = [s for s in report['inventory']['symbols'] if s['type'] == 2]
    page = []
    for symbol in functions[offset:offset+limit]:
        reason = rejection(symbol)
        page.append(dict(symbol, extractable=reason is None, rejection_reason=reason))
    return {'source_sha256': report['source_sha256'], 'total_function_symbols': len(functions),
            'offset': offset, 'limit': limit, 'returned': len(page),
            'next_offset': offset + len(page) if offset + len(page) < len(functions) else None,
            'functions': page, 'evidence': 'ELF_DECLARED; aliases are separate entries, not unique functions'}


def extract_function(store, input_id, symbol_id, cancel=None):
    if not isinstance(symbol_id, str) or not re.fullmatch(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})', symbol_id):
        raise ValidationError('symbol-id harus table-section:symbol-index kanonik, contoh 3:2.')
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id'] == input_id), None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan; daftarkan ELF terlebih dahulu.')

    def reader(stream, file_size, token):
        inventory = parse_symbols(stream, file_size, token)
        symbol = next((s for s in inventory['symbols'] if s['id'] == symbol_id), None)
        if symbol is None:
            raise ValidationError('ID simbol tidak ditemukan dalam input ini.')
        reason = rejection(symbol)
        if reason:
            raise ValidationError(reason)
        start, size = symbol['file_offset'], symbol['size']
        if not 0 <= start <= file_size or size > file_size - start:
            raise ValidationError('Rentang ekstraksi di luar file.')
        checkpoint(token)
        stream.seek(start)
        raw = stream.read(size)
        if len(raw) != size:
            raise ValidationError('Input terpotong saat ekstraksi.')
        return {'symbol': symbol, 'elf_type': inventory['elf_type'], 'raw': raw}

    selected, digest, source_size = _inspect_file(resolve_input(store, item), reader, cancel)
    if (digest, source_size) != (item['sha256'], item['size_bytes']):
        raise ConflictError('Input berubah sejak registrasi; ekstraksi tidak dipublikasikan.')
    raw = selected['raw']
    report = {'extraction_schema': 1, 'extractor': VERSION, 'symbol_parser': SYMBOL_VERSION,
              'source_sha256': digest, 'source_size': source_size, 'symbol': selected['symbol'],
              'elf_type': selected['elf_type'], 'payload_file': 'bytes.bin', 'payload_size': len(raw),
              'payload_sha256': hashlib.sha256(raw).hexdigest(),
              'evidence': 'Exact file bytes for an ELF-declared symbol range; not verified function semantics',
              'relocations_applied': False, 'disassembled': False, 'executed': False,
              'limitations': ['Not a standalone runnable binary', 'No relocation or dependency extraction',
                              'No compiler matching or source reconstruction']}
    encoded = (json.dumps(report, ensure_ascii=True, indent=2) + '\n').encode()
    base = f'extractions/{digest}/{VERSION}/{symbol_id.replace(":", "-")}'
    receipt_id = str(uuid4())
    receipt = {'receipt_id': receipt_id, 'created_at': now(), 'input_id': input_id,
               'workspace_id': snapshot.data['workspace_id'], 'manifest_token': snapshot.token,
               'source_sha256': digest, 'report_path': base + '/report.json',
               'report_sha256': hashlib.sha256(encoded).hexdigest()}
    with store.lock():
        checkpoint(cancel)
        if store.load().token != snapshot.token:
            raise ConflictError('Workspace berubah saat ekstraksi; buka ulang.')
        # Validate all existing outputs before writing any file in this result.
        targets = [('bytes.bin', raw), ('report.json', encoded)]
        for name, data in targets:
            destination = store.managed(base + '/' + name)
            if destination.exists() and read_bytes(destination) != data:
                raise ConflictError('Artefak ekstraksi berbeda/korup; tidak ditimpa.')
        parts = base.split('/')
        for index in range(1, len(parts)+1):
            store.managed('/'.join(parts[:index])).mkdir(exist_ok=True)
        store.managed('extractions/records').mkdir(exist_ok=True)
        for name, data in targets:
            if not store.managed(base + '/' + name).exists():
                store.atomic(base + '/' + name, data)
        store.atomic('extractions/records/' + receipt_id + '.json',
                     (json.dumps(receipt, indent=2) + '\n').encode())
    return {'report': report, 'receipt': receipt, 'report_file': str(store.managed(base + '/report.json')),
            'payload_file': str(store.managed(base + '/bytes.bin'))}
