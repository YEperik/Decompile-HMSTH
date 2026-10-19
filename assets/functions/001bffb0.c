
void FUN_001bffb0(void)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if ((((((uRam00859fe0 & 1) == 1) && ((uRam00859fe0 & 0x100) != 0x100)) &&
       ((uRam00859fe0 & 2) != 2)) && (((uRam00835050 & 0x20) != 0x20 && (cGpffff8aa4 != '\n')))) &&
     ((cGpffff8aa4 != '\v' && (cRam0085a004 == cGpffff8844)))) {
    if (((bRam00859fe4 & 8) != 8) && ((bGpffff8aac & 8) != 8)) {
      bGpffff8aac = bGpffff8aac | 8;
      bVar2 = bRam00859ff7 + 1;
      bVar1 = bRam00859ff7 == 9;
      bRam00859ff7 = bVar2;
      if (bVar1) {
        bRam00859fe4 = bRam00859fe4 | 8;
      }
    }
    if (((bRam00859fe4 & 8) == 8) || (uVar3 = FUN_00148df0(0,99), uVar3 < (uint)bRam00859ff7 * 10))
    {
      if ((uRam00859fe0 & 0x4000) == 0x4000) {
        FUN_00124180(uRam00834058,&uStack_10);
        uRam0085a010 = uStack_10;
        uRam0085a014 = uStack_c;
        uRam0085a018 = uStack_8;
        uRam0085a01c = uStack_4;
      }
      uRam00835050 = uRam00835050 & 0xffbfffff;
      if ((uRam00859fe0 & 0x20000000) == 0x20000000) {
        uGpffff8898 = 4;
        uRam00859fe0 = uRam00859fe0 & 0xbffb3fff;
        FUN_001c9020();
      }
      else {
        uRam00859fe0 = uRam00859fe0 & 0xbffb3fff;
        FUN_001c9bf0();
      }
    }
  }
  return;
}

