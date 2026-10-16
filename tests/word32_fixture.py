"""Synthetic ET_REL with one active word32 relocation in the selected function."""
import struct
from tests.relocation_fixture import make_relocations


def make_word32(rela=False):
    raw=bytearray(make_relocations(1,rela))
    struct.pack_into('<I',raw,0x504,(4<<8)|2)
    struct.pack_into('<I',raw,0x504+(12 if rela else 8),0)
    struct.pack_into('<I',raw,0x108,0xfffffff0)
    return bytes(raw)
