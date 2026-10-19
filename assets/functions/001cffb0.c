
void FUN_001cffb0(void)

{
  char cVar1;
  
  puGpffff8af8[1] = puGpffff8af8[1] + 1;
  cVar1 = FUN_001d23a0((float)(int)(short)puGpffff8af8[1]);
  if (cVar1 == '\x02') {
    FUN_00218ea0(0x17);
    FUN_001d7070();
  }
  else if (cVar1 == '\x01') {
    FUN_00218ea0(0x25);
    FUN_001d5670();
    *(undefined4 *)(puGpffff8af8 + 0x50) = *(undefined4 *)(puGpffff8af8 + 0x38);
    *(undefined4 *)(puGpffff8af8 + 0x52) = *(undefined4 *)(puGpffff8af8 + 0x3a);
    *(undefined4 *)(puGpffff8af8 + 0x54) = *(undefined4 *)(puGpffff8af8 + 0x3c);
    *(undefined4 *)(puGpffff8af8 + 0x56) = *(undefined4 *)(puGpffff8af8 + 0x3e);
    *(undefined4 *)(puGpffff8af8 + 0x52) = *(undefined4 *)(puGpffff8af8 + 0x4a);
    *(undefined1 *)((int)puGpffff8af8 + 0x10d) = 0;
    *(undefined1 *)(puGpffff8af8 + 0x85) = 0;
    puGpffff8af8[0x87] = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x18b) = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x10b) = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x1ab) = 1;
    *(undefined1 *)((int)puGpffff8af8 + 0x1b9) = 0;
    *(undefined1 *)(puGpffff8af8 + 0xc) = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x19) = 0;
    *(undefined1 *)(puGpffff8af8 + 0xd) = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x1b) = 0;
    *(undefined4 *)(puGpffff8af8 + 0x12) = 0;
    *(undefined4 *)(puGpffff8af8 + 0x14) = 0;
    *(undefined1 *)(puGpffff8af8 + 0xc2) = 0;
    *(undefined4 *)(puGpffff8af8 + 0x16) = 0;
    *(undefined4 *)(puGpffff8af8 + 0xe) = 0;
    *(char *)(puGpffff8af8 + 0xbf) = (*(char *)(puGpffff8af8 + 0x86) + -1) * -8 + ' ';
    puGpffff8af8[0xd6] = 0;
    *(undefined1 *)(puGpffff8af8 + 0xc3) = 0;
    puGpffff8af8[1] = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x1b3) = 0;
    *(undefined1 *)(puGpffff8af8 + 2) = 0;
    *(undefined1 *)((int)puGpffff8af8 + 5) = 0;
    *(undefined1 *)(puGpffff8af8 + 3) = 0;
    *(undefined1 *)(puGpffff8af8 + 8) = 0;
    *(undefined1 *)((int)puGpffff8af8 + 0x11) = 0;
    FUN_00128b50(puGpffff8af8 + 0xd0,puGpffff8af8 + 0x48,puGpffff8af8 + 0x50);
    *(float *)(puGpffff8af8 + 0xd2) = *(float *)(puGpffff8af8 + 0xd0) / 4.0;
    FUN_001d54d0(puGpffff8af8 + 0x40,puGpffff8af8 + 0x48,puGpffff8af8 + 0x50);
    FUN_001d29b0();
    *puGpffff8af8 = 6;
  }
  return;
}

