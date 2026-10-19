
/* WARNING: Removing unreachable block (ram,0x001d3c50) */

void FUN_001d3c20(void)

{
  undefined2 uVar1;
  short sVar2;
  long lVar3;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_8;
  float fStack_4;
  
  fStack_4 = ((float)*(byte *)((int)puGpffff8af8 + 7) * 80.0) / 2.0;
  uStack_20 = *(undefined4 *)(puGpffff8af8 + 0xa8);
  uStack_18 = *(undefined4 *)(puGpffff8af8 + 0xac);
  uStack_14 = *(undefined4 *)(puGpffff8af8 + 0xae);
  uStack_1c = *(undefined4 *)(puGpffff8af8 + 0x4a);
  FUN_00128b50(&fStack_8,&uStack_20,puGpffff8af8 + 0x48);
  FUN_001d4cf0();
  if (*(char *)((int)puGpffff8af8 + 0x10d) == '\0') {
    if (('\x01' < *(char *)(puGpffff8af8 + 0xbf)) && (*(char *)(puGpffff8af8 + 3) != '\0')) {
      *(char *)(puGpffff8af8 + 0xbf) = *(char *)(puGpffff8af8 + 0xbf) + -1;
    }
    if ((fStack_8 < fStack_4) && (lVar3 = FUN_001d89f0(), lVar3 != 0)) {
      FUN_001d7e00(1);
      if (*(char *)((int)puGpffff8af8 + 0x17d) == '\0') {
        *(undefined1 *)((int)puGpffff8af8 + 0x10d) = 2;
      }
      else {
        *(undefined1 *)((int)puGpffff8af8 + 0x10d) = 1;
        uVar1 = FUN_0011cf88((float)(7 - *(char *)((int)puGpffff8af8 + 0x17d)) * 10.0 + 60.0);
        puGpffff8af8[0x87] = uVar1;
      }
      FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x58);
      *(undefined1 *)((int)puGpffff8af8 + 0x17f) = 1;
      FUN_001d40e0();
    }
  }
  else {
    sVar2 = 1;
    if (*(char *)((int)puGpffff8af8 + 0x17d) < '\x04') {
      sVar2 = FUN_00148df0(0,(*(char *)((int)puGpffff8af8 + 0x17d) + 1) *
                             (int)*(char *)(puGpffff8af8 + 0xbf) * 0x400);
    }
    if ((((*(byte *)(puGpffff8af8 + 3) & 0x40) == 0) || (lVar3 = FUN_001d8c30(), lVar3 == 0)) &&
       (sVar2 != 0)) {
      puGpffff8af8[0x87] = puGpffff8af8[0x87] + -1;
      if ((((short)puGpffff8af8[0x87] < 0) && (*(char *)((int)puGpffff8af8 + 0x10d) == '\x01')) ||
         ((80.0 < fStack_8 && (fStack_4 < fStack_8)))) {
        *(undefined1 *)((int)puGpffff8af8 + 0x10d) = 0;
        if (*(char *)((int)puGpffff8af8 + 0x10b) == '\0') {
          FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x55);
        }
        else {
          FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x5a);
        }
        *(undefined1 *)((int)puGpffff8af8 + 0x17f) = 3;
        *(char *)(puGpffff8af8 + 0xbf) = *(char *)(puGpffff8af8 + 0xbf) + '\x10';
        FUN_001d40e0();
        FUN_001d9810(0,0x10);
        FUN_001d7db0();
      }
    }
    else {
      *(undefined1 *)(puGpffff8af8 + 0x85) = 1;
      *(undefined1 *)((int)puGpffff8af8 + 0x17f) = 2;
      FUN_001d40e0();
      *(float *)(puGpffff8af8 + 200) =
           (float)((uint)*(byte *)((int)puGpffff8af8 + 7) *
                   (*(byte *)(*(int *)(puGpffff8af8 + 0xbc) + 3) + 0x1e) + 0x5a);
      if ((*(byte *)(puGpffff8af8 + 3) & 0x40) == 0) {
        *puGpffff8af8 = 9;
      }
      else {
        FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x59);
        FUN_001d9810(*(char *)(*(int *)(puGpffff8af8 + 0xbc) + 2) + '\x01',0x1e);
        *puGpffff8af8 = 8;
      }
    }
  }
  return;
}

