"""Exact raw function-range comparison of registered ELF inputs, not build matching."""
import hashlib
import json
from app.application.targets import prepare,encoded
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ConflictError,ValidationError
from app.infrastructure.persistence.store import read_bytes,MAX_MANIFEST

VERSION='raw-function-comparison-1'


def byte_diff(reference,candidate,cancel=None):
    count=0;details=[]
    for offset in range(max(len(reference),len(candidate))):
        if offset%4096==0:checkpoint(cancel)
        a=reference[offset] if offset<len(reference) else None
        b=candidate[offset] if offset<len(candidate) else None
        if a!=b:
            count+=1
            if len(details)<64:details.append({'relative_offset':offset,'reference_byte':a,'candidate_byte':b})
    checkpoint(cancel)
    return count,details


def compare_functions(store,reference_input,reference_symbol,candidate_input,candidate_symbol,save=False,cancel=None):
    rs,rf,rpath=prepare(store,reference_input,reference_symbol,cancel)
    cs,cf,cpath=prepare(store,candidate_input,candidate_symbol,cancel)
    if rs.token!=cs.token:raise ConflictError('Manifest berubah antara pembacaan kedua target.')
    rm=json.loads(rf['metadata.json']);cm=json.loads(cf['metadata.json'])
    rr=json.loads(rf['references.json']);cr=json.loads(cf['references.json'])
    a,b=rf['bytes.bin'],cf['bytes.bin'];count,details=byte_diff(a,b,cancel)
    def side(iid,metadata,refs,files,path):
        return {'input_id':iid,'source_sha256':metadata['source_sha256'],
                'target_path':path,'target_index_sha256':hashlib.sha256(files['index.json']).hexdigest(),
                'elf_type':metadata['elf_type'],'symbol':metadata['symbol'],
                'payload_size':metadata['payload_size'],'payload_sha256':metadata['payload_sha256'],
                'relocations_starting_in_range':sum(x['location_inside_selected_range'] and x['type']!=0 for x in refs['matches']),
                'references_sha256':hashlib.sha256(files['references.json']).hexdigest()}
    for entry in details:
        off=entry['relative_offset']
        entry['reference_file_offset']=rm['symbol']['file_offset']+off if off<len(a) else None
        entry['candidate_file_offset']=cm['symbol']['file_offset']+off if off<len(b) else None
    report={'schema':1,'engine':VERSION,'status':'RAW_RANGE_IDENTICAL' if a==b else 'RAW_RANGE_DIFFERENT',
            'scope':'Selected ELF-declared function bytes only; no normalization',
            'reference':side(reference_input,rm,rr,rf,rpath),'candidate':side(candidate_input,cm,cr,cf,cpath),
            'source_files_have_same_hash':rm['source_sha256']==cm['source_sha256'],
            'same_selection':rm['source_sha256']==cm['source_sha256'] and reference_symbol==candidate_symbol,
            'elf_types_equal':rm['elf_type']==cm['elf_type'],
            'symbol_layout_fields_equal':all(rm['symbol'][k]==cm['symbol'][k] for k in ('address_kind','start','file_offset','size','section_index')),
            'differing_byte_positions':count,'differences':details,'differences_omitted':count-len(details),
            'build_verified':False,'source_to_candidate_link_verified':False,'instructions_compared':False,
            'relocations_applied':False,'relocations_normalized':False,'abi_compatibility_verified':False,
            'whole_binary_comparison_performed':False,'program_semantics_verified':False,'executed':False,
            'limitations':['Identical selected bytes do not prove compiler/source matching or program behavior',
                           'Relocation records are counted, not applied, masked or semantically compared',
                           'No automatic symbol-name pairing; both IDs are explicit',
                           'ET_REL and EXEC/DYN bytes may differ due to link layout; no link equivalence claim',
                           'Same input/selection is a self-check, not independent candidate evidence']}
    data=encoded(report)
    if len(data)>MAX_MANIFEST:raise ValidationError('Laporan perbandingan melebihi 1 MiB.')
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=rs.token:raise ConflictError('Manifest berubah selama perbandingan.')
        for files,path in ((rf,rpath),(cf,cpath)):
            for name,expected in files.items():
                if read_bytes(store.managed(path+'/'+name))!=expected:raise ConflictError('Paket target hilang/korup/berubah.')
        result={'comparison':report}
        if save:
            relative='comparisons/'+VERSION+'/'+hashlib.sha256(data).hexdigest()+'.json'
            destination=store.managed(relative)
            if destination.exists():
                if read_bytes(destination)!=data:raise ConflictError('Laporan perbandingan korup; tidak ditimpa.')
            else:
                store.managed('comparisons').mkdir(exist_ok=True)
                store.managed('comparisons/'+VERSION).mkdir(exist_ok=True)
                store.atomic(relative,data)
            result['report_file']=str(destination)
    return result
