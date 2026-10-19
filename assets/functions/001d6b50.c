
/* WARNING: Removing unreachable block (ram,0x001d6bf8) */

void FUN_001d6b50(void)

{
  ulong uVar1;
  float fVar2;
  
  if ((-1 < *(char *)(iGpffff8af8 + 0x1af)) && (*(float *)(iGpffff8af8 + 0x1a4) <= 64.0)) {
    *(char *)(iGpffff8af8 + 0x1ae) = *(char *)(iGpffff8af8 + 0x1ae) + '\x01';
    if (*(char *)(iGpffff8af8 + 0x1ae) == -1) {
      *(undefined1 *)(iGpffff8af8 + 0x1ae) = 1;
    }
    if (*(char *)(iGpffff8af8 + 0x1b0) == '\x01') {
      if ((uint)*(byte *)(iGpffff8af8 + 0x1ae) % (uint)*(byte *)(iGpffff8af8 + 0x1b2) == 0) {
        uVar1 = FUN_00148df0(0,*(undefined1 *)(iGpffff8af8 + 0x1b1));
        if ((long)uVar1 < 0) {
          fVar2 = (float)(uVar1 & 0xffffffff);
        }
        else {
          fVar2 = (float)(int)uVar1;
        }
        FUN_00120d30(0,0,0,0,sRam0083405a + 0x30);
        FUN_00121840(0,0x3f800000,0,
                     fVar2 / 10.0 +
                     (float)((uint)*(byte *)(iGpffff8af8 + 0x1b4) *
                             (uint)*(byte *)(iGpffff8af8 + 0x1b5) * 2),sRam0083405a + 0x30);
      }
    }
    else if (*(char *)(iGpffff8af8 + 0x1b0) == '\0') {
      FUN_00120d30(0,0,0,0,sRam0083405a + 0x30);
      FUN_00121840(0,0x3f800000,0,
                   (float)((uint)*(byte *)(iGpffff8af8 + 0x1ae) /
                           (uint)*(byte *)(iGpffff8af8 + 0x1b5) << 1),sRam0083405a + 0x30);
      FUN_00120d30(0,0,0,0,sRam0083405a + 0x2f);
      FUN_00121840(0,0x3f800000,0,
                   (float)((uint)*(byte *)(iGpffff8af8 + 0x1ae) /
                          (uint)*(byte *)(iGpffff8af8 + 0x1b5)),sRam0083405a + 0x2f);
      if (*(byte *)(iGpffff8af8 + 0x1b4) < *(byte *)(iGpffff8af8 + 0x1ae)) {
        *(undefined1 *)(iGpffff8af8 + 0x1b0) = 1;
        *(undefined1 *)(iGpffff8af8 + 0x1ae) = 0;
      }
    }
  }
  return;
}

