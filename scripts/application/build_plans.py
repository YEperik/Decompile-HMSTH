"""Immutable compile-only proposal. No compiler discovery, execution or build claims."""
import hashlib
import json
import re
from pathlib import PurePosixPath,PureWindowsPath
from app.application.targets import encoded
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes

VERSION='gcc-draft-plan-1'


def compiler_path(value):
    if not isinstance(value,str) or len(value)>1024 or any(ord(c)<32 for c in value):
        raise ValidationError('compiler harus path absolut tanpa karakter kontrol.')
    posix=PurePosixPath(value);windows=PureWindowsPath(value)
    if not (posix.is_absolute() or windows.is_absolute()) or '..' in posix.parts or '..' in windows.parts:
        raise ValidationError('compiler harus path absolut POSIX/Windows tanpa traversal.')
    return value


def proposal(record,bundle,source,compiler,optimization,use_context):
    compiler_path(compiler)
    if optimization not in ('0','1','2','3','s') or type(use_context) is not bool:
        raise ValidationError('Optimisasi harus 0/1/2/3/s; context harus boolean.')
    source_file=record['source_file']
    payloads={source_file:source,'context.h':bundle['texts']['context.h'].encode('utf-8'),
              'assembly.s':bundle['texts']['assembly.s'].encode('utf-8')}
    argv=[compiler,'-x','c' if record['language']=='c' else 'c++','-O'+optimization]
    if use_context:argv+=['-include','context.h']
    argv+=['-c',source_file,'-o','candidate.o']
    plan={'schema':1,'engine':VERSION,'status':'PLAN_ONLY_NOT_EXECUTED',
          'binding':bundle['manifest']['binding'],'material_bundle_id':bundle['bundle_id'],
          'compiler':{'path_user_supplied':compiler,'family_assumed':'GCC-compatible','expected_target':'mips64r5900el-ps2-elf',
                      'exists_verified':False,'identity_verified':False,'version_verified':False,'target_verified':False},
          'language':record['language'],'optimization_user_selected':optimization,
          'context_mode':'FORCED_INCLUDE_REQUESTED_UNVERIFIED' if use_context else 'REVIEW_ONLY',
          'inputs':{name:{'size':len(data),'sha256':hashlib.sha256(data).hexdigest()} for name,data in payloads.items()},
          'working_directory':'future-staged-run-directory','argv_proposal':argv,'shell':False,
          'output_proposal':'candidate.o','output_created':False,'build_verified':False,'executed':False,
          'readiness':'MANUAL_REVIEW_REQUIRED',
          'unresolved_gates':['Compiler identity/version/target and platform runner verification',
                              'PS2 ABI/code-generation flags and dependency review',
                              'Context/source syntax and include compatibility',
                              'Isolated build execution and validation of emitted ELF object'],
          'limitations':['No automatic build command is enabled by this plan',
                         'Optimization choice is not a matching recommendation',
                         'Assembly snapshot is reference material, not an input to this compile-only proposal',
                         'Stored source/header includes are not resolved; transitive dependencies and environment are not captured',
                         'Do not execute inside immutable plan storage; any future build must stage copies in a separate run directory']}
    return plan,payloads


def manage(store,record,bundle,source,options,cancel=None):
    checkpoint(cancel)
    if not isinstance(options,dict):raise ValidationError('Build options harus object.')
    root='build-plans/'+record['target_index_sha256']+'/'+record['revision']
    if set(options)=={'plan_id'}:
        pid=options['plan_id']
        if not isinstance(pid,str) or not re.fullmatch('[0-9a-f]{64}',pid):raise ValidationError('plan-id harus SHA-256 kanonik.')
        raw=read_bytes(store.managed(root+'/'+pid+'/plan.json'))
        if hashlib.sha256(raw).hexdigest()!=pid:raise ConflictError('Plan berubah/korup.')
        try:
            stored=json.loads(raw)
            expected,payloads=proposal(record,bundle,source,stored['compiler']['path_user_supplied'],stored['optimization_user_selected'],stored['context_mode']=='FORCED_INCLUDE_REQUESTED_UNVERIFIED')
        except (KeyError,TypeError,ValueError):raise ValidationError('Plan JSON invalid.')
        if raw!=encoded(expected):raise ConflictError('Plan tidak sesuai draft/material atau schema yang didukung.')
        for name,data in payloads.items():
            if read_bytes(store.managed(root+'/'+pid+'/'+name))!=data:raise ConflictError('Input snapshot plan berubah: '+name)
        return {'plan_id':pid,'plan':expected,'plan_dir':str(store.managed(root+'/'+pid)),'integrity_verified':True}
    if set(options)!={'compiler','optimization','use_context'}:raise ValidationError('Field build options tidak didukung.')
    plan,payloads=proposal(record,bundle,source,options['compiler'],options['optimization'],options['use_context'])
    raw=encoded(plan);pid=hashlib.sha256(raw).hexdigest();base=root+'/'+pid
    outputs={**payloads,'plan.json':raw}
    for name,data in outputs.items():
        path=store.managed(base+'/'+name)
        if path.exists() and read_bytes(path)!=data:raise ConflictError('Snapshot/plan korup; tidak ditimpa.')
    parts=base.split('/')
    for n in range(1,len(parts)+1):store.managed('/'.join(parts[:n])).mkdir(exist_ok=True)
    for name,data in outputs.items():
        checkpoint(cancel)
        if not store.managed(base+'/'+name).exists():store.atomic(base+'/'+name,data)
    return {'plan_id':pid,'plan':plan,'plan_dir':str(store.managed(base)),'integrity_verified':True}
