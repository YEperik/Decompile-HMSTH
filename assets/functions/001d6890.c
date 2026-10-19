
float FUN_001d6890(float param_1)

{
  float fStack_14;
  
  fStack_14 = 0.0;
  if (((param_1 < 0.0) && (380.0 < *(float *)(iGpffff8af8 + 0x1a0))) &&
     (*(float *)(iGpffff8af8 + 0x1a4) * 4.0 < *(float *)(iGpffff8af8 + 0x1a0))) {
    fStack_14 = (*(float *)(iGpffff8af8 + 0x1a0) / 256.0) * param_1;
    *(float *)(iGpffff8af8 + 0x1a0) = *(float *)(iGpffff8af8 + 0x1a0) + fStack_14;
    *(float *)(iGpffff8af8 + 0x1a4) = *(float *)(iGpffff8af8 + 0x1a4) - fStack_14;
  }
  return fStack_14;
}

