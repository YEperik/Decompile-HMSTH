
/* WARNING: Removing unreachable block (ram,0x001d2e68) */
/* WARNING: Removing unreachable block (ram,0x001d2eb0) */

void FUN_001d2d20(float param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  byte *pbVar3;
  short sVar4;
  char cVar5;
  float fStack_24;
  float fStack_1c;
  
  cVar5 = '\0';
  pbVar3 = &DAT_002446b0 + (uint)bRam0085a2f8 * 0x12;
  param_1 = param_1 - 920.0;
  if (1016.0 < param_1) {
    fStack_24 = 1.0;
    fStack_1c = 0.0;
  }
  else if (param_1 < 0.0) {
    fStack_24 = 0.0;
    fStack_1c = 1.0;
  }
  else {
    fStack_24 = param_1 / 1016.0;
    fStack_1c = 1.0 - fStack_24;
  }
  pcVar2 = param_2;
  for (sVar4 = 0; sVar4 < 9; sVar4 = sVar4 + 1) {
    cVar1 = FUN_0011cf88((float)pbVar3[1] * fStack_24 + (float)*pbVar3 * fStack_1c + 0.5);
    *pcVar2 = cVar1;
    cVar5 = cVar5 + *pcVar2;
    pcVar2 = pcVar2 + 1;
    pbVar3 = pbVar3 + 2;
  }
  *param_2 = *param_2 + (-0x80 - cVar5);
  return;
}

