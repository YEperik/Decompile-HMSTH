
void FUN_001c9bf0(void)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  
  bVar1 = false;
  bVar2 = true;
  if ((cGpffff8844 == '\0') || (cGpffff8844 == '\x01')) {
    for (uVar3 = 0; uVar3 < 5; uVar3 = uVar3 + 1 & 0xff) {
      if ((*(uint *)(uVar3 * 0x20 + 0x859f20) & 1) == 1) {
        if ((cGpffff8844 == *(char *)(uVar3 * 0x20 + 0x859f29)) &&
           ((*(uint *)(uVar3 * 0x20 + 0x859f20) & 0x80000) != 0x80000)) {
          bVar1 = true;
        }
      }
    }
    if (bVar1) {
      bVar2 = false;
      uRam00859fe0 = uRam00859fe0 | 0x10000000;
      FUN_001c8860();
    }
    else {
      bVar2 = true;
    }
  }
  if (bVar2) {
    uRam00859fe0 = uRam00859fe0 & 0xfffcffff;
    FUN_0013e2a0(0x10);
    if ((uRam00859fe0 & 8) == 8) {
      FUN_00139920(0x10,0x14);
    }
    else {
      FUN_00139920(0x10,0x13);
    }
    uGpffff8aa4 = 1;
  }
  if (cRam00859ffd != -1) {
    cRam00859ffd = cRam00859ffd + '\x01';
  }
  return;
}

