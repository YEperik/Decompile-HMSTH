"""Persistent manual review queue. No automatic execution or binary matching status."""
import hashlib
import json
import re
from app.application.targets import prepare,encoded
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes

STATES=('TODO','ACTIVE','PAUSED','REVIEWED')
MAX_ITEMS=256
HEX=re.compile('[0-9a-f]{64}')
ID=re.compile(r'(0|[1-9][0-9]{0,5}):(0|[1-9][0-9]{0,5})')


def priority_value(value):
    if type(value) is not int or not 0<=value<=100:raise ValidationError('priority harus integer 0–100.')


def note_value(value):
    if not isinstance(value,str) or len(value)>500 or '\x00' in value:raise ValidationError('note harus teks maksimum 500 karakter tanpa NUL.')


def load(store,snapshot):
    path=store.managed('queue/state.json')
    if path.exists():
        raw=read_bytes(path)
    else:
        raw=encoded({'schema':1,'workspace_id':snapshot.data['workspace_id'],'revision':0,'items':[]})
    return decode(raw,snapshot)


def decode(raw,snapshot):
    try:data=json.loads(raw)
    except (ValueError,UnicodeError):raise ValidationError('State antrean bukan JSON valid.')
    if not isinstance(data,dict) or set(data)!={'schema','workspace_id','revision','items'} or type(data['schema']) is not int or data['schema']!=1 or data['workspace_id']!=snapshot.data['workspace_id'] or type(data['revision']) is not int or not 0<=data['revision']<=1000000 or not isinstance(data['items'],list) or len(data['items'])>MAX_ITEMS:
        raise ValidationError('Schema/state antrean invalid.')
    seen=set();active=0
    for item in data['items']:
        keys={'id','input_id','symbol_id','symbol_name','source_sha256','target_index_sha256','priority','status','note','added_revision'}
        if not isinstance(item,dict) or set(item)!=keys:raise ValidationError('Item antrean invalid.')
        for key in ('id','source_sha256','target_index_sha256'):
            if not isinstance(item[key],str) or not HEX.fullmatch(item[key]):raise ValidationError('Hash item antrean invalid.')
        if not isinstance(item['input_id'],str) or not isinstance(item['symbol_id'],str) or not ID.fullmatch(item['symbol_id']) or not isinstance(item['symbol_name'],str):raise ValidationError('Identitas item antrean invalid.')
        expected=hashlib.sha256((item['input_id']+':'+item['symbol_id']).encode()).hexdigest()
        if item['id']!=expected or item['id'] in seen:raise ValidationError('ID antrean invalid/duplikat.')
        seen.add(item['id']);priority_value(item['priority']);note_value(item['note'])
        if item['status'] not in STATES or type(item['added_revision']) is not int or not 1<=item['added_revision']<=data['revision']:raise ValidationError('Status/revisi item invalid.')
        active+=item['status']=='ACTIVE'
    if active>1:raise ValidationError('Antrean memuat lebih dari satu fungsi ACTIVE.')
    return data,raw,hashlib.sha256(raw).hexdigest()


def result(data,token,status=None,min_priority=0):
    items=sorted((x for x in data['items'] if (status is None or x['status']==status) and x['priority']>=min_priority),key=lambda x:(-x['priority'],x['added_revision'],x['id']))
    return {'queue_revision':data['revision'],'queue_token':token,'total_items':len(data['items']),
            'counts':{s:sum(x['status']==s for x in data['items']) for s in STATES},'returned':len(items),'items':items,
            'order':'priority descending, added_revision ascending, id ascending',
            'scope':'Manual review progress only; REVIEWED does not mean build matched',
            'source_files_revalidated_by_listing':False,'automatic_execution':False,'binary_matching_claimed':False}


def queue_list(store,status=None,min_priority=0):
    if status is not None and status not in STATES:raise ValidationError('Filter status invalid.')
    priority_value(min_priority)
    with store.lock():
        snapshot=store.load();data,_,token=load(store,snapshot)
        return result(data,token,status,min_priority)


def mutate(store,action,input_id=None,symbol_id=None,item_id=None,expected_token=None,priority=None,status=None,note=None,cancel=None):
    if action not in ('add','update'):raise ValidationError('Aksi queue invalid.')
    if action=='add' and status is not None:raise ValidationError('Item baru selalu TODO.')
    if priority is not None:priority_value(priority)
    if note is not None:note_value(note)
    if status is not None and status not in STATES:raise ValidationError('Status queue invalid.')
    snapshot=store.load()
    if action=='update':
        if not isinstance(expected_token,str) or not HEX.fullmatch(expected_token):raise ValidationError('expected-token wajib dari queue-list.')
        if priority is None and status is None and note is None:raise ValidationError('Pilih perubahan status/priority/note.')
        initial,_,token=load(store,snapshot)
        if token!=expected_token:raise ConflictError('Antrean berubah; jalankan queue-list lagi.')
        old=next((x for x in initial['items'] if x['id']==item_id),None)
        if old is None:raise ValidationError('Item antrean tidak ditemukan.')
        input_id,symbol_id=old['input_id'],old['symbol_id']
    ps,files,target=prepare(store,input_id,symbol_id,cancel)
    if ps.token!=snapshot.token:raise ConflictError('Manifest berubah sebelum verifikasi target.')
    meta=json.loads(files['metadata.json']);target_hash=hashlib.sha256(files['index.json']).hexdigest()
    key=hashlib.sha256((input_id+':'+symbol_id).encode()).hexdigest()
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah selama perubahan antrean.')
        data,raw,token=load(store,snapshot)
        if action=='update' and token!=expected_token:raise ConflictError('Antrean berubah; perubahan tidak ditulis.')
        for name,expected in files.items():
            if read_bytes(store.managed(target+'/'+name))!=expected:raise ConflictError('Paket target berubah/korup.')
        if data['revision']>=1000000:raise ValidationError('Batas revisi antrean tercapai.')
        if action=='add':
            if len(data['items'])>=MAX_ITEMS:raise ValidationError('Maksimum 256 item antrean.')
            if any(x['id']==key for x in data['items']):raise ValidationError('Target sudah ada dalam antrean.')
            item={'id':key,'input_id':input_id,'symbol_id':symbol_id,'symbol_name':meta['symbol']['name'],
                  'source_sha256':meta['source_sha256'],'target_index_sha256':target_hash,
                  'priority':50 if priority is None else priority,'status':'TODO','note':'' if note is None else note,
                  'added_revision':data['revision']+1}
            data['items'].append(item)
        else:
            item=next(x for x in data['items'] if x['id']==key)
            if item['source_sha256']!=meta['source_sha256'] or item['target_index_sha256']!=target_hash:raise ConflictError('Binding target antrean tidak sesuai.')
            if priority is not None:item['priority']=priority
            if status is not None:item['status']=status
            if note is not None:item['note']=note
        if sum(x['status']=='ACTIVE' for x in data['items'])>1:raise ConflictError('Jeda/tinjau fungsi ACTIVE sebelumnya terlebih dahulu.')
        data['revision']+=1;new=encoded(data)
        # Archive previous state before committing the new atomic state file.
        store.managed('queue').mkdir(exist_ok=True);store.managed('queue/history').mkdir(exist_ok=True)
        history=f"queue/history/{data['revision']-1:06d}-{token}.json"
        if store.managed(history).exists():
            if read_bytes(store.managed(history))!=raw:raise ConflictError('Riwayat antrean korup; tidak ditimpa.')
        else:store.atomic(history,raw)
        checkpoint(cancel);store.atomic('queue/state.json',new)
        return result(data,hashlib.sha256(new).hexdigest())
