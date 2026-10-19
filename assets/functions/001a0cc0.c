
void FUN_001a0cc0(void)

{
  long lVar1;
  
  lVar1 = FUN_0015ee20();
  if (lVar1 == 0) {
    if (cGpffff8a60 == '\x01') {
      lVar1 = FUN_0013a2c0();
      if (lVar1 == 0) {
        FUN_00138ce0();
        cGpffff8a60 = -1;
      }
      else {
        lVar1 = FUN_00123d10(uRam00834058);
        if (lVar1 != 0) {
          FUN_00181020();
          FUN_0013ffc0();
          FUN_0013fae0(0,0x1a,2,0,0,0);
        }
      }
    }
    else if (cGpffff8a60 == '\0') {
      if (cRam00833de8 == '\0') {
        FUN_00139920(0,0x28);
        FUN_0018bbb0(0x4f);
        FUN_0016c7b0(0x4f,1);
        cGpffff8a60 = '\x01';
      }
      else {
        FUN_00207cb0();
        uGpffff8860 = 0;
      }
    }
    else {
      cGpffff8a60 = '\0';
      FUN_00166c00();
      uGpffff8860 = 0;
    }
  }
  return;
}

