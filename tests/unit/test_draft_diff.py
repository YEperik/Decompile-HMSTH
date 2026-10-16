import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from uuid import uuid4
from unittest.mock import patch
from tests.unit import test_drafts as fixture
from app.application.drafts import drafts
from app.application.draft_diff import compare
from app.application.targets import target_bundle
from app.domain.workspace.model import ValidationError,ConflictError,WorkspaceError,PathError
from app.domain.binary.elf import Cancelled

class DiffTests(unittest.TestCase):
    setUp=fixture.DraftTests.setUp
    call=fixture.DraftTests.call
    add=fixture.DraftTests.add

    def pair(self,before=b'int f(void) { return 1; }\n',after=b'int f(void) { return 2; }\n',language='c'):
        self.source.write_bytes(before);a=self.add()
        self.source.write_bytes(after);b=self.add(parent=a['record']['revision'],language=language)
        return a,b
    def diff(self,a,b,**kw):return self.call(revision=a['record']['revision'],compare_to=b['record']['revision'],**kw)
    def snapshot(self):return {str(p.relative_to(self.store.root)):p.read_bytes() for p in self.store.root.rglob('*') if p.is_file()}

    def test_changed_lines_and_read_only(self):
        a,b=self.pair();before=self.snapshot();r=self.diff(a,b)['comparison']
        self.assertEqual(before,self.snapshot());self.assertEqual(self.elf.read_bytes(),self.raw)
        self.assertEqual((r['lines_added'],r['lines_removed']),(1,1))
        self.assertTrue(r['direct_parent']);self.assertFalse(r['source_bytes_equal'])
        self.assertFalse(r['compiled']);self.assertFalse(r['binary_match_verified'])
        self.assertEqual(r['changes'][0]['before']['lines'],['int f(void) { return 1; }\n'])
    def test_identical_revisions_and_language_change(self):
        a,b=self.pair(after=b'int f(void) { return 1; }\n',language='cpp')
        r=self.diff(a,b)['comparison'];self.assertTrue(r['source_bytes_equal']);self.assertFalse(r['language_equal'])
        self.assertEqual(r['changes'],[])
        self.assertTrue(self.diff(a,a)['comparison']['source_bytes_equal'])
    def test_newline_and_crlf_not_normalized(self):
        for before,after in [(b'x\n',b'x'),(b'x\r\n',b'x\n'),('日本語\n'.encode(),'日本語\r\n'.encode())]:
            a,b=self.pair(before,after);r=self.diff(a,b)['comparison']
            self.assertFalse(r['source_bytes_equal']);self.assertTrue(r['changes'])
            self.assertEqual(r['changes'][0]['before']['lines'][0].encode(),before)
    def test_insertion_deletion_and_reverse(self):
        a,b=self.pair(b'a\nc\n',b'a\nb\nc\n');r=self.diff(a,b)['comparison']
        self.assertEqual((r['lines_added'],r['lines_removed']),(1,0))
        self.assertEqual(r['changes'][0]['before']['start_line'],2)
        self.assertEqual(r['changes'][0]['before']['line_count'],0)
        r=self.diff(b,a)['comparison'];self.assertEqual((r['lines_added'],r['lines_removed']),(0,1))
    def test_branch_comparison_allowed_without_parent_claim(self):
        a,b=self.pair();c=self.add(parent=a['record']['revision'])
        self.assertFalse(self.diff(b,c)['comparison']['direct_parent'])
    def test_save_repeatable_corrupt_not_overwritten(self):
        a,b=self.pair();x=self.diff(a,b,save_diff=True);y=self.diff(a,b,save_diff=True)
        self.assertEqual(x,y);path=Path(x['report_file']);self.assertEqual(json.loads(path.read_bytes()),x['comparison'])
        path.write_bytes(b'corrupt')
        with self.assertRaises(ConflictError):self.diff(a,b,save_diff=True)
        self.assertEqual(path.read_bytes(),b'corrupt')
    def test_bad_ids_missing_and_other_target(self):
        a,b=self.pair()
        for rid in ('../x',str(uuid4())):
            with self.assertRaises(ValidationError):self.call(revision=a['record']['revision'],compare_to=rid)
        target_bundle(self.store,self.iid,'3:1')
        other=drafts(self.store,self.iid,'3:1',source=str(self.source))
        with self.assertRaises(ValidationError):self.diff(a,other)
    def test_tampered_source_or_target(self):
        a,b=self.pair();p=Path(a['source_file']);original=p.read_bytes();p.write_text('bad')
        with self.assertRaises(ConflictError):self.diff(a,b)
        p.write_bytes(original);(self.bundle/'bytes.bin').write_bytes(b'bad')
        with self.assertRaises(ConflictError):self.diff(a,b)
    def test_limits_refuse_without_output(self):
        a,b=self.pair(b'x\n'*1001,b'y\n'*1001)
        with self.assertRaises(ValidationError):self.diff(a,b,save_diff=True)
        self.assertFalse((self.store.root/'draft-comparisons').exists())
        a,b=self.pair(b'x\n'*2001,b'y')
        with self.assertRaises(ValidationError):self.diff(a,b)
    def test_report_limit(self):
        a,b=self.pair()
        with patch('app.application.drafts.MAX_MANIFEST',10):
            with self.assertRaises(ValidationError):self.diff(a,b,save_diff=True)
        self.assertFalse((self.store.root/'draft-comparisons').exists())
    def test_cancel_and_symlink(self):
        a,b=self.pair();event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.diff(a,b,cancel=event)
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'draft-comparisons').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.diff(a,b,save_diff=True)
        self.assertEqual(list(outside.iterdir()),[])
    def test_invalid_mode_combinations(self):
        a,b=self.pair()
        for kw in ({'compare_to':b['record']['revision']},{'save_diff':True},{'revision':a['record']['revision'],'compare_to':b['record']['revision'],'source':str(self.source)}):
            with self.assertRaises(ValidationError):self.call(**kw)
    def test_cli_diff(self):
        a,b=self.pair()
        r=subprocess.run([sys.executable,'-m','app','draft-diff',str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--from-revision',a['record']['revision'],'--to-revision',b['record']['revision'],'--save'],cwd=fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr)
        result=json.loads(r.stdout);self.assertEqual(result['comparison']['status'],'TEXT_COMPARISON_ONLY');self.assertTrue(Path(result['report_file']).is_file())
