
void FUN_001bfd60(void)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  
  if ((((((uRam00859fe0 & 1) == 1) && ((uRam00859fe0 & 0x100) != 0x100)) &&
       ((uRam00859fe0 & 2) != 2)) && (((uRam00835050 & 0x20) != 0x20 && (bGpffff8844 < 0xb)))) &&
     ((cGpffff8aa4 != '\n' && ((cGpffff8aa4 != '\v' && (bRam0085a004 == bGpffff8844)))))) {
    if (((bRam00859fe4 & 4) != 4) && ((bGpffff8aac & 4) != 4)) {
      bGpffff8aac = bGpffff8aac | 4;
      bVar2 = bRam00859ff6 + 1;
      bVar1 = bRam00859ff6 == 9;
      bRam00859ff6 = bVar2;
      if (bVar1) {
        bRam00859fe4 = bRam00859fe4 | 4;
      }
    }
    if (((bRam00859fe4 & 4) != 4) && (uVar3 = FUN_00148df0(0,99), (uint)bRam00859ff6 * 10 <= uVar3))
    {
      return;
    }
    uRam00835050 = uRam00835050 & 0xffbfffff;
    if ((uRam00859fe0 & 0x20000000) == 0x20000000) {
      uGpffff8898 = 3;
      uRam00859fe0 = uRam00859fe0 & 0xbffb7fff;
      FUN_001c9020();
    }
    else {
      uRam00859fe0 = uRam00859fe0 & 0xbffb7fff;
      FUN_001c99c0();
    }
  }
  return;
}

