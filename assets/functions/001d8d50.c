
float FUN_001d8d50(void)

{
  float fVar1;
  
  if (858.6667 < *(float *)(iGpffff8af8 + 0x1a0) + *(float *)(iGpffff8af8 + 0x1a4)) {
    fVar1 = 1.0;
  }
  else if (*(float *)(iGpffff8af8 + 0x1a0) + *(float *)(iGpffff8af8 + 0x1a4) < 320.0) {
    fVar1 = 0.0;
  }
  else {
    fVar1 = (*(float *)(iGpffff8af8 + 0x1a0) - 320.0) / 538.6667;
  }
  return fVar1;
}

