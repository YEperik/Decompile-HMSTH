
void FUN_001d03a0(void)

{
  long lVar1;
  
  FUN_001d4cf0();
  lVar1 = FUN_00123d60(uRam00834058);
  if (lVar1 == 0) {
    if (*(char *)((int)puRam002679e8 + 0x1b3) == '\0') {
      *puRam002679e8 = 9;
    }
    else {
      *puRam002679e8 = 10;
      *(undefined1 *)((int)puRam002679e8 + 0x17f) = 5;
      FUN_001d40e0();
    }
    lVar1 = FUN_0012e120(0,0x40);
    if (lVar1 == 0) {
      FUN_001d8f20(*(undefined1 *)(puRam002679e8 + 0x86),0x55);
      *(undefined1 *)((int)puRam002679e8 + 0x10b) = 0;
    }
    else {
      FUN_001d8f20(*(undefined1 *)(puRam002679e8 + 0x86),0x5a);
      *(undefined1 *)((int)puRam002679e8 + 0x10b) = 1;
    }
  }
  return;
}

