"""Import user-selected ET_REL candidates. Association is not proof of compilation."""
import hashlib
import json
import re
from pathlib import Path
from app.application.baselines import _inspect_file
from app.application.comparisons import byte_diff
from app.application.extractions import rejection
from app.application.targets import encoded
from app.domain.binary.elf import parse,checkpoint,UnsupportedELF
from app.domain.binary.relocations import function_refs
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes,regular,MAX_MANIFEST

VERSION='user-object-candidate-1'


def inspect_candidate(path,symbol_id,target_files,stage,cancel=None):
    if not isinstance(symbol_id,str) or not re.fullmatch(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})',symbol_id):
        raise ValidationError('candidate-symbol harus table:index kanonik.')
    regular(path)
    def reader(stream,size,token):
        if not 0<size<=MAX_MANIFEST:raise ValidationError('Object kandidat harus 1 byte–1 MiB.')
        metadata=parse(stream,size,token)
        if metadata['elf_type']!=1:raise UnsupportedELF('Kandidat build harus ET_REL; EXEC/DYN tidak diterima.')
        refs=function_refs(stream,size,symbol_id,token);symbol=refs['selected_symbol']
        reason=rejection(symbol)
        if reason:raise ValidationError(reason)
        checkpoint(token);stream.seek(0);raw=stream.read(size)
        if len(raw)!=size:raise ValidationError('Object kandidat terpotong.')
        return metadata,refs,raw
    (metadata,refs,raw),digest,size=_inspect_file(path,reader,cancel)
    symbol=refs['selected_symbol'];start=symbol['file_offset'];payload=raw[start:start+symbol['size']]
    if len(payload)!=symbol['size']:raise ValidationError('Byte fungsi kandidat terpotong.')
    target=json.loads(target_files['metadata.json']);count,details=byte_diff(target_files['bytes.bin'],payload,cancel)
    for item in details:
        off=item['relative_offset']
        item['reference_file_offset']=target['symbol']['file_offset']+off if off<len(target_files['bytes.bin']) else None
        item['candidate_file_offset']=start+off if off<len(payload) else None
    report={'schema':1,'engine':VERSION,'association':'USER_SELECTED_NOT_BUILD_PROVEN',
            'stage_id':stage['stage_id'],'plan_id':stage['plan_id'],
            'stage_manifest_sha256':hashlib.sha256(encoded(stage['manifest'])).hexdigest(),
            'binding':stage['manifest']['binding'],
            'reference':{'source_sha256':target['source_sha256'],'symbol':target['symbol'],
                         'payload_sha256':target['payload_sha256'],'payload_size':target['payload_size']},
            'candidate':{'object_sha256':digest,'object_size':size,'elf_type':metadata['elf_type_name'],
                         'elf_flags':metadata['flags'],'symbol':symbol,'payload_sha256':hashlib.sha256(payload).hexdigest(),
                         'payload_size':len(payload),'references':refs},
            'comparison':{'status':'RAW_RANGE_IDENTICAL' if count==0 else 'RAW_RANGE_DIFFERENT',
                          'differing_byte_positions':count,'differences':details,'differences_omitted':count-len(details)},
            'compiler_executed_by_importer':False,'build_provenance_verified':False,'abi_verified':False,
            'relocations_applied':False,'instructions_compared':False,'whole_binary_match_verified':False,
            'limitations':['User-selected object linked to stage by choice, not a recorded compiler run',
                           'Raw range equality does not prove source-to-object matching or behavior',
                           'ELF flags and relocations recorded without ABI or relocation equivalence claims']}
    return report,raw


def manage(store,stage,target_files,options,cancel=None):
    checkpoint(cancel)
    if not isinstance(options,dict):raise ValidationError('Candidate options harus object.')
    base='build-candidates/'+stage['plan_id']+'/'+stage['stage_id']+'/'+VERSION
    if set(options)=={'candidate_id'}:
        cid=options['candidate_id']
        if not isinstance(cid,str) or not re.fullmatch('[0-9a-f]{64}',cid):raise ValidationError('candidate-id harus SHA-256 kanonik.')
        data=read_bytes(store.managed(base+'/'+cid+'/report.json'))
        if hashlib.sha256(data).hexdigest()!=cid:raise ConflictError('Report kandidat berubah.')
        try:sid=json.loads(data)['candidate']['symbol']['id']
        except (KeyError,TypeError,ValueError):raise ValidationError('Report kandidat invalid.')
        report,raw=inspect_candidate(store.managed(base+'/'+cid+'/candidate.o'),sid,target_files,stage,cancel)
        if encoded(report)!=data:raise ConflictError('Kandidat/report tidak sesuai sumber atau stage.')
        return {'candidate_id':cid,'report':report,'candidate_dir':str(store.managed(base+'/'+cid)),'integrity_verified':True}
    if set(options)!={'path','symbol_id'}:raise ValidationError('Field kandidat tidak didukung.')
    report,raw=inspect_candidate(Path(options['path']).absolute(),options['symbol_id'],target_files,stage,cancel)
    data=encoded(report)
    if len(data)>MAX_MANIFEST:raise ValidationError('Report kandidat melebihi 1 MiB.')
    cid=hashlib.sha256(data).hexdigest();relative=base+'/'+cid
    targets={'candidate.o':raw,'report.json':data}
    for name,content in targets.items():
        path=store.managed(relative+'/'+name)
        if path.exists() and read_bytes(path)!=content:raise ConflictError('Snapshot kandidat korup; tidak ditimpa.')
    parts=relative.split('/')
    for n in range(1,len(parts)+1):store.managed('/'.join(parts[:n])).mkdir(exist_ok=True)
    for name,content in targets.items():
        checkpoint(cancel)
        if not store.managed(relative+'/'+name).exists():store.atomic(relative+'/'+name,content)
    return {'candidate_id':cid,'report':report,'candidate_dir':str(store.managed(relative)),'integrity_verified':True}
