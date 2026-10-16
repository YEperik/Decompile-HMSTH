import hashlib
import json
from pathlib import Path
import struct
import tempfile
import unittest

from app.application.symbols import create_inventory
from app.application.workspaces import add_input
from app.domain.workspace.model import ConflictError
from app.infrastructure.persistence.store import Store
from tests.symbol_fixture import make_symbols


class SymbolPageTests(unittest.TestCase):
    def test_large_inventory_all_entries_persisted_and_corruption_refused(self):
        raw=bytearray(make_symbols());count=3000
        entries=bytes(raw[0x200:0x220])+bytes(raw[0x220:0x230])*(count-2)
        headers=bytearray(raw[0x400:0x400+200])
        struct.pack_into('<I',headers,3*40+16,0x500)
        struct.pack_into('<I',headers,3*40+20,len(entries))
        raw.extend(entries);shoff=len(raw);raw.extend(headers)
        struct.pack_into('<I',raw,32,shoff)
        with tempfile.TemporaryDirectory() as tmp:
            source=Path(tmp)/'many.elf';source.write_bytes(raw)
            store=Store(Path(tmp)/'workspace');store.create('Many');add_input(store,str(source))
            iid=store.load().data['inputs'][0]['id']
            result=create_inventory(store,iid);report=result['report'];inv=report['inventory']
            self.assertNotIn('symbols',inv);self.assertEqual(inv['counts']['symbols'],count)
            entries=[]
            for page in inv['symbol_pages']:
                data=(Path(result['report_file']).parent/page['file']).read_bytes()
                self.assertLessEqual(len(data),1024*1024)
                self.assertEqual(hashlib.sha256(data).hexdigest(),page['sha256'])
                entries.extend(json.loads(data)['symbols'])
            self.assertEqual(len(entries),count)
            self.assertEqual(len({s['id'] for s in entries}),count)
            self.assertEqual(create_inventory(store,iid)['report'],report)
            (Path(result['report_file']).parent/inv['symbol_pages'][0]['file']).write_text('corrupt')
            with self.assertRaises(ConflictError):create_inventory(store,iid)
            self.assertEqual(source.read_bytes(),raw)
