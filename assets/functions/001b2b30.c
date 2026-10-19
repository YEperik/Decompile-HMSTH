
void FUN_001b2b30(byte param_1)

{
  bool bVar1;
  ulong uVar2;
  int iVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  undefined4 uStack_24;
  
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 1) == 1) {
    if ((bGpffff89d8 & 1) == 1) {
      *(undefined1 *)((uint)param_1 * 0x20 + 0x859f29) = 1;
    }
    else {
      *(undefined1 *)((uint)param_1 * 0x20 + 0x859f29) = 0;
    }
    do {
      bVar1 = false;
      uVar2 = FUN_00148df0(0x100,0xa00);
      if ((long)uVar2 < 0) {
        fVar5 = (float)(uVar2 & 0xffffffff);
      }
      else {
        fVar5 = (float)(int)uVar2;
      }
      uVar2 = FUN_00148df0(0,0x900);
      if ((long)uVar2 < 0) {
        fVar6 = (float)(uVar2 & 0xffffffff);
      }
      else {
        fVar6 = (float)(int)uVar2;
      }
      fVar6 = fVar6 - 768.0;
      if (((((uRam00859fe0 & 1) == 1) &&
           (cRam0085a004 == *(char *)((uint)param_1 * 0x20 + 0x859f29))) &&
          (fRam0085a010 - 128.0 < fVar5)) &&
         (((fVar5 < fRam0085a010 + 128.0 && (fRam0085a018 - 128.0 < fVar6)) &&
          (fVar6 < fRam0085a018 + 128.0)))) {
        bVar1 = true;
      }
      if ((((uRam00859fc0 & 1) == 1) && (cRam00859fc9 == *(char *)((uint)param_1 * 0x20 + 0x859f29))
          ) && ((fRam00859fd0 - 128.0 < fVar5 &&
                (((fVar5 < fRam00859fd0 + 128.0 && (fRam00859fd8 - 128.0 < fVar6)) &&
                 (fVar6 < fRam00859fd8 + 128.0)))))) {
        bVar1 = true;
      }
      for (uVar4 = 0; uVar4 < 6; uVar4 = uVar4 + 1 & 0xff) {
        if ((((*(uint *)(uVar4 * 0x20 + 0x859e60) & 1) == 1) &&
            (*(char *)(uVar4 * 0x20 + 0x859e69) == *(char *)((uint)param_1 * 0x20 + 0x859f29))) &&
           (((*(float *)(uVar4 * 0x20 + 0x859e70) - 128.0 < fVar5 &&
             ((fVar5 < *(float *)(uVar4 * 0x20 + 0x859e70) + 128.0 &&
              (*(float *)(uVar4 * 0x20 + 0x859e78) - 128.0 < fVar6)))) &&
            (fVar6 < *(float *)(uVar4 * 0x20 + 0x859e78) + 128.0)))) {
          bVar1 = true;
        }
      }
      for (uVar4 = 0; uVar4 < 6; uVar4 = uVar4 + 1 & 0xff) {
        if (((((uVar4 != param_1) && ((*(uint *)(uVar4 * 0x20 + 0x859f20) & 1) == 1)) &&
             (*(char *)(uVar4 * 0x20 + 0x859f29) == *(char *)((uint)param_1 * 0x20 + 0x859f29))) &&
            ((*(float *)(uVar4 * 0x20 + 0x859f30) - 128.0 < fVar5 &&
             (fVar5 < *(float *)(uVar4 * 0x20 + 0x859f30) + 128.0)))) &&
           ((*(float *)(uVar4 * 0x20 + 0x859f38) - 128.0 < fVar6 &&
            (fVar6 < *(float *)(uVar4 * 0x20 + 0x859f38) + 128.0)))) {
          bVar1 = true;
        }
      }
      iVar3 = (uint)param_1 * 0x20;
      *(float *)(iVar3 + 0x859f30) = fVar5;
      *(undefined4 *)(iVar3 + 0x859f34) = 0;
      *(float *)(iVar3 + 0x859f38) = fVar6;
      *(undefined4 *)(iVar3 + 0x859f3c) = uStack_24;
    } while (bVar1);
  }
  return;
}

