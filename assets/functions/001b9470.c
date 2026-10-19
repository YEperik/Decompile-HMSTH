
void FUN_001b9470(void)

{
  undefined4 auStack_10 [2];
  undefined4 uStack_8;
  
  if ((((((uRam00859fc0 & 1) == 1) && (0x1d < bRam00859fc8)) && ((uRam00835150 & 0x20) != 0x20)) &&
      (((uRam00859fc0 & 0x100) != 0x100 && ((uRam00859fc0 & 0x20000) != 0x20000)))) &&
     (((uRam00859fc0 & 0x80000) != 0x80000 && (cRam00859fc9 == cRam00267734)))) {
    FUN_00124180(uRam00834058,auStack_10);
    uRam00859fc0 = uRam00859fc0 & 0xffdfffff;
    uRam00835150 = uRam00835150 & 0xffbffeff;
    FUN_0013e2a0(0x11);
    FUN_001389e0(auStack_10[0],0,uStack_8,0x11);
    uRam00835150 = uRam00835150 | 0x200000;
    if ((bRam00859fc8 < 0x1e) || (0x4f < bRam00859fc8)) {
      if ((bRam00859fc8 < 0x50) || (0x8b < bRam00859fc8)) {
        if ((bRam00859fc8 < 0x8c) || (199 < bRam00859fc8)) {
          if (199 < bRam00859fc8) {
            uRam008351a6 = 0x400;
          }
        }
        else {
          uRam008351a6 = 0x200;
        }
      }
      else {
        uRam008351a6 = 0x100;
      }
    }
    else {
      uRam008351a6 = 0x80;
    }
    uRam00267998 = 0;
    if ((bRam00267878 & 0x20) != 0x20) {
      FUN_001b7f40(1,9,0);
      bRam00267878 = bRam00267878 | 0x20;
    }
  }
  return;
}

