"""Bundle direct relocation-referenced OBJECT ranges with their function bytes."""
import hashlib
import re
from collections import deque

from app.application.baselines import _inspect_file
from app.application.data_symbols import bounds, inventory
from app.application.extractions import rejection
from app.application.targets import encoded
from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint
from app.domain.binary.relocations import function_refs
from app.domain.binary.reference_index import ReferenceIndex
from app.domain.workspace.model import ConflictError, ValidationError
from app.infrastructure.persistence.store import MAX_MANIFEST, read_bytes

VERSION = 'function-data-2'
MAX_OBJECTS = 64
MAX_PAYLOAD = 16 * 1024 * 1024


def function_data(store, input_id, symbol_id, verify=False, cancel=None, data_depth=0):
    if type(data_depth) is not int or not 0 <= data_depth <= 4:
        raise ValidationError('data-depth harus integer 0–4.')
    if not isinstance(symbol_id, str) or not re.fullmatch(
        r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})', symbol_id
    ):
        raise ValidationError('symbol-id harus table:index canonical.')
    snapshot = store.load()
    item = next((x for x in snapshot.data['inputs'] if x['id'] == input_id), None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan.')

    def reader(stream, size, token):
        index = ReferenceIndex() if data_depth else None
        refs = function_refs(stream, size, symbol_id, token, capture=index)
        if index is not None:
            index.finish()
        selected = refs['selected_symbol']
        reason = rejection(selected)
        if reason:
            raise ValidationError(reason)
        symbols, elf = inventory(stream, size, token)
        by_id = {s['id']: s for s in symbols['symbols']}
        files = {}
        rows = []
        total_bytes = 0
        object_count = 0

        def read_payload(name, offset, length):
            nonlocal total_bytes
            checkpoint(token)
            if length > MAX_PAYLOAD - total_bytes:
                raise ValidationError('Total payload function/data melebihi 16 MiB.')
            stream.seek(offset)
            raw = stream.read(length)
            if len(raw) != length:
                raise ValidationError('Byte function/data terpotong.')
            files[name] = raw
            total_bytes += length
            return {'file': name, 'size': length, 'sha256': hashlib.sha256(raw).hexdigest()}

        function_payload = read_payload('function.bin', selected['file_offset'], selected['size'])
        queue = deque((reference, 0, symbol_id) for reference in refs['referenced_symbols'])
        visited = set()
        edges = []
        frontier = []
        while queue:
            checkpoint(token)
            reference, depth, source_id = queue.popleft()
            target_id = reference['symbol_id']
            edges.append({'source_id': source_id, 'target_id': target_id,
                          'relocation_ids': reference['relocation_ids']})
            if target_id in visited:
                continue
            visited.add(target_id)
            if len(visited) > 1024:
                raise ValidationError('Maksimum 1024 simbol yang ditemukan.')
            symbol = by_id[target_id]
            row = dict(reference, depth=depth)
            if symbol['type'] != 1:
                row.update(status='NOT_OBJECT', reason='Di luar cakupan ekstraksi data OBJECT.')
            else:
                object_count += 1
                if object_count > MAX_OBJECTS:
                    raise ValidationError('Maksimum 64 OBJECT yang direferensikan per fungsi.')
                try:
                    resolved = bounds(symbol, elf)
                except ValidationError as exc:
                    row.update(status='UNRESOLVED', reason=str(exc))
                else:
                    row['range'] = resolved
                    if resolved['file_offset'] is None:
                        row.update(status='NOBITS', payload=None)
                    else:
                        filename = 'object-' + target_id.replace(':', '-') + '.bin'
                        row.update(status='EXTRACTED', payload=read_payload(
                            filename, resolved['file_offset'], resolved['size']))
                    if depth >= data_depth:
                        frontier.append(target_id)
                    else:
                        records = index.within(resolved, refs['elf_type'])
                        row['outgoing_relocations'] = records
                        grouped = {}
                        for record in records:
                            child_id = record['symbol_id']
                            child = by_id[child_id]
                            ref = grouped.setdefault(child_id, {
                                'symbol_id': child_id, 'name': child['name'],
                                'name_bytes_hex': child['name_bytes_hex'],
                                'definition': child['definition'], 'type_name': child['type_name'],
                                'value': child['value'], 'relocation_ids': [],
                                'relationship': 'RELOCATION_REFERENCE_NOT_CALL_GRAPH',
                            })
                            ref['relocation_ids'].append(record['id'])
                        queue.extend((ref, depth + 1, target_id) for ref in grouped.values())
            rows.append(row)
        return files, selected, function_payload, rows, refs, total_bytes, edges, frontier

    result, digest, size = _inspect_file(resolve_input(store, item), reader, cancel)
    if (digest, size) != (item['sha256'], item['size_bytes']):
        raise ConflictError('ELF berubah sejak registrasi.')
    files, selected, function_payload, rows, refs, total_bytes, edges, frontier = result
    counts = {status: sum(row['status'] == status for row in rows)
              for status in ('EXTRACTED', 'NOBITS', 'UNRESOLVED', 'NOT_OBJECT')}
    report = {
        'schema': 1, 'extractor': VERSION, 'source_sha256': digest, 'source_size': size,
        'function': selected, 'function_payload': function_payload,
        'references': rows, 'counts': counts, 'payload_bytes': total_bytes,
        'dependency_completeness': 'UNVERIFIED', 'recursive': data_depth > 0,
        'data_depth': data_depth, 'edges': edges, 'unexpanded_object_ids': frontier,
        'relocations_applied': False, 'executed': False,
        'reference_scope': 'Relocation symbol-table references; bounded OBJECT traversal',
        'relocation_matches': refs['matches'],
        'limitations': 'Symbol+addend and indirect references are not resolved; traversal stops at the requested depth.',
    }
    if data_depth == 0:
        # Preserve version 1 bytes and paths for existing direct-only bundles.
        report['extractor'] = 'function-data-1'
        report['reference_scope'] = 'Direct symbol-table references from relocations inside the selected function'
        report['limitations'] = 'Symbol+addend, indirect references and transitive dependencies are not resolved.'
        for key in ('data_depth', 'edges', 'unexpanded_object_ids'):
            del report[key]
        for row in rows:
            del row['depth']
    files['report.json'] = encoded(report)
    if len(files['report.json']) > MAX_MANIFEST:
        raise ValidationError('Laporan function/data melebihi 1 MiB.')
    base = f'function-data/{digest}/{VERSION}/{symbol_id.replace(":", "-")}/depth-{data_depth}'
    if data_depth == 0:
        base = f'function-data/{digest}/function-data-1/{symbol_id.replace(":", "-")}'
    with store.lock():
        checkpoint(cancel)
        if store.load().token != snapshot.token:
            raise ConflictError('Manifest berubah selama ekstraksi function/data.')
        folder = store.managed(base)
        if folder.exists() and {p.name for p in folder.iterdir()} - set(files):
            raise ConflictError('Paket function/data memuat file tak terduga.')
        for name, data in files.items():
            path = store.managed(base + '/' + name)
            if verify or path.exists():
                if read_bytes(path) != data:
                    raise ConflictError('Paket function/data berbeda atau korup: ' + name)
        if not verify:
            parts = base.split('/')
            for index in range(1, len(parts) + 1):
                store.managed('/'.join(parts[:index])).mkdir(exist_ok=True)
            # Publish report last; a failed write can be retried without replacing existing files.
            for name, data in files.items():
                checkpoint(cancel)
                if not store.managed(base + '/' + name).exists():
                    store.atomic(base + '/' + name, data)
    return {
        'status': 'VERIFIED_SOURCE_BYTES' if verify else 'EXPORTED',
        'function_id': symbol_id, 'data_depth': data_depth, 'counts': counts, 'payload_bytes': total_bytes,
        'unexpanded_objects': len(frontier),
        'dependency_completeness': 'UNVERIFIED', 'bundle_dir': str(folder),
        'report_file': str(folder / 'report.json'),
    }
