
void FUN_001d7c60(void)

{
  undefined1 uVar1;
  
  if ((*(char *)(iGpffff8af8 + 0x1ab) == '\0') &&
     (*(float *)(iGpffff8af8 + 0x1c) != *(float *)(iGpffff8af8 + 0x20))) {
    *(undefined4 *)(iGpffff8af8 + 0x1c) = *(undefined4 *)(iGpffff8af8 + 0x20);
    FUN_001d6f70(0,-*(float *)(iGpffff8af8 + 0x1c),0,iGpffff8af8 + 0xa0);
    uVar1 = FUN_001d7670(0x41f00000,*(undefined4 *)(iGpffff8af8 + 0x1a0),0x32d,iGpffff8af8 + 0x90,
                         iGpffff8af8 + 0xa0,iGpffff8af8 + 0x80,0);
    *(undefined1 *)(iGpffff8af8 + 0x1ab) = uVar1;
  }
  return;
}

