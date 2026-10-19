
void FUN_001de200(short param_1,short param_2)

{
  short sVar1;
  
  for (sVar1 = 0; sVar1 < param_2; sVar1 = sVar1 + 1) {
    FUN_0015be60(*(short *)(PTR_DAT_00267038 + 6) + param_1 + sVar1);
  }
  return;
}

