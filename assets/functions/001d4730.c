
void FUN_001d4730(short *param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  float afStack_14 [3];
  short *psStack_8;
  
  psStack_8 = param_1;
  uVar1 = FUN_00148df0(param_1[2],param_1[3]);
  *(undefined2 *)(iRam002679e8 + 0x180) = uVar1;
  if (*(char *)(iRam002679e8 + 0x17c) < '\x03') {
    *(float *)(iRam002679e8 + 0x170) = (float)(int)*psStack_8;
  }
  else {
    uVar2 = FUN_001d93e0((float)(int)*(char *)(iRam002679e8 + 0x17e),0,0x42000000,
                         (float)(int)*psStack_8,(float)(int)psStack_8[1]);
    *(undefined4 *)(iRam002679e8 + 0x170) = uVar2;
    *(float *)(iRam002679e8 + 0x170) =
         *(float *)(iRam002679e8 + 0x170) / (float)(*(char *)(iRam002679e8 + 0x17d) + 1);
    FUN_00128b50(afStack_14,iRam002679e8 + 0x90,iRam002679e8 + 0x150);
    *(float *)(iRam002679e8 + 0x170) = *(float *)(iRam002679e8 + 0x170) * (afStack_14[0] / 128.0);
  }
  *(undefined2 *)(iRam002679e8 + 0x182) = *(undefined2 *)(iRam002679e8 + 0x180);
  return;
}

