"""Immutable, user-supplied C/C++ draft revisions bound to a verified target."""
import hashlib
import json
import io
from itertools import islice
from pathlib import Path
from uuid import UUID, uuid4
from app.application.targets import prepare, encoded
from app.application.baselines import _inspect_file
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.persistence.store import read_bytes, regular, MAX_MANIFEST

MAX_SOURCE = 256 * 1024
MAX_REVISIONS = 64


def revision_id(value):
    try:
        if str(UUID(value)) != value: raise ValueError()
    except (ValueError, TypeError, AttributeError):
        raise ValidationError('revision harus UUID kanonik.')
    return value


def source_reader(stream,size,cancel):
    checkpoint(cancel)
    if not 0 < size <= MAX_SOURCE:raise ValidationError('Source harus 1–262144 byte.')
    raw=stream.read(size)
    try: text=raw.decode('utf-8')
    except UnicodeDecodeError:raise ValidationError('Source harus UTF-8.')
    if '\x00' in text or not text.strip():raise ValidationError('Source kosong atau mengandung NUL.')
    return raw


def read_revision(store,base,rid,target_hash):
    revision_id(rid)
    try: record=json.loads(read_bytes(store.managed(base+'/'+rid+'/record.json')))
    except (ValueError,UnicodeError):raise ValidationError('Record draft bukan JSON valid.')
    keys={'schema','revision','parent','created_at','status','language','source_sha256','source_size','target_index_sha256','source_file','built','matched'}
    if not isinstance(record,dict) or set(record)!=keys or record['schema']!=1 or record['revision']!=rid or record['status']!='DRAFT' or record['built'] is not False or record['matched'] is not False or record['target_index_sha256']!=target_hash or record['language'] not in ('c','cpp'):
        raise ValidationError('Record draft invalid atau target berbeda.')
    if record['parent'] is not None:revision_id(record['parent'])
    expected='source.c' if record['language']=='c' else 'source.cpp'
    if record['source_file']!=expected:raise ValidationError('Path source draft invalid.')
    raw=read_bytes(store.managed(base+'/'+rid+'/'+expected))
    if not 0<len(raw)<=MAX_SOURCE or record['source_size']!=len(raw) or hashlib.sha256(raw).hexdigest()!=record['source_sha256']:
        raise ConflictError('Hash/ukuran source draft berubah.')
    source_reader(io.BytesIO(raw),len(raw),None)
    return record,raw


def drafts(store,input_id,symbol_id,source=None,language='c',parent=None,revision=None,cancel=None,compare_to=None,save_diff=False,material_action=None,assembly=None,context=None,bundle_id=None,build_options=None,stage_action=None,stage_id=None,candidate_options=None):
    """Add when source is supplied, show when revision supplied, otherwise history."""
    if candidate_options is not None and (material_action != 'build-stage' or stage_action != 'verify'):raise ValidationError('Kandidat memerlukan stage terverifikasi.')
    if (stage_action is not None or stage_id is not None) and material_action != 'build-stage':raise ValidationError('Parameter stage hanya untuk build-stage.')
    if build_options is not None and material_action not in ('build-plan','build-stage'):raise ValidationError('Build options hanya untuk plan.')
    if material_action is not None:
        if revision is None or source is not None or parent is not None or compare_to is not None or save_diff:
            raise ValidationError('Material memerlukan satu revisi, tanpa operasi draft lain.')
    elif any(x is not None for x in (assembly,context,bundle_id)):
        raise ValidationError('Parameter material memerlukan aksi material.')
    if compare_to is not None:
        revision_id(compare_to)
        if revision is None or source is not None or parent is not None:raise ValidationError('Diff memerlukan dua revisi, tanpa source/parent.')
    if save_diff and compare_to is None:raise ValidationError('save-diff hanya untuk diff.')
    if language not in ('c','cpp'):raise ValidationError('language harus c/cpp.')
    if source is not None and revision is not None:raise ValidationError('Pilih add atau show.')
    if parent is not None:
        revision_id(parent)
        if source is None:raise ValidationError('parent hanya untuk draft-add.')
    if revision is not None:revision_id(revision)
    snapshot,files,target=prepare(store,input_id,symbol_id,cancel)
    target_hash=hashlib.sha256(files['index.json']).hexdigest()
    base='drafts/'+json.loads(files['config.json'])['source_sha256']+'/'+symbol_id.replace(':','-')
    raw=None
    if source is not None:
        source_path=Path(source).absolute()
        regular(source_path)
        raw,_,_=_inspect_file(source_path,source_reader,cancel)
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah selama draft.')
        for name,data in files.items():
            if read_bytes(store.managed(target+'/'+name))!=data:
                raise ConflictError('Target berubah/korup; draft tidak diproses.')
        folder=store.managed(base)
        # Incomplete directories are retained and reported; no silent cleanup.
        entries=sorted(islice(folder.iterdir(),MAX_REVISIONS+1)) if folder.exists() else []
        if len(entries)>MAX_REVISIONS:raise ValidationError('Batas 64 direktori revisi terlampaui.')
        records={};incomplete=[]
        for entry in entries:
            checkpoint(cancel);revision_id(entry.name)
            child=store.managed(base+'/'+entry.name)
            if not child.is_dir():raise ValidationError('Direktori revisi invalid.')
            if not store.managed(base+'/'+entry.name+'/record.json').exists():
                incomplete.append(entry.name);continue
            record,_=read_revision(store,base,entry.name,target_hash);records[entry.name]=record
        for rid,record in records.items():
            seen={rid};ancestor=record['parent']
            while ancestor is not None:
                if ancestor in seen or ancestor not in records:raise ValidationError('Rantai parent invalid/tidak lengkap.')
                seen.add(ancestor);ancestor=records[ancestor]['parent']
        if compare_to is not None:
            if revision not in records or compare_to not in records:raise ValidationError('Dua revisi lengkap pada target yang sama diperlukan.')
            from app.application.draft_diff import compare
            left,lraw=read_revision(store,base,revision,target_hash)
            right,rraw=read_revision(store,base,compare_to,target_hash)
            result=compare(left,lraw,right,rraw,cancel)
            result['target_path']=target
            result['record_sha256']={rid:hashlib.sha256(read_bytes(store.managed(base+'/'+rid+'/record.json'))).hexdigest() for rid in (revision,compare_to)}
            data=encoded(result)
            if len(data)>MAX_MANIFEST:raise ValidationError('Report diff melebihi 1 MiB.')
            if save_diff:
                checkpoint(cancel)
                key=hashlib.sha256(data).hexdigest()
                relative='draft-comparisons/'+target_hash+'/'+key+'.json'
                path=store.managed(relative)
                if path.exists():
                    if read_bytes(path)!=data:raise ConflictError('Report diff korup; tidak ditimpa.')
                else:
                    store.managed('draft-comparisons').mkdir(exist_ok=True)
                    store.managed('draft-comparisons/'+target_hash).mkdir(exist_ok=True)
                    store.atomic(relative,data)
                return {'comparison':result,'report_file':str(path)}
            return {'comparison':result}
        if revision is not None:
            if revision not in records:raise ValidationError('Revisi lengkap tidak ditemukan.')
            record,content=read_revision(store,base,revision,target_hash)
            if material_action is not None:
                from app.application.materials import manage
                if material_action == 'build-stage':
                    from app.application.build_plans import manage as plan_manage
                    from app.application.build_stages import manage as stage_manage
                    if not isinstance(build_options,dict) or set(build_options)!={'plan_id'}:
                        raise ValidationError('Staging memerlukan plan-id tersimpan.')
                    bundle=manage(store,record,base,'show',assembly,context,bundle_id,cancel)
                    plan=plan_manage(store,record,bundle,content,build_options,cancel)
                    stage=stage_manage(store,plan,stage_action,stage_id,cancel)
                    if candidate_options is not None:
                        from app.application.build_candidates import manage as candidate_manage
                        return candidate_manage(store,stage,files,candidate_options,cancel)
                    return stage
                if material_action == 'build-plan':
                    from app.application.build_plans import manage as plan_manage
                    bundle=manage(store,record,base,'show',assembly,context,bundle_id,cancel)
                    return plan_manage(store,record,bundle,content,build_options,cancel)
                if material_action == 'verify-words':
                    from app.application.words import verify
                    bundle=manage(store,record,base,'show',assembly,context,bundle_id,cancel)
                    return verify(bundle,files,cancel)
                if material_action == 'check':
                    from app.application.readiness import assess
                    bundle=manage(store,record,base,'show',assembly,context,bundle_id,cancel)
                    return assess(bundle,cancel)
                return manage(store,record,base,material_action,assembly,context,bundle_id,cancel)

            return {'record':record,'source_text':content.decode('utf-8'),'source_file':str(store.managed(base+'/'+revision+'/'+record['source_file']))}
        if source is None:
            return {'status':'DRAFT_HISTORY','revisions':list(records.values()),'incomplete_revisions':incomplete,'target_path':target}
        if parent is not None and parent not in records:raise ValidationError('Parent lengkap pada target ini tidak ditemukan.')
        if len(entries)>=MAX_REVISIONS:raise ValidationError('Maksimum 64 direktori revisi per target.')
        rid=str(uuid4());relative=base+'/'+rid
        if store.managed(relative).exists():raise ConflictError('ID revisi sudah ada; tidak ditimpa.')
        filename='source.c' if language=='c' else 'source.cpp'
        record={'schema':1,'revision':rid,'parent':parent,'created_at':now(),'status':'DRAFT',
                'language':language,'source_file':filename,'source_sha256':hashlib.sha256(raw).hexdigest(),
                'source_size':len(raw),'target_index_sha256':target_hash,'built':False,'matched':False}
        parts=relative.split('/')
        for n in range(1,len(parts)+1):store.managed('/'.join(parts[:n])).mkdir(exist_ok=True)
        store.atomic(relative+'/'+filename,raw)
        checkpoint(cancel)
        store.atomic(relative+'/record.json',encoded(record))
        return {'record':record,'source_file':str(store.managed(relative+'/'+filename)),'target_path':target}
