
undefined1 FUN_001deac0(int param_1,short param_2)

{
  long lVar1;
  
  for (lVar1 = 0; lVar1 < param_2; lVar1 = (long)((int)lVar1 + 1)) {
    if (*(char *)(param_1 + (int)lVar1) == -1) goto LAB_001deb34;
  }
  lVar1 = (long)param_2;
LAB_001deb34:
  return (char)lVar1;
}

