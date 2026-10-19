
void FUN_001c14a0(byte param_1)

{
  uint *puVar1;
  
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
  *puVar1 = *puVar1 & 0xfffffffd;
  *(undefined1 *)((uint)param_1 * 0x20 + 0x859f25) = 0;
  FUN_001b7f40(3,3,param_1);
  FUN_0013e2a0(param_1 + 0x12);
  if (((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x800) == 0x800) ||
     ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x1000) == 0x1000)) {
    FUN_001ff4f0(0,0x43000000,0,7,0,*(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834058));
  }
  else {
    FUN_001ff4f0(0,0x43200000,0,7,0,*(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834058));
  }
  *(undefined2 *)((param_1 + 0x12) * 0x100 + 0x8340a2) = 0x96;
  return;
}

