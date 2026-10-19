
void FUN_001c29f0(byte param_1)

{
  uint *puVar1;
  
  (&gp0xffff8110)[param_1] = 0;
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 | 0x80000;
  FUN_0013e2a0(param_1 + 0x12);
  FUN_00138760(0x44900000,0,0x44d80000,param_1 + 0x12);
  return;
}

