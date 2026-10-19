
void FUN_001c90f0(void)

{
  uint uVar1;
  uint uVar2;
  float afStack_40 [4];
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [2];
  float fStack_18;
  float fStack_4;
  
  if (DAT_00267008 == 0xff) {
    uRam00859fe0 = uRam00859fe0 & 0xefffffff;
    uRam00267994 = 0;
  }
  else {
    FUN_00124180(uRam00835058,afStack_30);
    FUN_00124180(*(undefined2 *)((DAT_00267008 + 0x12) * 0x100 + 0x834058),afStack_20);
    afStack_40[0] = afStack_30[0] - afStack_20[0];
    afStack_40[1] = 0.0;
    afStack_40[2] = fStack_28 - fStack_18;
    FUN_00128900(afStack_40);
    FUN_00128b50(&fStack_4,afStack_30,afStack_20);
    if (128.0 < fStack_4) {
      FUN_00137b90(0x10,afStack_40);
      uVar2 = uRam00835050 | 0x100;
      uVar1 = uRam00835050 & 4;
      uRam00835050 = uVar2;
      if (uVar1 != 4) {
        FUN_00138540(0x10,0x40);
      }
      if (bRam00859ffa < 200) {
        if (bRam00859ffa < 0x8c) {
          if (cRam00835056 != '\x02') {
            FUN_00139920(0x10,2);
          }
          uRam00835094 = 0x40c00000;
        }
        else {
          if (cRam00835056 != '\x03') {
            FUN_00139920(0x10,3);
          }
          uRam00835094 = 0x41100000;
        }
      }
      else {
        if (cRam00835056 != '\x04') {
          FUN_00139920(0x10,4);
        }
        uRam00835094 = 0x41400000;
      }
      fRam00859ff0 = fRam00859ff0 - 1.0;
      if (fRam00859ff0 <= 0.0) {
        FUN_0013e2a0(0x10);
        FUN_00138ce0(0x10);
        uRam00859fe0 = uRam00859fe0 & 0xefffffff;
        uRam00267994 = 0;
      }
    }
    else {
      FUN_0013e2a0(0x10);
      if ((uRam00859fe0 & 8) == 8) {
        FUN_00139920(0x10,0x14);
      }
      else {
        FUN_00139920(0x10,0x13);
      }
      FUN_001c29f0(DAT_00267008);
      uRam00267994 = 1;
    }
  }
  return;
}

