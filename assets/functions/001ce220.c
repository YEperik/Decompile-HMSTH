
void FUN_001ce220(int param_1)

{
  undefined1 uVar1;
  char cVar2;
  short sVar3;
  short sVar4;
  byte bVar5;
  uint uVar6;
  
  for (sVar3 = 0; (long)sVar3 < (long)*(char *)(iRam002679e4 + 7); sVar3 = sVar3 + 1) {
    cVar2 = FUN_001cdc90(*(undefined1 *)(iRam002679e4 + sVar3 + 8));
    if (cVar2 == -1) {
      *(undefined1 *)(param_1 + sVar3) = *(undefined1 *)(iRam002679e4 + sVar3 + 8);
    }
    else {
      *(char *)(param_1 + sVar3) = cVar2;
    }
  }
  for (sVar3 = (short)*(char *)(iRam002679e4 + 7); sVar3 < 3; sVar3 = sVar3 + 1) {
    *(undefined1 *)(param_1 + sVar3) = 0xff;
  }
  for (sVar3 = 0; sVar4 = sVar3, sVar3 < 2; sVar3 = sVar3 + 1) {
    while (sVar4 = sVar4 + 1, sVar4 < 3) {
      if ((*(char *)(param_1 + sVar3) == *(char *)(param_1 + sVar4)) &&
         (*(char *)(param_1 + sVar4) != -1)) {
        *(undefined1 *)(param_1 + sVar4) = 0xff;
      }
    }
  }
  uVar6 = 0;
  while (sVar3 = (short)uVar6, sVar3 < 2) {
    uVar6 = uVar6 & 0xff;
    bVar5 = *(byte *)(param_1 + sVar3);
    sVar4 = sVar3;
    while( true ) {
      sVar4 = sVar4 + 1;
      if (2 < sVar4) break;
      if ((((((0xf9 < bVar5) && (bVar5 != 0xff)) && (0xf9 < *(byte *)(param_1 + sVar4))) &&
           ((*(char *)(param_1 + sVar4) != -1 && (*(byte *)(param_1 + sVar4) < bVar5)))) ||
          (((bVar5 < 0xfa || (bVar5 == 0xff)) &&
           ((0xf9 < *(byte *)(param_1 + sVar4) && (*(char *)(param_1 + sVar4) != -1)))))) ||
         (((bVar5 < 0xfa || (bVar5 == 0xff)) && (*(byte *)(param_1 + sVar4) < bVar5)))) {
        bVar5 = *(byte *)(param_1 + sVar4);
        uVar6 = (int)sVar4 & 0xff;
      }
    }
    uVar1 = *(undefined1 *)(param_1 + uVar6);
    *(undefined1 *)(param_1 + uVar6) = *(undefined1 *)(param_1 + sVar3);
    *(undefined1 *)(param_1 + sVar3) = uVar1;
    uVar6 = (uint)(short)(sVar3 + 1);
  }
  return;
}

