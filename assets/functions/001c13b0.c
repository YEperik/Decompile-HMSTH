
void FUN_001c13b0(byte param_1)

{
  uint *puVar1;
  
  puVar1 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
  *puVar1 = *puVar1 & 0xfffffffd;
  *(undefined1 *)((uint)param_1 * 0x20 + 0x859e65) = 0;
  FUN_001b7f40(2,3,param_1);
  FUN_0013e2a0(param_1 + 0x1b);
  FUN_001ff4f0(0,0x43000000,0,7,0,*(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x834058));
  *(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x8340a2) = 0x96;
  return;
}

