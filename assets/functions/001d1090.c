
void FUN_001d1090(void)

{
  byte bVar1;
  long lVar2;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  lVar2 = FUN_00123d10(uRam00834058);
  bVar1 = bRam0026773c;
  if (lVar2 != 0) {
    FUN_00124180(*(undefined2 *)((uint)bRam0026773c * 0x100 + 0x834058),&uStack_10);
    FUN_0013c060();
    bRam0026773c = bVar1;
    FUN_00123f50(uStack_10,uStack_c,uStack_8,*(undefined2 *)((uint)bVar1 * 0x100 + 0x834058));
    if (*(char *)(puRam002679e8 + 0xbe) < '\x03') {
      FUN_0013dc60(0x43000000,0x41a00000,0x40400000,0,0x27);
    }
    else {
      FUN_0013dc60(0x43b80000,0x41f00000,0x40400000,0,0x27);
      *(undefined1 *)((int)puRam002679e8 + 0x189) = 0;
    }
    *puRam002679e8 = 0x13;
    puRam002679e8[1] = 0;
  }
  return;
}

