
void FUN_001b7360(byte param_1,undefined1 param_2)

{
  uint *puVar1;
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [4];
  byte bStack_10;
  undefined1 uStack_8;
  
  if (*(char *)((param_1 + 0x1b) * 0x100 + 0x834056) != '\x04') {
    bStack_10 = param_1;
    uStack_8 = param_2;
    FUN_00178c00(param_2);
    FUN_0013e2a0(bStack_10 + 0x1b);
    FUN_001ff4f0(0,0x42800000,0,0x17,0,*(undefined2 *)((bStack_10 + 0x1b) * 0x100 + 0x834058));
    FUN_00139920(bStack_10 + 0x1b,4);
    FUN_001244b0(uRam00834058,afStack_30);
    FUN_00124180(*(undefined2 *)((bStack_10 + 0x1b) * 0x100 + 0x834058),afStack_20);
    afStack_20[0] = afStack_20[0] + -afStack_30[0] * 128.0;
    afStack_20[1] = 0.0;
    afStack_20[2] = afStack_20[2] + -fStack_28 * 128.0;
    FUN_00137b90(bStack_10 + 0x1b,afStack_30);
    FUN_00137fa0(0x40800000,bStack_10 + 0x1b,0x40);
    puVar1 = (uint *)((bStack_10 + 0x1b) * 0x100 + 0x834050);
    *puVar1 = *puVar1 | 0x80000000;
  }
  return;
}

