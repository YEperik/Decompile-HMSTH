
void FUN_001de930(short param_1,short param_2)

{
  short sVar1;
  
  for (sVar1 = 0; sVar1 < param_2; sVar1 = sVar1 + 1) {
    FUN_0015ab30((int)param_1 + (int)sVar1 & 0xff);
    FUN_00159fe0((int)param_1 + (int)sVar1 & 0xff);
  }
  return;
}

