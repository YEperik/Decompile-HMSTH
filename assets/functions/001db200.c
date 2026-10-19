
void FUN_001db200(void)

{
  long lVar1;
  
  lVar1 = FUN_001df5e0();
  if (lVar1 != 0) {
    FUN_001532e0();
    if (*(char *)((int)puRam002679ec + 0x51) == '\0') {
      *puRam002679ec = puRam002679ec[1];
    }
    else {
      FUN_001dc7d0();
      *(undefined1 *)((int)puRam002679ec + 0x51) = 0;
    }
  }
  return;
}

