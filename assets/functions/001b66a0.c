
void FUN_001b66a0(byte param_1)

{
  uint *puVar1;
  
  FUN_00123950(param_1 + 2,1);
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
  *puVar1 = *puVar1 | 0x20;
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
  *puVar1 = *puVar1 | 0x40;
  return;
}

