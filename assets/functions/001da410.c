
void FUN_001da410(void)

{
  char cVar1;
  long lVar2;
  
  cVar1 = FUN_001da8f0();
  if (cVar1 == '\0') {
    *(undefined1 *)(iRam002679ec + 4) = *(undefined1 *)(iRam002679ec + 0x2a);
    FUN_001dbc70(iRam002679ec + 4,iRam002679ec + 0xb);
    FUN_001dbfc0(1,1);
    lVar2 = FUN_0012e170(0,0x100);
    if (lVar2 == 0) {
      lVar2 = FUN_0012e170(0,0x20);
      if (lVar2 != 0) {
        FUN_00218ea0(1);
        FUN_001dc7d0();
        return;
      }
      lVar2 = FUN_0012e170(0,0x40);
      if (lVar2 != 0) {
        if ((*(char *)(iRam002679ec + 10) == *(char *)(iRam002679ec + 0xb)) &&
           (*(char *)(iRam002679ec + 5) == *(char *)(iRam002679ec + 4))) {
          FUN_00218ea0(3);
        }
        else if (*(char *)(iRam002679ec + 5) == *(char *)(iRam002679ec + 4)) {
          FUN_00218ea0();
          FUN_001db4b0();
        }
        else {
          FUN_001db690();
        }
      }
    }
    else {
      FUN_00218ea0();
      FUN_001dc690(*(undefined1 *)(iRam002679ec + 4),*(undefined1 *)(iRam002679ec + 0xb));
    }
  }
  FUN_001dc400();
  FUN_001dc4d0(1);
  return;
}

