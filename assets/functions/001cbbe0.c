
void FUN_001cbbe0(undefined1 param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 auStack_130 [288];
  undefined1 uStack_10;
  undefined1 uStack_8;
  
  uStack_10 = param_1;
  uStack_8 = param_2;
  FUN_001cc310(uGpffff8974,6,2,0x24452c,0x70,0xc0,8,0x10);
  for (sVar1 = 0; sVar1 < 8; sVar1 = sVar1 + 1) {
    FUN_001cc050(sVar1 * 0xc + 0x244520,auStack_130 + sVar1 * 0x24,uStack_8,uStack_10,0xcf,0x100,
                 0x100);
  }
  FUN_001ddec0(8,auStack_130);
  FUN_001ddff0(8,auStack_130);
  return;
}

