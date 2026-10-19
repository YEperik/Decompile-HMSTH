
void FUN_001cf670(void)

{
  short sVar1;
  char *pcVar2;
  undefined **ppuVar3;
  
  ppuVar3 = &PTR_DAT_00244670;
  for (sVar1 = 1; sVar1 < 3; sVar1 = sVar1 + 1) {
    for (pcVar2 = *ppuVar3; *pcVar2 != -1; pcVar2 = pcVar2 + 4) {
      if (((byte)pcVar2[1] < 0xfa) && ((byte)pcVar2[2] < (byte)pcVar2[1])) {
        pcVar2[2] = pcVar2[2] ^ pcVar2[1];
        pcVar2[1] = pcVar2[1] ^ pcVar2[2];
        pcVar2[2] = pcVar2[2] ^ pcVar2[1];
      }
    }
    ppuVar3 = ppuVar3 + 1;
  }
  return;
}

