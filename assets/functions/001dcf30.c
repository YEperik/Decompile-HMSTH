
void FUN_001dcf30(void)

{
  FUN_0015d1f0(3);
  FUN_0015d1f0(4);
  if ('\0' < *(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc)) {
    FUN_0015cd00((float)(int)*(short *)(&DAT_00244990 + *(char *)(iGpffff8afc + 0x2a) * 8),
                 (float)(int)*(short *)(&DAT_00244992 + *(char *)(iGpffff8afc + 0x2a) * 8),
                 0x47c37200,3);
    FUN_0015d180(3);
  }
  if ((int)*(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc) << 2 <
      (int)(*(byte *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0x10) - 0xc)) {
    FUN_0015cd00((float)(int)*(short *)(&DAT_00244990 + (*(char *)(iGpffff8afc + 0x2a) * 2 + 1) * 4)
                 ,(float)(int)*(short *)(&DAT_00244992 + (*(char *)(iGpffff8afc + 0x2a) * 2 + 1) * 4
                                        ),0x47c37200,4);
    FUN_0015d180(4);
  }
  FUN_0015c1d0(*(short *)(iGpffff8148 + 6) + 1,5);
  FUN_0015c1d0(*(short *)(iGpffff8148 + 6) + 2,5);
  FUN_0015c1d0(*(char *)(iGpffff8afc + 0x2a) + 1 + *(short *)(iGpffff8148 + 6),4);
  return;
}

