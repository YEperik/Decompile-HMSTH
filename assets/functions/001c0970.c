
void FUN_001c0970(void)

{
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_8;
  float fStack_4;
  
  fStack_8 = 0.0;
  if ((uRam00859fe0 & 0x8000) == 0x8000) {
    uRam00859fe0 = uRam00859fe0 & 0xffff7fff;
    uRam008350a6 = 0;
  }
  FUN_00124180(uRam00834058,&uStack_20);
  FUN_00124180(uRam00835058,&uStack_30);
  FUN_00128b50(&fStack_8,&uStack_30,&uStack_20);
  if ((uRam00834050 & 0x80) == 0x80) {
    fStack_4 = 160.0;
  }
  else {
    fStack_4 = 80.0;
  }
  if (fStack_4 < fStack_8) {
    if ((uRam00835050 & 4) == 4) {
      if ((fStack_4 * 1.5 < fStack_8) && ((bRam00835056 < 2 || (2 < bRam00835056)))) {
        if (bRam00859ffa < 200) {
          if (bRam00859ffa < 0x8c) {
            if (bRam00835056 != 2) {
              FUN_00139920(0x10,2);
            }
            uRam00835094 = 0x40c00000;
          }
          else {
            if (bRam00835056 != 3) {
              FUN_00139920(0x10,3);
            }
            uRam00835094 = 0x41100000;
          }
        }
        else {
          if (bRam00835056 != 4) {
            FUN_00139920(0x10,4);
          }
          uRam00835094 = 0x41400000;
        }
      }
      if ((((fStack_4 * 1.5 < fStack_8) && (fStack_8 < fStack_4 * 2.0)) && (1 < bRam00835056)) &&
         (bRam00835056 < 5)) {
        uRam00835094 = 0x41080000;
      }
      if (((fStack_8 < fStack_4 * 1.5) && (cRam00834056 != '\x02')) &&
         ((cRam00834056 != '\t' && ((1 < bRam00835056 && (bRam00835056 < 5)))))) {
        FUN_00139920(0x10,1);
        uRam00835094 = 0x40400000;
      }
      uStack_1c = 0;
      uRam00835080 = uStack_20;
      uRam00835084 = 0;
      uRam00835088 = uStack_18;
      uRam0083508c = uStack_14;
    }
    else if (fStack_8 < fStack_4 * 1.5) {
      if (bRam00835056 == 1) {
        FUN_001382c0(uStack_20,0,uStack_18,0x40400000,0x10);
      }
      else {
        FUN_00138760(uStack_20,0,uStack_18,0x10);
      }
    }
    else {
      FUN_001389e0(uStack_20,0,uStack_18,0x10);
    }
  }
  else {
    FUN_001b9720(0x10);
    if (bRam00835056 != 6) {
      if (((((cRam00834056 != '\x02') && (cRam00834056 != '\x01')) && (cRam00834056 != '\b')) &&
          ((cRam00834056 != '\t' && (cRam00834056 != '9')))) &&
         ((cRam00834056 != ':' && ((cRam00834056 != ';' && (cRam00834056 != '<')))))) {
        FUN_00138ce0(0x10);
      }
      uRam00835050 = uRam00835050 & 0xffbfffdf;
    }
  }
  fRam00859ff0 = fRam00859ff0 - 2.4;
  if (fRam00859ff0 <= 0.0) {
    fRam00859ff0 = 0.0;
    uRam00859fe0 = uRam00859fe0 & 0xffffbfff;
    uRam0085a010 = uStack_30;
    uRam0085a014 = uStack_2c;
    uRam0085a018 = uStack_28;
    uRam0085a01c = uStack_24;
    FUN_0013dff0(0x10,0x80,0,0x80);
  }
  return;
}

