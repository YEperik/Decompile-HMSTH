"""Synthetic REL/RELA records; not executable code."""
import struct
from tests.symbol_fixture import make_symbols


def make_relocations(etype=2,rela=False):
    raw=bytearray(make_symbols(etype))
    base=0 if etype==1 else 0x100000
    entries=[(base+8,(3<<8)|4,-4),(base+12,(4<<8)|5,12),(base,(2<<8)|6,0)]
    entry_size=12 if rela else 8
    for location,info,addend in entries:
        raw.extend(struct.pack('<IIi',location,info,addend) if rela else struct.pack('<II',location,info))
    headers=bytes(raw[0x400:0x400+200]);shoff=len(raw)
    raw.extend(headers)
    raw.extend(struct.pack('<IIIIIIIIII',0,4 if rela else 9,0,0,0x500,len(entries)*entry_size,3,1,4,entry_size))
    struct.pack_into('<I',raw,32,shoff);struct.pack_into('<H',raw,48,6)
    return bytes(raw)
