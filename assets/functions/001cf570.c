
void FUN_001cf570(void)

{
  char cVar1;
  long lVar2;
  
  lVar2 = FUN_00123d10(uRam00834058);
  if (lVar2 != 0) {
    FUN_001cdb40(uRam00267840);
    cVar1 = FUN_001df760(uRam00267840);
    FUN_00123bf0(1);
    *(undefined1 *)(puRam002679e4 + 8) = 1;
    if (cVar1 != -1) {
      *puRam002679e4 = 6;
      puRam002679e4[1] = 0xc;
      FUN_00152f40(0,cVar1,0x20,0);
    }
  }
  return;
}

