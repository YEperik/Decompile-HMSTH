"""Immutable function relocation report with registered-input provenance."""
import hashlib
import json
import re
from uuid import uuid4

from app.application.baselines import _inspect_file
from app.application.workspaces import resolve_input
from app.domain.binary.elf import checkpoint
from app.domain.binary.relocations import function_refs, VERSION
from app.domain.workspace.model import ValidationError, ConflictError, now
from app.infrastructure.persistence.store import read_bytes, MAX_MANIFEST


def create_references(store, input_id, symbol_id, cancel=None):
    if not isinstance(symbol_id,str) or not re.fullmatch(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})',symbol_id):
        raise ValidationError('symbol-id harus table-section:symbol-index kanonik.')
    snapshot=store.load()
    item=next((x for x in snapshot.data['inputs'] if x['id']==input_id),None)
    if item is None:
        raise ValidationError('ID input tidak ditemukan.')
    def reader(stream,size,token):return function_refs(stream,size,symbol_id,token)
    refs,digest,size=_inspect_file(resolve_input(store,item),reader,cancel)
    if (digest,size)!=(item['sha256'],item['size_bytes']):
        raise ConflictError('Input berubah sejak registrasi; laporan relokasi tidak dipublikasikan.')
    report={'references_schema':1,'source_sha256':digest,'source_size':size,'references':refs,
            'evidence':'ELF_DECLARED_RELOCATION; function semantics and dependency completeness unverified'}
    raw=(json.dumps(report,ensure_ascii=True,indent=2)+'\n').encode()
    if len(raw)>MAX_MANIFEST:
        raise ValidationError('Laporan relokasi melebihi 1 MiB; tidak dipublikasikan.')
    base=f'references/{digest}/{VERSION}'
    relative=base+'/'+symbol_id.replace(':','-')+'.json'
    receipt_id=str(uuid4())
    receipt={'receipt_id':receipt_id,'created_at':now(),'input_id':input_id,
             'workspace_id':snapshot.data['workspace_id'],'manifest_token':snapshot.token,
             'source_sha256':digest,'report_path':relative,'report_sha256':hashlib.sha256(raw).hexdigest()}
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:
            raise ConflictError('Workspace berubah selama pemeriksaan relokasi.')
        for directory in ('references',f'references/{digest}',base,'references/records'):
            store.managed(directory).mkdir(exist_ok=True)
        destination=store.managed(relative)
        if destination.exists():
            if read_bytes(destination)!=raw:
                raise ConflictError('Report relokasi berbeda/korup; tidak ditimpa.')
        else:store.atomic(relative,raw)
        store.atomic(f'references/records/{receipt_id}.json',(json.dumps(receipt,indent=2)+'\n').encode())
    return {'report':report,'receipt':receipt,'report_file':str(destination)}
