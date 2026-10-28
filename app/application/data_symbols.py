"""Exact ELF OBJECT ranges, without inferred size or pointer interpretation."""
import hashlib
import re
from app.application.baselines import _inspect_file
from app.application.targets import encoded
from app.application.workspaces import resolve_input
from app.domain.binary.elf import parse,checkpoint
from app.domain.binary.symbols import parse_symbols
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes,MAX_MANIFEST

VERSION='object-bytes-1'


def bounds(symbol,elf):
    if symbol['type']!=1 or symbol['definition']!='SECTION':
        raise ValidationError('Hanya OBJECT dengan section terdefinisi.')
    if not 0<symbol['size']<=MAX_MANIFEST:raise ValidationError('Ukuran OBJECT harus 1 byte–1 MiB.')
    section=elf['sections'][symbol['section_index']]
    if section['type'] not in (1,8):raise ValidationError('OBJECT memerlukan PROGBITS atau NOBITS.')
    if symbol['other_raw'] & ~3:raise ValidationError('Bit st_other khusus target belum didukung.')
    if section['flags'] & (0x400|0x800):raise ValidationError('Section TLS/compressed belum didukung.')
    relative=symbol['value'] if elf['elf_type']==1 else symbol['value']-int(section['address'],16)
    if relative<0 or relative>=section['size'] or symbol['size']>section['size']-relative or symbol['value']+symbol['size']>2**32:
        raise ValidationError('Rentang OBJECT di luar section/ELF32.')
    return {'section_index':section['index'],'section_name':section['name'],'section_offset':relative,
            'address_kind':'SECTION_OFFSET' if elf['elf_type']==1 else 'VIRTUAL_ADDRESS',
            'start':symbol['value'],'end_exclusive':symbol['value']+symbol['size'],
            'size':symbol['size'],'file_offset':section['offset']+relative if section['file_backed'] else None,
            'storage':'FILE_BYTES' if section['file_backed'] else 'NOBITS_NO_FILE_PAYLOAD'}


def inventory(stream,size,token):
    return parse_symbols(stream,size,token),parse(stream,size,token)


def list_data_symbols(path,offset=0,limit=20):
    if type(offset) is not int or offset<0 or type(limit) is not int or not 1<=limit<=200:
        raise ValidationError('offset >= 0 dan limit 1–200 diperlukan.')
    (symbols,elf),digest,_=_inspect_file(path,inventory)
    objects=[s for s in symbols['symbols'] if s['type']==1]
    rows=[]
    for symbol in objects[offset:offset+limit]:
        try:resolved=bounds(symbol,elf);reason=None
        except ValidationError as exc:resolved=None;reason=str(exc)
        rows.append({'id':symbol['id'],'name':symbol['name'],'size':symbol['size'],
                     'definition':symbol['definition'],'extractable':reason is None,'range':resolved,'rejection_reason':reason})
    return {'source_sha256':digest,'total_objects':len(objects),'offset':offset,'returned':len(rows),
            'next_offset':offset+len(rows) if offset+len(rows)<len(objects) else None,'objects':rows}


def data_bundle(store,input_id,symbol_id,verify=False,cancel=None):
    if not isinstance(symbol_id,str) or not re.fullmatch(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})',symbol_id):
        raise ValidationError('symbol-id harus table:index canonical.')
    snapshot=store.load();item=next((x for x in snapshot.data['inputs'] if x['id']==input_id),None)
    if item is None:raise ValidationError('ID input tidak ditemukan.')
    def reader(stream,size,token):
        symbols,elf=inventory(stream,size,token)
        symbol=next((s for s in symbols['symbols'] if s['id']==symbol_id),None)
        if symbol is None:raise ValidationError('Simbol tidak ditemukan.')
        resolved=bounds(symbol,elf);raw=None
        if resolved['file_offset'] is not None:
            checkpoint(token);stream.seek(resolved['file_offset']);raw=stream.read(resolved['size'])
            if len(raw)!=resolved['size']:raise ValidationError('Byte OBJECT terpotong.')
        return symbol,resolved,raw,elf['elf_type_name']
    (symbol,resolved,raw,elf_type),digest,size=_inspect_file(resolve_input(store,item),reader,cancel)
    if (digest,size)!=(item['sha256'],item['size_bytes']):raise ConflictError('ELF berubah sejak registrasi.')
    metadata={'schema':1,'extractor':VERSION,'source_sha256':digest,'source_size':size,'elf_type':elf_type,
              'symbol_id':symbol_id,'symbol_name':symbol['name'],'name_bytes_hex':symbol['name_bytes_hex'],
              'range':resolved,'payload_size':len(raw) if raw is not None else 0,
              'payload_sha256':hashlib.sha256(raw).hexdigest() if raw is not None else None,
              'relocations_applied':False,'dependency_completeness':'UNVERIFIED','executed':False}
    files={} if raw is None else {'bytes.bin':raw}
    files['object.json']=encoded(metadata)
    base=f'data/{digest}/{VERSION}/{symbol_id.replace(":","-")}'
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah selama ekstraksi data.')
        folder=store.managed(base)
        if folder.exists() and {p.name for p in folder.iterdir()}-set(files):raise ConflictError('File tak terduga pada paket OBJECT.')
        for name,data in files.items():
            path=store.managed(base+'/'+name)
            if verify or path.exists():
                if read_bytes(path)!=data:raise ConflictError('Paket OBJECT berbeda/korup: '+name)
        if not verify:
            parts=base.split('/')
            for index in range(1,len(parts)+1):store.managed('/'.join(parts[:index])).mkdir(exist_ok=True)
            for name,data in files.items():
                checkpoint(cancel)
                if not store.managed(base+'/'+name).exists():store.atomic(base+'/'+name,data)
    return {'status':'VERIFIED_SOURCE_RANGE' if verify else 'EXPORTED','symbol_id':symbol_id,
            'symbol_name':symbol['name'],'storage':resolved['storage'],'payload_size':metadata['payload_size'],
            'bundle_dir':str(folder),'metadata':metadata}
