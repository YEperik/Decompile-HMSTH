
void FUN_001d9810(byte param_1,undefined2 param_2)

{
  if (((bGpffff88bc & 2) == 2) && (param_1 != 0)) {
    *(undefined2 *)(iGpffff8af8 + 8) = 1;
    *(ushort *)(iGpffff8af8 + 10) = (ushort)param_1;
    *(undefined2 *)(iGpffff8af8 + 0xc) = 4;
    *(undefined2 *)(iGpffff8af8 + 0xe) = param_2;
    if ((&DAT_00244811)[(param_1 - 2) * 2] == '\0') {
      if ((&DAT_00244810)[(param_1 - 2) * 2] == '\x01') {
        FUN_0012e2e0(0,(&DAT_00244810)[(param_1 - 2) * 2],0,4);
      }
    }
    else {
      FUN_0012e2e0(0,(&DAT_00244810)[(param_1 - 2) * 2],0xff,4);
    }
  }
  else {
    *(undefined2 *)(iGpffff8af8 + 10) = 0;
    *(undefined2 *)(iGpffff8af8 + 8) = 0;
    *(undefined2 *)(iGpffff8af8 + 0xe) = 0;
    *(undefined2 *)(iGpffff8af8 + 0xc) = 0;
    FUN_0012e2e0();
  }
  return;
}

