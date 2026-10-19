
void FUN_001c9550(void)

{
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_4;
  
  fStack_4 = 0.0;
  FUN_00124180(uRam00834058,&uStack_20);
  FUN_00124180(uRam00835158,auStack_30);
  FUN_00128b50(&fStack_4,auStack_30,&uStack_20);
  if (128.0 < fStack_4) {
    if (192.0 < fStack_4) {
      if ((uRam00835150 & 4) == 4) {
        uStack_1c = 0;
        uRam00835180 = uStack_20;
        uRam00835184 = 0;
        uRam00835188 = uStack_18;
        uRam0083518c = uStack_14;
      }
      else {
        FUN_00138760(uStack_20,0,uStack_18,0x11);
      }
    }
  }
  else {
    FUN_0013e2a0(0x11);
    FUN_00138ce0(0x11);
  }
  fRam002679c4 = fRam002679c4 - 2.4;
  if (fRam002679c4 <= 0.0) {
    fRam002679c4 = 0.0;
    uRam00267998 = 0;
    FUN_0013dff0(0x11,0x140,0,0x140);
    FUN_001c2c20();
  }
  return;
}

