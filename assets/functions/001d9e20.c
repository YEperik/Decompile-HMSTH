
void FUN_001d9e20(void)

{
  short sVar1;
  undefined1 auStack_110 [256];
  undefined1 auStack_10 [16];
  
  FUN_001361f0(1,0xff0000,0x1941000);
  FUN_00148e20(auStack_10,0x1941000,*(undefined2 *)(iGpffff8148 + 4),
               *(int *)(iGpffff8148 + 0x10) + 0x100,*(undefined4 *)(iGpffff8148 + 0x10));
  FUN_001cc050(0x2448d0,auStack_110,0,0,*(ushort *)(iGpffff8148 + 4) & 0xff,0x200,0x100);
  for (sVar1 = 1; sVar1 < 7; sVar1 = sVar1 + 1) {
    FUN_001cc050(&DAT_002448d0 + sVar1 * 0xc,auStack_110 + sVar1 * 0x24,0,0,0xcf,0x100,0x100);
  }
  FUN_001ddec0(7,auStack_110);
  FUN_001ddff0(7,auStack_110);
  FUN_0015bfb0(*(short *)(iGpffff8148 + 6) + 3);
  FUN_001dbb00();
  FUN_001dbfc0(1);
  return;
}

