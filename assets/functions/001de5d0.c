
void FUN_001de5d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 *param_13,char param_14,undefined1 param_15)

{
  FUN_0015ae30(param_1,param_2,param_3,param_4,param_5,0x10,0x10);
  FUN_001de710(param_5,param_9,param_10,param_11,param_12);
  FUN_0015bcd0(param_5,param_8,param_7,param_6);
  FUN_0015c1d0(param_5,param_14);
  if (param_14 == '\x06') {
    FUN_00123f50(*param_13,param_13[1],param_13[2],param_8);
  }
  else {
    FUN_00124510(0,0,0,0x3f800000,param_8);
    FUN_00123f50(0,0,0,param_8);
  }
  FUN_001de580(param_8,param_15);
  return;
}

