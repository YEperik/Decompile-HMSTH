
void FUN_001de9e0(int param_1)

{
  ushort uVar1;
  
  if ((*(byte *)(param_1 + 3) & 4) == 0) {
    uVar1 = (ushort)*(byte *)(param_1 + 2) + *(short *)(iGpffff8148 + 4);
  }
  else {
    uVar1 = (ushort)*(byte *)(param_1 + 2);
  }
  FUN_0015bcd0((ushort)*(byte *)(param_1 + 1) + *(short *)(iGpffff8148 + 6),
               (ushort)*(byte *)(param_1 + 1) + *(short *)(iGpffff8148 + 10),
               (ushort)*(byte *)(param_1 + 1) + *(short *)(iGpffff8148 + 8),uVar1);
  return;
}

