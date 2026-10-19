
void FUN_001cc550(float param_1,float param_2,undefined4 param_3,byte param_4,undefined1 param_5,
                 int param_6)

{
  int iVar1;
  int iVar2;
  byte abStack_38 [8];
  undefined4 uStack_30;
  byte bStack_28;
  undefined1 uStack_20;
  int iStack_18;
  float fStack_10;
  float fStack_8;
  
  uStack_30 = param_3;
  bStack_28 = param_4;
  uStack_20 = param_5;
  iStack_18 = param_6;
  fStack_10 = param_1;
  fStack_8 = param_2;
  FUN_001547b0(abStack_38,param_3,param_5,param_4);
  for (iVar2 = 0; iVar2 < (int)(uint)bStack_28; iVar2 = iVar2 + 1) {
    if (abStack_38[iVar2] == 0x10) {
      iVar1 = iStack_18 + iVar2 * 0x24;
      *(byte *)(iVar1 + 3) = *(byte *)(iVar1 + 3) & 0xfd;
      FUN_0015bfb0(*(short *)(PTR_DAT_00267038 + 6) +
                   (ushort)*(byte *)(iStack_18 + iVar2 * 0x24 + 1));
    }
    else {
      *(float *)(iStack_18 + iVar2 * 0x24 + 0x18) =
           (fStack_10 + (float)(int)(abStack_38[iVar2] - 0x11) * fStack_8 + 1.0) / 256.0;
      *(float *)(iStack_18 + iVar2 * 0x24 + 0x10) =
           (fStack_10 + (float)(int)(abStack_38[iVar2] - 0x10) * fStack_8) / 256.0;
      iVar1 = iStack_18 + iVar2 * 0x24;
      *(byte *)(iVar1 + 3) = *(byte *)(iVar1 + 3) | 2;
    }
  }
  return;
}

