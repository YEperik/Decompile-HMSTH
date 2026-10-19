
void FUN_001d2670(float param_1,float *param_2,float *param_3)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fStack_60;
  float fStack_5c;
  undefined4 uStack_58;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_30;
  float fStack_2c;
  float afStack_28 [4];
  float *pfStack_18;
  float *pfStack_10;
  float fStack_8;
  
  fStack_50 = *param_2;
  fVar4 = param_2[1];
  fStack_48 = param_2[2];
  fStack_40 = *param_3;
  fStack_38 = param_3[2];
  fStack_4c = 0.0;
  fStack_3c = 0.0;
  pfStack_18 = param_2;
  pfStack_10 = param_3;
  fStack_8 = param_1;
  FUN_00128b50(&fStack_30,&fStack_50,&fStack_40);
  uVar1 = FUN_001136a0(fStack_40 - fStack_50,fStack_38 - fStack_48);
  *(undefined4 *)(iRam002679e8 + 0x1bc) = uVar1;
  fStack_50 = 0.0;
  fStack_48 = 0.0;
  fStack_40 = fStack_30;
  fStack_3c = *(float *)(iRam002679e8 + 0x124);
  fStack_38 = 0.0;
  fStack_4c = fVar4;
  FUN_00128b50(&fStack_2c,&fStack_50,&fStack_40);
  fVar4 = fStack_50 + (fStack_40 - fStack_50) / 2.0;
  fVar2 = fStack_4c + (fStack_3c - fStack_4c) / 2.0;
  afStack_28[0] = (float)FUN_001136a0(fStack_4c - fStack_3c,fStack_50 - fStack_40);
  afStack_28[0] = afStack_28[0] + 1.57;
  FUN_001dff50(afStack_28);
  fVar3 = (float)FUN_00112f70(afStack_28[0]);
  fStack_60 = fVar4 + (fStack_2c / 3.0) * fVar3;
  fVar4 = (float)FUN_00112bf8(afStack_28[0]);
  fStack_5c = fVar2 + (fStack_2c / 3.0) * fVar4;
  uStack_58 = 0;
  FUN_00128b50(iRam002679e8 + 0x138,&fStack_60,&fStack_50);
  uVar1 = FUN_001136a0(fStack_4c - fStack_5c,fStack_50 - fStack_60);
  *(undefined4 *)(iRam002679e8 + 0x130) = uVar1;
  fVar4 = (float)FUN_001136a0(fStack_3c - fStack_5c,fStack_40 - fStack_60);
  *(float *)(iRam002679e8 + 0x134) = fStack_5c;
  *(float *)(iRam002679e8 + 0x13c) =
       ((fVar4 - *(float *)(iRam002679e8 + 0x130)) * 1024.0) / fStack_8;
  *(float *)(iRam002679e8 + 0x140) = fStack_30 / ((fStack_8 * fStack_8) / 2.0);
  *(float *)(iRam002679e8 + 0x130) = *(float *)(iRam002679e8 + 0x130) * 1024.0;
  *(undefined2 *)(iRam002679e8 + 2) = 0;
  return;
}

