
void FUN_001d1430(void)

{
  ushort uVar1;
  long lVar2;
  
  if ((*(char *)(iRam002679e8 + 0x1aa) != '\x01') ||
     ((lVar2 = FUN_001df430(), lVar2 != 0 && (lVar2 = FUN_0021a800(uRam00267734), lVar2 == 0)))) {
    uRam0083d070 = *(undefined1 *)(iRam002679e8 + 0x108);
    FUN_001e0070();
    if (*(char *)(iRam002679e8 + 0x1a9) == '\0') {
      FUN_001d2100();
      FUN_001d8f20(*(undefined1 *)(iRam002679e8 + 0x10c));
    }
    else {
      uRam00267840 = **(undefined1 **)(iRam002679e8 + 0x178);
    }
    FUN_001d8740();
    FUN_00123780(0x32e);
    FUN_001222a0(0x32e);
    FUN_0013e710();
    FUN_001376f0(0x68);
    FUN_001d9810(0,4);
    uRam00267888 = uRam00267888 & 0xffdf;
    FUN_0015e770(*(undefined2 *)(iRam002679e8 + 0x110));
    if (*(char *)(iRam002679e8 + 0x1aa) == '\0') {
      FUN_001612e0();
      FUN_0015e770(*(undefined2 *)(iRam002679e8 + 0x110));
    }
    else {
      FUN_001ff910(8);
      FUN_001ff950();
      FUN_001d8f20(*(undefined1 *)(iRam002679e8 + 0x10c));
      FUN_00137930();
      for (uVar1 = 1; (short)uVar1 < 0x80; uVar1 = uVar1 + 1) {
        FUN_00137930(uVar1 & 0xff);
        FUN_001376f0(uVar1 & 0xff);
      }
      FUN_001fad00(0x13,0x18,0x17);
    }
  }
  return;
}

