
undefined1 FUN_001d49c0(char param_1,undefined1 *param_2)

{
  uint uVar1;
  int iVar2;
  long lVar4;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_14;
  char cStack_10;
  undefined1 *puStack_8;
  ulong uVar3;
  
  cStack_10 = param_1;
  puStack_8 = param_2;
  uVar1 = FUN_00148df0(0,0x1f);
  iVar2 = (int)(uVar1 & 0xff) >> 3;
  uVar3 = (ulong)iVar2;
  if ((uVar3 == (long)*(char *)(iGpffff8af8 + 0x184)) &&
     ((cStack_10 == '\0' || (lVar4 = FUN_00148df0(0,7), lVar4 != 0)))) {
    uVar3 = (long)(iVar2 + 1) & 3;
  }
  if (uVar3 == 3) {
    uStack_30 = *(undefined4 *)(iGpffff8af8 + 0x50);
    uStack_28 = *(undefined4 *)(iGpffff8af8 + 0x58);
    uStack_24 = *(undefined4 *)(iGpffff8af8 + 0x5c);
    uStack_2c = *(undefined4 *)(iGpffff8af8 + 0x154);
    FUN_00128b50(&fStack_14,iGpffff8af8 + 0x150,&uStack_30);
    if (fStack_14 < 420.0) {
      uVar3 = 0;
    }
  }
  if (uVar3 == (long)*(char *)(iGpffff8af8 + 0x184)) {
    *puStack_8 = 0;
  }
  else {
    *puStack_8 = 1;
  }
  return (char)uVar3;
}

