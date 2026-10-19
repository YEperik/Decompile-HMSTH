
void FUN_001ddff0(short param_1,int param_2)

{
  short sVar1;
  undefined4 uStack_8;
  
  uStack_8 = param_2;
  for (sVar1 = 0; sVar1 < param_1; sVar1 = sVar1 + 1) {
    if ((*(byte *)(uStack_8 + 3) & 2) != 0) {
      FUN_0015bf20((ushort)*(byte *)(uStack_8 + 1) + *(short *)(iGpffff8148 + 6));
    }
    uStack_8 = uStack_8 + 0x24;
  }
  return;
}

