
void FUN_001d36d0(void)

{
  undefined1 uVar1;
  long lVar2;
  
  *(undefined1 *)(iRam002679e8 + 0x1b9) = 0;
  FUN_001d5770();
  lVar2 = FUN_0012e170(0,0x40);
  if (lVar2 != 0) {
    FUN_001d8f20(*(undefined1 *)(iRam002679e8 + 0x10c),0x5a);
    *(undefined1 *)(iRam002679e8 + 0x10b) = 1;
    *(undefined2 *)(iRam002679e8 + 0x1ac) = 0;
    *(undefined1 *)(iRam002679e8 + 0x1b9) = 2;
  }
  lVar2 = FUN_0012e120(0,0x40);
  if (((lVar2 == 0) && (*(char *)(iRam002679e8 + 0x10b) != '\0')) &&
     (*(undefined1 *)(iRam002679e8 + 0x10b) = 0, *(char *)(iRam002679e8 + 0x10d) != '\x01')) {
    FUN_001d8f20(*(undefined1 *)(iRam002679e8 + 0x10c),0x55);
  }
  if (*(char *)(iRam002679e8 + 0x10b) != '\0') {
    FUN_001d92f0(0x40000000);
  }
  uVar1 = FUN_001d7670(0x41f00000,*(undefined4 *)(iRam002679e8 + 0x1a0),0x32d,iRam002679e8 + 0x90,
                       iRam002679e8 + 0xa0,iRam002679e8 + 0x80,0);
  *(undefined1 *)(iRam002679e8 + 0x1ab) = uVar1;
  FUN_001d7c60();
  FUN_001d9000();
  return;
}

