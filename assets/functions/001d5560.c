
void FUN_001d5560(float *param_1)

{
  float fVar1;
  float fVar2;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float *pfStack_8;
  
  pfStack_8 = param_1;
  fStack_20 = (float)FUN_00112f70(*(undefined4 *)(iRam002679e8 + 0xf0));
  fStack_20 = *(float *)(iRam002679e8 + 0x40) * fStack_20;
  fStack_1c = *(float *)(iRam002679e8 + 0x44);
  fStack_18 = (float)FUN_00112bf8(*(undefined4 *)(iRam002679e8 + 0xf0));
  fStack_18 = *(float *)(iRam002679e8 + 0x48) * fStack_18;
  FUN_00128900(&fStack_20);
  fVar1 = *(float *)(iRam002679e8 + 0x54);
  fVar2 = *(float *)(iRam002679e8 + 0x58);
  *pfStack_8 = *(float *)(iRam002679e8 + 0x50) + fStack_20 * 191.8;
  pfStack_8[1] = fVar1 + fStack_1c * 191.8;
  pfStack_8[2] = fVar2 + fStack_18 * 191.8;
  pfStack_8[3] = fStack_24;
  return;
}

