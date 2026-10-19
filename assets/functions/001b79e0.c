
/* WARNING: Heritage AFTER dead removal. Example location: s0xffffffdc : 0x001b7ce0 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_001b79e0(byte param_1,byte param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined2 uStack_20;
  undefined1 uStack_1e;
  byte bStack_10;
  byte bStack_8;
  
  bStack_10 = param_1;
  bStack_8 = param_2;
  uStack_40 = (int)_DAT_002443a0;
  uStack_3c = (int)((ulong)_DAT_002443a0 >> 0x20);
  uStack_38 = DAT_002443a8;
  uStack_34 = DAT_002443ac;
  uStack_30 = DAT_002443b0;
  uStack_2c = DAT_002443b4;
  uStack_28 = (int)_DAT_002443b8;
  uStack_24 = (uint)((ulong)_DAT_002443b8 >> 0x20);
  uStack_20 = DAT_002443c0;
  uStack_1e = DAT_002443c2;
  uVar2 = 0xffff;
  iVar1 = 0;
  uVar3 = 0;
  if (param_1 == 3) {
    uVar3 = *(uint *)((uint)param_2 * 0x20 + 0x859f20) & 0xffff;
    if (((*(uint *)((uint)param_2 * 0x20 + 0x859f20) & 0x800) == 0x800) ||
       ((*(uint *)((uint)param_2 * 0x20 + 0x859f20) & 0x1000) == 0x1000)) {
      uVar2 = uStack_24 & 0xff;
    }
    else if (((*(uint *)((uint)param_2 * 0x20 + 0x859f20) & 0x2000) == 0x2000) ||
            ((*(uint *)((uint)param_2 * 0x20 + 0x859f20) & 0x1000000) == 0x1000000)) {
      if (*(char *)((uint)param_2 * 0x20 + 0x859f24) == '\n') {
        uVar2 = 0xd;
      }
      else if (*(byte *)((uint)param_2 * 0x20 + 0x859f24) < 2) {
        uVar2 = 0xf;
      }
      else {
        FUN_00154550(4,*(undefined1 *)((uint)param_2 * 0x20 + 0x859f24));
        uVar2 = 0xe;
      }
    }
    FUN_0016ce90((bStack_8 + 8) * 8 + 0x833e50,0x15);
  }
  else if (param_1 == 2) {
    uVar3 = *(uint *)((uint)param_2 * 0x20 + 0x859e60) & 0xffff;
    FUN_0016ce90((param_2 + 0xf) * 8 + 0x833e50,0x16);
    if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859e60) & 0x800) == 0x800) {
      uVar2 = 0x26;
    }
    else if (((*(uint *)((uint)bStack_8 * 0x20 + 0x859e60) & 0x100) == 0x100) &&
            ((*(uint *)((uint)bStack_8 * 0x20 + 0x859e60) & 0x200) != 0x200)) {
      uVar2 = (uint)*(byte *)((int)&uStack_3c + (uint)bStack_10 * 7 + 2);
    }
  }
  else if (param_1 == 1) {
    uVar3 = uRam00859fc0 & 0xffff;
    iVar1 = FUN_00148df0(0,2);
  }
  else if (param_1 == 0) {
    uVar3 = uRam00859fe0 & 0xffff;
    iVar1 = FUN_00148df0(0,2);
    if ((uRam00859fe0 & 0x100) == 0x100) {
      if ((uRam00859fe0 & 0x200) == 0x200) {
        uVar2 = (uint)*(byte *)((int)&uStack_40 + (uint)bStack_10 * 7 + 2);
      }
      else {
        uVar2 = (uint)*(byte *)((int)&uStack_3c + (uint)bStack_10 * 7 + 2);
      }
    }
  }
  if (uVar2 == 0xffff) {
    if ((uVar3 & 2) == 2) {
      uVar2 = (uint)*(byte *)((int)&uStack_40 + (uint)bStack_10 * 7 + 3);
    }
    else if ((uVar3 & 4) == 4) {
      uVar2 = (uint)*(byte *)((int)&uStack_40 + (uint)bStack_10 * 7 + 1);
    }
    else if ((uVar3 & 8) == 8) {
      uVar2 = (uint)*(byte *)((int)&uStack_40 + (uint)bStack_10 * 7 + 2);
    }
    else {
      uVar2 = iVar1 + (uint)*(byte *)((int)&uStack_40 + (uint)bStack_10 * 7) & 0xffff;
    }
  }
  FUN_0016cc90(uVar2);
  return;
}

