"""Bounded ELF32 REL/RELA inventory for one symbol. Does not apply relocations."""
import struct

from app.domain.binary.elf import parse, checkpoint, InvalidELF, UnsupportedELF
from app.domain.binary.symbols import parse_symbols

VERSION = 'elf32le-mips-function-refs-2'
MAX_RELOCATIONS = 262144
MAX_MATCHES = 1024
TYPES = {0:'R_MIPS_NONE',1:'R_MIPS_16',2:'R_MIPS_32',3:'R_MIPS_REL32',4:'R_MIPS_26',
         5:'R_MIPS_HI16',6:'R_MIPS_LO16',7:'R_MIPS_GPREL16',8:'R_MIPS_LITERAL',
         9:'R_MIPS_GOT16',10:'R_MIPS_PC16',11:'R_MIPS_CALL16',12:'R_MIPS_GPREL32'}


def function_refs(stream, file_size, symbol_id, cancel=None, capture=None):
    metadata = parse(stream, file_size, cancel)
    inventory = parse_symbols(stream, file_size, cancel)
    symbols = {s['id']: s for s in inventory['symbols']}
    selected = symbols.get(symbol_id)
    if selected is None:
        raise InvalidELF('ID simbol tidak ditemukan.')
    if selected['type'] != 2 or selected['definition'] != 'SECTION' or selected['end_exclusive'] is None or selected['warnings']:
        raise UnsupportedELF('Pilih FUNC section-defined dengan rentang diketahui dan tanpa peringatan.')
    sections = metadata['sections']
    tables, matches, dependencies = [], [], {}
    total = 0
    type_counts = {}

    def require(condition, message):
        if not condition:
            raise InvalidELF(message)

    for table in sections:
        if table['type'] not in (4, 9):
            continue
        entry_size = 12 if table['type'] == 4 else 8
        require(table['entry_size'] == entry_size and table['size'] % entry_size == 0,
                'Ukuran entri REL/RELA ELF32 invalid.')
        linked = sections[table['link']]
        require(linked['type'] in (2, 11), 'sh_link relokasi harus SYMTAB/DYNSYM.')
        count = table['size'] // entry_size
        total += count
        if total > MAX_RELOCATIONS:
            raise UnsupportedELF('Relokasi melebihi batas 262144 entri; hasil tidak dipotong.')
        target_index = table['info']
        if metadata['elf_type'] == 1:
            require(target_index != 0, 'ET_REL membutuhkan target section pada sh_info.')
        target = sections[target_index] if target_index else None
        tables.append({'section_index': table['index'], 'name': table['name'], 'kind': table['type_name'],
                       'count': count, 'symbol_table_index': table['link'], 'target_section_index': target_index})
        for index in range(count):
            checkpoint(cancel)
            entry_offset = table['offset'] + index * entry_size
            stream.seek(entry_offset)
            raw = stream.read(entry_size)
            require(len(raw) == entry_size, 'Relokasi terpotong saat dibaca.')
            location, info = struct.unpack_from('<II', raw)
            symbol_index, typ = info >> 8, info & 255
            type_counts[str(typ)] = type_counts.get(str(typ), 0) + 1
            reference_id = f'{table["link"]}:{symbol_index}'
            require(reference_id in symbols, 'Indeks simbol relokasi di luar tabel terkait.')
            reference = symbols[reference_id]
            relative = None
            if target:
                relative = location if metadata['elf_type'] == 1 else location-int(target['address'],16)
                if typ != 0:
                    require(0 <= relative < target['size'], 'Lokasi relokasi di luar target section.')
            if capture is not None and typ != 0 and symbol_index != 0:
                capture.add(target_index, location, {
                    'id': f'{table["index"]}:{index}', 'symbol_id': reference_id,
                    'type': typ, 'type_name': TYPES.get(typ,'UNKNOWN'),
                    'addend': struct.unpack_from('<i',raw,8)[0] if entry_size == 12 else None,
                    'addend_source': 'EXPLICIT' if entry_size == 12 else 'IMPLICIT_NOT_DECODED',
                })
            in_section = target_index == selected['section_index'] or (not target_index and metadata['elf_type'] != 1)
            inside = in_section and selected['start'] <= location < selected['end_exclusive']
            refers_to_selected = reference_id == symbol_id and typ != 0
            if not inside and not refers_to_selected:
                continue
            if len(matches) >= MAX_MATCHES:
                raise UnsupportedELF('Lebih dari 1024 relokasi terkait fungsi; laporan tidak dipotong.')
            file_offset = target['offset'] + relative if target and target['file_backed'] and relative is not None and 0 <= relative < target['size'] else None
            row = {'id': f'{table["index"]}:{index}', 'entry_file_offset': entry_offset,
                   'relocation_section_index': table['index'], 'entry_index': index,
                   'r_offset': location, 'r_info': info, 'type': typ, 'type_name': TYPES.get(typ,'UNKNOWN'),
                   'symbol_id': reference_id, 'symbol_name': reference['name'], 'symbol_definition': reference['definition'],
                   'target_section_index': target_index, 'location_file_offset': file_offset,
                   'addend': struct.unpack_from('<i',raw,8)[0] if entry_size == 12 else None,
                   'addend_source': 'EXPLICIT' if entry_size == 12 else 'IMPLICIT_NOT_DECODED',
                   'location_inside_selected_range': inside, 'references_selected_symbol': refers_to_selected,
                   'applies_change': False, 'semantics_verified': False}
            matches.append(row)
            if inside and typ != 0 and symbol_index != 0:
                dependency = dependencies.setdefault(reference_id, {'symbol_id': reference_id,
                    'name': reference['name'], 'name_bytes_hex': reference['name_bytes_hex'],
                    'definition': reference['definition'], 'type_name': reference['type_name'],
                    'value': reference['value'], 'relocation_ids': [], 'relationship': 'RELOCATION_REFERENCE_NOT_CALL_GRAPH'})
                dependency['relocation_ids'].append(row['id'])
    return {'parser': VERSION, 'selected_symbol': selected, 'elf_type': metadata['elf_type_name'],
            'relocation_tables': tables, 'total_relocations_scanned': total, 'matches': matches,
            'type_counts': type_counts, 'unknown_type_counts': {k:v for k,v in type_counts.items() if int(k) not in TYPES},
            'referenced_symbols': list(dependencies.values()),
            'counts': {'matches': len(matches), 'inside_range': sum(x['location_inside_selected_range'] for x in matches),
                       'references_selected': sum(x['references_selected_symbol'] for x in matches),
                       'referenced_symbols': len(dependencies)},
            'scope': 'First-byte relocation locations and exact symbol-table references, not call graph or complete dependencies',
            'relocations_applied': False, 'warnings': [
                'REL addends and MIPS HI16/LO16 pairing are not interpreted.',
                'Field width, target value, aliases, symbol+addend and indirect/code-only references are unresolved.',
                'No matching records does not prove no dependencies.']}
