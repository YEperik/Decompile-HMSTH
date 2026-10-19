
void FUN_001cd820(void)

{
  undefined1 uVar1;
  char *pcVar2;
  int iVar3;
  short sVar4;
  
  sVar4 = 0;
  while ((sVar4 < 3 && (*(char *)(iGpffff8af4 + sVar4 + 8) != -1))) {
    pcVar2 = (char *)FUN_001dfb10(0,*(undefined1 *)(iGpffff8af4 + sVar4 + 8));
    *pcVar2 = *pcVar2 + '\x01';
    uVar1 = *(undefined1 *)(iGpffff8af4 + sVar4 + 8);
    iVar3 = FUN_001df900();
    *(undefined1 *)(iVar3 + (uint)*(byte *)(iGpffff8af4 + sVar4 + 0xb)) = uVar1;
    sVar4 = sVar4 + 1;
  }
  return;
}

