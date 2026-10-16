"""Non-runnable ET_REL with one simple classic MIPS instruction pair."""
import struct
from tests.relocation_fixture import make_relocations


def make_hi_lo(rela=False):
    raw = bytearray(make_relocations(1, rela))
    stride = 12 if rela else 8
    struct.pack_into('<I', raw, 0x504, (4 << 8) | 5)
    struct.pack_into('<I', raw, 0x504 + stride, (4 << 8) | 6)
    struct.pack_into('<II', raw, 0x108, 0x3c080001, 0x25088000)
    return bytes(raw)
