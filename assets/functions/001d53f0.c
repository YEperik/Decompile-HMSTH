
void FUN_001d53f0(undefined4 *param_1)

{
  ulong uVar1;
  undefined1 auStack_70 [64];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_14;
  undefined4 *puStack_8;
  
  puStack_8 = param_1;
  uVar1 = FUN_00148df0(0,0x167);
  if ((long)uVar1 < 0) {
    fStack_14 = (float)(uVar1 & 0xffffffff);
  }
  else {
    fStack_14 = (float)(int)uVar1;
  }
  *puStack_8 = 0xbf800000;
  puStack_8[2] = 0;
  puStack_8[1] = 0;
  uStack_30 = *puStack_8;
  uStack_2c = puStack_8[1];
  uStack_28 = puStack_8[2];
  uStack_24 = puStack_8[3];
  FUN_00129020(fStack_14,auStack_70);
  FUN_00128ab0(puStack_8,auStack_70,&uStack_30);
  return;
}

