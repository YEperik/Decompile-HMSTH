
float FUN_001d8e20(void)

{
  float fVar1;
  
  fVar1 = ((float)(int)*(short *)(iGpffff8af8 + 0x180) / (float)(int)*(short *)(iGpffff8af8 + 0x182)
          ) * 32.0;
  if (*(float *)(iGpffff8af8 + 0x18c) - fVar1 < 0.0) {
    fVar1 = 0.0;
  }
  else {
    fVar1 = *(float *)(iGpffff8af8 + 0x18c) - fVar1;
  }
  return fVar1;
}

