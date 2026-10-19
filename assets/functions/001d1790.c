
void FUN_001d1790(void)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)FUN_00112f70(*(float *)(iRam002679e8 + 0xf0) + 0.3925);
  fVar2 = *(float *)(iRam002679e8 + 0x50) + fVar1 * 968.0;
  fVar1 = (float)FUN_00112bf8(*(float *)(iRam002679e8 + 0xf0) + 0.3925);
  FUN_001d1710(fVar2,0x43800000,*(float *)(iRam002679e8 + 0x58) + fVar1 * 968.0,0,0x43400000,0,0);
  uRam0083d044 = 0x43800000;
  return;
}

