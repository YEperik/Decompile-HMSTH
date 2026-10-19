
void FUN_001b9720(byte param_1)

{
  uint *puVar1;
  
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 & 0xffdfffff;
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 & 0xfffffdff;
  puVar1 = (uint *)((uint)param_1 * 0x100 + 0x834050);
  *puVar1 = *puVar1 & 0xfffffffb;
  *(undefined2 *)((uint)param_1 * 0x100 + 0x834098) = 0;
  *(undefined2 *)((uint)param_1 * 0x100 + 0x8340a6) = 0;
  if (param_1 == 0x10) {
    if ((uRam00859fe0 & 0x4000) != 0x4000) {
      uRam00859fe0 = uRam00859fe0 | 0x8000;
    }
  }
  else if (param_1 == 0x11) {
    uRam00859fc0 = uRam00859fc0 | 0x10000;
  }
  return;
}

