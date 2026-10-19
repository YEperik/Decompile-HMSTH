
void FUN_001cf430(void)

{
  char cVar1;
  long lVar2;
  
  lVar2 = FUN_00123d60(1);
  if (lVar2 == 0) {
    FUN_001ff950();
    FUN_001ce7b0(0x267840);
    FUN_00123950(1,(uint)*(byte *)(puRam002679e4 + 2) * 2 + 0x15);
    cVar1 = *(char *)(puRam002679e4 + 2);
    if (cVar1 == '\x02') {
      FUN_00218ea0(0x67);
    }
    else if (cVar1 == '\x01') {
      FUN_00218fc0(100);
    }
    else if (cVar1 == '\0') {
      FUN_00218fc0(0x62);
    }
    *puRam002679e4 = 10;
  }
  return;
}

