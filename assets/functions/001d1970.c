
void FUN_001d1970(void)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)FUN_00112f70(*(float *)(iGpffff8af8 + 0xf0) + 3.14);
  fVar2 = *(float *)(iGpffff8af8 + 0x50) - fVar1 * 514.0;
  fVar1 = (float)FUN_00112bf8(*(float *)(iGpffff8af8 + 0xf0) + 3.14);
  FUN_001d1710(fVar2,0x43800000,*(float *)(iGpffff8af8 + 0x58) - fVar1 * 514.0,0,0x43600000,0,0);
  return;
}

