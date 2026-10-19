
void FUN_001cd2d0(byte param_1,float *param_2)

{
  if (((param_1 == 3) || (param_1 == 2)) || (param_1 == 1)) {
    FUN_00124180(1,param_2);
    *param_2 = *param_2 + *(float *)(&DAT_00244680 + (param_1 - 1) * 0x10);
    param_2[1] = param_2[1] + *(float *)(&DAT_00244684 + (param_1 - 1) * 0x10);
    param_2[2] = param_2[2] + *(float *)(&DAT_00244688 + (param_1 - 1) * 0x10);
  }
  else if (param_1 == 0) {
    FUN_00126a90(param_2);
  }
  return;
}

