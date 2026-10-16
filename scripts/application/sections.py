"""Extract declared section bytes; never relocate, decompress or execute them."""
import hashlib
from app.application.baselines import _inspect_file
from app.application.targets import encoded
from app.application.workspaces import resolve_input
from app.domain.binary.elf import parse,checkpoint
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes,MAX_MANIFEST

VERSION='section-bytes-1'
MAX_SECTION=32*1024*1024


def section_bundle(store,input_id,section_index,verify=False,cancel=None):
    if type(section_index) is not int or not 1<=section_index<512:
        raise ValidationError('section-index harus integer 1–511; NULL tidak diekstrak.')
    snapshot=store.load()
    item=next((x for x in snapshot.data['inputs'] if x['id']==input_id),None)
    if item is None:raise ValidationError('ID input tidak ditemukan.')
    def reader(stream,size,token):
        elf=parse(stream,size,token)
        if section_index>=len(elf['sections']):raise ValidationError('Section tidak ditemukan.')
        section=elf['sections'][section_index]
        if section['type']==0:raise ValidationError('Section NULL tidak memiliki payload.')
        if section['file_backed'] and section['size']>MAX_SECTION:
            raise ValidationError('Section file-backed melebihi 32 MiB.')
        files={};chunks=[];digest=hashlib.sha256()
        if section['file_backed']:
            stream.seek(section['offset'])
            for offset in range(0,section['size'],MAX_MANIFEST):
                checkpoint(token)
                length=min(MAX_MANIFEST,section['size']-offset)
                raw=stream.read(length)
                if len(raw)!=length:raise ValidationError('Payload section terpotong.')
                name=f'chunk-{len(chunks):04d}.bin';files[name]=raw;digest.update(raw)
                chunks.append({'file':name,'section_offset':offset,'source_offset':section['offset']+offset,
                               'size':length,'sha256':hashlib.sha256(raw).hexdigest()})
        return elf,section,files,chunks,digest.hexdigest() if section['file_backed'] else None
    (elf,section,files,chunks,payload_hash),source_hash,source_size=_inspect_file(resolve_input(store,item),reader,cancel)
    if (source_hash,source_size)!=(item['sha256'],item['size_bytes']):
        raise ConflictError('ELF berubah sejak registrasi.')
    metadata={'schema':1,'extractor':VERSION,'source_sha256':source_hash,'source_size':source_size,
              'elf_type':elf['elf_type_name'],'section':section,'chunks':chunks,
              'payload_size':section['size'] if section['file_backed'] else 0,'payload_sha256':payload_hash,
              'storage':'FILE_BYTES' if section['file_backed'] else 'NOBITS_NO_FILE_PAYLOAD',
              'elf_warnings':elf['warnings'],'relocations_applied':False,'executed':False,'standalone':False}
    files['section.json']=encoded(metadata)
    base=f'sections/{source_hash}/{VERSION}/{section_index}'
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah selama ekstraksi section.')
        folder=store.managed(base)
        if folder.exists():
            unexpected={p.name for p in folder.iterdir()}-set(files)
            if unexpected:raise ConflictError('Paket section memuat file tak terduga.')
        for name,data in files.items():
            path=store.managed(base+'/'+name)
            if verify or path.exists():
                if read_bytes(path)!=data:raise ConflictError('Artefak section berbeda/korup: '+name)
        if not verify:
            parts=base.split('/')
            for index in range(1,len(parts)+1):store.managed('/'.join(parts[:index])).mkdir(exist_ok=True)
            # Metadata last: retries can finish a partial bundle without overwriting files.
            for name,data in files.items():
                checkpoint(cancel)
                if not store.managed(base+'/'+name).exists():store.atomic(base+'/'+name,data)
    return {'status':'VERIFIED_SOURCE_BYTES' if verify else 'EXPORTED','bundle_dir':str(folder),
            'files_verified':len(files) if verify else None,'metadata':metadata}
