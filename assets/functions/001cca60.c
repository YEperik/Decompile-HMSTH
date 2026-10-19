
/* WARNING: Removing unreachable block (ram,0x001ccab4) */
/* WARNING: Removing unreachable block (ram,0x001ccaf4) */

void FUN_001cca60(short param_1,short param_2,short param_3,int param_4,ushort param_5)

{
  short sVar1;
  undefined4 uStack_10;
  
  uStack_10 = param_4;
  for (sVar1 = 0; (long)sVar1 < (long)(ulong)param_5; sVar1 = sVar1 + 1) {
    FUN_001cc990((float)*(ushort *)(uStack_10 + 0x20),(float)*(ushort *)(uStack_10 + 0x22),
                 *(undefined4 *)(uStack_10 + 0x10),*(undefined4 *)(uStack_10 + 0x14),
                 *(undefined4 *)(uStack_10 + 0x18),*(undefined4 *)(uStack_10 + 0x1c),
                 *(undefined4 *)(uStack_10 + 4),*(undefined4 *)(uStack_10 + 8),
                 (ushort)*(byte *)(uStack_10 + 1) + param_1,
                 (ushort)*(byte *)(uStack_10 + 1) + param_2,
                 (ushort)*(byte *)(uStack_10 + 1) + param_3);
    uStack_10 = uStack_10 + 0x24;
  }
  return;
}

