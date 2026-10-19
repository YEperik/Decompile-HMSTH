
void FUN_001d0210(void)

{
  char cVar1;
  
  puRam002679e8[1] = puRam002679e8[1] + 1;
  cVar1 = FUN_0011d018(*(float *)(puRam002679e8 + 0xba) * (float)(int)(short)puRam002679e8[1]);
  FUN_00123780(0x32e,-0x80 - cVar1);
  FUN_00122780(0x32e);
  if (0x17 < (short)puRam002679e8[1]) {
    FUN_00123780(0x32e,1);
    *puRam002679e8 = 7;
  }
  return;
}

