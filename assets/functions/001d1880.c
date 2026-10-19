
void FUN_001d1880(undefined4 param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)FUN_00112f70(*(float *)(iGpffff8af8 + 0xf0) + 0.3925);
  fVar2 = *(float *)(iGpffff8af8 + 0x50) + fVar1 * 968.0;
  fVar1 = (float)FUN_00112bf8(*(float *)(iGpffff8af8 + 0xf0) + 0.3925);
  FUN_00136920(fVar2,0x43800000,*(float *)(iGpffff8af8 + 0x58) + fVar1 * 968.0,param_1);
  FUN_00136c10(param_1,0);
  uRam0083d044 = 0x43800000;
  return;
}

