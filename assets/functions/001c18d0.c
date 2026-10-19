
void FUN_001c18d0(void)

{
  ulong uVar1;
  float fVar2;
  float fStack_8;
  
  fStack_8 = 0.0;
  if (((uRam00859fc0 & 2) != 2) && (cRam00859fc5 != '\0')) {
    if (cRam00859fc5 == '\x03') {
      fStack_8 = 100.0;
    }
    else if (cRam00859fc5 == '\x02') {
      fStack_8 = 50.0;
    }
    else if (cRam00859fc5 == '\x01') {
      fStack_8 = 25.0;
    }
    uVar1 = FUN_00148df0(0,999999);
    if ((long)uVar1 < 0) {
      fVar2 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar2 = (float)(int)uVar1;
    }
    if (fVar2 / 10000.0 <= fStack_8) {
      uRam00859fc0 = uRam00859fc0 & 0xfffffff3 | 2;
      uRam00859fc4 = 0;
      cRam00859fc5 = '\a';
      uGpffff8aa8 = 3;
    }
  }
  return;
}

