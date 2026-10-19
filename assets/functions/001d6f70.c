
void FUN_001d6f70(undefined4 param_1,undefined4 param_2,undefined4 param_3,float *param_4)

{
  float fStack_80;
  undefined4 uStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [64];
  float fStack_30;
  undefined4 uStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  float *pfStack_20;
  undefined4 uStack_18;
  undefined4 uStack_10;
  undefined4 uStack_8;
  
  pfStack_20 = param_4;
  uStack_18 = param_1;
  uStack_10 = param_2;
  uStack_8 = param_3;
  FUN_001290c0(param_1,param_2,param_3,auStack_70);
  fStack_80 = 0.0;
  uStack_7c = *(undefined4 *)(iGpffff8af8 + 0xfc);
  fStack_78 = 191.8;
  fStack_30 = 0.0;
  fStack_28 = 191.8;
  uStack_24 = uStack_74;
  uStack_2c = uStack_7c;
  FUN_00128ab0(&fStack_80,auStack_70,&fStack_30);
  fStack_30 = fStack_80;
  uStack_2c = uStack_7c;
  fStack_28 = fStack_78;
  uStack_24 = uStack_74;
  FUN_00128ab0(&fStack_80,iGpffff8af8 + 0xb0,&fStack_30);
  *pfStack_20 = *(float *)(iGpffff8af8 + 0x50) - fStack_80;
  pfStack_20[1] = *(float *)(iGpffff8af8 + 0xfc);
  pfStack_20[2] = *(float *)(iGpffff8af8 + 0x58) - fStack_78;
  return;
}

