"""Synthetic container for parser tests; not a commercial game or runnable PS2 demo."""
import struct


def make_elf():
    names = b'\0.text\0.bss\0.shstrtab\0'
    raw = bytearray(0x140 + 4*40)
    raw[:16] = b'\x7fELF\x01\x01\x01' + bytes(9)
    struct.pack_into('<HHIIIIIHHHHHH', raw, 16, 2, 8, 1, 0x100000, 52, 0x140, 0, 52, 32, 1, 40, 4, 3)
    struct.pack_into('<IIIIIIII', raw, 52, 1, 0x100, 0x100000, 0x100000, 16, 48, 5, 0x100)
    raw[0x100:0x110] = bytes(range(16))  # arbitrary bytes, never executed
    raw[0x110:0x110+len(names)] = names
    struct.pack_into('<IIIIIIIIII', raw, 0x140+40, 1, 1, 6, 0x100000, 0x100, 16, 0, 0, 16, 0)
    struct.pack_into('<IIIIIIIIII', raw, 0x140+80, 7, 8, 3, 0x100010, 0x110, 32, 0, 0, 16, 0)
    struct.pack_into('<IIIIIIIIII', raw, 0x140+120, 12, 3, 0, 0, 0x110, len(names), 0, 0, 1, 0)
    return bytes(raw)


def edit(raw, offset, value, fmt='I'):
    result = bytearray(raw)
    struct.pack_into('<'+fmt, result, offset, value)
    return bytes(result)
