
void FUN_001b6fc0(byte param_1,undefined1 param_2)

{
  uint *puVar1;
  int iVar2;
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [4];
  byte bStack_10;
  undefined1 uStack_8;
  
  if ((&gp0xffff8108)[param_1] != '\x04') {
    puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
    *puVar1 = *puVar1 & 0xffffbfff;
    bStack_10 = param_1;
    uStack_8 = param_2;
    if (((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 2) != 2) &&
       ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x100) == 0x100)) {
      if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x200) != 0x200) {
        FUN_001b7f40(2,6,param_1);
      }
      *(undefined2 *)((bStack_10 + 0x1b) * 0x100 + 0x8340a2) = 0;
      puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859e60);
      *puVar1 = *puVar1 | 0x200;
    }
    FUN_00178c00(uStack_8);
    FUN_0013e2a0(bStack_10 + 0x1b);
    FUN_001ff4f0(0,0x42800000,0,0x17,0,*(undefined2 *)((bStack_10 + 0x1b) * 0x100 + 0x834058));
    FUN_00139920(bStack_10 + 0x1b,4);
    FUN_001244b0(uRam00834058,afStack_30);
    FUN_00124180(*(undefined2 *)((bStack_10 + 0x1b) * 0x100 + 0x834058),afStack_20);
    afStack_20[0] = afStack_20[0] + -afStack_30[0] * 128.0;
    afStack_20[1] = 0.0;
    afStack_20[2] = afStack_20[2] + -fStack_28 * 128.0;
    FUN_00137b90(bStack_10 + 0x1b,afStack_30);
    FUN_00137fa0(0x40800000,bStack_10 + 0x1b,0x40);
    puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859e60);
    *puVar1 = *puVar1 & 0xffffefff;
    iVar2 = *(byte *)((uint)bStack_10 * 0x20 + 0x859e68) - 10;
    if (iVar2 < 0) {
      *(undefined1 *)((uint)bStack_10 * 0x20 + 0x859e68) = 0;
    }
    else {
      *(char *)((uint)bStack_10 * 0x20 + 0x859e68) = (char)iVar2;
    }
    (&gp0xffff8108)[bStack_10] = 4;
    puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859e60);
    *puVar1 = *puVar1 & 0xfffffffb;
    puVar1 = (uint *)((uint)bStack_10 * 0x20 + 0x859e60);
    *puVar1 = *puVar1 | 8;
  }
  return;
}

