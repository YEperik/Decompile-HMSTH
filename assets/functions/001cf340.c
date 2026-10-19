
void FUN_001cf340(void)

{
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  puRam002679e4[7] = puRam002679e4[7] + 1;
  if (0x1d < (short)puRam002679e4[7]) {
    *puRam002679e4 = 9;
    if (*(char *)(puRam002679e4 + 2) == '\x01') {
      FUN_00218ea0(100);
    }
    else if (*(char *)(puRam002679e4 + 2) == '\0') {
      FUN_00218ea0(0x62);
    }
    if (*(char *)(puRam002679e4 + 2) != '\x02') {
      FUN_001cd2d0(*(char *)(puRam002679e4 + 2) + '\x01',&uStack_10);
      FUN_001ff4f0(uStack_10,uStack_c,uStack_8,0xd,0,1);
    }
  }
  return;
}

