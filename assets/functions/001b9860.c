
void FUN_001b9860(void)

{
  uint uVar1;
  
  if ((uGpffff8834 & 1) != 1) {
    if ((((uRam00859fe0 & 1) == 1) || ((uRam00859fe0 & 0x80000) == 0x80000)) &&
       ((uRam00835050 & 0x2000) != 0x2000)) {
      if ((cGpffff8844 == cRam0085a004) && (sRam00835058 != -1)) {
        FUN_001b9d10();
      }
      else if ((uRam00859fe0 & 2) == 2) {
        uGpffff8aa4 = 3;
      }
      else {
        uGpffff8aa4 = 0;
      }
    }
    if ((((uRam00859fc0 & 1) == 1) && ((uRam00834050 & 0x80) != 0x80)) &&
       ((uRam00835150 & 0x2000) != 0x2000)) {
      if ((cGpffff8844 == cRam00859fc9) && (sRam00835158 != -1)) {
        FUN_001bada0();
      }
      else if ((uRam00859fc0 & 2) == 2) {
        uGpffff8aa8 = 3;
      }
      else {
        uGpffff8aa8 = 0;
      }
    }
    for (uVar1 = 0; uVar1 < 6; uVar1 = uVar1 + 1 & 0xff) {
      if ((*(uint *)(uVar1 * 0x20 + 0x859e60) & 1) == 1) {
        if ((cGpffff8844 == *(char *)(uVar1 * 0x20 + 0x859e69)) &&
           (*(short *)((uVar1 + 0x1b) * 0x100 + 0x834058) != -1)) {
          if ((*(uint *)(uVar1 * 0x20 + 0x859e60) & 0x800) == 0x800) {
            FUN_001bc3e0(uVar1);
          }
          else {
            FUN_001bba90(uVar1);
          }
        }
        else if ((*(uint *)(uVar1 * 0x20 + 0x859e60) & 2) == 2) {
          (&gp0xffff8108)[uVar1] = 3;
        }
        else {
          (&gp0xffff8108)[uVar1] = 0;
        }
      }
    }
    for (uVar1 = 0; uVar1 < 5; uVar1 = uVar1 + 1 & 0xff) {
      if ((*(uint *)(uVar1 * 0x20 + 0x859f20) & 1) == 1) {
        if ((cGpffff8844 == *(char *)(uVar1 * 0x20 + 0x859f29)) &&
           (*(short *)((uVar1 + 0x12) * 0x100 + 0x834058) != -1)) {
          FUN_001bca40(uVar1);
        }
        else if ((*(uint *)(uVar1 * 0x20 + 0x859e60) & 2) == 2) {
          (&gp0xffff8110)[uVar1] = 3;
        }
        else {
          (&gp0xffff8110)[uVar1] = 0;
        }
      }
    }
    for (uVar1 = 0; uVar1 < 6; uVar1 = uVar1 + 1 & 0xff) {
      if (((*(byte *)(uVar1 * 8 + 0x859930) & 1) == 1) &&
         (*(short *)((uint)*(ushort *)(uVar1 * 8 + 0x859932) * 0x100 + 0x834058) != -1)) {
        FUN_001c7690(uVar1);
      }
    }
  }
  return;
}

