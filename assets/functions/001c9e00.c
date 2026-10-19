
void FUN_001c9e00(void)

{
  undefined4 auStack_10 [2];
  undefined4 uStack_8;
  
  uRam00859fe0 = uRam00859fe0 & 0xbff87fff;
  uRam00835050 = uRam00835050 & 0xffbfffff;
  uGpffff8aa4 = 0;
  if ((bRam00859ffa < 0x1f) || (0x50 < bRam00859ffa)) {
    if ((bRam00859ffa < 0x51) || (0x8c < bRam00859ffa)) {
      if ((bRam00859ffa < 0x8d) || (200 < bRam00859ffa)) {
        if (200 < bRam00859ffa) {
          uRam008350a6 = 0x1000;
          if (((bRam00859fe4 & 4) == 4) && (bGpffff8844 < 0xb)) {
            uRam00859fe0 = uRam00859fe0 | 0x4000;
          }
          uRam00859ff0 = 0x47070000;
        }
      }
      else {
        uRam008350a6 = 0x400;
        if (((bRam00859fe4 & 4) == 4) && (bGpffff8844 < 0xb)) {
          uRam00859fe0 = uRam00859fe0 | 0x4000;
        }
        uRam00859ff0 = 0x46870000;
      }
    }
    else {
      uRam008350a6 = 0x200;
      if (((bRam00859fe4 & 4) == 4) && (bGpffff8844 < 0xb)) {
        uRam00859fe0 = uRam00859fe0 | 0x4000;
      }
      uRam00859ff0 = 0x46070000;
    }
  }
  else {
    uRam008350a6 = 0x80;
  }
  FUN_00124180(uRam00834058,auStack_10);
  FUN_0013e2a0(0x10);
  FUN_001389e0(auStack_10[0],0,uStack_8,0x10);
  uRam00835050 = uRam00835050 | 0x200000;
  if (cRam00859fff != -1) {
    cRam00859fff = cRam00859fff + '\x01';
  }
  if ((bGpffff898c & 0x20) != 0x20) {
    FUN_001b7f40(0,9,0);
    bGpffff898c = bGpffff898c | 0x20;
  }
  uRam00859fe0 = uRam00859fe0 & 0xfc0fffff;
  return;
}

