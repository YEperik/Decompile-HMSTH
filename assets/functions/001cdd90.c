
undefined4 FUN_001cdd90(void)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  undefined4 uVar4;
  short sVar5;
  
  bVar3 = 0;
  bVar1 = false;
  sVar5 = 0;
  while( true ) {
    if ((long)*(char *)(iGpffff8af4 + 7) <= (long)sVar5) {
      if (bVar3 < 3) {
        if (bVar3 < 2) {
          if (bVar3 == 0) {
            uVar4 = 0xff;
          }
          else {
            uVar4 = 0x2a;
          }
        }
        else {
          uVar4 = 0x1a;
        }
      }
      else if (bVar1) {
        uVar4 = 0x35;
      }
      else {
        uVar4 = 0x1c;
      }
      return uVar4;
    }
    cVar2 = FUN_001cdc90(*(undefined1 *)(iGpffff8af4 + sVar5 + 8));
    if (cVar2 != -5) break;
    bVar3 = bVar3 + *(char *)(iGpffff8af4 + sVar5 + 8) + -5;
    if (*(char *)(iGpffff8af4 + sVar5 + 8) == '\t') {
      bVar1 = true;
    }
    sVar5 = sVar5 + 1;
  }
  return 0xff;
}

