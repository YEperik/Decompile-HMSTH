
void FUN_001b6e30(byte param_1,undefined1 param_2)

{
  uint *puVar1;
  undefined1 auStack_20 [16];
  byte bStack_10;
  undefined1 uStack_8;
  
  if ((*(uint *)((param_1 + 0x6f) * 0x100 + 0x834050) & 0x80000000) != 0x80000000) {
    bStack_10 = param_1;
    uStack_8 = param_2;
    FUN_00178c00(param_2);
    FUN_0013e2a0(bStack_10 + 0x6f);
    FUN_001ff4f0(0,0x43200000,0,0x17,0,*(undefined2 *)((bStack_10 + 0x6f) * 0x100 + 0x834058));
    FUN_001244b0(uRam00834058,auStack_20);
    FUN_00137b90(bStack_10 + 0x6f,auStack_20);
    FUN_00138540(bStack_10 + 0x6f,0x20);
    if ((int)((byte)(&gp0xffff8930)[bStack_10] - 0x14) < 0) {
      (&gp0xffff8930)[bStack_10] = 0;
    }
    else {
      (&gp0xffff8930)[bStack_10] = (char)((byte)(&gp0xffff8930)[bStack_10] - 0x14);
    }
    puVar1 = (uint *)((bStack_10 + 0x6f) * 0x100 + 0x834050);
    *puVar1 = *puVar1 | 0x80000000;
  }
  return;
}

