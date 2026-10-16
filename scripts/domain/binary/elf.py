"""Bounded structural ELF32 little-endian MIPS reader, not a disassembler."""
import struct
from app.domain.workspace.model import WorkspaceError


class InvalidELF(WorkspaceError):
    code = 'invalid_elf'


class UnsupportedELF(WorkspaceError):
    code = 'unsupported_elf'


class Cancelled(WorkspaceError):
    code = 'cancelled'


PARSER_VERSION = 'elf32le-mips-1'
MAX_SECTIONS = 512
MAX_SEGMENTS = 256
MAX_STRING_TABLE = 1024 * 1024


def checkpoint(cancel):
    if cancel is not None and cancel.is_set():
        raise Cancelled('Pemeriksaan baseline dibatalkan; tidak ada baseline baru dipublikasikan.')


def parse(stream, file_size, cancel=None):
    """Read a seekable binary stream of declared size, with bounds before every read."""
    def check(condition, message):
        if not condition:
            raise InvalidELF(message)

    def bounds(offset, size, label):
        check(0 <= offset <= file_size and 0 <= size <= file_size - offset,
              f'{label}: offset/ukuran di luar file ({offset}, {size}).')

    def read(offset, size, label):
        checkpoint(cancel)
        bounds(offset, size, label)
        stream.seek(offset)
        raw = stream.read(size)
        check(len(raw) == size, f'{label}: file terpotong saat dibaca.')
        return raw

    if file_size < 4 or read(0, 4, 'magic') != b'\x7fELF':
        raise UnsupportedELF('Bukan ELF. ISO/BIN/disc image belum didukung; ekstrak ELF secara eksplisit terlebih dahulu.')
    ident = read(0, 16, 'e_ident')
    check(ident[4] in (1, 2) and ident[5] in (1, 2), 'Class atau byte order ELF invalid.')
    if ident[4] != 1 or ident[5] != 1:
        raise UnsupportedELF('Tahap 2 hanya mendukung ELF32 little-endian; ELF64/big-endian belum didukung.')
    check(ident[6] == 1, 'EI_VERSION ELF invalid.')
    header = struct.unpack('<HHIIIIIHHHHHH', read(16, 36, 'ELF32 header'))
    (etype, machine, version, entry, phoff, shoff, flags, ehsize,
     phentsize, phnum, shentsize, shnum, shstrndx) = header
    check(version == 1 and ehsize == 52, 'Versi atau ukuran header ELF32 invalid.')
    if machine != 8:
        raise UnsupportedELF(f'e_machine={machine}; parser ini hanya menerima EM_MIPS (8).')
    if etype not in (1, 2, 3):
        raise UnsupportedELF(f'e_type={etype} belum didukung (hanya REL/EXEC/DYN).')
    if phnum == 0xffff or shstrndx == 0xffff or (shnum == 0 and shoff != 0):
        raise UnsupportedELF('Extended numbering ELF belum didukung; file tidak dianggap invalid hanya karena fitur ini.')
    if phnum > MAX_SEGMENTS or shnum > MAX_SECTIONS:
        raise UnsupportedELF('Jumlah segment/section melebihi batas parser tahap ini (256/512).')
    check((phnum == 0 and phoff == 0) or (phnum > 0 and phoff >= ehsize and phentsize == 32),
          'Program header table offset/entry size invalid.')
    check((shnum == 0 and shoff == 0 and shstrndx == 0) or
          (shnum > 0 and shoff >= ehsize and shentsize == 40 and shstrndx < shnum),
          'Section header table offset/entry size/string index invalid.')
    if phnum:
        bounds(phoff, phnum * phentsize, 'program header table')
    if shnum:
        bounds(shoff, shnum * shentsize, 'section header table')
    warnings = []
    if not shnum:
        warnings.append('Tidak ada section table; baseline hanya header/segment, bukan inventaris fungsi.')
    segments = []
    for index in range(phnum):
        values = struct.unpack('<IIIIIIII', read(phoff + index*32, 32, 'program header'))
        typ, off, va, pa, filesz, memsz, pflags, align = values
        if typ == 0:  # PT_NULL: remaining fields are undefined, retain but do not dereference
            segments.append(dict(index=index, type=typ, type_name='NULL', offset=off,
                                 virtual_address=f'0x{va:08x}', physical_address=f'0x{pa:08x}',
                                 file_size=filesz, memory_size=memsz, flags=pflags, alignment=align,
                                 interpreted=False))
            continue
        bounds(off, filesz, f'segment {index}')
        check(align in (0, 1) or align & (align-1) == 0, f'Segment {index}: alignment bukan pangkat dua.')
        if typ == 1:
            check(filesz <= memsz, f'PT_LOAD {index}: filesz > memsz.')
            check(va + memsz <= 2**32, f'PT_LOAD {index}: rentang alamat overflow ELF32.')
            check(align in (0, 1) or va % align == off % align,
                  f'PT_LOAD {index}: vaddr/offset tidak kongruen dengan alignment.')
        segments.append(dict(index=index, type=typ, type_name={1:'LOAD',2:'DYNAMIC',3:'INTERP',4:'NOTE',6:'PHDR',7:'TLS'}.get(typ,'OTHER'),
                             offset=off, virtual_address=f'0x{va:08x}', physical_address=f'0x{pa:08x}',
                             file_size=filesz, memory_size=memsz, flags=pflags, alignment=align,
                             interpreted=True))
    sections = []
    for index in range(shnum):
        values = struct.unpack('<IIIIIIIIII', read(shoff + index*40, 40, 'section header'))
        name, typ, sflags, addr, off, size, link, info, align, entsize = values
        if index == 0:
            check(all(value == 0 for value in values), 'Section 0 harus NULL (extended numbering tidak didukung).')
        elif typ != 0:
            if typ != 8:  # SHT_NOBITS occupies no file bytes
                bounds(off, size, f'section {index}')
            check(align in (0, 1) or align & (align-1) == 0, f'Section {index}: alignment invalid.')
            if sflags & 2:
                check(addr + size <= 2**32, f'Section {index}: alamat ALLOC overflow.')
            check(entsize == 0 or size % entsize == 0, f'Section {index}: ukuran bukan kelipatan entsize.')
            if typ in (2, 4, 6, 9, 11, 17, 18):
                check(link < shnum, f'Section {index}: sh_link invalid.')
            if typ in (4, 9):
                check(info < shnum, f'Section {index}: target relocation invalid.')
        sections.append(dict(index=index, name_offset=name, name='', type=typ,
                             type_name={0:'NULL',1:'PROGBITS',2:'SYMTAB',3:'STRTAB',4:'RELA',8:'NOBITS',9:'REL',11:'DYNSYM'}.get(typ,'OTHER'),
                             flags=sflags, address=f'0x{addr:08x}', offset=off, size=size,
                             link=link, info=info, alignment=align, entry_size=entsize,
                             file_backed=typ not in (0, 8)))
    if shstrndx:
        names = sections[shstrndx]
        check(names['type'] == 3, 'shstrndx harus menunjuk SHT_STRTAB.')
        if names['size'] > MAX_STRING_TABLE:
            raise UnsupportedELF('Section name string table melebihi 1 MiB.')
        table = read(names['offset'], names['size'], 'section name string table')
        check(bool(table) and table[0] == 0 and table[-1] == 0, 'String table nama harus mulai/berakhir NUL.')
        for section in sections:
            if section['type'] == 0:
                continue
            start = section['name_offset']
            check(start < len(table), 'Offset nama section di luar string table.')
            end = table.find(b'\0', start)
            check(end >= start, 'Nama section tanpa terminator.')
            if end - start > 256:
                raise UnsupportedELF('Nama section lebih dari 256 byte; batas laporan parser.')
            raw = table[start:end]
            section['name'] = raw.decode('utf-8', errors='replace')
            section['name_bytes_hex'] = raw.hex()
    elif any(s['name_offset'] for s in sections if s['type'] != 0):
        check(False, 'Nama section merujuk string table yang tidak tersedia.')
    mapped = [p['index'] for p in segments if p['type']==1 and
              int(p['virtual_address'],16) <= entry < int(p['virtual_address'],16)+p['memory_size']]
    if etype == 2 and not mapped:
        warnings.append('Entry point tidak terpetakan dalam PT_LOAD; perlu pemeriksaan format/loading khusus.')
    if len(mapped) > 1:
        warnings.append('Entry point berada pada beberapa PT_LOAD; pemetaan ambigu/overlap perlu diperiksa.')
    checkpoint(cancel)
    return dict(parser=PARSER_VERSION, format='ELF32', byte_order='little', machine=machine,
                architecture='MIPS', elf_type=etype, elf_type_name={1:'REL',2:'EXEC',3:'DYN'}[etype],
                elf_version=version, osabi=ident[7], abi_version=ident[8],
                flags=f'0x{flags:08x}', entry_point=f'0x{entry:08x}', header_size=ehsize,
                program_header_offset=phoff, section_header_offset=shoff,
                section_name_table_index=shstrndx, entry_load_segments=mapped,
                segments=segments, sections=sections, warnings=warnings,
                target={'value':'UNKNOWN', 'evidence_status':'UNRESOLVED',
                        'reason':'EM_MIPS tidak membuktikan EE/IOP/VU atau game PS2; e_flags dicatat tanpa menebak ABI.'},
                validation_scope='ELF32 header, table bounds, segment/section ranges and names; no code/relocation semantics')
