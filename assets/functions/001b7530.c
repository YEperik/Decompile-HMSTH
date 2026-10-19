
void FUN_001b7530(byte param_1,undefined1 param_2)

{
  uint *puVar1;
  int iVar2;
  undefined1 auStack_20 [16];
  byte bStack_10;
  undefined1 uStack_8;
  
  if ((&DAT_00267000)[param_1] != '\x04') {
    puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
    *puVar1 = *puVar1 & 0xff7fffff;
    bStack_10 = param_1;
    uStack_8 = param_2;
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x100) == 0x100) {
      if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x200) != 0x200) {
        FUN_001b7f40(3,6,param_1);
      }
      *(undefined2 *)((bStack_10 + 0x12) * 0x100 + 0x8340a2) = 0;
      puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859f20);
      *puVar1 = *puVar1 | 0x200;
    }
    if (((*(uint *)((uint)bStack_10 * 0x20 + 0x859f20) & 0x800) == 0x800) ||
       ((*(uint *)((uint)bStack_10 * 0x20 + 0x859f20) & 0x1000) == 0x1000)) {
      FUN_001ff4f0(0,0x43000000,0,0x17,0,*(undefined2 *)((bStack_10 + 0x12) * 0x100 + 0x834058));
    }
    else {
      FUN_001ff4f0(0,0x43200000,0,0x17,0,*(undefined2 *)((bStack_10 + 0x12) * 0x100 + 0x834058));
    }
    FUN_00178c00(uStack_8);
    if (((*(uint *)((uint)bStack_10 * 0x20 + 0x859f20) & 0x80000) != 0x80000) &&
       ((*(uint *)((uint)bStack_10 * 0x20 + 0x859f20) & 0x200000) != 0x200000)) {
      FUN_0013e2a0(bStack_10 + 0x12);
      FUN_001244b0(uRam00834058,auStack_20);
      FUN_00137b90(bStack_10 + 0x12,auStack_20);
      FUN_00138360(bStack_10 + 0x12,0x80);
      (&DAT_00267000)[bStack_10] = 4;
    }
    iVar2 = *(byte *)((uint)bStack_10 * 0x20 + 0x859f28) - 0x14;
    if (iVar2 < 0) {
      *(undefined1 *)((uint)bStack_10 * 0x20 + 0x859f28) = 0;
    }
    else {
      *(char *)((uint)bStack_10 * 0x20 + 0x859f28) = (char)iVar2;
    }
    puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859f20);
    *puVar1 = *puVar1 & 0xfffffffb;
    puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859f20);
    *puVar1 = *puVar1 | 8;
  }
  return;
}

