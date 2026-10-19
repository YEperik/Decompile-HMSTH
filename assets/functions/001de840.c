
void FUN_001de840(ushort param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = ((uint)param_1 * 0x12 + (uint)param_1) * 0x10;
  *(undefined4 *)(iVar1 + 0x80dd90) = *param_2;
  *(undefined4 *)(iVar1 + 0x80dd94) = param_2[1];
  *(undefined4 *)(iVar1 + 0x80dda0) = *param_3;
  *(undefined4 *)(iVar1 + 0x80dda4) = param_3[1];
  *(undefined4 *)(iVar1 + 0x80ddb0) = *param_4;
  *(undefined4 *)(iVar1 + 0x80ddb4) = param_4[1];
  *(undefined4 *)(iVar1 + 0x80ddc0) = *param_5;
  *(undefined4 *)(iVar1 + 0x80ddc4) = param_5[1];
  *(undefined4 *)(iVar1 + 0x80ddd0) = *param_4;
  *(undefined4 *)(iVar1 + 0x80ddd4) = param_4[1];
  *(undefined4 *)(iVar1 + 0x80dde0) = *param_3;
  *(undefined4 *)(iVar1 + 0x80dde4) = param_3[1];
  return;
}

