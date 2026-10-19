
void FUN_001da7f0(void)

{
  long lVar1;
  
  FUN_001dac90();
  lVar1 = FUN_0012e170(0,0x20);
  if ((lVar1 == 0) &&
     ((lVar1 = FUN_0012e170(0,0x40), lVar1 == 0 || (*(char *)((int)puRam002679ec + 0x29) != '\0'))))
  {
    lVar1 = FUN_0012e170(0,0x40);
    if (lVar1 != 0) {
      FUN_00218ea0();
      FUN_001db900();
      FUN_001dbb00();
      puRam002679ec[1] = 3;
      *puRam002679ec = 3;
    }
  }
  else {
    puRam002679ec[1] = 5;
    *puRam002679ec = 5;
    FUN_00218ea0(1);
    FUN_001dbb00();
  }
  return;
}

