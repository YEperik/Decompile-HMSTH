"""Literal 32-bit LE word listings, not instruction decoding or assembler execution."""
import hashlib
import json
import re
import struct
from app.application.targets import prepare
from app.domain.binary.elf import checkpoint
from app.domain.workspace.model import ValidationError,ConflictError
from app.infrastructure.persistence.store import read_bytes

VERSION='literal-word32le-1'
MAX_WORDS=4096
MAX_TEXT=256*1024
LINE=re.compile(r'\.word[ \t]+0x([0-9a-fA-F]{8})')


def validate_target(payload,symbol):
    if not payload or len(payload)%4 or len(payload)>4*MAX_WORDS:
        raise ValidationError('Listing memerlukan 1–4096 word lengkap (4 byte/word).')
    if symbol['start']%4 or symbol['file_offset']%4:
        raise ValidationError('Alamat/offset target harus aligned 4 byte.')


def render(payload,symbol):
    validate_target(payload,symbol)
    return '# Literal word32 little-endian; not disassembly or reconstructed source.\n'+''.join(f'.word 0x{word:08x}\n' for (word,) in struct.iter_unpack('<I',payload))


def parse_listing(text,cancel=None):
    if not isinstance(text,str) or len(text.encode('utf-8'))>MAX_TEXT:
        raise ValidationError('Listing melebihi batas teks 256 KiB.')
    result=bytearray()
    for number,line in enumerate(text.split('\n'),1):
        checkpoint(cancel)
        # Only literal values, whitespace and # comments; never expressions/includes.
        code=line.split('#',1)[0].strip(' \t\r')
        if not code:continue
        match=LINE.fullmatch(code)
        if not match:raise ValidationError(f'Listing word literal invalid pada baris {number}; instruksi/label/ekspresi tidak didukung.')
        if len(result)>=4*MAX_WORDS:raise ValidationError('Listing melebihi 4096 word.')
        result.extend(struct.pack('<I',int(match.group(1),16)))
    if not result:raise ValidationError('Listing tidak memuat word.')
    return bytes(result)


def verify(bundle,files,cancel=None):
    metadata=json.loads(files['metadata.json']);expected=files['bytes.bin'];symbol=metadata['symbol']
    validate_target(expected,symbol)
    actual=parse_listing(bundle['texts']['assembly.s'],cancel)
    mismatches=[];count=0
    for offset in range(max(len(expected),len(actual))):
        checkpoint(cancel)
        left=expected[offset] if offset<len(expected) else None
        right=actual[offset] if offset<len(actual) else None
        if left!=right:
            count+=1
            if len(mismatches)<64:mismatches.append({'target_relative_offset':offset,
                'source_file_offset':symbol['file_offset']+offset if offset<len(expected) else None,
                'expected_byte':left,'listing_byte':right})
    return {'schema':1,'engine':VERSION,'status':'BYTE_IDENTICAL' if expected==actual else 'BYTE_DIFFERENT',
            'bundle_id':bundle['bundle_id'],'binding':bundle['manifest']['binding'],
            'symbol_id':symbol['id'],'target_start':symbol['start'],'target_file_offset':symbol['file_offset'],
            'target_sha256':hashlib.sha256(expected).hexdigest(),'listing_bytes_sha256':hashlib.sha256(actual).hexdigest(),
            'target_size':len(expected),'listing_size':len(actual),'differing_bytes':count,
            'differences':mismatches,'differences_omitted':count-len(mismatches),
            'scope':'Exact bytes of selected ELF-declared range only; literal .word subset',
            'source_reconstruction_verified':False,'instructions_decoded':False,'compiled':False,
            'relocations_applied':False,'context_verified':False,'executed':False,
            'limitations':['Listing copied from target is a roundtrip, not independent reconstruction evidence',
                           'No mnemonic assembly, symbols, relocations, dependencies or ABI checking',
                           'Stored draft/material status is not changed']}


def target_words(store,input_id,symbol_id,save=False,cancel=None):
    snapshot,files,target=prepare(store,input_id,symbol_id,cancel)
    metadata=json.loads(files['metadata.json']);text=render(files['bytes.bin'],metadata['symbol']);raw=text.encode('utf-8')
    with store.lock():
        checkpoint(cancel)
        if store.load().token!=snapshot.token:raise ConflictError('Manifest berubah saat membuat listing.')
        for name,data in files.items():
            if read_bytes(store.managed(target+'/'+name))!=data:raise ConflictError('Paket target korup/berubah.')
        result={'schema':1,'engine':VERSION,'source_sha256':metadata['source_sha256'],
                'target_index_sha256':hashlib.sha256(files['index.json']).hexdigest(),
                'symbol':metadata['symbol'],'listing_sha256':hashlib.sha256(raw).hexdigest(),
                'listing_text':text,'disassembled':False,'executed':False}
        if save:
            base='word-listings/'+result['target_index_sha256']+'/'+VERSION
            path=store.managed(base+'/words.s')
            if path.exists():
                if read_bytes(path)!=raw:raise ConflictError('Listing tersimpan korup; tidak ditimpa.')
            else:
                parts=base.split('/')
                for n in range(1,len(parts)+1):store.managed('/'.join(parts[:n])).mkdir(exist_ok=True)
                store.atomic(base+'/words.s',raw)
            result['listing_file']=str(path)
    return result
