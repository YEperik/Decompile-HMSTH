
void FUN_001d1c00(void)

{
  undefined8 uVar1;
  
  if (cGpffff8954 == '[') {
    *(undefined1 *)(iGpffff8af8 + 0x10c) = 2;
  }
  else if (cGpffff8954 == '\\') {
    *(undefined1 *)(iGpffff8af8 + 0x10c) = 3;
  }
  else {
    *(undefined1 *)(iGpffff8af8 + 0x10c) = 1;
  }
  uVar1 = FUN_0014c100(0x67);
  FUN_001361f0(uVar1,0xffa000,0x1ad51c0);
  uVar1 = FUN_0014c130(0x67);
  FUN_00137200(0x68,0x32d,0xd3d,uVar1,0,0,0x1ad51c0);
  FUN_00139920(0x68);
  FUN_001d8f20(*(undefined1 *)(iGpffff8af8 + 0x10c),0x55);
  FUN_0013a620(0x68,1,2);
  uRam0083a850 = uRam0083a850 & 0xffffffef;
  FUN_0013a3e0(0,0x41700000,0,0x41700000,0x68,1);
  return;
}

