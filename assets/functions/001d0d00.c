
void FUN_001d0d00(void)

{
  long lVar1;
  
  if (*(char *)(puGpffff8af8 + 0xbe) == '\b') {
    lVar1 = FUN_0012e170(0,0x40);
    if (lVar1 != 0) {
      bGpffff896c = bGpffff896c | 4;
      FUN_00149760(0x89);
      *(undefined1 *)(puGpffff8af8 + 0xd5) = 1;
      *puGpffff8af8 = 0x17;
      FUN_001df400();
      FUN_0021a780();
    }
  }
  else {
    lVar1 = FUN_001df5e0();
    if (lVar1 != 0) {
      switch(*(undefined1 *)(puGpffff8af8 + 0xbe)) {
      case 0:
      case 1:
        FUN_00152f40(0,0x10,0x20,0);
        FUN_0013d410();
        FUN_00139920(0,0x12);
        *puGpffff8af8 = 0x11;
        break;
      case 2:
        FUN_00178b90(2);
        FUN_00139920(0,0xe);
        *puGpffff8af8 = 0x16;
        break;
      case 3:
      case 4:
      case 5:
        *puGpffff8af8 = 0x15;
        break;
      case 6:
        bGpffff896c = bGpffff896c | 1;
        FUN_001d1640();
        FUN_00139920(0,0xc);
        *puGpffff8af8 = 0x12;
        break;
      case 7:
        bGpffff896c = bGpffff896c | 2;
        FUN_00139920(0,0xc);
        FUN_001d1640();
        *puGpffff8af8 = 0x12;
      }
    }
  }
  return;
}

