
void FUN_001d54d0(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 - *param_3;
  param_1[1] = param_2[1] - param_3[1];
  param_1[2] = param_2[2] - param_3[2];
  FUN_00128900(param_1);
  return;
}

