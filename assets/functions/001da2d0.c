
void FUN_001da2d0(void)

{
  char cVar1;
  long lVar2;
  
  cVar1 = FUN_001da8f0();
  if (cVar1 == '\0') {
    *(undefined1 *)((int)puRam002679ec + 5) = *(undefined1 *)(puRam002679ec + 0x15);
    FUN_001dbc70((int)puRam002679ec + 5,puRam002679ec + 5);
    FUN_001dbfc0(1);
    lVar2 = FUN_0012e170(0,0x100);
    if (lVar2 == 0) {
      lVar2 = FUN_0012e170(0,0x20);
      if (lVar2 == 0) {
        lVar2 = FUN_0012e170(0,0x40);
        if (lVar2 != 0) {
          FUN_00218ea0();
          FUN_001dcb80(5);
        }
      }
      else {
        FUN_00218ea0(1);
        FUN_001df370();
        *puRam002679ec = 9;
      }
    }
    else {
      FUN_00218ea0();
      FUN_001dc690(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5));
    }
  }
  FUN_001dc400();
  FUN_001dc4d0();
  return;
}

