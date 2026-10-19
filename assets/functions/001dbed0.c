
undefined4 FUN_001dbed0(undefined1 param_1,char param_2,byte param_3)

{
  undefined4 uVar1;
  
  if ((param_2 == -1) || (param_3 == 0xff)) {
    FUN_0015ab30(param_1);
    uVar1 = 0;
  }
  else {
    FUN_0015a0e0((float)(int)*(short *)(&DAT_00244930 + (uint)param_3 * 4),
                 (float)(int)*(short *)(&DAT_00244932 + (uint)param_3 * 4) + -18.0,0x47c36180,
                 param_1);
    FUN_0015aab0(param_1);
    uVar1 = 1;
  }
  return uVar1;
}

