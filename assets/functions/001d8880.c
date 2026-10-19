
void FUN_001d8880(void)

{
  float afStack_10 [2];
  float fStack_8;
  
  *(undefined1 *)((int)puGpffff8af8 + 0x17f) = 7;
  FUN_001d40e0();
  puGpffff8af8[0xc0] = 0x78;
  *puGpffff8af8 = 0xe;
  puGpffff8af8[1] = 0x18;
  FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x59);
  FUN_00218ea0(0x25);
  FUN_001ff4f0(*(undefined4 *)(puGpffff8af8 + 0x48),*(undefined4 *)(puGpffff8af8 + 0x4a),
               *(undefined4 *)(puGpffff8af8 + 0x4c),0xb);
  FUN_0013a620(0x68);
  *(undefined4 *)(puGpffff8af8 + 0xa2) = 0x41f00000;
  *(undefined4 *)(puGpffff8af8 + 0x9c) = 0x42700000;
  *(undefined4 *)(puGpffff8af8 + 0x98) = 0;
  *(undefined4 *)(puGpffff8af8 + 0x9e) = 0x3dd65b7b;
  FUN_001d54d0(afStack_10,puGpffff8af8 + 0x50,puGpffff8af8 + 0x48);
  *(float *)(puGpffff8af8 + 0xa4) = (afStack_10[0] * 40.0) / 30.0;
  *(float *)(puGpffff8af8 + 0xa6) = (fStack_8 * 40.0) / 30.0;
  return;
}

