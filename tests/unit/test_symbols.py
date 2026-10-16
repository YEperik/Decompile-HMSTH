import hashlib
import io
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import threading
import unittest
from unittest.mock import patch

from app.application.symbols import inspect_symbols, create_inventory
from app.application.baselines import inspect_file
from app.application.workspaces import add_input, rename
from app.domain.binary.symbols import parse_symbols
from app.domain.binary.elf import InvalidELF, UnsupportedELF, Cancelled
from app.domain.workspace.model import ConflictError, PathError, ValidationError
from app.infrastructure.persistence.store import Store
from tests.elf_fixture import make_elf, edit
from tests.symbol_fixture import make_symbols

ROOT = Path(__file__).resolve().parents[2]


class SymbolTests(unittest.TestCase):
    def setUp(self):
        self.tmp=tempfile.TemporaryDirectory();self.addCleanup(self.tmp.cleanup)
        self.parent=Path(self.tmp.name)
        self.path=self.parent/'input 日本 spasi.elf';self.path.write_bytes(make_symbols())
        self.store=Store(self.parent/'workspace');self.store.create('Symbols')

    def parse(self, raw):return parse_symbols(io.BytesIO(raw),len(raw))

    def register(self):
        add_input(self.store,str(self.path))
        return self.store.load().data['inputs'][0]['id']

    def test_declared_functions_aliases_imports_and_unknown_sizes(self):
        result=inspect_symbols(self.path)
        inventory=result['inventory'];s=inventory['symbols']
        self.assertEqual(result['source_sha256'],hashlib.sha256(self.path.read_bytes()).hexdigest())
        self.assertEqual(s[2]['name'],'global_fn')
        self.assertEqual(s[2]['start'],0x100008);self.assertEqual(s[2]['end_exclusive'],0x100010)
        self.assertEqual(s[2]['file_offset'],0x108)
        self.assertEqual(s[3]['definition'],'UNDEFINED');self.assertIsNone(s[3]['start'])
        self.assertIsNone(s[5]['end_exclusive'])
        self.assertIsNone(s[6]['start'])
        self.assertEqual(s[7]['definition'],'COMMON')
        self.assertEqual(s[8]['name'],'alias');self.assertEqual(s[8]['start'],s[2]['start'])
        self.assertEqual(inventory['counts'],{'symbols':9,'function_symbols':6,'section_defined_functions':4})

    def test_relocatable_values_are_section_offsets(self):
        s=self.parse(make_symbols(1))['symbols'][2]
        self.assertEqual(s['start'],8);self.assertEqual(s['address_kind'],'SECTION_OFFSET')
        self.assertEqual(s['end_exclusive'],16)

    def test_dynamic_symbol_table_and_dyn_addresses(self):
        inv=self.parse(make_symbols(3,11))
        self.assertEqual(inv['tables'][0]['kind'],'DYNSYM')
        self.assertEqual(inv['symbols'][2]['address_kind'],'VIRTUAL_ADDRESS')

    def test_stripped_input_has_no_invented_functions(self):
        inv=self.parse(make_elf());self.assertEqual(inv['symbols'],[])
        self.assertEqual(inv['counts']['function_symbols'],0)
        self.assertTrue(any('Tidak ada SYMTAB' in w for w in inv['warnings']))

    def test_invalid_symbol_tables(self):
        raw=make_symbols();tab=0x400+3*40
        cases=[edit(raw,tab+36,8),edit(raw,tab+24,1),edit(raw,tab+28,0),
               edit(raw,0x200,1),edit(raw,0x210,99999),edit(raw,0x21e,20,'H'),
               edit(raw,0x200+2*16+12,2,'B')]
        for data in cases:
            with self.subTest(data_hash=hashlib.sha256(data).hexdigest()),self.assertRaises(InvalidELF):self.parse(data)

    def test_extended_index_and_symbol_limit_explicitly_unsupported(self):
        with self.assertRaises(UnsupportedELF):self.parse(edit(make_symbols(),0x21e,0xffff,'H'))
        with patch('app.domain.binary.symbols.MAX_SYMBOLS',8):
            with self.assertRaises(UnsupportedELF):self.parse(make_symbols())

    def test_out_of_section_size_keeps_raw_without_inferred_end(self):
        inv=self.parse(edit(make_symbols(),0x218,0xfffffff0))
        item=inv['symbols'][1];self.assertEqual(item['size'],0xfffffff0)
        self.assertIsNone(item['end_exclusive']);self.assertIsNone(item['file_offset'])
        self.assertTrue(item['warnings'])

    def test_non_utf8_name_preserves_exact_bytes(self):
        raw=bytearray(make_symbols());raw[0x181]=255
        item=self.parse(bytes(raw))['symbols'][1]
        self.assertTrue(item['name_bytes_hex'].startswith('ff'))

    def test_cancelled_before_read_or_publish(self):
        event=threading.Event();event.set()
        with self.assertRaises(Cancelled):inspect_symbols(self.path,event)
        iid=self.register()
        with self.assertRaises(Cancelled):create_inventory(self.store,iid,event)
        self.assertFalse((self.store.root/'symbols').exists())

    def test_repeated_inventory_is_immutable_and_baseline_unchanged(self):
        iid=self.register();before=self.path.read_bytes();baseline=inspect_file(self.path)
        first=create_inventory(self.store,iid);second=create_inventory(self.store,iid)
        self.assertEqual(first['report'],second['report'])
        self.assertNotEqual(first['receipt']['receipt_id'],second['receipt']['receipt_id'])
        self.assertEqual(self.path.read_bytes(),before);self.assertEqual(inspect_file(self.path),baseline)
        Path(first['report_file']).write_text('corrupt')
        with self.assertRaises(ConflictError):create_inventory(self.store,iid)

    def test_registered_input_changed_is_rejected(self):
        iid=self.register();self.path.write_bytes(make_symbols(1))
        with self.assertRaises(ConflictError):create_inventory(self.store,iid)
        self.assertFalse((self.store.root/'symbols').exists())

    def test_manifest_changed_during_inventory_is_rejected(self):
        iid=self.register();real=inspect_symbols
        def inspect_and_change(*args):
            result=real(*args);rename(self.store,'Changed');return result
        with patch('app.application.symbols.inspect_symbols',side_effect=inspect_and_change):
            with self.assertRaises(ConflictError):create_inventory(self.store,iid)

    def test_large_report_rejected_before_publication(self):
        iid=self.register()
        with patch('app.application.symbols.MAX_MANIFEST',10):
            with self.assertRaises(ValidationError):create_inventory(self.store,iid)
        self.assertFalse((self.store.root/'symbols').exists())

    def test_symlink_output_directory_is_rejected(self):
        iid=self.register()
        outside=self.parent/'outside';outside.mkdir()
        try:(self.store.root/'symbols').symlink_to(outside,target_is_directory=True)
        except OSError:self.skipTest('Symlink privilege unavailable')
        with self.assertRaises(PathError):create_inventory(self.store,iid)
        self.assertEqual(list(outside.iterdir()),[])

    def test_input_change_during_parse_is_rejected(self):
        real=parse_symbols
        def mutate(stream,size,cancel):
            result=real(stream,size,cancel)
            self.path.write_bytes(make_symbols(1))
            return result
        with patch('app.application.symbols.parse_symbols',side_effect=mutate):
            with self.assertRaises(ValidationError):inspect_symbols(self.path)

    def test_truncated_and_broken_string_table(self):
        raw=bytearray(make_symbols());raw[0x180]=65
        for sample in (make_symbols()[:0x410],bytes(raw)):
            with self.assertRaises(InvalidELF):self.parse(sample)

    def test_cli_inspect_and_save_and_errors(self):
        def cli(*args):return subprocess.run([sys.executable,'-m','app',*map(str,args)],cwd=ROOT,capture_output=True,text=True)
        result=cli('inspect-symbols',self.path);self.assertEqual(result.returncode,0,result.stderr)
        self.assertEqual(json.loads(result.stdout),inspect_symbols(self.path))
        self.assertEqual(cli('inspect-symbols',self.parent/'missing').returncode,2)
        self.assertEqual(cli('inspect-symbols').returncode,2)
        result=cli('symbols',self.store.root,'--input-id',self.register())
        self.assertEqual(result.returncode,0,result.stderr)
        self.assertTrue(Path(json.loads(result.stdout)['report_file']).is_file())

    @unittest.skipUnless(shutil.which('readelf'), 'readelf unavailable')
    def test_readelf_independent_comparison(self):
        p=subprocess.run([shutil.which('readelf'),'--wide','--symbols',str(self.path)],capture_output=True,text=True)
        self.assertEqual(p.returncode,0,p.stderr)
        rows={}
        for line in p.stdout.splitlines():
            parts=line.split()
            if parts and parts[0].endswith(':') and parts[0][:-1].isdigit():
                rows[int(parts[0][:-1])]=parts
        inv=inspect_symbols(self.path)['inventory']
        self.assertEqual(len(rows),len(inv['symbols']))
        for symbol in inv['symbols']:
            row=rows[symbol['symbol_index']]
            self.assertEqual(int(row[1],16),symbol['value'])
            self.assertEqual(int(row[2]),symbol['size'])
            self.assertEqual(row[3],symbol['type_name'])
            self.assertEqual(row[4],symbol['binding_name'])
            self.assertEqual(row[7] if len(row)>7 else '',symbol['name'])
