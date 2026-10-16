"""Synthetic named symbols; bytes in .text are arbitrary and never executed."""
import struct


def make_symbols(etype=2, table_type=2):
    raw = bytearray(0x500)
    raw[:16] = b'\x7fELF\x01\x01\x01' + bytes(9)
    struct.pack_into('<HHIIIIIHHHHHH', raw, 16, etype, 8, 1, 0x100000, 0, 0x400, 0, 52, 0, 0, 40, 5, 4)
    names = b'\0.text\0.strtab\0.symtab\0.shstrtab\0'
    strings = b'\0local_fn\0global_fn\0imported\0object\0unknown_size\0absolute\0common\0alias\0'
    raw[0x100:0x140] = bytes(range(64))
    raw[0x180:0x180+len(strings)] = strings
    raw[0x300:0x300+len(names)] = names
    base = 0 if etype == 1 else 0x100000
    entries = [(0,0,0,0,0,0),
               (1,base,8,2,0,1),
               (10,base+8,8,18,0,1),
               (20,0,0,18,0,0),
               (29,base+24,4,17,0,1),
               (36,base+32,0,18,0,1),
               (49,42,0,18,0,0xfff1),
               (58,4,8,17,0,0xfff2),
               (65,base+8,8,34,0,1)]
    for i,entry in enumerate(entries):struct.pack_into('<IIIBBH',raw,0x200+i*16,*entry)
    for i,entry in enumerate([(0,0,0,0,0,0,0,0,0,0),
                             (1,1,6,base,0x100,64,0,0,4,0),
                             (7,3,0,0,0x180,len(strings),0,0,1,0),
                             (15,table_type,0,0,0x200,len(entries)*16,2,2,4,16),
                             (23,3,0,0,0x300,len(names),0,0,1,0)]):
        struct.pack_into('<IIIIIIIIII',raw,0x400+i*40,*entry)
    return bytes(raw)
