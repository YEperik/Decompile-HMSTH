
void FUN_001beea0(void)

{
  char cVar1;
  
  cVar1 = FUN_00123d60(uRam00835158);
  switch(uRam00835156) {
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
    if ((uRam00835150 & 0x4000) == 0x4000) {
      FUN_0013e2a0(0x11);
    }
    if (cVar1 == '\0') {
      FUN_0013dff0(0x11,0x140,0,0x140);
      FUN_001c2c20();
    }
    break;
  default:
    if (((uRam00835150 & 0x20) != 0x20) && ((uRam00835150 & 0x400000) != 0x400000)) {
      FUN_001c2c20();
    }
    break;
  case 0x14:
    FUN_0013e2a0(0x11);
    if (cVar1 == '\0') {
      if ((bRam0085a2f5 < 0x14) && (5 < bRam0085a2f5)) {
        FUN_00139920(0x11,0x15);
        uRam00835198 = 0xf0;
        uGpffff8aa8 = 1;
      }
      else {
        uRam00859fc0 = uRam00859fc0 | 0x100;
        FUN_00139920(0x11,0x17);
        uGpffff8aa8 = 2;
      }
    }
  }
  return;
}

