"""Hash and inventory the same open input, then publish an immutable report."""
import hashlib
import json
from uuid import uuid4

from app.application.baselines import _inspect_file
from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint
from app.domain.binary.symbols import parse_symbols, VERSION
from app.domain.workspace.model import ConflictError, ValidationError, now
from app.infrastructure.persistence.store import read_bytes, MAX_MANIFEST


def inspect_symbols(path, cancel=None):
    inventory, digest, size = _inspect_file(path, parse_symbols, cancel)
    return {'inventory_schema': 1, 'source_sha256': digest, 'source_size': size,
            'inventory': inventory,
            'evidence': {'status': 'ELF_DECLARED', 'parser': VERSION,
                         'claim': 'Symbol fields extracted from these hashed bytes; function semantics not verified'}}


def create_inventory(store, input_id, cancel=None):
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id'] == input_id), None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan; gunakan add-input terlebih dahulu.')
    report = inspect_symbols(resolve_input(store, item), cancel)
    if (report['source_sha256'], report['source_size']) != (item['sha256'], item['size_bytes']):
        raise ConflictError('Input berubah dari registrasi; inventaris tidak dipublikasikan.')
    raw = (json.dumps(report, ensure_ascii=True, separators=(',', ':')) + '\n').encode()
    pages = []
    if len(raw) > MAX_MANIFEST:
        inventory = report['inventory']
        entries = inventory.pop('symbols')
        inventory['symbol_pages'] = []
        for start in range(0, len(entries), 256):
            data = (json.dumps({'symbols': entries[start:start+256]}, ensure_ascii=True,
                               separators=(',', ':')) + '\n').encode()
            name = f'{VERSION}-page-{start//256:04d}.json'
            if len(data) > MAX_MANIFEST:
                raise ValidationError('Halaman simbol melebihi batas metadata; tidak dipublikasikan.')
            pages.append((name, data))
            inventory['symbol_pages'].append({'file': name, 'count': len(entries[start:start+256]),
                                               'sha256': hashlib.sha256(data).hexdigest()})
        raw = (json.dumps(report, ensure_ascii=True, separators=(',', ':')) + '\n').encode()
        if len(raw) > MAX_MANIFEST:
            raise ValidationError('Indeks inventaris melebihi batas metadata; tidak dipublikasikan.')
    relative = f"symbols/{report['source_sha256']}/{VERSION}.json"
    receipt_id = str(uuid4())
    receipt = {'receipt_id': receipt_id, 'created_at': now(), 'input_id': input_id,
               'workspace_id': snapshot.data['workspace_id'], 'manifest_token': snapshot.token,
               'source_sha256': report['source_sha256'], 'report_path': relative,
               'report_sha256': hashlib.sha256(raw).hexdigest(), 'parser': VERSION}
    with store.lock():
        checkpoint(cancel)
        if store.load().token != snapshot.token:
            raise ConflictError('Workspace berubah saat inventaris; buka ulang sebelum mencoba lagi.')
        for directory in ('symbols', f"symbols/{report['source_sha256']}", 'symbols/records'):
            store.managed(directory).mkdir(exist_ok=True)
        for name, data in pages:
            page_relative = f"symbols/{report['source_sha256']}/{name}"
            page = store.managed(page_relative)
            if page.exists():
                if read_bytes(page) != data:
                    raise ConflictError('Halaman simbol berbeda/korup; tidak ditimpa.')
            else:
                store.atomic(page_relative, data)
        destination = store.managed(relative)
        if destination.exists():
            if read_bytes(destination) != raw:
                raise ConflictError('Inventaris tersimpan berbeda/korup; tidak ditimpa.')
        else:
            store.atomic(relative, raw)
        store.atomic(f'symbols/records/{receipt_id}.json', (json.dumps(receipt, indent=2) + '\n').encode())
    return {'report_file': str(destination), 'receipt': receipt, 'report': report}
