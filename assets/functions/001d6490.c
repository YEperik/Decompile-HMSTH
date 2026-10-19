
void FUN_001d6490(void)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  uStack_1c = 0;
  fStack_18 = 0.0;
  uStack_30 = *(undefined4 *)(iRam002679e8 + 0x150);
  uStack_28 = *(undefined4 *)(iRam002679e8 + 0x158);
  uStack_24 = *(undefined4 *)(iRam002679e8 + 0x15c);
  cVar1 = *(char *)(iRam002679e8 + 0x12);
  cVar2 = *(char *)(iRam002679e8 + 0x10);
  cVar3 = *(char *)(iRam002679e8 + 0x13);
  cVar4 = *(char *)(iRam002679e8 + 0x11);
  *(undefined4 *)(iRam002679e8 + 0x20) = *(undefined4 *)(iRam002679e8 + 0x1c);
  uStack_2c = *(undefined4 *)(iRam002679e8 + 0xfc);
  fStack_18 = (float)FUN_001136a0(*(float *)(iRam002679e8 + 0xa0) - *(float *)(iRam002679e8 + 0x150)
                                  ,*(float *)(iRam002679e8 + 0xa8) -
                                   *(float *)(iRam002679e8 + 0x158));
  fStack_18 = fStack_18 - *(float *)(iRam002679e8 + 0xf0);
  *(float *)(iRam002679e8 + 0x1c) = (fStack_18 * 180.0) / 3.14;
  fStack_14 = (float)FUN_001d87a0(*(float *)(iRam002679e8 + 0x1a0) +
                                  *(float *)(iRam002679e8 + 0x1a4));
  FUN_001d7d20(-fStack_14,fStack_14,iRam002679e8 + 0x1c);
  FUN_001d6f70(0,-*(float *)(iRam002679e8 + 0x1c),0,iRam002679e8 + 0xa0);
  FUN_001d54d0(iRam002679e8 + 0x80,&uStack_30,iRam002679e8 + 0xa0);
  FUN_00128b50(&fStack_10,iRam002679e8 + 0x150,iRam002679e8 + 0xa0);
  if (fStack_10 < *(float *)(iRam002679e8 + 0x1a0) + *(float *)(iRam002679e8 + 0x1a4)) {
    fStack_c = (*(float *)(iRam002679e8 + 0x1a0) + *(float *)(iRam002679e8 + 0x1a4)) - fStack_10;
    *(float *)(iRam002679e8 + 0x1a4) = fStack_c;
  }
  else {
    *(undefined4 *)(iRam002679e8 + 0x1a4) = 0;
  }
  *(float *)(iRam002679e8 + 0x1a0) = fStack_10;
  fStack_8 = (float)(int)(char)(cVar1 - cVar2) / 4.0;
  fStack_4 = (float)(int)(char)(cVar3 - cVar4) / -4.0;
  *(float *)(iRam002679e8 + 0x30) = *(float *)(iRam002679e8 + 0x30) + fStack_4;
  *(float *)(iRam002679e8 + 0x2c) = *(float *)(iRam002679e8 + 0x2c) + fStack_8;
  FUN_001d7d20(0xc2000000,0x42000000,iRam002679e8 + 0x30);
  FUN_001d7d20(0xc2000000,0x42000000,iRam002679e8 + 0x2c);
  uStack_1c = *(undefined4 *)(iRam002679e8 + 0x30);
  fStack_18 = *(float *)(iRam002679e8 + 0x2c);
  FUN_00120d30(0,0,0,0,sRam0083405a + 4);
  FUN_00121840(0,0x3f800000,0,fStack_18,sRam0083405a + 4);
  FUN_00121840(0x3f800000,0,0,uStack_1c,sRam0083405a + 4);
  FUN_001d6f70(uStack_1c,-fStack_18,0,iRam002679e8 + 0x70);
  *(undefined1 *)(iRam002679e8 + 0x1b9) = 1;
  return;
}

