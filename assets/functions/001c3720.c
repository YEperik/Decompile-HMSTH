
void FUN_001c3720(byte param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if (param_1 == 0x73) {
    if (bRam00267824 < 0x15) {
      FUN_0016cc90(0x83,0x20);
    }
    else {
      FUN_0016cc90(0x88,0x20);
    }
    iVar1 = 5;
  }
  else if (param_1 == 0x72) {
    if (bRam00267823 < 0x15) {
      FUN_0016cc90(0x83,0x20);
    }
    else {
      FUN_0016cc90(0x87,0x20);
    }
    iVar1 = 4;
  }
  else if (param_1 == 0x71) {
    if (bRam00267822 < 0x15) {
      FUN_0016cc90(0x83,0x20);
    }
    else {
      FUN_0016cc90(0x86,0x20);
    }
    iVar1 = 3;
  }
  else if (param_1 == 0x70) {
    if (bRam00267821 < 0x15) {
      FUN_0016cc90(0x83,0x20);
    }
    else {
      FUN_0016cc90(0x85,0x20);
    }
    iVar1 = 2;
  }
  else if (param_1 == 0x6f) {
    if (bRam00267820 < 0x15) {
      FUN_0016cc90(0x83,0x20);
    }
    else {
      FUN_0016cc90(0x84,0x20);
    }
    iVar1 = 1;
  }
  else if (param_1 == 0x12) {
    FUN_0016cc90(0x89,0x20);
    iVar1 = 0;
  }
  if (((bRam002678cc & 8) == 8) && ((*(byte *)(iVar1 + 0x267898) & 8) != 8)) {
    FUN_001c3390(param_1);
    FUN_001ff4f0(0,0x43200000,0,0x11,0,*(undefined2 *)((uint)param_1 * 0x100 + 0x834058));
    *(byte *)(iVar1 + 0x267898) = *(byte *)(iVar1 + 0x267898) | 8;
  }
  return;
}

