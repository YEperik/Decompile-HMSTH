
void FUN_001cc310(undefined4 param_1,byte param_2,undefined1 param_3,int param_4,byte param_5,
                 byte param_6,byte param_7,byte param_8)

{
  int iVar1;
  byte abStack_48 [8];
  undefined4 uStack_40;
  byte bStack_38;
  undefined1 uStack_30;
  int iStack_28;
  byte bStack_20;
  byte bStack_18;
  byte bStack_10;
  byte bStack_8;
  
  uStack_40 = param_1;
  bStack_38 = param_2;
  uStack_30 = param_3;
  iStack_28 = param_4;
  bStack_20 = param_5;
  bStack_18 = param_6;
  bStack_10 = param_7;
  bStack_8 = param_8;
  FUN_001547b0(abStack_48,param_1,param_3,param_2);
  for (iVar1 = 0; iVar1 < (int)(uint)bStack_38; iVar1 = iVar1 + 1) {
    if (abStack_48[iVar1] == 0x10) {
      *(undefined1 *)(iStack_28 + iVar1 * 0xc + 4) = 0x3e;
      *(undefined1 *)(iStack_28 + iVar1 * 0xc + 5) = 0x1e;
      *(undefined1 *)(iStack_28 + iVar1 * 0xc + 8) = 1;
      *(undefined1 *)(iStack_28 + iVar1 * 0xc + 9) = 1;
    }
    else {
      *(char *)(iStack_28 + iVar1 * 0xc + 4) =
           (char)((int)((uint)bStack_20 + (abStack_48[iVar1] - 0x11) * (uint)bStack_10 & 0xff) >> 2)
      ;
      *(char *)(iStack_28 + iVar1 * 0xc + 5) = (char)((int)(uint)bStack_18 >> 2);
      *(char *)(iStack_28 + iVar1 * 0xc + 8) = (char)((int)(uint)bStack_10 >> 2);
      *(char *)(iStack_28 + iVar1 * 0xc + 9) = (char)((int)(uint)bStack_8 >> 2);
    }
  }
  return;
}

