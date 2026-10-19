
void FUN_001dbfc0(char param_1,char param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  undefined1 auStack_18 [4];
  char *pcStack_14;
  char cStack_10;
  char cStack_8;
  
  cStack_10 = param_1;
  cStack_8 = param_2;
  FUN_001cc7a0(7);
  FUN_001cc7a0(10);
  if (cStack_10 != '\0') {
    bVar1 = FUN_001dc230(*(undefined1 *)(iGpffff8afc + 5),*(undefined1 *)(iGpffff8afc + 10),
                         auStack_18,&pcStack_14);
    if ((bVar1 != 0xff) && (*pcStack_14 != -1)) {
      bVar2 = FUN_001dfbb0(*(undefined1 *)(iGpffff8afc + *(char *)(iGpffff8afc + 5) + 0x12),
                           *pcStack_14);
      if (1 < bVar2) {
        FUN_001cc7d0((float)(*(short *)(&DAT_00244930 + (uint)bVar1 * 4) + -0xc),
                     (float)(*(short *)(&DAT_00244932 + (uint)bVar1 * 4) + -0x16),0x47c35100,7,bVar2
                    );
      }
    }
  }
  if (cStack_8 != '\0') {
    uVar3 = FUN_001dc230(*(undefined1 *)(iGpffff8afc + 4),*(undefined1 *)(iGpffff8afc + 0xb),
                         auStack_18,&pcStack_14);
    if (*pcStack_14 != -1) {
      bVar1 = FUN_001dfbb0(*(undefined1 *)(iGpffff8afc + *(char *)(iGpffff8afc + 4) + 0x12),
                           *pcStack_14);
      if (1 < bVar1) {
        FUN_001cc7d0((float)(*(short *)(&DAT_00244930 + (uVar3 & 0xff) * 4) + -0xc),
                     (float)(*(short *)(&DAT_00244932 + (uVar3 & 0xff) * 4) + -0x16),0x47c35100,10,
                     bVar1);
      }
    }
  }
  return;
}

