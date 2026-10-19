
void FUN_001bf040(byte param_1)

{
  uint *puVar1;
  
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 2) == 2) {
    FUN_00139920(0x1b,0xb);
  }
  else if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x100) == 0x100) {
    FUN_00139920(param_1 + 0x1b,10);
  }
  else {
    FUN_00139920(param_1 + 0x1b);
  }
  (&DAT_00266ff8)[param_1] = 0;
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
  *puVar1 = *puVar1 & 0xffffbfff;
  return;
}

