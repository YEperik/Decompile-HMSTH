
void FUN_001d02d0(void)

{
  long lVar1;
  
  FUN_001d36d0();
  lVar1 = FUN_0012e170(0,0x20);
  if ((lVar1 != 0) || (*(float *)(iRam002679e8 + 0x1a0) + *(float *)(iRam002679e8 + 0x1a4) <= 320.0)
     ) {
    FUN_001d7070();
  }
  else if ((long)(int)((uint)*(byte *)(iRam002679e8 + 0x10c) * 0xb4) <
           (long)*(short *)(iRam002679e8 + 0x1ac)) {
    FUN_001d8880();
  }
  else {
    FUN_001d3c20();
  }
  return;
}

