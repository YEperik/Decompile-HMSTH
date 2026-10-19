
undefined1 FUN_001d23a0(float param_1)

{
  undefined1 uVar1;
  long lVar2;
  float fVar3;
  undefined4 uVar4;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_18;
  float fStack_14;
  float fStack_8;
  
  uVar1 = *(float *)(iRam002679e8 + 0x144) < param_1;
  fStack_8 = param_1;
  if ((bool)uVar1) {
    fStack_30 = *(float *)(iRam002679e8 + 0x120);
    fStack_2c = *(float *)(iRam002679e8 + 0x124);
    fStack_28 = *(float *)(iRam002679e8 + 0x128);
    FUN_001244b0(uRam00834058,iRam002679e8 + 0x80);
  }
  else {
    fStack_18 = (*(float *)(iRam002679e8 + 0x140) * param_1 * param_1) / 2.0;
    *(float *)(iRam002679e8 + 0x130) =
         *(float *)(iRam002679e8 + 0x130) + *(float *)(iRam002679e8 + 0x13c);
    fStack_14 = *(float *)(iRam002679e8 + 0x130) / 1024.0;
    fVar3 = (float)FUN_00112f70(fStack_14);
    fStack_2c = *(float *)(iRam002679e8 + 0x134) + *(float *)(iRam002679e8 + 0x138) * fVar3;
    fVar3 = (float)FUN_00112f70(*(undefined4 *)(iRam002679e8 + 0xf0));
    fStack_30 = *(float *)(iRam002679e8 + 0x70) - fStack_18 * fVar3;
    fVar3 = (float)FUN_00112bf8(*(undefined4 *)(iRam002679e8 + 0xf0));
    fStack_28 = *(float *)(iRam002679e8 + 0x78) - fStack_18 * fVar3;
    uVar4 = FUN_00112f70(fStack_14);
    *(undefined4 *)(iRam002679e8 + 0x84) = uVar4;
  }
  fStack_40 = fStack_30 - *(float *)(iRam002679e8 + 0x90);
  fStack_3c = fStack_2c - *(float *)(iRam002679e8 + 0x94);
  fStack_38 = fStack_28 - *(float *)(iRam002679e8 + 0x98);
  lVar2 = FUN_001d7700(0x41f00000,0x32d,iRam002679e8 + 0x90,iRam002679e8 + 0x90,&fStack_40,2);
  if (lVar2 == 0) {
    uVar1 = 2;
  }
  else {
    if ((*(float *)(iRam002679e8 + 0x94) <= *(float *)(iRam002679e8 + 100)) &&
       (*(char *)(iRam002679e8 + 0x189) == '\0')) {
      *(undefined1 *)(iRam002679e8 + 0x189) = 1;
      if (*(short *)(iRam002679e8 + 0x112) < 0x24) {
        FUN_001ff4f0(*(undefined4 *)(iRam002679e8 + 0x90),*(undefined4 *)(iRam002679e8 + 100),
                     *(undefined4 *)(iRam002679e8 + 0x98),10);
      }
      else {
        FUN_001ff4f0(*(undefined4 *)(iRam002679e8 + 0x90),*(undefined4 *)(iRam002679e8 + 100),
                     *(undefined4 *)(iRam002679e8 + 0x98),0xb);
      }
    }
    FUN_00137b90(0x68,iRam002679e8 + 0x80);
  }
  return uVar1;
}

