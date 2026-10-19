
bool FUN_001d7b50(float *param_1)

{
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float afStack_30 [7];
  float afStack_14 [3];
  float *pfStack_8;
  
  pfStack_8 = param_1;
  uStack_40 = FUN_00112f70(*(undefined4 *)(iGpffff8af8 + 0xf0));
  uStack_38 = FUN_00112bf8(*(undefined4 *)(iGpffff8af8 + 0xf0));
  uStack_3c = 0;
  afStack_30[0] = *pfStack_8 - *(float *)(iGpffff8af8 + 0x50);
  afStack_30[2] = pfStack_8[2] - *(float *)(iGpffff8af8 + 0x58);
  afStack_30[1] = 0.0;
  FUN_00128900(afStack_30);
  FUN_00128980(afStack_14,&uStack_40,afStack_30);
  if (afStack_14[0] < 0.0) {
    afStack_14[0] = -afStack_14[0];
  }
  return 0.9 <= afStack_14[0];
}

