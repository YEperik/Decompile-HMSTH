
void FUN_001de710(ushort param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = ((uint)param_1 * 0x12 + (uint)param_1) * 0x10;
  *(undefined4 *)(iVar1 + 0x80dcd0) = *param_2;
  *(undefined4 *)(iVar1 + 0x80dcd4) = param_2[1];
  *(undefined4 *)(iVar1 + 0x80dcd8) = param_2[2];
  *(undefined4 *)(iVar1 + 0x80dce0) = *param_3;
  *(undefined4 *)(iVar1 + 0x80dce4) = param_3[1];
  *(undefined4 *)(iVar1 + 0x80dce8) = param_3[2];
  *(undefined4 *)(iVar1 + 0x80dcf0) = *param_4;
  *(undefined4 *)(iVar1 + 0x80dcf4) = param_4[1];
  *(undefined4 *)(iVar1 + 0x80dcf8) = param_4[2];
  *(undefined4 *)(iVar1 + 0x80dd00) = *param_5;
  *(undefined4 *)(iVar1 + 0x80dd04) = param_5[1];
  *(undefined4 *)(iVar1 + 0x80dd08) = param_5[2];
  *(undefined4 *)(iVar1 + 0x80dd10) = *param_4;
  *(undefined4 *)(iVar1 + 0x80dd14) = param_4[1];
  *(undefined4 *)(iVar1 + 0x80dd18) = param_4[2];
  *(undefined4 *)(iVar1 + 0x80dd20) = *param_3;
  *(undefined4 *)(iVar1 + 0x80dd24) = param_3[1];
  *(undefined4 *)(iVar1 + 0x80dd28) = param_3[2];
  return;
}

