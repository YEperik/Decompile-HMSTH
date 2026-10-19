
void FUN_001d7ff0(float param_1,float param_2,char param_3)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  float afStack_190 [4];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  float afStack_90 [16];
  short *apsStack_50 [4];
  undefined1 auStack_40 [16];
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  char cStack_18;
  float fStack_10;
  float fStack_8;
  
  cStack_18 = param_3;
  fStack_10 = param_1;
  fStack_8 = param_2;
  FUN_00126a90(auStack_40);
  FUN_00128b50(&fStack_2c,iGpffff8af8 + 0x90,auStack_40);
  fStack_30 = fStack_2c / 768.0;
  bVar1 = *(byte *)(iGpffff8af8 + 0x1b6);
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    fStack_28 = (float)(int)(char)(&gp0xffff8138)[sVar3 * 2];
    fStack_24 = (float)(int)(char)(&gp0xffff8139)[sVar3 * 2];
    apsStack_50[sVar3] = (short *)(&PTR_DAT_002448a0)[sVar3];
    if ((long)sVar3 == (long)cStack_18) {
      fStack_28 = fStack_28 + fStack_10;
      fStack_24 = fStack_24 + fStack_8;
      apsStack_50[sVar3] = apsStack_50[sVar3] + (short)((bVar1 / 0x2a) % 6) * 4;
    }
    afStack_90[sVar3 * 4] = fStack_28 * fStack_30;
    afStack_90[sVar3 * 4 + 1] = fStack_24 * fStack_30;
    afStack_90[sVar3 * 4 + 2] = 0.0;
    for (sVar2 = 0; sVar2 < 4; sVar2 = sVar2 + 1) {
      afStack_190[sVar3 * 0x10 + sVar2 * 4] =
           fStack_30 * (float)(int)(char)(&gp0xffff8140)[sVar2 * 2] + afStack_90[sVar3 * 4];
      afStack_190[sVar3 * 0x10 + sVar2 * 4 + 1] =
           fStack_30 * (float)(int)(char)(&gp0xffff8141)[sVar2 * 2] + afStack_90[sVar3 * 4 + 1];
      afStack_190[sVar3 * 0x10 + sVar2 * 4 + 2] = 0.0;
    }
  }
  FUN_001de5d0((float)(int)*apsStack_50[0] / 256.0,(float)(int)apsStack_50[0][1] / 256.0,
               (float)(int)apsStack_50[0][2] / 256.0,(float)(int)apsStack_50[0][3] / 256.0,0x10f,
               0xcf,0xd5d,0x32f,afStack_190,auStack_180,auStack_170,auStack_160);
  FUN_001de5d0((float)(int)*apsStack_50[1] / 256.0,(float)(int)apsStack_50[1][1] / 256.0,
               (float)(int)apsStack_50[1][2] / 256.0,(float)(int)apsStack_50[1][3] / 256.0,0x110,
               0xcf,0xd5e,0x330,auStack_150,auStack_140,auStack_130,auStack_120);
  FUN_001de5d0((float)(int)*apsStack_50[2] / 256.0,(float)(int)apsStack_50[2][1] / 256.0,
               (float)(int)apsStack_50[2][2] / 256.0,(float)(int)apsStack_50[2][3] / 256.0,0x111,
               0xcf,0xd5f,0x331,auStack_110,auStack_100,auStack_f0,auStack_e0);
  FUN_001de5d0((float)(int)*apsStack_50[3] / 256.0,(float)(int)apsStack_50[3][1] / 256.0,
               (float)(int)apsStack_50[3][2] / 256.0,(float)(int)apsStack_50[3][3] / 256.0,0x112,
               0xcf,0xd60,0x332,auStack_d0,auStack_c0,auStack_b0,auStack_a0);
  FUN_001de310(0x10f,3);
  FUN_001de310(0x111,3);
  FUN_00123780(0x32f,0x40);
  FUN_00123780(0x330,0x40);
  FUN_00123780(0x331,0x40);
  FUN_00123780(0x332,0x40);
  FUN_0015bf20(0x10f);
  FUN_0015bf20(0x111);
  FUN_0015bf20(0x110);
  FUN_0015bf20(0x112);
  return;
}

