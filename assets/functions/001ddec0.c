
void FUN_001ddec0(short param_1,int param_2)

{
  short sVar1;
  undefined4 uStack_8;
  
  uStack_8 = param_2;
  for (sVar1 = 0; sVar1 < param_1; sVar1 = sVar1 + 1) {
    if ((*(byte *)(uStack_8 + 3) & 1) != 0) {
      FUN_0015ae30(*(undefined4 *)(uStack_8 + 0x10),*(undefined4 *)(uStack_8 + 0x14),
                   *(undefined4 *)(uStack_8 + 0x18),*(undefined4 *)(uStack_8 + 0x1c),
                   (ushort)*(byte *)(uStack_8 + 1) + *(short *)(iGpffff8148 + 6),
                   *(undefined2 *)(uStack_8 + 0x20),*(undefined2 *)(uStack_8 + 0x22));
      FUN_001de9e0(uStack_8);
      FUN_0015c040(*(undefined4 *)(uStack_8 + 4),*(undefined4 *)(uStack_8 + 8),
                   *(undefined4 *)(uStack_8 + 0xc),
                   (ushort)*(byte *)(uStack_8 + 1) + *(short *)(iGpffff8148 + 6));
    }
    uStack_8 = uStack_8 + 0x24;
  }
  return;
}

