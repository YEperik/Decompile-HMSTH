
/* WARNING: Removing unreachable block (ram,0x001d4ba4) */

void FUN_001d4b40(byte param_1,undefined4 *param_2)

{
  short sVar1;
  long lVar2;
  undefined1 auStack_70 [64];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_14;
  byte bStack_10;
  undefined4 *puStack_8;
  
  *param_2 = 0xbf800000;
  param_2[1] = 0;
  param_2[2] = 0;
  fStack_14 = (float)param_1 * 90.0;
  bStack_10 = param_1;
  puStack_8 = param_2;
  sVar1 = FUN_00148df0(0,0x2d);
  lVar2 = FUN_00148df0(0,1);
  if (lVar2 == 0) {
    sVar1 = -sVar1;
  }
  fStack_14 = fStack_14 + (float)(int)sVar1;
  uStack_30 = *puStack_8;
  uStack_2c = puStack_8[1];
  uStack_28 = puStack_8[2];
  uStack_24 = puStack_8[3];
  FUN_001d7d20(0xc3b40000,0x43b40000,&fStack_14);
  FUN_00129020(fStack_14,auStack_70);
  FUN_00128ab0(puStack_8,auStack_70,&uStack_30);
  uStack_30 = *puStack_8;
  uStack_2c = puStack_8[1];
  uStack_28 = puStack_8[2];
  uStack_24 = puStack_8[3];
  FUN_00128ab0(puStack_8,iGpffff8af8 + 0xb0,&uStack_30);
  return;
}

