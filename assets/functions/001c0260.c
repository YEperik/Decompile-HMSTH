
void FUN_001c0260(void)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (((((uRam00859fe0 & 1) == 1) && ((uRam00859fe0 & 0x100) != 0x100)) && ((uRam00859fe0 & 2) != 2)
      ) && ((((uRam00835050 & 0x20) != 0x20 && (cRam00267994 != '\n')) &&
            ((cRam00267994 != '\v' && (cRam0085a004 == cRam00267734)))))) {
    if (((bRam00859fe4 & 0x10) != 0x10) && ((bRam0026799c & 0x10) != 0x10)) {
      bRam0026799c = bRam0026799c | 0x10;
      bVar3 = bRam00859ff8 + 1;
      bVar1 = bRam00859ff8 == 9;
      bRam00859ff8 = bVar3;
      if (bVar1) {
        bRam00859fe4 = bRam00859fe4 | 0x10;
      }
    }
    if ((((bRam00859fe4 & 0x10) == 0x10) ||
        (uVar2 = FUN_00148df0(0,99), uVar2 < (uint)bRam00859ff8 * 10)) &&
       ((uRam00859fe0 & 0x20000000) != 0x20000000)) {
      if ((uRam00859fe0 & 0x4000) == 0x4000) {
        FUN_00124180(uRam00834058,&uStack_10);
        uRam0085a010 = uStack_10;
        uRam0085a014 = uStack_c;
        uRam0085a018 = uStack_8;
        uRam0085a01c = uStack_4;
      }
      uRam00859fe0 = uRam00859fe0 & 0xaffb3fff;
      uRam00835050 = uRam00835050 & 0xffbfffff;
      FUN_0013e2a0(0x10);
      FUN_00139920(0x10,5);
      FUN_0013b110(0x41800000,0x41800000,0x3f99999a,0,0x10,6);
      uRam00835050 = uRam00835050 & 0xffffffef | 0x28;
      cRam00267994 = '\0';
      uRam00859fe0 = uRam00859fe0 & 0xfffc7fff;
      if (cRam00859ffd != -1) {
        cRam00859ffd = cRam00859ffd + '\x01';
      }
    }
  }
  return;
}

