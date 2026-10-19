
void FUN_001d0580(void)

{
  FUN_001d40c0();
  FUN_001d3820();
  if ((*(char *)(puRam002679e8 + 0x85) == '\0') ||
     ((long)(int)((uint)*(byte *)(puRam002679e8 + 0x86) * 0xb4) < (long)(short)puRam002679e8[0xd6]))
  {
    FUN_00161310();
    FUN_001d8880();
  }
  else if (*(float *)(puRam002679e8 + 0xd0) + *(float *)(puRam002679e8 + 0xd2) <= 320.0) {
    FUN_001d5670();
    FUN_001d8f20(*(undefined1 *)(puRam002679e8 + 0x86),0x5b);
    *puRam002679e8 = 0xb;
    FUN_00161310();
    FUN_001d1fd0();
    FUN_00218ea0(0x5e);
    FUN_001ff4f0(*(undefined4 *)(puRam002679e8 + 0x48),*(undefined4 *)(puRam002679e8 + 0x4a),
                 *(undefined4 *)(puRam002679e8 + 0x4c),0xb,0,0);
    FUN_00123750(0x32e);
    FUN_001d7db0();
    FUN_001d9810(*(char *)(*(int *)(puRam002679e8 + 0xbc) + 2) + '\x04',0x10);
  }
  return;
}

