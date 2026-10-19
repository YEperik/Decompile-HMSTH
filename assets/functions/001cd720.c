
void FUN_001cd720(byte param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = FUN_001df900();
  *(undefined1 *)(iRam002679e4 + *(char *)(iRam002679e4 + 7) + 8) =
       *(undefined1 *)(iVar1 + (uint)param_1);
  pcVar2 = (char *)FUN_001dfb10(0,*(undefined1 *)(iRam002679e4 + *(char *)(iRam002679e4 + 7) + 8));
  *pcVar2 = *pcVar2 + -1;
  *(byte *)(iRam002679e4 + *(char *)(iRam002679e4 + 7) + 0xb) = param_1;
  if (*pcVar2 == '\0') {
    iVar1 = FUN_001df900();
    *(undefined1 *)(iVar1 + (uint)param_1) = 0xff;
  }
  *(char *)(iRam002679e4 + 7) = *(char *)(iRam002679e4 + 7) + '\x01';
  return;
}

