
void FUN_001c5730(byte param_1)

{
  short sVar1;
  int iVar2;
  uint *puVar3;
  
  FUN_0013e1b0(param_1 + 0x1b,3);
  if ((0x13 < bRam0085a2f5) || (bRam0085a2f5 < 6)) {
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x200) == 0x200) {
      iVar2 = (param_1 + 0x1b) * 0x100;
      sVar1 = *(short *)(iVar2 + 0x8340a2);
      *(short *)(iVar2 + 0x8340a2) = sVar1 + 1;
      if (300 < (ushort)(sVar1 + 1U)) {
        FUN_0013e2a0(param_1 + 0x1b);
        puVar3 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
        *puVar3 = *puVar3 & 0xfffffdff;
        *(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x8340a2) = 0;
        (&DAT_00266ff8)[param_1] = 2;
        FUN_00139920(param_1 + 0x1b,4);
      }
    }
    else if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 1) == 1) {
      (&DAT_00266ff8)[param_1] = 2;
      FUN_00139920(param_1 + 0x1b,4);
      FUN_0013e2a0(param_1 + 0x1b);
      puVar3 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
      *puVar3 = *puVar3 | 0x100;
    }
  }
  return;
}

