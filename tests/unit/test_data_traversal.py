import json
from pathlib import Path
import struct
import subprocess
import sys
import unittest
from unittest.mock import patch
from tests.unit import test_function_data as fixture
from tests.relocation_fixture import make_relocations
from app.application.function_data import function_data
from app.domain.binary.reference_index import ReferenceIndex
from app.domain.binary.elf import UnsupportedELF
from app.domain.workspace.model import ValidationError


def chain(etype=2, cycle=True, zero=False):
    raw=bytearray(make_relocations(etype))
    base=0 if etype==1 else 0x100000
    # Convert the fixture COMMON symbol into a second OBJECT in .text.
    struct.pack_into('<I',raw,0x200+7*16+4,base+32)
    struct.pack_into('<I',raw,0x200+7*16+8,0 if zero else 4)
    struct.pack_into('<H',raw,0x200+7*16+14,1)
    extra=struct.pack('<II',base+24,(7<<8)|2)
    if cycle:extra+=struct.pack('<II',base+32,(4<<8)|2)
    old=struct.unpack_from('<I',raw,32)[0]
    raw=raw[:old]+extra+raw[old:]
    new=old+len(extra)
    struct.pack_into('<I',raw,32,new)
    struct.pack_into('<I',raw,new+5*40+20,24+len(extra))
    return bytes(raw)


class TraversalTests(unittest.TestCase):
    setUp=fixture.FunctionDataTests.setUp
    register=fixture.FunctionDataTests.register
    run_bundle=fixture.FunctionDataTests.run_bundle
    report=fixture.FunctionDataTests.report

    def test_default_remains_direct(self):
        self.register(chain());a=self.run_bundle();r=self.report(a)
        self.assertEqual(a['counts']['EXTRACTED'],1);self.assertFalse(r['recursive'])
        self.assertEqual(a['unexpanded_objects'],1)
        self.assertEqual(r['extractor'],'function-data-1')
        self.assertNotIn('edges',r)

    def test_depth_one_and_cycle_depth_two(self):
        self.register(chain())
        a=self.run_bundle(data_depth=1);r=self.report(a)
        self.assertEqual(a['counts']['EXTRACTED'],2);self.assertEqual(r['unexpanded_object_ids'],['3:7'])
        b=self.run_bundle(data_depth=2);r=self.report(b)
        self.assertEqual(b['counts']['EXTRACTED'],2);self.assertEqual(r['unexpanded_object_ids'],[])
        self.assertIn({'source_id':'3:7','target_id':'3:4','relocation_ids':['5:4']},r['edges'])
        folder=Path(b['bundle_dir']);self.assertEqual((folder/'object-3-7.bin').read_bytes(),self.raw[0x120:0x124])
        self.assertEqual(len(list(folder.glob('object-*.bin'))),2)
        self.run_bundle(data_depth=2,verify=True)

    def test_depth_four_terminates_and_single_scan(self):
        self.register(chain())
        from app.application.function_data import function_refs
        with patch('app.application.function_data.function_refs',wraps=function_refs) as scan:
            a=self.run_bundle(data_depth=4)
        self.assertEqual(scan.call_count,1);self.assertEqual(a['counts']['EXTRACTED'],2)

    def test_rel_mapping(self):
        self.register(chain(1));a=self.run_bundle(data_depth=2)
        self.assertEqual(a['counts']['EXTRACTED'],2);self.run_bundle(data_depth=2,verify=True)

    def test_unresolved_child_not_guessed(self):
        self.register(chain(zero=True));a=self.run_bundle(data_depth=4)
        self.assertEqual(a['counts']['UNRESOLVED'],1)
        self.assertFalse((Path(a['bundle_dir'])/'object-3-7.bin').exists())

    def test_depth_invalid_and_separate_outputs(self):
        for value in (-1,5,True,'1'):
            with self.assertRaises(ValidationError):self.run_bundle(data_depth=value)
        self.register(chain());a=self.run_bundle(data_depth=0);b=self.run_bundle(data_depth=1)
        self.assertNotEqual(a['bundle_dir'],b['bundle_dir'])
        with self.assertRaises(FileNotFoundError):self.run_bundle(data_depth=2,verify=True)

    def test_object_limit_stops_before_publish(self):
        self.register(chain())
        with patch('app.application.function_data.MAX_OBJECTS',1):
            with self.assertRaises(ValidationError):self.run_bundle(data_depth=2)
        self.assertFalse((self.store.root/'function-data').exists())

    def test_index_section_bounds_and_global_locations(self):
        index=ReferenceIndex()
        for section,location,sid in ((1,10,'inside'),(2,10,'wrong-section'),(1,14,'end'),(1,9,'before'),(0,10,'global')):
            index.add(section,location,{'symbol_id':sid})
        index.finish();resolved={'section_index':1,'start':10,'end_exclusive':14}
        self.assertEqual([x['symbol_id'] for x in index.within(resolved,'REL')],['inside'])
        self.assertEqual([x['symbol_id'] for x in index.within(resolved,'EXEC')],['inside','global'])

    def test_index_limit(self):
        index=ReferenceIndex()
        for i in range(1025):index.add(1,10,{'id':str(i)})
        index.finish()
        with self.assertRaises(UnsupportedELF):index.within({'section_index':1,'start':10,'end_exclusive':14},'REL')

    def test_cli_depth(self):
        self.register(chain())
        for command in ('extract-function-data','verify-function-data'):
            p=subprocess.run([sys.executable,'-m','app',command,str(self.store.root),'--input-id',self.iid,'--symbol-id','3:2','--data-depth','2'],capture_output=True,text=True)
            self.assertEqual(p.returncode,0,p.stderr);self.assertEqual(json.loads(p.stdout)['counts']['EXTRACTED'],2)
