
void FUN_001cd3f0(undefined4 param_1,char param_2)

{
  float afStack_40 [2];
  float fStack_38;
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [4];
  char cStack_10;
  undefined4 uStack_8;
  
  cStack_10 = param_2;
  uStack_8 = param_1;
  if (param_2 == '\0') {
    FUN_001244b0(uRam00834058,afStack_20);
  }
  else {
    FUN_00124180(uRam00834058,afStack_30);
    FUN_001cd2d0(cStack_10,afStack_40);
    afStack_20[0] = afStack_30[0] - afStack_40[0];
    afStack_20[1] = 0.0;
    afStack_20[2] = fStack_28 - fStack_38;
    FUN_00128900(afStack_20);
  }
  FUN_00137cc0(uStack_8,0,afStack_20);
  return;
}

