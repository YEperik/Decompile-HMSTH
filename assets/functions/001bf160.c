
void FUN_001bf160(void)

{
  float afStack_20 [4];
  float afStack_10 [2];
  float fStack_8;
  
  uRam00859fe0 = uRam00859fe0 & 0xfffbffff;
  FUN_00124180(uRam00835058,afStack_10);
  afStack_20[0] = afStack_10[0] - -1230.0;
  afStack_20[1] = 0.0;
  afStack_20[2] = fStack_8 - 2500.0;
  FUN_00128900(afStack_20);
  FUN_00137b90(0x10,afStack_20);
  FUN_00139920(0x10,0xd);
  uRam00267994 = 1;
  return;
}

