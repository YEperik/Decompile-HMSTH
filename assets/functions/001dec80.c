
void FUN_001dec80(byte param_1,byte param_2)

{
  short sVar1;
  
  for (sVar1 = 0; sVar1 < (short)(ushort)param_2; sVar1 = sVar1 + 1) {
    FUN_001543b0((uint)param_1 + (int)sVar1 & 0xff);
  }
  return;
}

