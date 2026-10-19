
void FUN_001d48a0(undefined2 *param_1)

{
  undefined2 uVar1;
  ulong uVar2;
  float fVar3;
  
  uVar1 = FUN_00148df0(param_1[2],param_1[3]);
  *(undefined2 *)(iGpffff8af8 + 0x180) = uVar1;
  uVar2 = FUN_00148df0(*param_1,param_1[1]);
  if ((long)uVar2 < 0) {
    fVar3 = (float)(uVar2 & 0xffffffff);
  }
  else {
    fVar3 = (float)(int)uVar2;
  }
  *(float *)(iGpffff8af8 + 0x170) = fVar3;
  *(float *)(iGpffff8af8 + 0x170) =
       *(float *)(iGpffff8af8 + 0x170) * (float)(*(char *)(iGpffff8af8 + 0x17d) + 1);
  *(float *)(iGpffff8af8 + 0x170) = *(float *)(iGpffff8af8 + 0x170) / 16.0;
  *(undefined2 *)(iGpffff8af8 + 0x182) = *(undefined2 *)(iGpffff8af8 + 0x180);
  return;
}

