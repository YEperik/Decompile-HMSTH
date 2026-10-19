
undefined4 FUN_001d7d20(float param_1,float param_2,float *param_3)

{
  undefined4 uVar1;
  
  if (*param_3 < param_1) {
    *param_3 = param_1;
    uVar1 = 0;
  }
  else if (param_2 < *param_3) {
    *param_3 = param_2;
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

