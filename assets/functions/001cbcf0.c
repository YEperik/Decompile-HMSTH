
/* WARNING: Removing unreachable block (ram,0x001cbe20) */
/* WARNING: Removing unreachable block (ram,0x001cbd2c) */
/* WARNING: Removing unreachable block (ram,0x001cbd68) */
/* WARNING: Removing unreachable block (ram,0x001cbe5c) */

void FUN_001cbcf0(undefined1 param_1,undefined1 param_2)

{
  short sVar1;
  char cVar2;
  undefined1 auStack_40 [16];
  float fStack_30;
  float fStack_24;
  float fStack_14;
  undefined1 uStack_10;
  undefined1 uStack_8;
  
  if (0.75 <= (float)bGpffff8942 / (float)bGpffff8943) {
    cVar2 = '\x02';
  }
  else if (0.5 <= (float)bGpffff8942 / (float)bGpffff8943) {
    cVar2 = '\x01';
  }
  else {
    cVar2 = '\0';
  }
  fStack_14 = (float)bGpffff8940 / (float)bGpffff8941;
  if (0.5 <= fStack_14) {
    sVar1 = 0;
  }
  else if (0.25 <= fStack_14) {
    sVar1 = 1;
  }
  else {
    sVar1 = 2;
  }
  DAT_00244584 = (byte)(((int)sVar1 << 5) >> 2);
  uStack_10 = param_1;
  uStack_8 = param_2;
  for (sVar1 = 0; sVar1 < 1; sVar1 = sVar1 + 1) {
    FUN_001cc050(sVar1 * 0xc + 0x244580,auStack_40 + sVar1 * 0x24,uStack_8,uStack_10,cVar2 + -0x31,
                 0x100,0x100);
  }
  fStack_24 = (float)((uint)DAT_00244585 * 4 + 0x1f) / 256.0;
  fStack_30 = (float)((uint)DAT_00244584 * 4 + 0x1f) / 256.0;
  FUN_001ddec0(1,auStack_40);
  FUN_001ddff0(1,auStack_40);
  return;
}

