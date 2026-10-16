"""ELF-declared symbols only; no guessed function recovery or disassembly."""
import struct

from app.domain.binary.elf import parse, checkpoint, InvalidELF, UnsupportedELF

VERSION = 'elf32le-mips-symbols-2'
MAX_SYMBOLS = 65536
MAX_NAMES = 1024 * 1024


def parse_symbols(stream, file_size, cancel=None):
    metadata = parse(stream, file_size, cancel)
    sections = metadata['sections']
    tables, symbols, warnings = [], [], list(metadata['warnings'])

    def require(condition, message):
        if not condition:
            raise InvalidELF(message)

    def read(offset, size):
        checkpoint(cancel)
        require(0 <= offset <= file_size and 0 <= size <= file_size - offset,
                'Symbol data di luar file.')
        stream.seek(offset)
        raw = stream.read(size)
        require(len(raw) == size, 'Symbol data terpotong.')
        return raw

    for table in sections:
        if table['type'] not in (2, 11):
            continue
        require(table['entry_size'] == 16 and table['size'] % 16 == 0,
                'ELF32 symbol entry harus 16 byte.')
        count = table['size'] // 16
        require(count >= 1 and 1 <= table['info'] <= count, 'Symbol count/sh_info invalid.')
        if len(symbols) + count > MAX_SYMBOLS:
            raise UnsupportedELF('Inventaris awal dibatasi 65536 simbol total; tidak memotong hasil diam-diam.')
        names = sections[table['link']]
        require(names['type'] == 3, 'Symbol sh_link harus menunjuk STRTAB.')
        if names['size'] > MAX_NAMES:
            raise UnsupportedELF('Symbol string table melebihi 1 MiB.')
        strings = read(names['offset'], names['size'])
        require(not strings or strings[0] == strings[-1] == 0, 'Symbol STRTAB tidak dibatasi NUL.')
        tables.append({'section_index': table['index'], 'kind': table['type_name'],
                       'name': table['name'], 'count': count, 'string_section_index': names['index']})
        for index in range(count):
            offset = table['offset'] + index * 16
            entry = read(offset, 16)
            name, value, size, info, other, shndx = struct.unpack('<IIIBBH', entry)
            if index == 0:
                require(entry == bytes(16), 'Simbol pertama harus NULL.')
            binding, typ = info >> 4, info & 15
            require((binding == 0) == (index < table['info']), 'Urutan LOCAL/sh_info tidak sesuai.')
            if shndx == 0xffff:
                raise UnsupportedELF('SHN_XINDEX simbol belum didukung.')
            require(shndx == 0 or shndx >= 0xff00 or shndx < len(sections), 'Indeks section simbol invalid.')
            raw_name = b''
            if name:
                require(name < len(strings), 'Offset nama simbol di luar STRTAB.')
                end = strings.find(b'\0', name, min(len(strings), name + 258))
                if end < 0 or end - name > 256:
                    raise UnsupportedELF('Nama simbol melebihi 256 byte atau tanpa terminator dalam batas.')
                raw_name = strings[name:end]
            definition = ('UNDEFINED' if shndx == 0 else 'ABSOLUTE' if shndx == 0xfff1 else
                          'COMMON' if shndx == 0xfff2 else 'RESERVED' if shndx >= 0xff00 else 'SECTION')
            item = {'id': f'{table["index"]}:{index}', 'table_section_index': table['index'],
                    'symbol_index': index, 'entry_file_offset': offset,
                    'name': raw_name.decode('utf-8', errors='replace'), 'name_bytes_hex': raw_name.hex(),
                    'value': value, 'size': size, 'type': typ,
                    'type_name': {0:'NOTYPE',1:'OBJECT',2:'FUNC',3:'SECTION',4:'FILE',5:'COMMON',6:'TLS'}.get(typ,'OTHER'),
                    'binding': binding, 'binding_name': {0:'LOCAL',1:'GLOBAL',2:'WEAK'}.get(binding,'OTHER'),
                    'other_raw': other, 'section_index': shndx, 'definition': definition,
                    'evidence': 'ELF_DECLARED', 'start': None, 'end_exclusive': None,
                    'file_offset': None, 'address_kind': 'UNRESOLVED', 'warnings': []}
            if typ == 2 and definition == 'SECTION':
                section = sections[shndx]
                relative = value if metadata['elf_type'] == 1 else value - int(section['address'], 16)
                item['address_kind'] = 'SECTION_OFFSET' if metadata['elf_type'] == 1 else 'VIRTUAL_ADDRESS'
                item['start'] = value
                if not section['flags'] & 4:
                    item['warnings'].append('Section tidak bertanda executable; identitas fungsi belum diverifikasi.')
                if relative < 0 or relative >= section['size'] or size > section['size'] - relative or value + size > 2**32:
                    item['warnings'].append('Rentang simbol di luar section/ELF32; end dan file offset tidak disimpulkan.')
                else:
                    if size:
                        item['end_exclusive'] = value + size
                    else:
                        item['warnings'].append('Ukuran nol: batas akhir tidak diketahui.')
                    if section['file_backed']:
                        item['file_offset'] = section['offset'] + relative
                if other & ~3:
                    item['warnings'].append('Bit st_other khusus target belum diinterpretasi; alamat mentah dipertahankan.')
            symbols.append(item)
    if not tables:
        warnings.append('Tidak ada SYMTAB/DYNSYM berbasis section. Fungsi tidak ditebak dari entry point atau bytes.')
    return {'parser': VERSION, 'elf_type': metadata['elf_type_name'], 'target': metadata['target'],
            'tables': tables, 'symbols': symbols,
            'function_symbol_ids': [s['id'] for s in symbols if s['type'] == 2],
            'counts': {'symbols': len(symbols), 'function_symbols': sum(s['type'] == 2 for s in symbols),
                       'section_defined_functions': sum(s['type'] == 2 and s['definition'] == 'SECTION' for s in symbols)},
            'warnings': warnings,
            'scope': 'Declared symbol metadata only; aliases retained; no disassembly, ABI interpretation or stripped function recovery'}
