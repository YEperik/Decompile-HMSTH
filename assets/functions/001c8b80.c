
undefined4 FUN_001c8b80(void)

{
  short sVar1;
  char cVar2;
  short sVar3;
  long lVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  cVar2 = FUN_00123d60(sRam00835058);
  sVar1 = sRam00835058;
  uVar5 = 1;
  uVar6 = 1;
  if (cRam00835056 == '\x05') {
    if ((uint)uRam00835098 == bRam008350aa - 1) {
      FUN_00139920(0x10,6);
      uVar6 = uVar5;
    }
  }
  else if (cRam00835056 == '\x06') {
    if ((uRam00835098 == 0) && (uVar6 = uVar5, (uRam00835050 & 0x400000) == 0x400000)) {
      if (((uRam00859fe0 & 0x40000) == 0x40000) ||
         (sVar3 = FUN_00124be0(0x42a00000,0x3f800000,uRam00834058,sRam00835058), sVar1 != sVar3)) {
        uRam00835050 = uRam00835050 & 0xffbfffff | 0x10;
        FUN_0013a620(0x10,1,1);
        if (((uRam00859fe0 & 0x10000000) == 0x10000000) || ((uRam00859fe0 & 0x4000) == 0x4000)) {
          FUN_00146bc0(0x10);
        }
        else {
          FUN_0013dff0(0x10,0x100,0,0x100);
        }
        uVar6 = 0;
      }
      else {
        FUN_001b9720(0x10);
        uRam00859fe0 = uRam00859fe0 & 0xffff7fff;
        uRam008350a6 = 0;
      }
    }
    if (cVar2 == '\0') {
      uRam00859fe0 = uRam00859fe0 & 0xffff7fff;
      FUN_0013a620(0x10,1,1);
      uRam00835050 = uRam00835050 & 0xffbfffff;
      uVar6 = 0;
    }
    else {
      lVar4 = FUN_00123d10(sRam00835058);
      if (lVar4 != 0) {
        uRam00835050 = uRam00835050 & 0xffbfffff | 0x10;
        uRam00859fe0 = uRam00859fe0 & 0xffff7fff;
        FUN_0013a620(0x10,1,1);
      }
    }
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}

