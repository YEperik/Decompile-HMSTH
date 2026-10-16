import json
from pathlib import Path
import subprocess
import sys
import threading
import unittest
from unittest.mock import patch
from tests.unit import test_drafts as fixture
from app.domain.workspace.model import ValidationError,ConflictError,WorkspaceError,PathError
from app.domain.binary.elf import Cancelled

class MaterialTests(unittest.TestCase):
    call=fixture.DraftTests.call
    add=fixture.DraftTests.add
    def setUp(self):
        fixture.DraftTests.setUp(self)
        self.revision=self.add()['record']['revision']
        self.asm=self.parent/'input.s';self.asm.write_bytes(b'# User example only\r\n.word 0\r\n')
        self.header=self.parent/'context.h';self.header.write_text('/* User context example */\ntypedef unsigned int u32;\n')
    def material(self,action='add',**kw):
        if action=='add':kw={'assembly':str(self.asm),'context':str(self.header),**kw}
        return self.call(revision=self.revision,material_action=action,**kw)
    def snapshot(self):return {str(p.relative_to(self.store.root)):p.read_bytes() for p in self.store.root.rglob('*') if p.is_file()}
    def test_roundtrip_binding_and_no_semantic_claim(self):
        original=self.snapshot();a=self.material();b=self.material();self.assertEqual(a,b)
        self.assertEqual(Path(a['bundle_dir'],'assembly.s').read_bytes(),self.asm.read_bytes())
        m=a['manifest'];self.assertEqual(m['binding']['revision'],self.revision)
        self.assertFalse(m['assembly_matches_target']);self.assertFalse(m['context_verified']);self.assertFalse(m['executed'])
        before=self.snapshot();shown=self.material('show',bundle_id=a['bundle_id']);listed=self.material('list')
        self.assertEqual(before,self.snapshot());self.assertEqual(shown['texts']['assembly.s'].encode(),self.asm.read_bytes())
        self.assertEqual(listed['bundles'],[a['bundle_id']])
        for name,data in original.items():self.assertEqual(self.snapshot()[name],data)
        self.assertEqual(self.elf.read_bytes(),self.raw)
    def test_changed_input_creates_separate_bundle(self):
        a=self.material();self.header.write_text('typedef int replacement;\n');b=self.material()
        self.assertNotEqual(a['bundle_id'],b['bundle_id']);self.assertEqual(len(self.material('list')['bundles']),2)
        self.assertIn('u32',Path(a['bundle_dir'],'context.h').read_text())
    def test_invalid_text_and_oversize(self):
        for data in (b'',b' \n',b'x\x00',b'\xff',b'x'*(256*1024+1)):
            self.asm.write_bytes(data)
            with self.assertRaises(ValidationError):self.material()
        self.assertFalse((self.store.root/'draft-materials').exists())
    def test_corrupt_files_or_manifest_not_repaired(self):
        a=self.material()
        for name in ('assembly.s','context.h','manifest.json'):
            path=Path(a['bundle_dir'],name);original=path.read_bytes();path.write_bytes(b'corrupt')
            before=self.snapshot()
            for action,kw in [('show',{'bundle_id':a['bundle_id']}),('list',{}),('add',{})]:
                with self.assertRaises(WorkspaceError):self.material(action,**kw)
                self.assertEqual(before,self.snapshot())
            path.write_bytes(original)
    def test_missing_file_rejected(self):
        a=self.material();Path(a['bundle_dir'],'context.h').unlink()
        with self.assertRaises((WorkspaceError,OSError)):self.material('show',bundle_id=a['bundle_id'])
    def test_bundle_from_other_revision_rejected(self):
        a=self.material();self.revision=self.add()['record']['revision']
        with self.assertRaises((WorkspaceError,OSError)):self.material('show',bundle_id=a['bundle_id'])
    def test_bad_ids_and_modes(self):
        for bid in ('../x','A'*64,'0'*64):
            with self.assertRaises((WorkspaceError,OSError)):self.material('show',bundle_id=bid)
        with self.assertRaises(ValidationError):self.material('wrong')
        with self.assertRaises(ValidationError):self.material('list',assembly=str(self.asm))
        with self.assertRaises(ValidationError):self.call(material_action='list')
    def test_changed_source_and_target(self):
        (self.bundle/'bytes.bin').write_bytes(b'bad')
        with self.assertRaises(ConflictError):self.material()
        self.assertFalse((self.store.root/'draft-materials').exists())
    def test_symlink_source_and_output(self):
        link=self.parent/'link.s';link.symlink_to(self.asm)
        with self.assertRaises(WorkspaceError):self.material(assembly=str(link))
        outside=self.parent/'outside';outside.mkdir();(self.store.root/'draft-materials').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.material()
        self.assertEqual(list(outside.iterdir()),[])
    def test_cancel(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.material(cancel=event)
        self.assertFalse((self.store.root/'draft-materials').exists())
    def test_partial_failure_recoverable_without_overwriting(self):
        original=self.store.atomic
        def fail(relative,data):
            if relative.endswith('manifest.json'):raise OSError('injected')
            return original(relative,data)
        with patch.object(self.store,'atomic',side_effect=fail):
            with self.assertRaises(OSError):self.material()
        info=self.material('list');self.assertEqual(len(info['incomplete_bundles']),1);self.assertEqual(info['bundles'],[])
        a=self.material();self.assertEqual(a['bundle_id'],info['incomplete_bundles'][0]);self.assertEqual(self.material('list')['incomplete_bundles'],[])
    def test_limit(self):
        a=self.material()
        with patch('app.application.materials.MAX_BUNDLES',1):
            self.assertEqual(self.material()['bundle_id'],a['bundle_id'])
            self.header.write_text('/* changed */')
            with self.assertRaises(ValidationError):self.material()
    def test_cli(self):
        args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--revision',self.revision]
        r=subprocess.run([sys.executable,'-m','app','draft-materials-add']+args+['--assembly',str(self.asm),'--context',str(self.header)],cwd=fixture.ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,0,r.stderr);bid=json.loads(r.stdout)['bundle_id']
        for action,extra in [('show',['--bundle-id',bid]),('list',[])]:
            r=subprocess.run([sys.executable,'-m','app','draft-materials-'+action]+args+extra,cwd=fixture.ROOT,capture_output=True,text=True)
            self.assertEqual(r.returncode,0,r.stderr)
