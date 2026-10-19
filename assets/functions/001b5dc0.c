
void FUN_001b5dc0(byte param_1)

{
  uint *puVar1;
  
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 & 0xfffffffb;
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 & 0xfffffff7;
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 | 0x1000000;
  *(undefined1 *)((uint)param_1 * 0x20 + 0x859f24) = 10;
  return;
}

