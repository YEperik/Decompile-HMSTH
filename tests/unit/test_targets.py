import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch
from app.application.targets import target_bundle, _inspect_file
from app.application.workspaces import add_input,rename
from app.infrastructure.persistence.store import Store
from app.domain.workspace.model import WorkspaceError,ConflictError,ValidationError,PathError
from app.domain.binary.elf import Cancelled
from tests.relocation_fixture import make_relocations

ROOT=Path(__file__).resolve().parents[2]

class TargetTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.path=self.parent/'input.elf'
        self.raw=make_relocations();self.path.write_bytes(self.raw)
        self.store=Store(self.parent/'workspace');self.store.create('Targets')
        add_input(self.store,str(self.path));self.iid=self.store.load().data['inputs'][0]['id']
    def run_target(self,**kw):return target_bundle(self.store,self.iid,'3:2',**kw)
    def files(self):return {str(p.relative_to(self.store.root)):p.read_bytes() for p in self.store.root.rglob('*') if p.is_file()}

    def test_export_verify_exact_bytes_metadata_and_no_mutation(self):
        result=self.run_target();folder=Path(result['bundle_dir'])
        self.assertEqual((folder/'bytes.bin').read_bytes(),self.raw[0x108:0x110])
        index=json.loads((folder/'index.json').read_bytes())
        for name,entry in index['files'].items():
            data=(folder/name).read_bytes();self.assertEqual(hashlib.sha256(data).hexdigest(),entry['sha256'])
            self.assertEqual(len(data),entry['size'])
        before=self.files();verified=self.run_target(verify=True)
        self.assertEqual(verified['files_verified'],5);self.assertFalse(verified['semantics_verified'])
        self.assertEqual(before,self.files());self.assertEqual(self.path.read_bytes(),self.raw)

    def test_repeat_export_stable_artifacts_distinct_receipts(self):
        a=self.run_target();before={p.name:p.read_bytes() for p in Path(a['bundle_dir']).iterdir()}
        b=self.run_target();self.assertNotEqual(a['receipt']['id'],b['receipt']['id'])
        self.assertEqual(before,{p.name:p.read_bytes() for p in Path(b['bundle_dir']).iterdir()})

    def test_cross_workspace_reproducibility(self):
        a=Path(self.run_target()['bundle_dir'])
        other=Store(self.parent/'other');other.create('Different');add_input(other,str(self.path))
        b=Path(target_bundle(other,other.load().data['inputs'][0]['id'],'3:2')['bundle_dir'])
        self.assertEqual({p.name:p.read_bytes() for p in a.iterdir()},{p.name:p.read_bytes() for p in b.iterdir()})

    def test_verify_missing_never_creates_bundle(self):
        with self.assertRaises((WorkspaceError,OSError)):self.run_target(verify=True)
        self.assertFalse((self.store.root/'targets').exists())

    def test_corruption_all_files_refused_without_repair(self):
        folder=Path(self.run_target()['bundle_dir'])
        for name in ('bytes.bin','config.json','metadata.json','references.json','index.json'):
            path=folder/name;original=path.read_bytes();path.write_bytes(b'corrupt')
            before=self.files()
            for verify in (False,True):
                with self.assertRaises(ConflictError):self.run_target(verify=verify)
                self.assertEqual(before,self.files())
            path.write_bytes(original)

    def test_partial_write_recoverable_only_by_export(self):
        folder=Path(self.run_target()['bundle_dir']);(folder/'bytes.bin').unlink()
        with self.assertRaises((WorkspaceError,OSError)):self.run_target(verify=True)
        self.assertFalse((folder/'bytes.bin').exists())
        self.run_target();self.assertEqual((folder/'bytes.bin').read_bytes(),self.raw[0x108:0x110])

    def test_source_modified_refused(self):
        self.run_target();self.path.write_bytes(self.raw+b'changed')
        with self.assertRaises(ConflictError):self.run_target(verify=True)

    def test_cancel_and_manifest_conflict(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):self.run_target(cancel=event)
        def mutate(*args):
            r=_inspect_file(*args);rename(self.store,'Changed');return r
        with patch('app.application.targets._inspect_file',side_effect=mutate):
            with self.assertRaises(ConflictError):self.run_target()
        self.assertFalse((self.store.root/'targets').exists())

    def test_symlink_output_refused(self):
        outside=self.parent/'outside';outside.mkdir()
        (self.store.root/'targets').symlink_to(outside,target_is_directory=True)
        with self.assertRaises(PathError):self.run_target()
        self.assertEqual(list(outside.iterdir()),[])

    def test_ids_size_and_unknown_boundary_rejected(self):
        for sid in ('../x','3:02','3:5','3:0'):
            with self.assertRaises(WorkspaceError):target_bundle(self.store,self.iid,sid)
        with self.assertRaises(ValidationError):target_bundle(self.store,'missing','3:2')
        with patch('app.application.targets.MAX_MANIFEST',10):
            with self.assertRaises(ValidationError):self.run_target()
        self.assertFalse((self.store.root/'targets').exists())

    def test_cli_export_verify_and_tamper(self):
        args=[str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2']
        for command in ('export-target','verify-target'):
            r=subprocess.run([sys.executable,'-m','app',command]+args,cwd=ROOT,capture_output=True,text=True)
            self.assertEqual(r.returncode,0,r.stderr)
        folder=Path(json.loads(r.stdout)['bundle_dir']);(folder/'config.json').write_text('{}')
        r=subprocess.run([sys.executable,'-m','app','verify-target']+args,cwd=ROOT,capture_output=True,text=True)
        self.assertEqual(r.returncode,2)
