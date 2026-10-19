
void FUN_001c0fa0(void)

{
  short sVar1;
  short sVar2;
  float afStack_30 [4];
  float afStack_20 [2];
  float fStack_18;
  float afStack_10 [2];
  float fStack_8;
  
  sVar1 = sRam00835058;
  sVar2 = FUN_00124be0(0x43000000,0x3f800000,uRam00834058,sRam00835058);
  if (sVar1 == sVar2) {
    if ((uRam00835050 & 0x4000) == 0x4000) {
      FUN_0013e2a0(0x10);
    }
    if ((uRam00835050 & 4) != 4) {
      FUN_00138540(0x10,0x40);
    }
    FUN_00124180(uRam00834058,afStack_20);
    FUN_00124180(sRam00835058,afStack_10);
    afStack_30[0] = afStack_20[0] - afStack_10[0];
    afStack_30[1] = 0.0;
    afStack_30[2] = fStack_18 - fStack_8;
    FUN_00128900(afStack_30);
    FUN_00137b90(0x10,afStack_30);
  }
  else if (((uRam00835050 & 0x4000) != 0x4000) && ((uRam00835050 & 4) != 4)) {
    FUN_0013dff0(0x10,0x100,0,0x100);
  }
  return;
}

