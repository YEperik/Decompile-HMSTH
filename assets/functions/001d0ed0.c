
void FUN_001d0ed0(void)

{
  long lVar1;
  
  lVar1 = FUN_0012e170(0,0x40);
  if (lVar1 == 0) {
    lVar1 = FUN_0012e170(0,8);
    if (lVar1 == 0) {
      lVar1 = FUN_0012e170(0,0x20);
      if (lVar1 != 0) {
        *puGpffff8af8 = 0x17;
        *(undefined1 *)((int)puGpffff8af8 + 0x1a9) = 1;
      }
    }
    else if (*(byte *)(**(byte **)(puGpffff8af8 + 0xbc) + 0x85a2a0) < 99) {
      FUN_0013d410();
      FUN_00139920(0,0x12);
      FUN_0016bff0(uGpffff8950,1);
      *puGpffff8af8 = 0x11;
    }
    else {
      FUN_00218ea0(3);
    }
  }
  else {
    FUN_001d1790();
    FUN_001d1640();
    FUN_00139920(0,0xc);
    *puGpffff8af8 = 0x12;
  }
  return;
}

