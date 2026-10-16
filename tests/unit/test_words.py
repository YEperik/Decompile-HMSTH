import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_materials as fixture
from app.application.words import parse_listing,render,target_words
from app.domain.workspace.model import ValidationError,ConflictError,PathError
from app.domain.binary.elf import Cancelled

class WordListingTests(unittest.TestCase):
    setUp=fixture.MaterialTests.setUp
    call=fixture.MaterialTests.call
    add=fixture.MaterialTests.add
    material=fixture.MaterialTests.material
    snapshot=fixture.MaterialTests.snapshot
    def listing(self,**kw):return target_words(self.store,self.iid,'3:2',**kw)
    def verify_text(self,text):
        self.asm.write_text(text);a=self.material()
        return self.material('verify-words',bundle_id=a['bundle_id'])
    def test_render_little_endian_known_bytes(self):
        raw=b'\x78\x56\x34\x12\xff\x00\x00\x80';text=render(raw,{'start':0,'file_offset':4})
        self.assertIn('.word 0x12345678\n.word 0x800000ff\n',text)
        self.assertEqual(parse_listing(text),raw)
    def test_parser_rejects_unsupported_syntax(self):
        for text in ('','.word 1','.word -1','.word 0x100000000','.word symbol','.word 0x00000001+1','label: .word 0x00000001','.include "x"','jr $ra','.word 0x00000001, 0x00000002','.word 0x00000001;'):
            with self.assertRaises(ValidationError):parse_listing(text)
    def test_comments_crlf_and_whitespace(self):
        self.assertEqual(parse_listing('# hi\r\n \t.word\t0x01020304 # comment\r\n'),b'\x04\x03\x02\x01')
    def test_limits_alignment_and_cancel(self):
        for raw,sym in [(b'x',{'start':0,'file_offset':0}),(b'xxxx',{'start':1,'file_offset':0}),(b'xxxx',{'start':0,'file_offset':1})]:
            with self.assertRaises(ValidationError):render(raw,sym)
        with self.assertRaises(ValidationError):parse_listing('.word 0x00000000\n'*4097)
        with self.assertRaises(ValidationError):parse_listing('#'*(256*1024+1))
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):parse_listing('.word 0x00000000',event)
    def test_verified_roundtrip_read_only(self):
        before=self.snapshot();listing=self.listing();self.assertEqual(before,self.snapshot())
        self.asm.write_text(listing['listing_text']);a=self.material();before=self.snapshot()
        r=self.material('verify-words',bundle_id=a['bundle_id'])
        self.assertEqual(r['status'],'BYTE_IDENTICAL');self.assertEqual(r['differing_bytes'],0)
        self.assertFalse(r['source_reconstruction_verified']);self.assertFalse(r['context_verified'])
        self.assertEqual(before,self.snapshot());self.assertEqual(self.elf.read_bytes(),self.raw)
    def test_changed_word_reports_byte_offset(self):
        raw=(self.bundle/'bytes.bin').read_bytes();changed=bytearray(raw);changed[2]^=255
        r=self.verify_text(render(bytes(changed),{'start':0,'file_offset':0}))
        self.assertEqual(r['status'],'BYTE_DIFFERENT');self.assertEqual(r['differing_bytes'],1)
        self.assertEqual(r['differences'][0]['target_relative_offset'],2)
        self.assertEqual(r['differences'][0]['source_file_offset'],0x10a)
    def test_short_and_long_listings(self):
        text=self.listing()['listing_text'];body=text.splitlines()[1:]
        short=self.verify_text(body[0]+'\n');self.assertEqual(short['differing_bytes'],4)
        long=self.verify_text(text+'.word 0x00000000\n');self.assertEqual(long['differing_bytes'],4)
        self.assertIsNone(long['differences'][0]['source_file_offset'])
    def test_differences_capped_not_silently_truncated(self):
        r=self.verify_text('.word 0xffffffff\n'*30)
        self.assertEqual(len(r['differences']),64);self.assertEqual(r['differences_omitted'],r['differing_bytes']-64)
    def test_save_repeat_and_corrupt_refused(self):
        a=self.listing(save=True);self.assertEqual(a,self.listing(save=True))
        p=Path(a['listing_file']);self.assertEqual(p.read_text(),a['listing_text']);p.write_text('bad')
        with self.assertRaises(ConflictError):self.listing(save=True)
        self.assertEqual(p.read_text(),'bad')
    def test_corrupt_target_and_input_refused(self):
        p=self.bundle/'bytes.bin';raw=p.read_bytes();p.write_bytes(b'bad')
        with self.assertRaises(ConflictError):self.listing()
        p.write_bytes(raw);self.elf.write_bytes(self.raw+b'x')
        with self.assertRaises(ConflictError):self.listing()
    def test_save_symlink_refused(self):
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'word-listings').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.listing(save=True)
        self.assertEqual(list(outside.iterdir()),[])
    def test_cli_status_codes(self):
        root=fixture.fixture.ROOT;args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2']
        r=subprocess.run([sys.executable,'-m','app','target-words']+args+['--save'],cwd=root,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);listing=json.loads(r.stdout)
        for text,code in [(listing['listing_text'],0),(listing['listing_text']+'.word 0x00000000\n',1),('jr $ra\n',2)]:
            self.asm.write_text(text);a=self.material()
            r=subprocess.run([sys.executable,'-m','app','draft-materials-verify-words']+args+['--revision',self.revision,'--bundle-id',a['bundle_id']],cwd=root,capture_output=True,text=True)
            self.assertEqual(r.returncode,code,r.stderr)
