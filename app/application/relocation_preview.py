"""Hypothetical classic-MIPS HI16/LO16 arithmetic. Never patches an input."""
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

VERSION = 'mips-hi-lo-preview-1'


def calculate(hi_word, lo_word, symbol_value):
    for value in (hi_word, lo_word, symbol_value):
        if type(value) is not int or not 0 <= value <= 0xffffffff:
            raise ValidationError('Operand harus integer unsigned 32-bit.')
    # Limit to LUI rt,imm; ADDIU rt,rt,imm. ORI has different low-half semantics.
    register = (hi_word >> 16) & 31
    if hi_word >> 26 != 15 or (hi_word >> 21) & 31 or register == 0:
        raise UnsupportedELF('HI harus pola LUI register nonzero pada encoding MIPS klasik.')
    if lo_word >> 26 != 9 or (lo_word >> 21) & 31 != register or (lo_word >> 16) & 31 != register:
        raise UnsupportedELF('LO harus pola ADDIU dengan register yang sama; ORI/pola lain belum didukung.')
    lo = lo_word & 0xffff
    signed_lo = lo if lo < 0x8000 else lo - 0x10000
    addend = ((hi_word & 0xffff) << 16) + signed_lo
    mathematical = addend + symbol_value
    value32 = mathematical & 0xffffffff
    new_hi = ((value32 + 0x8000) >> 16) & 0xffff
    new_lo = value32 & 0xffff
    return {'AHL': addend, 'S_user_supplied': symbol_value, 'sum_untruncated': mathematical,
            'value32': value32, 'wrapped_to_32_bits': mathematical != value32,
            'before_words': [hi_word, lo_word],
            'preview_words': [(hi_word & 0xffff0000) | new_hi, (lo_word & 0xffff0000) | new_lo],
            'formula': 'AHL=(HI_imm<<16)+sign16(LO_imm); V=(AHL+S) mod 2^32; HI=((V+0x8000)>>16)&0xffff; LO=V&0xffff'}


def create_preview(store, input_id, function_id, hi_id, symbol_value, cancel=None):
    for identifier in (function_id, hi_id):
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
        high=next((x for x in matches if x['id']==hi_id),None)
        if high is None or high['type']!=5 or not high['location_inside_selected_range']:
            raise ValidationError('Pilih entri HI16 di dalam rentang fungsi terpilih.')
        low_id=f"{high['relocation_section_index']}:{high['entry_index']+1}"
        low=next((x for x in matches if x['id']==low_id),None)
        if low is None or low['type']!=6 or not low['location_inside_selected_range'] or low['symbol_id']!=high['symbol_id']:
            raise UnsupportedELF('Pasangan LO16 berurutan dengan simbol yang sama tidak tersedia; pairing kompleks tidak ditebak.')
        selected=refs['selected_symbol']
        for entry in (high,low):
            if entry['addend_source']!='IMPLICIT_NOT_DECODED':
                raise UnsupportedELF('Preview awal hanya SHT_REL, bukan RELA.')
            if entry['location_file_offset'] is None or entry['r_offset'] % 4 or entry['r_offset']+4>selected['end_exclusive']:
                raise UnsupportedELF('Field instruksi harus aligned, file-backed dan sepenuhnya dalam fungsi.')
        if low['r_offset'] != high['r_offset']+4 or low['location_file_offset'] != high['location_file_offset']+4:
            raise UnsupportedELF('Preview awal hanya dua instruksi bersebelahan.')
        for entry in matches:
            if entry['id'] not in (high['id'],low['id']) and entry['type']!=0 and entry['target_section_index']==high['target_section_index'] and high['r_offset']<=entry['r_offset']<low['r_offset']+4:
                raise UnsupportedELF('Ada relokasi lain pada field pasangan; tidak menghitung kasus bertumpuk.')
        inventory=parse_symbols(stream,file_size,token)
        symbol=next(s for s in inventory['symbols'] if s['id']==high['symbol_id'])
        if symbol['name'] in ('_gp_disp','__gnu_local_gp') or symbol['binding'] not in (1,2) or symbol['type'] not in (0,1,2) or symbol['other_raw'] != 0 or symbol['definition'] not in ('SECTION','UNDEFINED','ABSOLUTE'):
            raise UnsupportedELF('Simbol khusus/local-section/TLS/atribut target belum didukung oleh preview ini.')
        words=[]
        for entry in (high,low):
            checkpoint(token);stream.seek(entry['location_file_offset']);raw=stream.read(4)
            if len(raw)!=4:raise ValidationError('Input terpotong saat membaca field relokasi.')
            words.append(struct.unpack('<I',raw)[0])
        return {'elf_flags':metadata['flags'],'function':selected,'referenced_symbol':symbol,
                'relocations':[high,low], 'calculation':calculate(*words,symbol_value)}

    result,digest,size=_inspect_file(resolve_input(store,item),reader,cancel)
    if (digest,size)!=(item['sha256'],item['size_bytes']):
        raise ConflictError('Input berubah sejak registrasi; preview tidak dipublikasikan.')
    report={'preview_schema':1,'engine':VERSION,'status':'ASSUMPTION_BASED_PREVIEW',
            'source_sha256':digest,'source_size':size,'preview':result,
            'input_modified':False,'relocations_applied':False,'symbol_value_verified':False,
            'assumptions':['Classic MIPS instruction encoding; ABI/PS2 role not verified',
                           'S is an explicit hypothetical value supplied by the user, not linker-resolved',
                           'Simple adjacent REL HI16/LO16 only; no whole-link correctness claim']}
    raw=(json.dumps(report,ensure_ascii=True,indent=2)+'\n').encode()
    key=f'{function_id.replace(":","-")}-{hi_id.replace(":","-")}-{symbol_value:08x}'
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
