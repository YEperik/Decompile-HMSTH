
void FUN_001c3f40(void)

{
  uint *puVar1;
  uint uVar2;
  
  uGpffff8acc = 0;
  if ((uRam00859fc0 & 1) == 1) {
    if ((cGpffff8aa8 == '\x05') || ((uRam00859fc0 & 0x20000) == 0x20000)) {
      FUN_001b24b0();
    }
    if ((cGpffff8aa8 == '\a') || ((uRam00859fc0 & 0x80000) == 0x80000)) {
      FUN_001b25d0();
    }
    uRam00859fc0 = uRam00859fc0 & 0xfff1ffff;
    cGpffff8aa8 = '\0';
  }
  for (uVar2 = 0; uVar2 < 5; uVar2 = uVar2 + 1 & 0xff) {
    if ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 1) == 1) {
      if ((((&gp0xffff8110)[uVar2] == '\x06') || ((&gp0xffff8110)[uVar2] == '\x05')) ||
         ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x80000) == 0x80000)) {
        FUN_001b2510(uVar2);
      }
      if (((&gp0xffff8110)[uVar2] == '\a') ||
         ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x200000) == 0x200000)) {
        FUN_001b2b30(uVar2);
      }
      puVar1 = (uint *)(uVar2 * 0x20 + 0x859f20);
      *puVar1 = *puVar1 & 0xfff7ffff;
      puVar1 = (uint *)(uVar2 * 0x20 + 0x859f20);
      *puVar1 = *puVar1 & 0xffdfffff;
      puVar1 = (uint *)(uVar2 * 0x20 + 0x859f20);
      *puVar1 = *puVar1 & 0xffefffff;
      (&gp0xffff8110)[uVar2] = 0;
    }
  }
  return;
}

