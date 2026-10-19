
void FUN_001cceb0(float param_1,float param_2,float param_3,short param_4,undefined2 param_5,
                 undefined2 param_6,undefined4 param_7)

{
  undefined8 uVar1;
  short sVar2;
  undefined1 auStack_150 [4];
  float afStack_14c [65];
  float fStack_48;
  float fStack_44;
  short sStack_38;
  undefined2 uStack_30;
  undefined2 uStack_28;
  float fStack_20;
  float fStack_18;
  float fStack_10;
  undefined4 uStack_8;
  
  sStack_38 = param_4;
  uStack_30 = param_5;
  uStack_28 = param_6;
  fStack_20 = param_1;
  fStack_18 = param_2;
  fStack_10 = param_3;
  uStack_8 = param_7;
  FUN_001cc310(param_7,6,2,0x24452c,0x70,0xc0,8,0x10);
  for (sVar2 = 0; sVar2 < 7; sVar2 = sVar2 + 1) {
    uVar1 = FUN_0011cf88(fStack_10 - 1.0);
    FUN_001cc050((sVar2 + 1) * 0xc + 0x244520,auStack_150 + sVar2 * 0x24,0,uVar1,0xcf,0x100,0x100);
    if (sVar2 == 0) {
      fStack_48 = afStack_14c[0] - fStack_20;
      fStack_44 = afStack_14c[1] - fStack_18;
    }
    afStack_14c[sVar2 * 9] = afStack_14c[sVar2 * 9] - fStack_48;
    afStack_14c[sVar2 * 9 + 1] = afStack_14c[sVar2 * 9 + 1] - fStack_44;
  }
  FUN_001cca60(sStack_38 + -1,uStack_30,uStack_28,auStack_150,7);
  return;
}

