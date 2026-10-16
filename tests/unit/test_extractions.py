import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch

from app.application.extractions import extract_function, list_functions
from app.application.workspaces import add_input, rename
from app.domain.binary.elf import Cancelled
from app.domain.workspace.model import ConflictError, ValidationError, PathError
from app.infrastructure.persistence.store import Store
from tests.symbol_fixture import make_symbols
from tests.elf_fixture import edit, make_elf

ROOT=Path(__file__).resolve().parents[2]


class ExtractionTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name);self.source=self.parent/'input 日本 spasi.elf'
        self.source.write_bytes(make_symbols());self.store=Store(self.parent/'workspace')
        self.store.create('Extraction');add_input(self.store,str(self.source))
        self.iid=self.store.load().data['inputs'][0]['id']

    def extract(self,symbol='3:2'):return extract_function(self.store,self.iid,symbol)

    def test_real_bytes_hash_and_provenance(self):
        before=self.source.read_bytes();manifest=(self.store.root/'workspace.json').read_bytes()
        result=self.extract();raw=Path(result['payload_file']).read_bytes()
        self.assertEqual(raw,before[0x108:0x110])
        self.assertEqual(result['report']['payload_sha256'],hashlib.sha256(raw).hexdigest())
        self.assertEqual(result['report']['source_sha256'],hashlib.sha256(before).hexdigest())
        self.assertFalse(result['report']['executed']);self.assertFalse(result['report']['relocations_applied'])
        self.assertEqual((self.store.root/'workspace.json').read_bytes(),manifest)
        self.assertEqual(self.source.read_bytes(),before)

    def test_pages_and_eligibility_and_aliases(self):
        first=list_functions(self.source,0,2);second=list_functions(self.source,2,2)
        self.assertEqual(first['total_function_symbols'],6);self.assertEqual(first['next_offset'],2)
        self.assertTrue(first['functions'][0]['extractable'])
        self.assertFalse(second['functions'][0]['extractable'])
        self.assertEqual(list_functions(self.source,100,2)['returned'],0)
        self.assertEqual(Path(self.extract('3:2')['payload_file']).read_bytes(),Path(self.extract('3:8')['payload_file']).read_bytes())

    def test_invalid_pagination_and_symbol_id(self):
        for off,lim in [(-1,20),(0,0),(0,201)]:
            with self.assertRaises(ValidationError):list_functions(self.source,off,lim)
        for sid in ('../x','3:02','-1:2','3:99999'):
            with self.assertRaises(ValidationError):self.extract(sid)

    def test_unknown_size_import_object_and_absolute_refused(self):
        for sid in ('3:3','3:4','3:5','3:6'):
            with self.assertRaises(ValidationError):self.extract(sid)
        self.assertFalse((self.store.root/'extractions').exists())

    def test_stripped_has_no_candidates(self):
        self.source.write_bytes(make_elf());self.assertEqual(list_functions(self.source)['functions'],[])

    def test_repeated_result_is_identical_and_corrupt_payload_refused(self):
        first=self.extract();second=self.extract()
        self.assertEqual(first['report'],second['report']);self.assertNotEqual(first['receipt'],second['receipt'])
        Path(first['payload_file']).write_bytes(b'corrupt')
        with self.assertRaises(ConflictError):self.extract()
        self.assertEqual(Path(first['payload_file']).read_bytes(),b'corrupt')

    def test_changed_input_refused(self):
        self.source.write_bytes(edit(self.source.read_bytes(),0x108,123))
        with self.assertRaises(ConflictError):self.extract()
        self.assertFalse((self.store.root/'extractions').exists())

    def test_cancel_before_publication(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):extract_function(self.store,self.iid,'3:2',event)
        self.assertFalse((self.store.root/'extractions').exists())

    def test_manifest_conflict_refused(self):
        from app.application.extractions import _inspect_file
        def changed(*args):
            result=_inspect_file(*args);rename(self.store,'Changed');return result
        with patch('app.application.extractions._inspect_file',side_effect=changed):
            with self.assertRaises(ConflictError):self.extract()
        self.assertFalse((self.store.root/'extractions').exists())

    def test_symlink_output_refused(self):
        outside=self.parent/'outside';outside.mkdir()
        try:(self.store.root/'extractions').symlink_to(outside,target_is_directory=True)
        except OSError:self.skipTest('Symlink privilege unavailable')
        with self.assertRaises(PathError):self.extract()
        self.assertEqual(list(outside.iterdir()),[])

    def test_maximum_extract_size_and_warnings_refused(self):
        with patch('app.application.extractions.MAX_EXTRACT',4):
            with self.assertRaises(ValidationError):self.extract()
        # Existing symbol parser annotates unsupported target-specific st_other bits.
        self.source.write_bytes(edit(self.source.read_bytes(),0x200+2*16+13,0x80,'B'))
        with self.assertRaises(ValidationError):self.extract()

    def test_relocatable_extraction_uses_section_offset(self):
        path=self.parent/'rel.elf';path.write_bytes(make_symbols(1));add_input(self.store,str(path))
        iid=self.store.load().data['inputs'][1]['id']
        result=extract_function(self.store,iid,'3:2')
        self.assertEqual(result['report']['symbol']['address_kind'],'SECTION_OFFSET')
        self.assertEqual(Path(result['payload_file']).read_bytes(),path.read_bytes()[0x108:0x110])

    def test_cli_list_extract_and_missing_arguments(self):
        def cli(*args):return subprocess.run([sys.executable,'-m','app',*map(str,args)],cwd=ROOT,capture_output=True,text=True)
        listed=cli('list-functions',self.source,'--limit','1')
        self.assertEqual(listed.returncode,0,listed.stderr);self.assertEqual(json.loads(listed.stdout)['returned'],1)
        result=cli('extract-function',self.store.root,'--input-id',self.iid,'--symbol-id','3:2')
        self.assertEqual(result.returncode,0,result.stderr);self.assertTrue(Path(json.loads(result.stdout)['payload_file']).is_file())
        self.assertEqual(cli('extract-function',self.store.root).returncode,2)
