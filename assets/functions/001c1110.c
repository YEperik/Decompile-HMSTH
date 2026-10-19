
undefined4 FUN_001c1110(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((uRam00859fe0 & 1) == 1) {
    if ((((uRam00859fe0 & 0x20000000) != 0x20000000) && ((uRam00835050 & 0x20) != 0x20)) &&
       ((uRam00835050 & 0x400000) != 0x400000)) {
      uVar1 = 1;
    }
  }
  else if ((uRam00859fe0 & 0x80000) == 0x80000) {
    if ((uRam00859fe0 & 0x800) == 0x800) {
      if (0x1e < bRam00267828) {
        uVar1 = 1;
      }
    }
    else if (0x1e < bRam0026782c) {
      uVar1 = 1;
    }
  }
  return uVar1;
}

