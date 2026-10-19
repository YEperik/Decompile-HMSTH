
ushort FUN_001d2fc0(byte *param_1)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  ushort uVar4;
  byte *pbStack_8;
  
  uVar1 = FUN_00148df0(0,0x7f);
  uVar3 = 0;
  if (((((((bGpffff896c & 4) == 4) || (cGpffff8954 != '\\')) || (cGpffff8944 != '\0')) ||
       (0x17 < bRam0085a2f5)) ||
      (((((cRam0085a2f7 != '\0' && (cRam0085a2f7 != '\x02')) || (bRam0085a2f5 < 0x12)) &&
        ((cRam0085a2f7 != '\x01' || (bRam0085a2f5 < 0x13)))) &&
       ((cRam0085a2f7 != '\x03' || (bRam0085a2f5 < 0x11)))))) ||
     ((bRam0085a2f9 == 0 ||
      (lVar2 = FUN_00148df0(0,(5 - (uint)bRam0085a2f9) * (0x29 - *(short *)(iGpffff8af8 + 0x112))),
      lVar2 != 0)))) {
    pbStack_8 = param_1;
    for (uVar4 = 0; (short)uVar4 < 9; uVar4 = uVar4 + 1) {
      if (((*pbStack_8 != 0) && (uVar3 <= (uVar1 & 0xff))) && ((uVar1 & 0xff) < uVar3 + *pbStack_8))
      {
        return uVar4 & 0xff;
      }
      uVar3 = uVar3 + *pbStack_8 & 0xff;
      pbStack_8 = pbStack_8 + 1;
    }
    uVar4 = 0;
  }
  else {
    uVar4 = 8;
  }
  return uVar4;
}

