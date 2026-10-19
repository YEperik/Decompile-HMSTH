
void FUN_001b6720(byte param_1)

{
  uint *puVar1;
  
  FUN_00123950(param_1 + 3,1);
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 | 0x20;
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 | 0x40;
  return;
}

