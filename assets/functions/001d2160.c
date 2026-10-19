
void FUN_001d2160(void)

{
  int iVar1;
  ulong uVar2;
  float fVar3;
  float fStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 auStack_20 [2];
  undefined4 uStack_18;
  float fStack_8;
  float fStack_4;
  
  fStack_4 = (float)(*(short *)(iRam002679e8 + 0x112) + -0x13);
  fStack_8 = fStack_4 * 60.0 + 420.0;
  uVar2 = FUN_00148df0(0,0x80);
  if ((long)uVar2 < 0) {
    fVar3 = (float)(uVar2 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)uVar2;
  }
  fStack_8 = fStack_8 + fVar3;
  FUN_001d5560(&fStack_30);
  *(float *)(iRam002679e8 + 0xfc) = *(float *)(iRam002679e8 + 100) - 30.0;
  fVar3 = (float)FUN_00112f70(*(undefined4 *)(iRam002679e8 + 0xf0));
  *(float *)(iRam002679e8 + 0x120) = fStack_30 - fStack_8 * fVar3;
  fVar3 = (float)FUN_00112bf8(*(undefined4 *)(iRam002679e8 + 0xf0));
  *(float *)(iRam002679e8 + 0x128) = fStack_28 - fStack_8 * fVar3;
  *(undefined4 *)(iRam002679e8 + 0x124) = *(undefined4 *)(iRam002679e8 + 0xfc);
  iVar1 = iRam002679e8;
  *(float *)(iRam002679e8 + 0x70) = fStack_30;
  *(undefined4 *)(iVar1 + 0x74) = uStack_2c;
  *(float *)(iVar1 + 0x78) = fStack_28;
  *(undefined4 *)(iVar1 + 0x7c) = uStack_24;
  iVar1 = iRam002679e8;
  *(float *)(iRam002679e8 + 0x90) = fStack_30;
  *(undefined4 *)(iVar1 + 0x94) = uStack_2c;
  *(float *)(iVar1 + 0x98) = fStack_28;
  *(undefined4 *)(iVar1 + 0x9c) = uStack_24;
  *(undefined1 *)(iRam002679e8 + 0x189) = 0;
  FUN_001244b0(uRam00834058,auStack_20);
  *(undefined4 *)(iRam002679e8 + 0x80) = auStack_20[0];
  *(undefined4 *)(iRam002679e8 + 0x88) = uStack_18;
  FUN_00137ae0(*(undefined4 *)(iRam002679e8 + 0x90),*(undefined4 *)(iRam002679e8 + 0x94),
               *(undefined4 *)(iRam002679e8 + 0x98),0x68);
  FUN_001234c0();
  *(float *)(iRam002679e8 + 0x144) = (fStack_4 + 4.0) * 1.8;
  FUN_001d2670(*(undefined4 *)(iRam002679e8 + 0x144),&fStack_30,iRam002679e8 + 0x120);
  return;
}

