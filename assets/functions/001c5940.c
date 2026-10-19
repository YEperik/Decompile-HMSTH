
void FUN_001c5940(byte param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                 undefined4 param_5)

{
  uint *puVar1;
  
  FUN_00137200(param_1,param_2,param_3,param_4,0,0,param_5);
  FUN_0013a3e0(0,0x42000000,0,0x42000000,param_1);
  FUN_0013a620(param_1,0,2);
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 & 0xffffffef;
  FUN_00137930(param_1);
  return;
}

