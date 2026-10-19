
void FUN_001cfe40(void)

{
  short sVar1;
  long lVar2;
  
  FUN_001d1970();
  sVar1 = puGpffff8af8[0x89];
  puGpffff8af8[0x89] = sVar1 + 1;
  if (0x28 < (short)(sVar1 + 1)) {
    FUN_00139a20();
    puGpffff8af8[0x89] = 0x28;
  }
  lVar2 = FUN_0012e120(0,0x40);
  if (lVar2 == 0) {
    FUN_00124180(uRam00834058,puGpffff8af8 + 0x28);
    FUN_00218ea0(0x5f);
    if ((short)puGpffff8af8[0x89] < 0x14) {
      *puGpffff8af8 = 2;
      FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x55);
    }
    else {
      FUN_001d2160();
      FUN_00139a20();
      FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x57);
      *puGpffff8af8 = 4;
    }
  }
  return;
}

