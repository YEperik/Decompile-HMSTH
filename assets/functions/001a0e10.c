
void FUN_001a0e10(void)

{
  long lVar1;
  float afStack_20 [2];
  float fStack_18;
  float afStack_10 [4];
  
  if (cGpffff8a64 == '\0') {
    lVar1 = FUN_001536f0();
    if (lVar1 == 0) {
      FUN_00124180(uRam00834058,afStack_20);
      afStack_10[0] = afStack_20[0] - -2224.0;
      afStack_10[1] = 0.0;
      afStack_10[2] = fStack_18 - 1894.0;
      FUN_00128900(afStack_10);
      FUN_00137b90(0,afStack_10);
      FUN_00138540(0,0x20);
      cGpffff8a64 = '\x01';
    }
  }
  else if ((uRam00834050 & 4) != 4) {
    FUN_00138ce0();
    FUN_00207cb0();
    FUN_001612e0();
    uGpffff8860 = 0;
    cGpffff8a64 = '\0';
  }
  return;
}

