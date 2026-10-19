
void FUN_001b6c40(undefined1 param_1)

{
  undefined1 auStack_20 [24];
  undefined1 uStack_8;
  
  if ((cGpffff8aa8 != '\x04') && ((uRam00835150 & 0x20) != 0x20)) {
    uRam00859fc0 = uRam00859fc0 & 0xffdfffff;
    uStack_8 = param_1;
    FUN_00178c00(param_1);
    uRam00835150 = uRam00835150 & 0xffbfffff;
    FUN_0013e2a0(0x11);
    FUN_001ff4f0(0,0x43200000,0,0x17,0,uRam00835158);
    FUN_001244b0(uRam00834058,auStack_20);
    FUN_00137b90(0x11,auStack_20);
    FUN_00138540(0x11,0x20);
    if ((int)(bRam00859fc8 - 0x14) < 0) {
      bRam00859fc8 = 0;
    }
    else {
      bRam00859fc8 = (byte)(bRam00859fc8 - 0x14);
    }
    if (((uRam00859fc0 & 2) != 2) && ((uRam00859fc0 & 0x100) == 0x100)) {
      if ((uRam00859fc0 & 0x200) != 0x200) {
        FUN_001b7f40(1,6);
      }
      uRam008351a2 = 0;
      uRam00859fc0 = uRam00859fc0 | 0x200;
    }
    cGpffff8aa8 = '\x04';
    uRam00859fc0 = uRam00859fc0 & 0xfffffffb | 8;
  }
  return;
}

