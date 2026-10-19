
/* WARNING: Removing unreachable block (ram,0x001d7f00) */

void FUN_001d7e60(void)

{
  ushort uVar1;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_8 = 0.0;
  uStack_4 = 0.0;
  if (*(char *)(iGpffff8af8 + 0x1b7) != '\0') {
    uVar1 = *(byte *)(iGpffff8af8 + 0x1b7) - 1;
    *(char *)(iGpffff8af8 + 0x1b6) = *(char *)(iGpffff8af8 + 0x1b6) + '\x10';
    uStack_c = (float)FUN_00112f70(((float)*(byte *)(iGpffff8af8 + 0x1b6) * 3.14) / 256.0);
    uStack_c = uStack_c * 12.0;
    if (1 < (short)uVar1) {
      uStack_c = -uStack_c;
    }
    if ((uVar1 & 1) == 0) {
      uStack_8 = -uStack_c;
    }
    else {
      uStack_4 = uStack_c;
    }
    FUN_001d7ff0(uStack_8,uStack_4,(char)uVar1);
  }
  return;
}

