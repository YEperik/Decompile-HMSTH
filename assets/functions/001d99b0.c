
void FUN_001d99b0(void)

{
  if ((*(short *)(iGpffff8af8 + 8) != 0) &&
     (*(short *)(iGpffff8af8 + 0xc) = *(short *)(iGpffff8af8 + 0xc) + -1,
     *(short *)(iGpffff8af8 + 0xc) < 1)) {
    *(undefined2 *)(iGpffff8af8 + 0xc) = *(undefined2 *)(iGpffff8af8 + 0xe);
    *(undefined2 *)(iGpffff8af8 + 0xe) = 0;
    *(undefined2 *)(iGpffff8af8 + 8) = *(undefined2 *)(iGpffff8af8 + 10);
    *(undefined2 *)(iGpffff8af8 + 10) = 0;
    if (1 < *(short *)(iGpffff8af8 + 8)) {
      FUN_0012e2e0(0,(&DAT_00244810)[(*(short *)(iGpffff8af8 + 8) + -2) * 2],
                   (&DAT_00244811)[(*(short *)(iGpffff8af8 + 8) + -2) * 2],
                   *(undefined2 *)(iGpffff8af8 + 0xc));
    }
  }
  return;
}

