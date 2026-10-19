
void FUN_001beb90(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  
  cVar1 = FUN_00123d60(uRam00835058);
  if (cRam00835056 == '\x1c') {
    if (cVar1 == '\0') {
      uRam00859fe0 = uRam00859fe0 & 0xfffdffff;
      FUN_0013dff0(0x10,0x140,0,0x140);
      FUN_001be400();
    }
  }
  else if (cRam00835056 == '\x1a') {
    FUN_0013e2a0(0x10);
    if (cVar1 == '\0') {
      if ((uRam00859fe0 & 2) == 2) {
        FUN_00139920(0x10,0x24);
        uGpffff8aa4 = 3;
      }
      else {
        FUN_00139920(0x10,0x1b);
        sRam00835098 = bRam00859ffa + 0x5a;
        uRam00859fe0 = uRam00859fe0 | 0x20000;
        uGpffff8aa4 = 1;
      }
    }
  }
  else if (cRam00835056 == '\'') {
    if ((cVar1 == '\0') &&
       (uVar2 = uRam00859fe0 & 0xfffeffff, uVar3 = uRam00859fe0 & 0x4000, uRam00859fe0 = uVar2,
       uVar3 != 0x4000)) {
      FUN_0013dff0(0x10,0x140,0,0x140);
      FUN_001be400();
    }
  }
  else if (cRam00835056 == '%') {
    FUN_0013e2a0(0x10);
    if (cVar1 == '\0') {
      FUN_00139920(0x10,0x26);
      sRam00835098 = 0x5a;
      uGpffff8aa4 = 1;
      uRam00859fe0 = uRam00859fe0 | 0x10000;
    }
  }
  else if (((((cRam00835056 == '\x14') || (cRam00835056 == '\x13')) || (cRam00835056 == '\x19')) ||
           ((cRam00835056 == '\n' || (cRam00835056 == '\t')))) ||
          ((cRam00835056 == '\x15' || ((cRam00835056 == '\b' || (cRam00835056 == '\a')))))) {
    if ((uRam00835050 & 0x4000) == 0x4000) {
      FUN_0013e2a0(0x10);
    }
    if (cVar1 == '\0') {
      FUN_0013dff0(0x10,0x140,0,0x140);
      FUN_001be400();
    }
  }
  else if (((uRam00835050 & 0x20) != 0x20) && ((uRam00835050 & 0x400000) != 0x400000)) {
    FUN_001be400();
  }
  return;
}

