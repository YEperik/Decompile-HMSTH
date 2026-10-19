
void FUN_001d06f0(void)

{
  char cVar1;
  float fVar2;
  float fVar3;
  
  FUN_001d4cf0();
  *(short *)(iRam002679e8 + 2) = *(short *)(iRam002679e8 + 2) + -1;
  *(float *)(iRam002679e8 + 0x144) = *(float *)(iRam002679e8 + 0x144) - 1.0;
  if (-1 < *(short *)(iRam002679e8 + 2)) {
    cVar1 = FUN_0011d018(*(float *)(iRam002679e8 + 0x174) * (float)(int)*(short *)(iRam002679e8 + 2)
                        );
    FUN_00123780(0x32e,-0x80 - cVar1);
    FUN_00122780(0x32e);
  }
  if (-1.0 < *(float *)(iRam002679e8 + 0x144)) {
    if ((*(float *)(iRam002679e8 + 0x130) <= 1.57) &&
       (1.57 <= *(float *)(iRam002679e8 + 0x130) + *(float *)(iRam002679e8 + 0x13c))) {
      *(float *)(iRam002679e8 + 0x148) = -*(float *)(iRam002679e8 + 0x148);
      *(float *)(iRam002679e8 + 0x14c) = -*(float *)(iRam002679e8 + 0x14c);
    }
    *(float *)(iRam002679e8 + 0x130) =
         *(float *)(iRam002679e8 + 0x130) + *(float *)(iRam002679e8 + 0x13c);
    fVar3 = (float)FUN_00112f70(*(undefined4 *)(iRam002679e8 + 0x130));
    fVar2 = *(float *)(iRam002679e8 + 0x138);
    *(float *)(iRam002679e8 + 0x90) =
         *(float *)(iRam002679e8 + 0x90) + *(float *)(iRam002679e8 + 0x148);
    *(float *)(iRam002679e8 + 0x98) =
         *(float *)(iRam002679e8 + 0x98) + *(float *)(iRam002679e8 + 0x14c);
    FUN_00137ae0(*(undefined4 *)(iRam002679e8 + 0x90),
                 *(float *)(iRam002679e8 + 0x94) + fVar2 * fVar3,
                 *(undefined4 *)(iRam002679e8 + 0x98),0x68);
  }
  if (*(short *)(iRam002679e8 + 0x180) < 0) {
    FUN_001d7070();
  }
  return;
}

