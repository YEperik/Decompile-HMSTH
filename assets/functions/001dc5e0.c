
uint FUN_001dc5e0(char param_1,char param_2)

{
  int iVar1;
  ulong uVar2;
  
  uVar2 = (long)param_1 & 3;
  iVar1 = (int)uVar2;
  if (((long)param_1 < 0) && (uVar2 != 0)) {
    iVar1 = iVar1 + -4;
  }
  return (uint)('\x03' < param_1) * 0xc + iVar1 + param_2 * 4 & 0xff;
}

