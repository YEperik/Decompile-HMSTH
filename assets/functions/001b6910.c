
void FUN_001b6910(byte param_1)

{
  if (param_1 == 0) {
    FUN_00123950(7,1);
  }
  else {
    FUN_00123950(param_1 + 1,1);
  }
  (&gp0xffff89a8)[param_1] = (&gp0xffff89a8)[param_1] | 0x10;
  return;
}

