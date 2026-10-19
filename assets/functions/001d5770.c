
void FUN_001d5770(void)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  fStack_20 = 0.0;
  fStack_1c = 0.0;
  fStack_18 = 0.0;
  bVar1 = *(byte *)(iRam002679e8 + 6);
  cVar2 = *(char *)(iRam002679e8 + 0x12) - *(char *)(iRam002679e8 + 0x10);
  cVar3 = *(char *)(iRam002679e8 + 0x13) - *(char *)(iRam002679e8 + 0x11);
  *(undefined4 *)(iRam002679e8 + 0x20) = *(undefined4 *)(iRam002679e8 + 0x1c);
  fStack_4 = (float)FUN_001d87a0(*(float *)(iRam002679e8 + 0x1a0) + *(float *)(iRam002679e8 + 0x1a4)
                                );
  if ((bVar1 & 0x30) != 0) {
    *(undefined4 *)(iRam002679e8 + 0x24) = 0;
    *(undefined1 *)(iRam002679e8 + 0x14) = *(undefined1 *)(iRam002679e8 + 0x16);
    *(undefined1 *)(iRam002679e8 + 0x1a) = 0;
    *(undefined1 *)(iRam002679e8 + 0x18) = 0;
    *(undefined1 *)(iRam002679e8 + 0x1b9) = 2;
  }
  if ((bVar1 & 0xc0) != 0) {
    *(undefined4 *)(iRam002679e8 + 0x28) = 0;
    *(undefined1 *)(iRam002679e8 + 0x15) = *(undefined1 *)(iRam002679e8 + 0x17);
    *(undefined1 *)(iRam002679e8 + 0x1b) = 0;
    *(undefined1 *)(iRam002679e8 + 0x19) = 0;
    *(undefined1 *)(iRam002679e8 + 0x1b9) = 2;
  }
  if (*(char *)(iRam002679e8 + 0x1a) < '\x10') {
    *(char *)(iRam002679e8 + 0x1a) = *(char *)(iRam002679e8 + 0x1a) + '\x01';
  }
  if ((*(char *)(iRam002679e8 + 0x14) == *(char *)(iRam002679e8 + 0x16)) &&
     (*(char *)(iRam002679e8 + 0x16) != '\0')) {
    *(float *)(iRam002679e8 + 0x24) = *(float *)(iRam002679e8 + 0x24) + (float)(int)cVar2;
  }
  else if (('\x0f' < *(char *)(iRam002679e8 + 0x1a)) && (*(char *)(iRam002679e8 + 0x18) == '\0')) {
    *(undefined1 *)(iRam002679e8 + 0x18) = 1;
    *(float *)(iRam002679e8 + 0x24) = (*(float *)(iRam002679e8 + 0x24) * 3.0) / 4.0;
  }
  if ('\x0f' < *(char *)(iRam002679e8 + 0x1a)) {
    fStack_14 = *(float *)(iRam002679e8 + 0x24) / 64.0;
    *(float *)(iRam002679e8 + 0x24) = *(float *)(iRam002679e8 + 0x24) - fStack_14;
    fStack_c = fStack_14 / 4.0;
    *(float *)(iRam002679e8 + 0x1c) = *(float *)(iRam002679e8 + 0x1c) + fStack_c;
  }
  FUN_001d7d20(-fStack_4,fStack_4,iRam002679e8 + 0x1c);
  if (*(char *)(iRam002679e8 + 0x1b) < '\x10') {
    *(char *)(iRam002679e8 + 0x1b) = *(char *)(iRam002679e8 + 0x1b) + '\x01';
  }
  if ((*(char *)(iRam002679e8 + 0x15) == *(char *)(iRam002679e8 + 0x17)) &&
     (*(char *)(iRam002679e8 + 0x17) != '\0')) {
    *(float *)(iRam002679e8 + 0x28) = *(float *)(iRam002679e8 + 0x28) + (float)(int)cVar3;
  }
  else if (('\x0f' < *(char *)(iRam002679e8 + 0x1b)) && (*(char *)(iRam002679e8 + 0x19) == '\0')) {
    *(undefined1 *)(iRam002679e8 + 0x19) = 1;
    *(undefined4 *)(iRam002679e8 + 0x28) = 0;
  }
  if ('\x0f' < *(char *)(iRam002679e8 + 0x1b)) {
    fStack_10 = *(float *)(iRam002679e8 + 0x28) / 64.0;
    *(float *)(iRam002679e8 + 0x28) = *(float *)(iRam002679e8 + 0x28) - fStack_10;
    fStack_8 = (float)FUN_001d6890(fStack_10);
  }
  if (((1.0 < fStack_8 * (float)(int)*(char *)(iRam002679e8 + 0x15)) ||
      (1.0 < fStack_c * (float)(int)*(char *)(iRam002679e8 + 0x14))) &&
     (*(char *)(iRam002679e8 + 0x1b9) == '\0')) {
    *(undefined1 *)(iRam002679e8 + 0x1b9) = 1;
  }
  fStack_1c = (float)(int)*(char *)(iRam002679e8 + 0x12) +
              ((float)((int)*(char *)(iRam002679e8 + 0x13) * (int)*(char *)(iRam002679e8 + 0x17)) /
              4.0) * ((float)((int)cVar2 * (int)*(char *)(iRam002679e8 + 0x16)) / 128.0 + 1.0);
  fStack_20 = (float)(int)*(char *)(iRam002679e8 + 0x13) +
              ((float)((int)*(char *)(iRam002679e8 + 0x12) * (int)*(char *)(iRam002679e8 + 0x16)) /
              4.0) * ((float)((int)cVar3 * (int)*(char *)(iRam002679e8 + 0x17)) / 128.0 + 1.0);
  FUN_001d7d20(0xc2fe0000,0x42fe0000,&fStack_1c);
  FUN_001d7d20(0xc2fe0000,0x42fe0000,&fStack_20);
  fStack_1c = fStack_1c / 4.0;
  fStack_20 = fStack_20 / -4.0;
  *(float *)(iRam002679e8 + 0x30) = fStack_20;
  *(float *)(iRam002679e8 + 0x2c) = fStack_1c;
  fStack_18 = -*(float *)(iRam002679e8 + 0x1c);
  FUN_00120d30(0,0,0,0,sRam0083405a + 4);
  FUN_00121840(0,0x3f800000,0,fStack_1c,sRam0083405a + 4);
  FUN_00121840(0x3f800000,0,0,fStack_20,sRam0083405a + 4);
  FUN_001d6f70(fStack_20,-fStack_1c,0,iRam002679e8 + 0x70);
  FUN_001d6f70(0,fStack_18,0,iRam002679e8 + 0xa0);
  return;
}

