
void FUN_001b9230(float param_1,undefined4 param_2,float param_3)

{
  float afStack_50 [4];
  float fStack_40;
  undefined4 uStack_3c;
  float fStack_38;
  float afStack_30 [2];
  float fStack_28;
  float fStack_18;
  float fStack_8;
  
  uStack_3c = 0;
  if ((((uRam00859fe0 & 1) == 1) && ((uRam00859fe0 & 0x100) != 0x100)) &&
     (cRam00267734 == cRam0085a004)) {
    uRam00859fe0 = uRam00859fe0 & 0xbfffffff;
    uRam00835050 = uRam00835050 & 0xffbfffff;
    fStack_40 = param_1;
    fStack_38 = param_3;
    fStack_18 = param_1;
    fStack_8 = param_3;
    FUN_00124180(uRam00835058,afStack_30);
    afStack_50[0] = fStack_40 - afStack_30[0];
    afStack_50[1] = 0.0;
    afStack_50[2] = fStack_38 - afStack_30[0];
    FUN_00128900(afStack_50);
    afStack_50[0] = afStack_50[0] * 64.0;
    afStack_50[2] = afStack_50[2] * 64.0;
    fStack_40 = fStack_40 - afStack_50[0];
    if (fStack_38 < fStack_28) {
      fStack_38 = fStack_38 + afStack_50[2];
    }
    else {
      fStack_38 = fStack_38 - afStack_50[2];
    }
    uRam00835050 = uRam00835050 & 0xfffffeff;
    FUN_0013e2a0(0x10);
    FUN_001389e0(fStack_40,0,fStack_38,0x10);
    uRam00267994 = 0;
    uRam00859fe0 = uRam00859fe0 & 0xeffc7fff;
  }
  return;
}

