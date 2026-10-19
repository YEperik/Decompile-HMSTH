
void FUN_001d6970(undefined1 param_1,byte param_2)

{
  *(undefined1 *)(iGpffff8af8 + 0x1af) = param_1;
  *(undefined1 *)(iGpffff8af8 + 0x1b0) = 1;
  *(undefined1 *)(iGpffff8af8 + 0x1ae) = 0;
  FUN_00120d30(0,0,0,0,sRam0083405a + 0x30);
  FUN_00120d30(0,0,0,0,sRam0083405a + 0x2f);
  *(char *)(iGpffff8af8 + 0x1b1) = (char)((int)(uint)param_2 >> 3) + ' ';
  *(char *)(iGpffff8af8 + 0x1b2) = (char)((int)(0xff - (uint)param_2) >> 5) + '\x03';
  return;
}

