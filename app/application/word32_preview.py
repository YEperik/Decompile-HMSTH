"""Hypothetical R_MIPS_32 arithmetic. Never patches an input."""
import hashlib
import json
import re
import struct
from uuid import uuid4

from app.application.baselines import _inspect_file
from app.application.workspaces import resolve_input
from app.domain.binary.elf import parse, checkpoint, UnsupportedELF
from app.domain.binary.symbols import parse_symbols
from app.domain.binary.relocations import function_refs
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.persistence.store import read_bytes

VERSION = 'mips-word32-preview-1'


def calculate(addend, symbol_value):
    for value in (addend, symbol_value):
        if type(value) is not int or not 0 <= value <= 0xffffffff:
            raise ValidationError('Operand harus integer unsigned 32-bit.')
    total = addend + symbol_value
    value = total & 0xffffffff
    return {'A_unsigned': addend, 'S_user_supplied': symbol_value,
            'sum_untruncated': total, 'value32': value,
            'wrapped_to_32_bits': total != value,
            'before_bytes_le': struct.pack('<I', addend).hex(),
            'preview_bytes_le': struct.pack('<I', value).hex(),
            'formula': 'V=(A+S) mod 2^32'}


def create_preview(store, input_id, function_id, reloc_id, symbol_value, cancel=None):
    for identifier in (function_id, reloc_id):
        if not isinstance(identifier,str) or not re.fullmatch(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})',identifier):
            raise ValidationError('ID harus table-section:entry-index kanonik.')
    if type(symbol_value) is not int or not 0 <= symbol_value <= 0xffffffff:
        raise ValidationError('symbol-value harus unsigned 32-bit.')
    snapshot=store.load()
    item=next((x for x in snapshot.data['inputs'] if x['id']==input_id),None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan.')

    def reader(stream, file_size, token):
        metadata=parse(stream,file_size,token)
        if metadata['elf_type'] != 1:
            raise UnsupportedELF('Pratinjau hanya ET_REL. EXEC/DYN bisa sudah direlokasi; gunakan function-refs tanpa menerapkan ulang.')
        refs=function_refs(stream,file_size,function_id,token)
        matches=refs['matches']
        entry=next((x for x in matches if x['id']==reloc_id),None)
        if entry is None or entry['type'] != 2 or not entry['location_inside_selected_range']:
            raise ValidationError('Pilih R_MIPS_32 di dalam fungsi terpilih.')
        selected=refs['selected_symbol']
        if entry['addend_source'] != 'IMPLICIT_NOT_DECODED':
            raise UnsupportedELF('Preview awal hanya SHT_REL, bukan RELA.')
        if entry['location_file_offset'] is None or entry['r_offset'] % 4 or entry['r_offset']+4 > selected['end_exclusive']:
            raise UnsupportedELF('Field word harus aligned, file-backed dan seluruhnya dalam fungsi.')
        # Conservatively refuse any additional non-NONE relocation in this function.
        # Unknown field widths and composed relocations must not be guessed.
        if any(x['id'] != entry['id'] and x['type'] != 0 and x['location_inside_selected_range'] for x in matches):
            raise UnsupportedELF('Preview word32 hanya satu relokasi aktif dalam fungsi; komposisi belum didukung.')
        inventory=parse_symbols(stream,file_size,token)
        symbol=next(s for s in inventory['symbols'] if s['id']==entry['symbol_id'])
        if symbol['name'] in ('_gp_disp','__gnu_local_gp') or symbol['binding'] not in (1,2) or symbol['type'] not in (0,1,2) or symbol['other_raw'] != 0 or symbol['definition'] not in ('SECTION','UNDEFINED','ABSOLUTE'):
            raise UnsupportedELF('Simbol khusus/local-section/TLS/atribut target belum didukung oleh preview ini.')
        checkpoint(token)
        stream.seek(entry['location_file_offset']); raw=stream.read(4)
        if len(raw)!=4: raise ValidationError('Input terpotong saat membaca word.')
        return {'elf_flags':metadata['flags'], 'function':selected,
                'referenced_symbol':symbol, 'relocation':entry,
                'calculation':calculate(struct.unpack('<I',raw)[0],symbol_value)}

    result,digest,size=_inspect_file(resolve_input(store,item),reader,cancel)
    if (digest,size)!=(item['sha256'],item['size_bytes']):
        raise ConflictError('Input berubah sejak registrasi; preview tidak dipublikasikan.')
    report={'preview_schema':1,'engine':VERSION,'status':'ASSUMPTION_BASED_PREVIEW',
            'source_sha256':digest,'source_size':size,'preview':result,
            'input_modified':False,'relocations_applied':False,'symbol_value_verified':False,
            'assumptions':['MIPS ELF32 little-endian word field; ABI/PS2 role not verified',
                           'S is an explicit hypothetical value supplied by the user, not linker-resolved',
                           'Single active REL R_MIPS_32 in selected function only; no whole-link correctness claim']}
    raw=(json.dumps(report,ensure_ascii=True,indent=2)+'\n').encode()
    key=f'{function_id.replace(":","-")}-{reloc_id.replace(":","-")}-{symbol_value:08x}'
    base=f'previews/{digest}/{VERSION}'
    relative=f'{base}/{key}.json';receipt_id=str(uuid4())
    receipt={'receipt_id':receipt_id,'created_at':now(),'input_id':input_id,
             'workspace_id':snapshot.data['workspace_id'],'manifest_token':snapshot.token,
             'report_path':relative,'report_sha256':hashlib.sha256(raw).hexdigest()}
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah saat preview.')
        for directory in ('previews',f'previews/{digest}',base,'previews/records'):
            store.managed(directory).mkdir(exist_ok=True)
        destination=store.managed(relative)
        if destination.exists():
            if read_bytes(destination)!=raw:raise ConflictError('Preview berbeda/korup; tidak ditimpa.')
        else:store.atomic(relative,raw)
        store.atomic(f'previews/records/{receipt_id}.json',(json.dumps(receipt,indent=2)+'\n').encode())
    return {'report':report,'receipt':receipt,'report_file':str(destination)}
