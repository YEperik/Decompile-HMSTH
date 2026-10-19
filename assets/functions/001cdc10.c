
void FUN_001cdc10(byte param_1)

{
  int iVar1;
  
  if (param_1 != 0xff) {
    iVar1 = FUN_001df900();
    if (*(char *)(iVar1 + (uint)param_1) != -1) {
      FUN_001cdb40(*(char *)(iVar1 + (uint)param_1));
    }
  }
  return;
}

