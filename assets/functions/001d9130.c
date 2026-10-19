
void FUN_001d9130(float *param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_2[2] * (param_5[2] - param_4[2]) +
          *param_2 * (*param_5 - *param_4) + param_2[1] * (param_5[1] - param_4[1]);
  fVar2 = param_2[2] * (param_3[2] - param_4[2]) +
          *param_2 * (*param_3 - *param_4) + param_2[1] * (param_3[1] - param_4[1]);
  if (fVar1 != 0.0) {
    *param_1 = *param_4 + (fVar2 * (*param_5 - *param_4)) / fVar1;
    param_1[1] = param_4[1] + (fVar2 * (param_5[1] - param_4[1])) / fVar1;
    param_1[2] = param_4[2] + (fVar2 * (param_5[2] - param_4[2])) / fVar1;
  }
  return;
}

