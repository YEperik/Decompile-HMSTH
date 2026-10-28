"""Stage verified plan inputs in separate work directories. Never executes a build."""
import hashlib
from itertools import islice
from pathlib import Path
from uuid import uuid4
from app.application.drafts import revision_id
from app.application.targets import encoded
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes

MAX_STAGES=64
VERSION='build-input-stage-1'


def manage(store,verified_plan,action,stage_id=None,cancel=None):
    """Caller holds writer lock after verifying ELF, target, draft, materials and plan."""
    checkpoint(cancel)
    if action not in ('create','verify','list'):raise ValidationError('Aksi staging invalid.')
    if action=='verify':revision_id(stage_id)
    elif stage_id is not None:raise ValidationError('stage-id hanya untuk verify.')
    pid=verified_plan['plan_id'];plan=verified_plan['plan']
    base='build-stages/'+pid
    plan_base=str(Path(verified_plan['plan_dir']).relative_to(store.root))
    payloads={name:read_bytes(store.managed(plan_base+'/'+name)) for name in plan['inputs']}
    for name,data in payloads.items():
        if {'size':len(data),'sha256':hashlib.sha256(data).hexdigest()}!=plan['inputs'][name]:
            raise ConflictError('Input plan berubah sebelum staging.')
    plan_raw=read_bytes(store.managed(plan_base+'/plan.json'))
    if hashlib.sha256(plan_raw).hexdigest()!=pid:raise ConflictError('Plan berubah sebelum staging.')
    payloads['plan.json']=plan_raw
    source='source.c' if plan['language']=='c' else 'source.cpp'
    argv=[plan['compiler']['path_user_supplied'],'-x','c' if plan['language']=='c' else 'c++','-O'+plan['optimization_user_selected']]
    if plan['context_mode']=='FORCED_INCLUDE_REQUESTED_UNVERIFIED':argv+=['-include','inputs/context.h']
    argv+=['-c','inputs/'+source,'-o','outputs/candidate.o']

    def manifest(sid):
        return {'schema':1,'engine':VERSION,'stage_id':sid,'plan_id':pid,
                'binding':plan['binding'],'creation_status':'STAGED_WITHOUT_EXECUTION',
                'inputs':{'inputs/'+name:{'size':len(data),'sha256':hashlib.sha256(data).hexdigest()} for name,data in payloads.items()},
                'working_directory':'.','argv_proposal':argv,'shell':False,
                'output_proposal':'outputs/candidate.o','build_executed_by_stager':False,
                'compiler_verified':False,'build_verified':False,
                'limitations':['Separate directories are not an execution sandbox',
                               'Staging does not resolve includes, inspect a compiler or validate ABI',
                               'Input verification does not inspect output files or prove a build occurred']}

    def verify(sid):
        expected=manifest(sid);prefix=base+'/'+sid
        if read_bytes(store.managed(prefix+'/stage.json'))!=encoded(expected):raise ConflictError('Manifest staging berubah/invalid.')
        for name,data in payloads.items():
            checkpoint(cancel)
            if read_bytes(store.managed(prefix+'/inputs/'+name))!=data:raise ConflictError('Input staging berubah: '+name)
        outputs=store.managed(prefix+'/outputs')
        if not outputs.is_dir():raise ValidationError('Direktori output staging hilang/invalid.')
        return {'status':'STAGED_INPUTS_VERIFIED','stage_id':sid,'plan_id':pid,
                'stage_dir':str(store.managed(prefix)),'manifest':expected,
                'output_files_inspected':False,'build_execution_verified':False}

    if action=='verify':return verify(stage_id)
    folder=store.managed(base)
    entries=sorted(islice(folder.iterdir(),MAX_STAGES+1)) if folder.exists() else []
    if len(entries)>MAX_STAGES:raise ValidationError('Batas staging terlampaui.')
    complete=[];incomplete=[]
    for child in entries:
        checkpoint(cancel);revision_id(child.name)
        path=store.managed(base+'/'+child.name)
        if not path.is_dir():raise ValidationError('Direktori stage invalid.')
        if not store.managed(base+'/'+child.name+'/stage.json').exists():incomplete.append(child.name)
        else:verify(child.name);complete.append(child.name)
    if action=='list':return {'plan_id':pid,'verified_input_stages':complete,'incomplete_stages':incomplete,'build_execution_verified':False}
    if len(entries)>=MAX_STAGES:raise ValidationError('Maksimum 64 direktori staging per plan, termasuk parsial.')
    sid=str(uuid4());prefix=base+'/'+sid
    if store.managed(prefix).exists():raise ConflictError('Stage ID sudah ada; tidak ditimpa.')
    parts=prefix.split('/')
    for n in range(1,len(parts)+1):store.managed('/'.join(parts[:n])).mkdir(exist_ok=True)
    store.managed(prefix+'/inputs').mkdir();store.managed(prefix+'/outputs').mkdir()
    for name,data in payloads.items():
        checkpoint(cancel);store.atomic(prefix+'/inputs/'+name,data)
    checkpoint(cancel);store.atomic(prefix+'/stage.json',encoded(manifest(sid)))
    return verify(sid)
