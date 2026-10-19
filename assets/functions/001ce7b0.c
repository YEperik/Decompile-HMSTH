
undefined4 FUN_001ce7b0(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  char acStack_14 [12];
  char *pcStack_8;
  
  *param_1 = -1;
  if (*(char *)(iRam002679e4 + 7) == '\0') {
    uVar2 = 0xff;
  }
  else {
    pcStack_8 = param_1;
    FUN_001ce220(acStack_14);
    cVar1 = FUN_001ce040(acStack_14);
    *pcStack_8 = cVar1;
    if (cVar1 == -1) {
      if (*(char *)(iRam002679e4 + 4) == '\x01') {
        if (acStack_14[0] == -3) {
          cVar1 = FUN_001cdf00();
          *pcStack_8 = cVar1;
          if (cVar1 != -1) {
            return 1;
          }
        }
        if (acStack_14[0] == -5) {
          cVar1 = FUN_001cdd90();
          *pcStack_8 = cVar1;
          if (cVar1 != -1) {
            return 1;
          }
        }
      }
      cVar1 = FUN_001ce6c0(*(undefined1 *)(iRam002679e4 + 4),acStack_14);
      *pcStack_8 = cVar1;
      if (cVar1 == -1) {
        cVar1 = FUN_001ce940(*(undefined1 *)(iRam002679e4 + 4),acStack_14);
        *pcStack_8 = cVar1;
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

