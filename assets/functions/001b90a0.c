
void FUN_001b90a0(void)

{
  ulong uVar1;
  
  if ((((((uRam00859fe0 & 1) == 1) && (0x1e < bRam00859ffa)) && ((uRam00859fe0 & 0x100) != 0x100))
      && (((uRam00859fe0 & 2) != 2 && ((uRam00835050 & 0x20) != 0x20)))) &&
     (cRam0085a004 == cRam00267734)) {
    if ((bRam00859ffa < 0x1f) || (0x50 < bRam00859ffa)) {
      if ((0x50 < bRam00859ffa) &&
         ((bRam00859ffa < 0x8d && (uVar1 = FUN_00148df0(0,99), uVar1 < 0x19)))) {
        return;
      }
    }
    else {
      uVar1 = FUN_00148df0(0,99);
      if (uVar1 < 0x32) {
        return;
      }
    }
    if ((uRam00859fe0 & 0x20000000) == 0x20000000) {
      uRam00267788 = 1;
      FUN_001c9020(1);
    }
    else {
      FUN_001c9e00();
    }
  }
  return;
}

