
void FUN_001dae90(char param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 auStack_18 [4];
  int iStack_14;
  char cStack_8;
  
  iVar5 = *(int *)(iGpffff8afc + 0x24);
  iVar2 = *(int *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) * 4 + 0x14);
  iVar3 = *(int *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) * 4 + 0x1c);
  if (param_1 < '\x01') {
    iVar9 = iVar3 + 4;
    iVar7 = iVar3 + 8;
    iVar4 = *(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc) + -1;
    iVar8 = iVar3;
    iStack_14 = iVar3;
  }
  else {
    iVar4 = *(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc) + 3;
    iVar7 = iVar3;
    iVar8 = iVar3 + 4;
    iVar9 = iVar3;
    iStack_14 = iVar3 + 8;
  }
  cStack_8 = param_1;
  for (sVar6 = 0; sVar6 < 4; sVar6 = sVar6 + 1) {
    FUN_0015ab30(*(undefined1 *)(iVar7 + sVar6));
    FUN_001dbdf0(*(undefined1 *)(iVar5 + sVar6),*(undefined1 *)(iVar2 + iVar4 * 4 + (int)sVar6));
    *(byte *)(iVar5 + sVar6) = *(byte *)(iVar5 + sVar6) ^ *(byte *)(iVar7 + sVar6);
    *(byte *)(iVar7 + sVar6) = *(byte *)(iVar7 + sVar6) ^ *(byte *)(iVar5 + sVar6);
    *(byte *)(iVar5 + sVar6) = *(byte *)(iVar5 + sVar6) ^ *(byte *)(iVar7 + sVar6);
  }
  FUN_001167c0(auStack_18,iVar7,4);
  FUN_00116870(iVar9,iVar8,8);
  FUN_001167c0(iStack_14,auStack_18,4);
  iVar5 = iGpffff8afc + *(char *)(iGpffff8afc + 0x2a);
  *(char *)(iVar5 + 0xc) = *(char *)(iVar5 + 0xc) + cStack_8;
  cVar1 = *(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc);
  iVar5 = *(int *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) * 4 + 0x14);
  for (sVar6 = 0; sVar6 < 0xc; sVar6 = sVar6 + 1) {
    FUN_001dbed0(*(undefined1 *)(iVar3 + sVar6),*(undefined1 *)(iVar5 + cVar1 * 4 + (int)sVar6),
                 (int)sVar6 + *(char *)(iGpffff8afc + 0x2a) * 0xc & 0xff);
  }
  FUN_001dcf30();
  return;
}

