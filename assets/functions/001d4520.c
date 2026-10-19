
void FUN_001d4520(short *param_1,char param_2)

{
  ulong uVar1;
  undefined8 uVar2;
  float fVar3;
  
  if (param_2 == '\x01') {
    *(float *)(iRam002679e8 + 400) = *(float *)(iRam002679e8 + 400) + 16.0;
    *(undefined1 *)(iRam002679e8 + 0x185) = 0;
    *(undefined1 *)(iRam002679e8 + 0x186) = 0;
    *(undefined1 *)(iRam002679e8 + 0x18b) = 0;
  }
  if (*(char *)(iRam002679e8 + 0x17c) < '\x03') {
    *(float *)(iRam002679e8 + 0x170) = (float)((int)*param_1 >> 1);
  }
  else {
    uVar1 = FUN_00148df0(*param_1,param_1[1]);
    if ((long)uVar1 < 0) {
      fVar3 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar3 = (float)(int)uVar1;
    }
    *(float *)(iRam002679e8 + 0x170) = fVar3;
    *(float *)(iRam002679e8 + 0x170) =
         *(float *)(iRam002679e8 + 0x170) * (*(float *)(iRam002679e8 + 0x18c) + 1024.0);
    *(float *)(iRam002679e8 + 0x170) = *(float *)(iRam002679e8 + 0x170) / 2048.0;
  }
  FUN_001d7e00(*(undefined1 *)(iRam002679e8 + 0x184));
  FUN_001d4b40(*(undefined1 *)(iRam002679e8 + 0x184),iRam002679e8 + 0x160);
  uVar2 = FUN_001d8ec0();
  FUN_001d6a50(*(undefined1 *)(iRam002679e8 + 0x184),uVar2);
  *(undefined2 *)(iRam002679e8 + 0x182) = *(undefined2 *)(iRam002679e8 + 0x180);
  return;
}

