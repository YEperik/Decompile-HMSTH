
void FUN_001c1690(void)

{
  ulong uVar1;
  float fVar2;
  undefined4 uStack_8;
  
  uStack_8 = 0.0;
  if ((uRam00859fe0 & 2) != 2) {
    if (bRam0085a002 < 0x32) {
      if (cRam00859fe6 == '\x03') {
        uStack_8 = 100.0;
      }
      else if (cRam00859fe6 == '\x02') {
        uStack_8 = 50.0;
      }
      else if (cRam00859fe6 == '\x01') {
        uStack_8 = 25.0;
      }
    }
    else if (cRam00859fe6 == '\x03') {
      uStack_8 = 50.0;
    }
    else if (cRam00859fe6 == '\x02') {
      uStack_8 = 25.0;
    }
    else if (cRam00859fe6 == '\x01') {
      uStack_8 = 12.5;
    }
    uVar1 = FUN_00148df0(0,999999);
    if ((long)uVar1 < 0) {
      fVar2 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar2 = (float)(int)uVar1;
    }
    if (fVar2 / 10000.0 <= uStack_8) {
      uRam00859fe0 = uRam00859fe0 & 0xfffffff3 | 2;
      uRam00859fe5 = 0;
      cRam00859fe6 = '\n';
      uRam00267994 = 3;
      FUN_00149760(0x97);
    }
  }
  return;
}

