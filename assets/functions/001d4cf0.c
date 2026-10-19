
void FUN_001d4cf0(void)

{
  char cVar1;
  ulong uVar2;
  long lVar3;
  float fVar4;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_8;
  float fStack_4;
  
  *(short *)(iGpffff8af8 + 0x180) = *(short *)(iGpffff8af8 + 0x180) + -1;
  uVar2 = FUN_00148df0(4,0xc);
  if ((long)uVar2 < 0) {
    fStack_8 = (float)(uVar2 & 0xffffffff);
  }
  else {
    fStack_8 = (float)(int)uVar2;
  }
  fStack_8 = fStack_8 / 100.0;
  *(float *)(iGpffff8af8 + 0x100) = *(float *)(iGpffff8af8 + 0x100) + fStack_8;
  FUN_001dff50(iGpffff8af8 + 0x100);
  fVar4 = (float)FUN_00112f70(*(undefined4 *)(iGpffff8af8 + 0x100));
  fStack_2c = (*(float *)(iGpffff8af8 + 0xfc) + *(float *)(iGpffff8af8 + 0x104) * fVar4) -
              *(float *)(iGpffff8af8 + 0x154);
  if ((*(char *)(iGpffff8af8 + 0x17f) == '\x02') &&
     (FUN_00128b50(&fStack_4,iGpffff8af8 + 0x150,iGpffff8af8 + 0x90),
     fStack_4 < *(float *)(iGpffff8af8 + 0x170))) {
    *(undefined1 *)(iGpffff8af8 + 0x1b3) = 1;
    *(undefined2 *)(iGpffff8af8 + 0x180) = 0xffff;
  }
  if (*(short *)(iGpffff8af8 + 0x180) < 0) {
    switch(*(undefined1 *)(iGpffff8af8 + 0x17f)) {
    case 1:
      *(char *)(iGpffff8af8 + 0x17e) = *(char *)(iGpffff8af8 + 0x17e) + '\x02';
    case 0:
    case 3:
      FUN_00128b50(&fStack_4,iGpffff8af8 + 0x150,iGpffff8af8 + 0x90);
      if (('\a' < *(char *)(iGpffff8af8 + 0x17e)) ||
         (*(float *)(iGpffff8af8 + 0x1a0) + *(float *)(iGpffff8af8 + 0x1a4) <= 420.0)) {
        *(undefined1 *)(iGpffff8af8 + 0x17f) = 0;
      }
      else {
        *(undefined1 *)(iGpffff8af8 + 0x17f) = 1;
      }
      break;
    case 4:
      *(undefined1 *)(iGpffff8af8 + 0x17f) = 5;
      break;
    case 5:
      if ((*(char *)(iGpffff8af8 + 0x18a) < '\x01') ||
         (lVar3 = FUN_00148df0(0,0x30 / (int)*(char *)(iGpffff8af8 + 0x18a)), lVar3 != 0)) {
        *(undefined1 *)(iGpffff8af8 + 0x17f) = 5;
      }
      else {
        *(char *)(iGpffff8af8 + 0x18a) = *(char *)(iGpffff8af8 + 0x18a) + -1;
        *(undefined1 *)(iGpffff8af8 + 0x17f) = 6;
      }
      break;
    case 6:
      if (*(char *)(iGpffff8af8 + 0x17f) == '\x06') {
        *(float *)(iGpffff8af8 + 0x18c) = *(float *)(iGpffff8af8 + 0x18c) - 64.0;
        if (*(float *)(iGpffff8af8 + 0x18c) < 0.0) {
          *(undefined4 *)(iGpffff8af8 + 0x18c) = 0;
        }
        *(undefined1 *)(iGpffff8af8 + 0x17f) = 5;
      }
      break;
    case 7:
      return;
    }
    FUN_001d40e0();
  }
  cVar1 = *(char *)(iGpffff8af8 + 0x17f);
  if (cVar1 != '\x05') {
    if (cVar1 == '\a') {
      FUN_001d54d0(iGpffff8af8 + 0x160,iGpffff8af8 + 0xa0,iGpffff8af8 + 0x150);
      *(float *)(iGpffff8af8 + 0x160) = -*(float *)(iGpffff8af8 + 0x160);
      *(float *)(iGpffff8af8 + 0x168) = -*(float *)(iGpffff8af8 + 0x168);
    }
    else if ((cVar1 == '\x02') || (cVar1 == '\x01')) {
      FUN_001d54d0(iGpffff8af8 + 0x160,iGpffff8af8 + 0x90,iGpffff8af8 + 0x150);
    }
  }
  fStack_30 = *(float *)(iGpffff8af8 + 0x160) * *(float *)(iGpffff8af8 + 0x170);
  fStack_28 = *(float *)(iGpffff8af8 + 0x168) * *(float *)(iGpffff8af8 + 0x170);
  uStack_20 = *(undefined4 *)(iGpffff8af8 + 0x150);
  uStack_1c = *(undefined4 *)(iGpffff8af8 + 0x154);
  uStack_18 = *(undefined4 *)(iGpffff8af8 + 0x158);
  uStack_14 = *(undefined4 *)(iGpffff8af8 + 0x15c);
  cVar1 = FUN_001d7700(0x41f00000,0x32e,iGpffff8af8 + 0x150,iGpffff8af8 + 0x150,&fStack_30,0);
  if ((*(char *)(iGpffff8af8 + 0x17f) == '\x05') || (*(char *)(iGpffff8af8 + 0x17f) == '\x06')) {
    FUN_00128b50(&fStack_4,iGpffff8af8 + 0x150,iGpffff8af8 + 0xa0);
    if (*(float *)(iGpffff8af8 + 0x1a0) + *(float *)(iGpffff8af8 + 0x1a4) < fStack_4) {
      *(undefined4 *)(iGpffff8af8 + 0x150) = uStack_20;
      *(undefined4 *)(iGpffff8af8 + 0x154) = uStack_1c;
      *(undefined4 *)(iGpffff8af8 + 0x158) = uStack_18;
      *(undefined4 *)(iGpffff8af8 + 0x15c) = uStack_14;
      cVar1 = '\0';
    }
    if (cVar1 == '\0') {
      FUN_001d4b40(*(undefined1 *)(iGpffff8af8 + 0x184),iGpffff8af8 + 0x160);
    }
  }
  if ((cVar1 == '\0') && (*(char *)(iGpffff8af8 + 0x17f) == '\0')) {
    FUN_001d53f0(iGpffff8af8 + 0x160);
  }
  cVar1 = *(char *)(iGpffff8af8 + 0x17f);
  if (cVar1 == '\x05') {
    if (*(char *)(iGpffff8af8 + 0x17c) < '\x03') {
      *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 0.985;
    }
    else if ((long)*(short *)(iGpffff8af8 + 0x180) <
             (long)((int)*(short *)(iGpffff8af8 + 0x182) >> 1)) {
      *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 1.02;
    }
    else {
      *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 0.99;
    }
  }
  else if ((cVar1 == '\x02') || (cVar1 == '\x06')) {
    *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 1.005;
  }
  else if (cVar1 == '\a') {
    *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 1.025;
  }
  else {
    *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) * 0.985;
  }
  return;
}

