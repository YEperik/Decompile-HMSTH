
void FUN_001c9470(byte param_1)

{
  if ((((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 1) == 1) &&
      ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 2) != 2)) &&
     ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x100) != 0x100)) {
    *(undefined4 *)((uint)param_1 * 4 + 0x85a3d0) = 0x45070000;
    (&DAT_00267000)[param_1] = 9;
  }
  return;
}

