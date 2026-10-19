
void FUN_001c3df0(void)

{
  uint *puVar1;
  uint uVar2;
  
  if ((uRam00859fe0 & 1) == 1) {
    uRam00859fe0 = uRam00859fe0 | 0x20;
  }
  if ((uRam00859fc0 & 1) == 1) {
    uRam00859fc0 = uRam00859fc0 | 0x20;
  }
  for (uVar2 = 0; uVar2 < 6; uVar2 = uVar2 + 1 & 0xff) {
    if ((*(uint *)(uVar2 * 0x20 + 0x859e60) & 1) == 1) {
      puVar1 = (uint *)(uVar2 * 0x20 + 0x859e60);
      *puVar1 = *puVar1 | 0x20;
    }
  }
  for (uVar2 = 0; uVar2 < 5; uVar2 = uVar2 + 1 & 0xff) {
    if ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 1) == 1) {
      puVar1 = (uint *)(uVar2 * 0x20 + 0x859f20);
      *puVar1 = *puVar1 | 0x20;
    }
  }
  return;
}

