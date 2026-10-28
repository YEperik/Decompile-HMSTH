"""Reproducible single-function target bundles; verification never repairs outputs."""
import hashlib
import json
import re
from uuid import uuid4
from app.application.baselines import _inspect_file
from app.application.extractions import rejection
from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint
from app.domain.binary.relocations import function_refs
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.persistence.store import read_bytes, MAX_MANIFEST

VERSION = 'declared-target-1'


def encoded(value):
    return (json.dumps(value, ensure_ascii=True, sort_keys=True, indent=2)+'\n').encode()


def prepare(store, input_id, symbol_id, cancel):
    if not isinstance(symbol_id,str) or not re.fullmatch(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})',symbol_id):
        raise ValidationError('symbol-id harus table:index kanonik.')
    snapshot=store.load()
    item=next((x for x in snapshot.data['inputs'] if x['id']==input_id),None)
    if item is None:raise ValidationError('ID input tidak ditemukan.')
    def reader(stream,size,token):
        refs=function_refs(stream,size,symbol_id,token)
        symbol=refs['selected_symbol']
        reason=rejection(symbol)
        if reason:raise ValidationError(reason)
        checkpoint(token)
        stream.seek(symbol['file_offset']);payload=stream.read(symbol['size'])
        if len(payload)!=symbol['size']:raise ValidationError('Byte target terpotong.')
        return refs,payload
    (refs,payload),digest,size=_inspect_file(resolve_input(store,item),reader,cancel)
    if (digest,size)!=(item['sha256'],item['size_bytes']):
        raise ConflictError('Input berubah sejak registrasi.')
    symbol=refs['selected_symbol']
    config={'schema':1,'engine':VERSION,'source_sha256':digest,'source_size':size,
            'symbol_id':symbol_id,'boundary_policy':'ELF_DECLARED_SIZE',
            'relocation_policy':'METADATA_ONLY'}
    metadata={'schema':1,'source_sha256':digest,'elf_type':refs['elf_type'],
              'symbol':symbol,'payload_file':'bytes.bin','payload_size':len(payload),
              'payload_sha256':hashlib.sha256(payload).hexdigest(),
              'relocations_applied':False,'executed':False,'standalone':False,
              'dependency_completeness':'UNVERIFIED',
              'limitations':['Declared symbol range only; semantics not verified',
                             'Reference metadata does not extract dependent bytes',
                             'No source reconstruction, disassembly or compiler matching']}
    files={'config.json':encoded(config),'metadata.json':encoded(metadata),
           'references.json':encoded(refs),'bytes.bin':payload}
    for data in files.values():
        if len(data)>MAX_MANIFEST:raise ValidationError('Artefak target melebihi 1 MiB.')
    index={'schema':1,'engine':VERSION,'source_sha256':digest,
           'files':{name:{'size':len(data),'sha256':hashlib.sha256(data).hexdigest()} for name,data in files.items()}}
    files['index.json']=encoded(index)
    base=f'targets/{digest}/{VERSION}/{symbol_id.replace(":","-")}'
    return snapshot,files,base


def target_bundle(store,input_id,symbol_id,verify=False,cancel=None):
    snapshot,files,base=prepare(store,input_id,symbol_id,cancel)
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah saat membaca target.')
        # Validate every existing artifact before publishing any missing artifact.
        for name,data in files.items():
            path=store.managed(base+'/'+name)
            if verify or path.exists():
                if read_bytes(path)!=data:
                    raise ConflictError('Artefak target berbeda dari sumber/konfigurasi: '+name)
        if verify:
            return {'status':'VERIFIED_SOURCE_BYTES_AND_METADATA','bundle_dir':str(store.managed(base)),
                    'files_verified':len(files),'source_sha256':snapshot.data['inputs'][next(i for i,x in enumerate(snapshot.data['inputs']) if x['id']==input_id)]['sha256'],
                    'semantics_verified':False,'relocations_applied':False}
        for index in range(1,len(base.split('/'))+1):
            store.managed('/'.join(base.split('/')[:index])).mkdir(exist_ok=True)
        store.managed('targets/records').mkdir(exist_ok=True)
        for name,data in files.items():
            if not store.managed(base+'/'+name).exists():store.atomic(base+'/'+name,data)
        receipt={'id':str(uuid4()),'created_at':now(),'input_id':input_id,
                 'workspace_id':snapshot.data['workspace_id'],'manifest_token':snapshot.token,
                 'bundle_path':base,'index_sha256':hashlib.sha256(files['index.json']).hexdigest()}
        store.atomic('targets/records/'+receipt['id']+'.json',encoded(receipt))
    return {'status':'EXPORTED','bundle_dir':str(store.managed(base)),'receipt':receipt,
            'config':json.loads(files['config.json'])}
