
void FUN_001bfa20(void)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (((((uRam00859fe0 & 1) == 1) && ((uRam00859fe0 & 0x100) != 0x100)) && ((uRam00859fe0 & 2) != 2)
      ) && ((((uRam00835050 & 0x20) != 0x20 && (cGpffff8aa4 != '\n')) &&
            ((cGpffff8aa4 != '\v' && (cRam0085a004 == cGpffff8844)))))) {
    if (((bRam00859fe4 & 2) != 2) && ((bGpffff8aac & 2) != 2)) {
      bGpffff8aac = bGpffff8aac | 2;
      bVar3 = bRam00859ff5 + 1;
      bVar1 = bRam00859ff5 == 9;
      bRam00859ff5 = bVar3;
      if (bVar1) {
        bRam00859fe4 = bRam00859fe4 | 2;
      }
    }
    if ((((bRam00859fe4 & 2) == 2) || (uVar2 = FUN_00148df0(0,99), uVar2 < (uint)bRam00859ff5 * 10))
       && ((uRam00859fe0 & 0x20000000) != 0x20000000)) {
      if ((uRam00859fe0 & 0x4000) == 0x4000) {
        FUN_00124180(uRam00834058,&uStack_10);
        uRam0085a010 = uStack_10;
        uRam0085a014 = uStack_c;
        uRam0085a018 = uStack_8;
        uRam0085a01c = uStack_4;
      }
      uRam00835050 = uRam00835050 & 0xffbfffff;
      uRam00859fe0 = uRam00859fe0 & 0xaffa3fff;
      FUN_0013e2a0(0x10);
      if (((uRam00859fe0 & 0x20000) != 0x20000) || (cRam00835056 == '\x1c')) {
        FUN_00139920(0x10,0x1a);
      }
      if (cRam00859ffd != -1) {
        cRam00859ffd = cRam00859ffd + '\x01';
      }
    }
  }
  return;
}

