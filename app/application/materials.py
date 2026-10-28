"""User-supplied assembly/context snapshots. Storage integrity is not semantic proof."""
import hashlib
import io
import json
import re
from itertools import islice
from pathlib import Path
from app.application.baselines import _inspect_file
from app.application.drafts import source_reader
from app.application.targets import encoded
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes,regular

MAX_BUNDLES=64
NAMES=('assembly.s','context.h')


def sha(data):return hashlib.sha256(data).hexdigest()


def manage(store,record,draft_base,action,assembly=None,context=None,bundle_id=None,cancel=None):
    """Called only after draft/target validation, with the workspace writer lock held."""
    checkpoint(cancel)
    if action not in ('add','show','list'):raise ValidationError('Aksi material invalid.')
    if action=='add':
        if assembly is None or context is None or bundle_id is not None:raise ValidationError('Assembly dan context wajib untuk add.')
    elif assembly is not None or context is not None:raise ValidationError('Path input hanya untuk add.')
    if action=='show':
        if not isinstance(bundle_id,str) or not re.fullmatch('[0-9a-f]{64}',bundle_id):raise ValidationError('bundle-id harus SHA-256 kanonik.')
    elif bundle_id is not None:raise ValidationError('bundle-id hanya untuk show.')
    rid=record['revision'];base='draft-materials/'+record['target_index_sha256']+'/'+rid
    binding={'revision':rid,'draft_record_sha256':sha(read_bytes(store.managed(draft_base+'/'+rid+'/record.json'))),
             'draft_source_sha256':record['source_sha256'],'target_index_sha256':record['target_index_sha256']}

    def read_bundle(bid):
        path=store.managed(base+'/'+bid+'/manifest.json');raw=read_bytes(path)
        if sha(raw)!=bid:raise ConflictError('Manifest material berubah.')
        try:manifest=json.loads(raw)
        except (ValueError,UnicodeError):raise ValidationError('Manifest material invalid.')
        expected={'schema':1,'status':'USER_SUPPLIED_UNVERIFIED','binding':binding,
                  'assembly_matches_target':False,'context_verified':False,'executed':False}
        if not isinstance(manifest,dict) or set(manifest)!=set(expected)|{'files'} or any(manifest[k]!=v for k,v in expected.items()):
            raise ValidationError('Material tidak sesuai revisi/target/status.')
        entries=manifest['files']
        if not isinstance(entries,dict) or set(entries)!=set(NAMES):raise ValidationError('Daftar material invalid.')
        payloads={}
        for name in NAMES:
            info=entries[name]
            if not isinstance(info,dict) or set(info)!={'sha256','size'}:raise ValidationError('Metadata file material invalid.')
            data=read_bytes(store.managed(base+'/'+bid+'/'+name))
            source_reader(io.BytesIO(data),len(data),cancel)
            if info!={'sha256':sha(data),'size':len(data)}:raise ConflictError('Material berubah: '+name)
            payloads[name]=data.decode('utf-8')
        return manifest,payloads

    if action=='show':
        manifest,text=read_bundle(bundle_id)
        return {'bundle_id':bundle_id,'manifest':manifest,'texts':text,'bundle_dir':str(store.managed(base+'/'+bundle_id))}
    folder=store.managed(base)
    entries=sorted(islice(folder.iterdir(),MAX_BUNDLES+1)) if folder.exists() else []
    if len(entries)>MAX_BUNDLES:raise ValidationError('Batas direktori material terlampaui.')
    complete=[];incomplete=[]
    for child in entries:
        checkpoint(cancel)
        if not re.fullmatch('[0-9a-f]{64}',child.name) or not store.managed(base+'/'+child.name).is_dir():raise ValidationError('Direktori material invalid.')
        if not store.managed(base+'/'+child.name+'/manifest.json').exists():incomplete.append(child.name)
        else:
            read_bundle(child.name);complete.append(child.name)
    if action=='list':return {'bundles':complete,'incomplete_bundles':incomplete,'binding':binding}
    payloads={}
    for name,value in zip(NAMES,(assembly,context)):
        path=Path(value).absolute();regular(path)
        data,_,_=_inspect_file(path,source_reader,cancel)
        payloads[name]=data
    manifest={'schema':1,'status':'USER_SUPPLIED_UNVERIFIED','binding':binding,
              'assembly_matches_target':False,'context_verified':False,'executed':False,
              'files':{name:{'sha256':sha(data),'size':len(data)} for name,data in payloads.items()}}
    manifest_raw=encoded(manifest);bid=sha(manifest_raw);relative=base+'/'+bid
    existing=store.managed(relative).exists()
    if not existing and len(entries)>=MAX_BUNDLES:raise ValidationError('Maksimum 64 bundle per revisi.')
    outputs={**payloads,'manifest.json':manifest_raw}
    for name,data in outputs.items():
        path=store.managed(relative+'/'+name)
        if path.exists() and read_bytes(path)!=data:raise ConflictError('Material berbeda/korup; tidak ditimpa.')
    parts=relative.split('/')
    for i in range(1,len(parts)+1):store.managed('/'.join(parts[:i])).mkdir(exist_ok=True)
    for name,data in outputs.items():
        checkpoint(cancel)
        if not store.managed(relative+'/'+name).exists():store.atomic(relative+'/'+name,data)
    return {'bundle_id':bid,'manifest':manifest,'bundle_dir':str(store.managed(relative))}
