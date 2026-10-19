
undefined4 FUN_001c21f0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 auStack_10 [16];
  
  uVar2 = 0;
  cVar1 = FUN_0013a880(0x42480000,0,auStack_10);
  if ((((cVar1 == '\x11') && (cRam00267998 != '\x05')) && (cRam00267998 != '\x06')) &&
     (cRam00267998 != '\a')) {
    if (bRam002679a8 < 0x1f) {
      bRam002679a8 = bRam002679a8 + 1;
    }
    else {
      uVar2 = 1;
      uRam00859fc0 = uRam00859fc0 | 0x40000;
      if ((uRam00835150 & 0x4000) == 0x4000) {
        FUN_0013e2a0(0x11);
      }
      if ((uRam00835150 & 4) == 4) {
        FUN_00137b90(0x11,auStack_10);
        uRam00835198 = 0x40;
        uRam00835190 = 0x40000000;
        cRam00267998 = '\0';
      }
      else {
        FUN_00137b90(0x11,auStack_10);
        FUN_00138360(0x11,0x40);
      }
      if ((0x13 < bRam0085a2f5) || (bRam0085a2f5 < 6)) {
        if ((uRam00859fc0 & 0x200) != 0x200) {
          FUN_001b7f40(1,6);
          FUN_001ff4f0(0,0x43200000,0,0x18,0,uRam00835158);
          uRam00859fc0 = uRam00859fc0 & 0xfffffffb | 0x88;
        }
        uRam00859fc0 = uRam00859fc0 | 0x200;
        uRam008351a2 = 0;
      }
    }
    if (cRam00267998 == '\t') {
      cRam00267998 = '\0';
    }
  }
  return uVar2;
}

