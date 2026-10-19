
void FUN_001c2a90(byte param_1)

{
  uint *puVar1;
  
  if (param_1 == 0x10) {
    FUN_00139920(0x10,5);
    FUN_0013b110(0x43700000,0x41f00000,0x40400000,0,0x10,6);
    FUN_0013ffc0(0x10);
    FUN_0013fae0(0x10,0xe,2,0,0,0);
  }
  else {
    FUN_00139920(0x11,5);
    FUN_0013b110(0x43aa0000,0x41a00000,0x3f800000,0,0x11,4);
    FUN_0013ffc0(0x11);
    FUN_0013fae0(0x11,0xe,2,0,0,0);
  }
  FUN_0013a620(param_1,1,2);
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 & 0xffffffef;
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 | 0x20;
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 | 8;
  return;
}

