
void FUN_001b6240(void)

{
  short sVar1;
  
  if ((bRam002678c8 & 1) == 1) {
    if ((cRam0085a2f6 == '\x01') && (bRam0085a2f5 < 6)) {
      sVar1 = *(short *)(&DAT_00267018 + (bRam0085a2f7 - 1) * 2);
    }
    else {
      sVar1 = *(short *)(&DAT_00267018 + (uint)bRam0085a2f7 * 2);
    }
  }
  else if ((cRam0085a2f6 == '\x01') && (bRam0085a2f5 < 6)) {
    sVar1 = *(short *)(&DAT_00267010 + (bRam0085a2f7 - 1) * 2);
  }
  else {
    sVar1 = *(short *)(&DAT_00267010 + (uint)bRam0085a2f7 * 2);
  }
  FUN_00123950(sVar1 + 1,1);
  return;
}

