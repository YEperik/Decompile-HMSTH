
undefined4 FUN_001c31f0(byte param_1)

{
  ulong uVar1;
  undefined4 uVar2;
  float fVar3;
  
  if (*(byte *)((uint)param_1 * 0x20 + 0x859f28) < 0x5a) {
    uVar2 = 6;
  }
  else if (*(byte *)((uint)param_1 * 0x20 + 0x859f28) < 0x96) {
    uVar2 = 7;
  }
  else if (*(byte *)((uint)param_1 * 0x20 + 0x859f28) < 0xdc) {
    uVar2 = 8;
  }
  else {
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 4) == 4) {
      uVar1 = FUN_00148df0(0,999999);
      if ((long)uVar1 < 0) {
        fVar3 = (float)(uVar1 & 0xffffffff);
      }
      else {
        fVar3 = (float)(int)uVar1;
      }
      if (fVar3 / 10000.0 <= 25.0) {
        return 9;
      }
    }
    uVar2 = 8;
  }
  return uVar2;
}

