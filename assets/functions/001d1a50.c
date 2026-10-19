
void FUN_001d1a50(void)

{
  float fVar1;
  float fVar2;
  
  fVar1 = (float)FUN_00112f70(*(undefined4 *)(iGpffff8af8 + 0xf0));
  fVar2 = *(float *)(iGpffff8af8 + 0x50) - fVar1 * 640.0;
  fVar1 = (float)FUN_00112bf8(*(undefined4 *)(iGpffff8af8 + 0xf0));
  FUN_00136890(fVar2,0xc2800000,*(float *)(iGpffff8af8 + 0x58) - fVar1 * 640.0);
  FUN_00136a60(0);
  uRam0083d044 = 0x42c00000;
  return;
}

