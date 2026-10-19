
void FUN_001be090(void)

{
  char cVar1;
  long lVar2;
  float afStack_40 [2];
  float fStack_38;
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [7];
  undefined4 uStack_4;
  
  lVar2 = FUN_00151510(0x11);
  if (((lVar2 != 0) && ((uRam0026774c & 0x400) != 0x400)) && (sRam00834058 != -1)) {
    FUN_00124180(sRam00834058,afStack_40);
    FUN_00124180(uRam00835158,afStack_30);
    afStack_20[0] = afStack_30[0] - afStack_40[0];
    afStack_20[1] = 0.0;
    afStack_20[2] = fStack_28 - fStack_38;
    FUN_00128900(afStack_20);
    FUN_00137b90(0x11,afStack_20);
    FUN_0013e2a0(0x11);
    FUN_00138360(0x11,0x80);
    uRam00267998 = 0xc;
  }
  if (((uRam00835150 & 4) == 4) && ((uRam00859fc0 & 0x40000) == 0x40000)) {
    FUN_00124180(uRam00835158,afStack_40);
    cVar1 = FUN_0014f600(afStack_40);
    if (cVar1 == -0x19) {
      if (((uRam00859fc0 & 0x40000) == 0x40000) || ((uRam00859fc0 & 0x20000) == 0x20000)) {
        uRam00859fc0 = uRam00859fc0 & 0xfffbffff | 0x20000;
        FUN_0013e2a0(0x11);
        FUN_00138760(0x44900000,0,0x45400000,0x11);
        if (cRam002679bc == '\0') {
          FUN_00150200(2);
        }
        cRam002679bc = cRam002679bc + '\x01';
        uStack_4 = FUN_00141880(0x11);
        FUN_0013a3e0(0,uStack_4,0,uStack_4,0x11,2);
        uRam00267998 = 5;
      }
    }
    else if ((cVar1 == -0x18) &&
            (((uRam00859fc0 & 0x40000) == 0x40000 || ((uRam00859fc0 & 0x80000) == 0x80000)))) {
      uRam00859fc0 = uRam00859fc0 & 0xfffbffff | 0x80000;
      uRam00267998 = 7;
      FUN_0013e2a0(0x11);
      FUN_00138760(0,0,0xc4800000,0x11);
      if (cRam002679bc == '\0') {
        FUN_00150200(0x15);
      }
      cRam002679bc = cRam002679bc + '\x01';
      uStack_4 = FUN_00141880(0x11);
      FUN_0013a3e0(0,uStack_4,0,uStack_4,0x11,2);
    }
  }
  return;
}

