
void FUN_001d92f0(float param_1)

{
  float fVar1;
  
  if (*(char *)(iRam002679e8 + 0x1ab) == '\0') {
    *(short *)(iRam002679e8 + 0x1ac) = *(short *)(iRam002679e8 + 0x1ac) + 1;
  }
  else if (*(float *)(iRam002679e8 + 0x1a4) == 0.0) {
    *(float *)(iRam002679e8 + 0x1a0) = *(float *)(iRam002679e8 + 0x1a0) - param_1;
  }
  else if (*(float *)(iRam002679e8 + 0x1a4) < param_1) {
    fVar1 = *(float *)(iRam002679e8 + 0x1a4);
    *(undefined4 *)(iRam002679e8 + 0x1a4) = 0;
    *(float *)(iRam002679e8 + 0x1a0) = *(float *)(iRam002679e8 + 0x1a0) - (param_1 - fVar1);
  }
  else {
    *(float *)(iRam002679e8 + 0x1a4) = *(float *)(iRam002679e8 + 0x1a4) - param_1;
  }
  return;
}

