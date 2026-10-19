
void FUN_001d6a50(undefined8 param_1,byte param_2)

{
  *(undefined1 *)(iGpffff8af8 + 0x1b0) = 0;
  *(undefined1 *)(iGpffff8af8 + 0x1ae) = 0;
  *(char *)(iGpffff8af8 + 0x1b4) = (char)((int)(uint)param_2 >> 6) + '\b';
  *(undefined1 *)(iGpffff8af8 + 0x1b5) = 1;
  FUN_00120d30(0,0,0,0,sRam0083405a + 0x30);
  FUN_00120d30(0,0,0,0,sRam0083405a + 0x2f);
  *(char *)(iGpffff8af8 + 0x1b1) = (char)((int)(uint)param_2 >> 3) + ' ';
  *(char *)(iGpffff8af8 + 0x1b2) = (char)((int)(0xff - (uint)param_2) >> 5) + '\x03';
  return;
}

