
void FUN_001d3820(void)

{
  undefined1 uVar1;
  long lVar2;
  undefined8 uVar3;
  float fVar4;
  undefined4 uVar5;
  
  fVar4 = (float)FUN_001d8d50();
  *(undefined1 *)(iGpffff8af8 + 0x1b9) = 0;
  *(float *)(iGpffff8af8 + 0x194) = ((1024.0 - *(float *)(iGpffff8af8 + 0x18c)) * 2.0) / 1024.0;
  lVar2 = FUN_001d7470(*(undefined1 *)(iGpffff8af8 + 0x184));
  if (lVar2 == 0) {
    if (*(char *)(iGpffff8af8 + 0x185) == '\x01') {
      FUN_001d6ee0();
      uVar3 = FUN_001d8ec0();
      FUN_001d6a50(*(undefined1 *)(iGpffff8af8 + 0x184),uVar3);
      *(undefined1 *)(iGpffff8af8 + 0x18b) = 0;
    }
    *(undefined1 *)(iGpffff8af8 + 0x185) = 0;
    *(float *)(iGpffff8af8 + 400) = *(float *)(iGpffff8af8 + 400) - fVar4;
  }
  else {
    *(char *)(iGpffff8af8 + 0x18b) = *(char *)(iGpffff8af8 + 0x18b) + '\x01';
    if (*(char *)(iGpffff8af8 + 0x18b) != '\0') {
      *(undefined1 *)(iGpffff8af8 + 0x18b) = 0;
    }
    if (*(char *)(iGpffff8af8 + 0x185) == '\0') {
      *(undefined1 *)(iGpffff8af8 + 0x185) = 1;
      *(undefined1 *)(iGpffff8af8 + 0x18b) = 0;
      *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 0.8;
      FUN_001d6ee0();
      uVar3 = FUN_001d8ec0();
      FUN_001d6970(*(undefined1 *)(iGpffff8af8 + 0x184),uVar3);
      *(undefined1 *)(iGpffff8af8 + 0x1b9) = 2;
      if (*(char *)(iGpffff8af8 + 0x186) == '\0') {
        uVar5 = FUN_001d8e20();
        *(undefined4 *)(iGpffff8af8 + 0x18c) = uVar5;
        *(undefined1 *)(iGpffff8af8 + 0x186) = 1;
      }
    }
  }
  if (*(float *)(iGpffff8af8 + 400) < 0.0) {
    *(undefined1 *)(iGpffff8af8 + 0x10a) = 0;
  }
  if (((*(char *)(iGpffff8af8 + 0x185) != '\0') &&
      (-1 < (long)(ulong)*(byte *)(iGpffff8af8 + 0x18b))) || (fVar4 < 0.25)) {
    FUN_001d5ed0();
  }
  else {
    FUN_001d6490();
  }
  lVar2 = FUN_0012e170(0,0x40);
  if (lVar2 != 0) {
    *(undefined1 *)(iGpffff8af8 + 0x10b) = 1;
    *(undefined2 *)(iGpffff8af8 + 0x1ac) = 0;
    FUN_001d8f20(*(undefined1 *)(iGpffff8af8 + 0x10c),0x5a);
  }
  lVar2 = FUN_0012e120(0,0x40);
  if ((lVar2 == 0) && (*(char *)(iGpffff8af8 + 0x10b) != '\0')) {
    *(undefined1 *)(iGpffff8af8 + 0x10b) = 0;
    FUN_001d8f20(*(undefined1 *)(iGpffff8af8 + 0x10c),0x55);
  }
  if (((*(char *)(iGpffff8af8 + 0x185) != '\0') || (fVar4 < 0.25)) &&
     ((*(char *)(iGpffff8af8 + 0x10b) != '\0' &&
      (FUN_001d92f0(*(undefined4 *)(iGpffff8af8 + 0x194)), *(char *)(iGpffff8af8 + 0x17f) == '\x06')
      ))) {
    *(short *)(iGpffff8af8 + 0x1ac) =
         *(short *)(iGpffff8af8 + 0x1ac) + (short)*(char *)(iGpffff8af8 + 0x17c);
  }
  uVar1 = FUN_001d7670(0x41f00000,*(undefined4 *)(iGpffff8af8 + 0x1a0),0x32d,iGpffff8af8 + 0x90,
                       iGpffff8af8 + 0xa0,iGpffff8af8 + 0x80,0);
  *(undefined1 *)(iGpffff8af8 + 0x1ab) = uVar1;
  FUN_001d7c60();
  *(undefined4 *)(iGpffff8af8 + 0x150) = *(undefined4 *)(iGpffff8af8 + 0x90);
  *(undefined4 *)(iGpffff8af8 + 0x154) = *(undefined4 *)(iGpffff8af8 + 0x94);
  *(undefined4 *)(iGpffff8af8 + 0x158) = *(undefined4 *)(iGpffff8af8 + 0x98);
  FUN_00123f50(*(undefined4 *)(iGpffff8af8 + 0x150),*(undefined4 *)(iGpffff8af8 + 0x154),
               *(undefined4 *)(iGpffff8af8 + 0x158),0x32e);
  FUN_001d6b50();
  FUN_001d9000();
  return;
}

