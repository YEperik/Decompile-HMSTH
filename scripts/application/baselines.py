"""Read-only input inspection + content-addressed, immutable structural baseline."""
import hashlib
import json
import os
import stat
from uuid import uuid4

from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint, parse, PARSER_VERSION, UnsupportedELF
from app.domain.workspace.model import ConflictError, PathError, ValidationError, now
from app.infrastructure.persistence.store import read_bytes

MAX_INPUT_BYTES = 2 * 1024**3


def identity(s):
    return (s.st_dev, s.st_ino, s.st_size, s.st_mtime_ns, s.st_ctime_ns)


def _inspect_file(path, reader, cancel=None, progress=None):
    before = path.stat()
    if not stat.S_ISREG(before.st_mode) or before.st_nlink != 1:
        raise PathError('Input baseline harus regular file tanpa hardlink.')
    if before.st_size > MAX_INPUT_BYTES:
        raise UnsupportedELF('Input melebihi batas 2 GiB tahap ini.')
    checkpoint(cancel)
    with path.open('rb') as stream:
        opened = os.fstat(stream.fileno())
        metadata = reader(stream, opened.st_size, cancel)
        stream.seek(0)
        h = hashlib.sha256()
        total = 0
        next_notice = 0
        while True:
            checkpoint(cancel)
            raw = stream.read(1024 * 1024)
            if not raw:
                break
            h.update(raw)
            total += len(raw)
            if total > MAX_INPUT_BYTES:
                raise ValidationError('Input tumbuh saat dibaca; baseline dibatalkan.')
            if progress and total >= next_notice:
                progress({'event':'baseline_hash', 'bytes_read':total, 'total_bytes':opened.st_size})
                next_notice = total + 32 * 1024**2
        after = os.fstat(stream.fileno())
    if not identity(before) == identity(opened) == identity(after) == identity(path.stat()) or total != opened.st_size:
        raise ValidationError('Input berubah saat parsing/hashing; tidak membuat baseline.')
    checkpoint(cancel)
    return metadata, h.hexdigest(), total


def inspect_file(path, cancel=None, progress=None):
    metadata, digest, total = _inspect_file(path, parse, cancel, progress)
    return {'baseline_schema':1, 'source_sha256':digest, 'source_size':total,
            'metadata':metadata,
            'evidence':{'status':'VERIFIED', 'claim':'Structural fields read from these hashed bytes only',
                        'criteria':'elf32le-mips-structural-v1', 'parser':PARSER_VERSION,
                        'not_proven':['PS2 game identity','EE/IOP/VU role','instruction semantics','retail matching']}}


def create_baseline(store, input_id, cancel=None, progress=None):
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id']==input_id), None)
    if item is None:
        raise ValidationError('ID input tidak ada. Daftarkan file lalu pilih ID dari workspace.')
    path = resolve_input(store, item)
    report = inspect_file(path, cancel, progress)
    if report['source_sha256'] != item['sha256'] or report['source_size'] != item['size_bytes']:
        raise ConflictError('Input berbeda dari hash saat registrasi; baseline tidak dipublikasikan. Periksa file asli.')
    raw = (json.dumps(report, ensure_ascii=False, indent=2)+'\n').encode('utf-8')
    relative = f"baselines/{report['source_sha256']}/{PARSER_VERSION}.json"
    receipt_id = str(uuid4())
    receipt = {'receipt_schema':1, 'receipt_id':receipt_id, 'created_at':now(),
               'workspace_id':snapshot.data['workspace_id'], 'workspace_revision':snapshot.data['revision'],
               'manifest_token':snapshot.token, 'input_id':input_id, 'input_reference':item['path'],
               'source_sha256':report['source_sha256'], 'report_path':relative,
               'report_sha256':hashlib.sha256(raw).hexdigest(), 'parser':PARSER_VERSION,
               'status':'baseline_created'}
    with store.lock():
        checkpoint(cancel)
        if store.load().token != snapshot.token:
            raise ConflictError('Workspace berubah saat baseline berjalan; buka ulang dan coba lagi.')
        for directory in ('baselines', f"baselines/{report['source_sha256']}", 'baselines/records'):
            store.managed(directory).mkdir(exist_ok=True)
        destination = store.managed(relative)
        if destination.exists():
            if read_bytes(destination) != raw:
                raise ConflictError('Baseline dengan hash/parser sama berbeda atau korup; tidak ditimpa.')
        else:
            store.atomic(relative, raw)
        # Commit phase: cancellation after this point does not revoke an already published baseline.
        store.atomic(f'baselines/records/{receipt_id}.json',
                     (json.dumps(receipt, ensure_ascii=False, indent=2)+'\n').encode('utf-8'))
    return {'baseline':report, 'receipt':receipt, 'report_file':str(destination)}
