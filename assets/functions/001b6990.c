
void FUN_001b6990(undefined1 param_1)

{
  uint uVar1;
  uint uVar2;
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 uStack_8;
  
  if (((cGpffff8aa4 != '\x04') && ((uRam00859fe0 & 0x20000000) != 0x20000000)) &&
     ((uRam00835050 & 0x20) != 0x20)) {
    uRam00859fe0 = uRam00859fe0 & 0xbfffffff;
    uStack_8 = param_1;
    FUN_00178c00(param_1);
    uRam00835050 = uRam00835050 & 0xffbfffff;
    FUN_0013e2a0(0x10);
    if ((uRam00859fe0 & 0x4000) == 0x4000) {
      FUN_00124180(uRam00834058,&uStack_20);
      uRam0085a010 = uStack_20;
      uRam0085a014 = uStack_1c;
      uRam0085a018 = uStack_18;
      uRam0085a01c = uStack_14;
    }
    uVar1 = uRam00859fe0 & 0xfffcbfff;
    if (((uRam00859fe0 & 2) != 2) && ((uRam00859fe0 & 0x100) == 0x100)) {
      uVar2 = uRam00859fe0 & 0x200;
      uRam00859fe0 = uVar1;
      if (uVar2 != 0x200) {
        FUN_001b7f40(0,6);
      }
      uRam008350a2 = 0;
      uVar1 = uRam00859fe0 | 0x200;
    }
    uRam00859fe0 = uVar1;
    FUN_001ff4f0(0,0x42800000,0,0x17,0,uRam00835058);
    FUN_001244b0(uRam00834058,auStack_30);
    FUN_00137b90(0x10,auStack_30);
    FUN_00138540(0x10,0x20);
    if ((int)(bRam00859ffa - 0x14) < 0) {
      bRam00859ffa = 0;
    }
    else {
      bRam00859ffa = (byte)(bRam00859ffa - 0x14);
    }
    cGpffff8aa4 = '\x04';
    uRam00859fe0 = uRam00859fe0 & 0xfffffffb | 8;
  }
  return;
}

