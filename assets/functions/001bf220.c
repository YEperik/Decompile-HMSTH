
void FUN_001bf220(void)

{
  uint uVar1;
  
  uRam00859fe0 = (uint)((ulong)((long)(int)(uRam00859fe0 & 0xbfffffff) << 0x21) >> 0x21);
  if ((uRam00859fe0 & 0x100) == 0x100) {
    if ((uRam00859fe0 & 0x200) == 0x200) {
      FUN_00139920(0x10,0x30);
    }
    else {
      FUN_00139920(0x10,0x31);
    }
  }
  else {
    if ((uRam00859fe0 & 2) == 2) {
      FUN_00139920(0x10,0x31);
    }
    else if ((uRam00859fe0 & 8) == 8) {
      FUN_00139920(0x10,0x30);
    }
    else {
      FUN_00139920(0x10,0x2f);
    }
    uRam00267994 = 0;
  }
  if ((bRam0026787c & 8) != 8) {
    FUN_001b7f40(0,7,0);
    bRam0026787c = bRam0026787c | 8;
  }
  if (cRam0085a001 != -1) {
    cRam0085a001 = cRam0085a001 + '\x01';
  }
  if (((uRam00859fe0 & 0x1000000) == 0x1000000) ||
     (uVar1 = uRam00859fe0 & 0xeffa3fff, (uRam00859fe0 & 0x2000000) == 0x2000000)) {
    uRam00859fe0 = uRam00859fe0 & 0xecfa3fff;
    FUN_001497c0(0xb6);
    uVar1 = uRam00859fe0;
    if (bRam00859ffa + 10 < 0x100) {
      bRam00859ffa = (byte)(bRam00859ffa + 10);
    }
    else {
      bRam00859ffa = 0xff;
    }
  }
  uRam00859fe0 = uVar1;
  if (((uRam00859fe0 & 0x400000) == 0x400000) ||
     (uVar1 = uRam00859fe0 & 0xffcfffff, (uRam00859fe0 & 0x800000) == 0x800000)) {
    uRam00859fe0 = uRam00859fe0 & 0xff0fffff;
    FUN_001497c0(0x95);
    uVar1 = uRam00859fe0;
    if (bRam00859ffa + 5 < 0x100) {
      bRam00859ffa = (byte)(bRam00859ffa + 5);
    }
    else {
      bRam00859ffa = 0xff;
    }
  }
  uRam00859fe0 = uVar1;
  uRam00835050 = uRam00835050 & 0xffbfffdf;
  return;
}

