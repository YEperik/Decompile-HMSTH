
void FUN_001deb50(int param_1,short param_2)

{
  short sVar1;
  
  for (sVar1 = 0; (sVar1 < param_2 && (*(char *)(param_1 + sVar1) != -1)); sVar1 = sVar1 + 1) {
  }
  for (; sVar1 < 8; sVar1 = sVar1 + 1) {
    *(undefined1 *)(param_1 + sVar1) = 0xff;
  }
  return;
}

