
void FUN_001c7950(byte param_1)

{
  if ((*(char *)((uint)param_1 * 8 + 0x859935) == '\0') &&
     ((*(uint *)((uint)*(ushort *)((uint)param_1 * 8 + 0x859932) * 0x100 + 0x834050) & 4) != 4)) {
    FUN_001c7510(param_1);
  }
  return;
}

