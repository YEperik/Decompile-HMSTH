"""Read-only historical snapshots; hashes detect corruption, not authorship."""
import os
import re
from app.application.queue import load,decode,result
from app.infrastructure.persistence.store import read_bytes
from app.domain.workspace.model import ValidationError,ConflictError

MAX_ENTRIES=4096
NAME=re.compile(r'([0-9]{6,7})-([0-9a-f]{64})\.json')


def revision_value(value):
    if type(value) is not int or not 0<=value<=1000000:
        raise ValidationError('revision harus integer 0–1000000.')


def catalog(store,snapshot,current,token):
    folder=store.managed('queue/history');entries={}
    if not folder.exists():return entries
    with os.scandir(folder) as scan:
        for count,entry in enumerate(scan,1):
            if count>MAX_ENTRIES:raise ValidationError('Batas inspeksi history 4096 entri tercapai.')
            match=NAME.fullmatch(entry.name)
            if match is None:raise ValidationError('Nama file history invalid.')
            revision=int(match[1]);digest=match[2]
            if entry.name!=f'{revision:06d}-{digest}.json':raise ValidationError('Nama revisi history tidak canonical.')
            if not entry.is_file(follow_symlinks=False):raise ValidationError('History harus regular file, bukan link/direktori.')
            if revision>current['revision']:raise ConflictError('History memiliki revisi masa depan.')
            if revision==current['revision']:
                # A failed state commit may have archived the still-current snapshot.
                data,_,archived_token=decode(read_bytes(store.managed('queue/history/'+entry.name)),snapshot)
                if archived_token!=token or digest!=token or data!=current:
                    raise ConflictError('Checkpoint history tidak sesuai state saat ini.')
                continue
            if revision in entries:raise ConflictError('Revisi history duplikat/ambigu.')
            entries[revision]=(entry.name,digest)
    return entries


def inspect(store,snapshot,revision,entry):
    name,digest=entry
    data,_,token=decode(read_bytes(store.managed('queue/history/'+name)),snapshot)
    if token!=digest or data['revision']!=revision:
        raise ConflictError('Hash/revisi snapshot history tidak sesuai nama file.')
    return data,token


def scope(current,token):
    return {'current_revision':current['revision'],'current_queue_token':token,
            'read_only':True,'source_files_revalidated':False,'binary_matching_claimed':False,
            'history_authenticity_proven':False,
            'scope':'Stored manual review snapshots; hashes are not a signed audit chain'}


def history_list(store,before_revision=None,limit=20):
    if before_revision is not None:revision_value(before_revision)
    if type(limit) is not int or not 1<=limit<=50:raise ValidationError('limit harus integer 1–50.')
    with store.lock():
        snapshot=store.load();current,_,token=load(store,snapshot)
        entries=catalog(store,snapshot,current,token)
        revisions=sorted((r for r in entries if before_revision is None or r<before_revision),reverse=True)
        rows=[]
        for revision in revisions[:limit]:
            data,digest=inspect(store,snapshot,revision,entries[revision]);summary=result(data,digest)
            rows.append({'revision':revision,'snapshot_token':digest,'total_items':summary['total_items'],'counts':summary['counts']})
        return {**scope(current,token),'snapshots':rows,'returned':len(rows),
                'total_archived_snapshots':len(entries),'expected_archived_snapshots':current['revision'],
                'archive_revisions_complete':len(entries)==current['revision'],
                'payload_validation_scope':'Returned page only; not the entire archive',
                'next_before_revision':rows[-1]['revision'] if len(revisions)>limit else None}


def history_show(store,revision):
    revision_value(revision)
    with store.lock():
        snapshot=store.load();current,_,token=load(store,snapshot)
        entries=catalog(store,snapshot,current,token)
        if revision not in entries:raise ValidationError('Revisi arsip tidak tersedia; state terbaru memakai queue-list.')
        data,digest=inspect(store,snapshot,revision,entries[revision])
        return {**scope(current,token),'snapshot':result(data,digest)}
