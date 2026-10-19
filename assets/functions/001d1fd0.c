
void FUN_001d1fd0(void)

{
  FUN_0014bd30(**(undefined1 **)(iGpffff8af8 + 0x178));
  uRam00836750 = uRam00836750 & 0xffffffef;
  if (*(char *)(iGpffff8af8 + 0x17c) < '\x03') {
    FUN_00139920(0x27);
  }
  else {
    FUN_00120d30(0x3f800000,0,0x3f800000,0x43870000,uRam0083675a);
    FUN_00139920(0x27,1);
  }
  FUN_00137ae0(*(undefined4 *)(iGpffff8af8 + 0x90),*(undefined4 *)(iGpffff8af8 + 0x94),
               *(undefined4 *)(iGpffff8af8 + 0x98),0x27);
  FUN_00137930(0x68);
  *(undefined4 *)(iGpffff8af8 + 0x144) = 0x42180000;
  FUN_001d2670(iGpffff8af8 + 0x90,iGpffff8af8 + 0x50);
  FUN_001378a0(0x27);
  return;
}

