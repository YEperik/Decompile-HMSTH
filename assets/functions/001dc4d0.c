
void FUN_001dc4d0(char param_1)

{
  uint uVar1;
  undefined1 auStack_18 [4];
  undefined1 auStack_14 [12];
  char cStack_8;
  
  cStack_8 = param_1;
  FUN_001de160(3,1);
  if (cStack_8 != '\0') {
    uVar1 = FUN_001dc230(*(undefined1 *)(iRam002679ec + 5),*(undefined1 *)(iRam002679ec + 10),
                         auStack_14,auStack_18);
    uVar1 = uVar1 & 0xff;
    if (uVar1 != 0xff) {
      FUN_0015c040((float)(int)*(short *)(&DAT_00244930 + uVar1 * 4),
                   (float)(int)*(short *)(&DAT_00244932 + uVar1 * 4),0x47c37180,
                   *(short *)(PTR_DAT_00267038 + 6) + 3);
      FUN_0015bf20(*(short *)(PTR_DAT_00267038 + 6) + 3);
    }
  }
  return;
}

