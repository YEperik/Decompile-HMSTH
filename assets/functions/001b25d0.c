
void FUN_001b25d0(void)

{
  bool bVar1;
  ulong uVar2;
  uint uVar3;
  float fVar4;
  undefined4 uStack_14;
  
  if ((uRam00859fc0 & 1) == 1) {
    if ((bRam002678c8 & 1) == 1) {
      cRam00859fc9 = '\x01';
    }
    else {
      cRam00859fc9 = '\0';
    }
    do {
      bVar1 = false;
      uVar2 = FUN_00148df0(0x100,0xa00);
      if ((long)uVar2 < 0) {
        fVar4 = (float)(uVar2 & 0xffffffff);
      }
      else {
        fVar4 = (float)(int)uVar2;
      }
      uVar2 = FUN_00148df0(0,0x900);
      if ((long)uVar2 < 0) {
        fRam00859fd8 = (float)(uVar2 & 0xffffffff);
      }
      else {
        fRam00859fd8 = (float)(int)uVar2;
      }
      fRam00859fd8 = fRam00859fd8 - 768.0;
      if ((((((uRam00859fe0 & 1) == 1) && (cRam0085a004 == cRam00859fc9)) &&
           (fRam0085a010 - 128.0 < fVar4)) &&
          ((fVar4 < fRam0085a010 + 128.0 && (fRam0085a018 - 128.0 < fRam00859fd8)))) &&
         (fRam00859fd8 < fRam0085a018 + 128.0)) {
        bVar1 = true;
      }
      for (uVar3 = 0; uVar3 < 6; uVar3 = uVar3 + 1 & 0xff) {
        if ((((*(uint *)(uVar3 * 0x20 + 0x859e60) & 1) == 1) &&
            (cRam00859fc9 == *(char *)(uVar3 * 0x20 + 0x859e69))) &&
           ((*(float *)(uVar3 * 0x20 + 0x859e70) - 128.0 < fVar4 &&
            (((fVar4 < *(float *)(uVar3 * 0x20 + 0x859e70) + 128.0 &&
              (*(float *)(uVar3 * 0x20 + 0x859e78) - 128.0 < fRam00859fd8)) &&
             (fRam00859fd8 < *(float *)(uVar3 * 0x20 + 0x859e78) + 128.0)))))) {
          bVar1 = true;
        }
      }
      for (uVar3 = 0; uVar3 < 6; uVar3 = uVar3 + 1 & 0xff) {
        if (((((*(uint *)(uVar3 * 0x20 + 0x859f20) & 1) == 1) &&
             (cRam00859fc9 == *(char *)(uVar3 * 0x20 + 0x859f29))) &&
            ((*(float *)(uVar3 * 0x20 + 0x859f30) - 128.0 < fVar4 &&
             ((fVar4 < *(float *)(uVar3 * 0x20 + 0x859f30) + 128.0 &&
              (*(float *)(uVar3 * 0x20 + 0x859f38) - 128.0 < fRam00859fd8)))))) &&
           (fRam00859fd8 < *(float *)(uVar3 * 0x20 + 0x859f38) + 128.0)) {
          bVar1 = true;
        }
      }
      uRam00859fd4 = 0;
      uRam00859fdc = uStack_14;
      fRam00859fd0 = fVar4;
    } while (bVar1);
  }
  return;
}

