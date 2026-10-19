
undefined4 FUN_001dd180(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  long lVar3;
  char cStack_1;
  
  uVar1 = uRam002679f0;
  if (cRam00267840 == -1) {
    lVar3 = FUN_001dd8e0(uRam002679f0,&cStack_1);
    if (lVar3 == 0) {
      uVar1 = FUN_001dd6a0(uRam002679f0,&cStack_1);
    }
    if (cStack_1 == -1) {
      uVar2 = 0;
    }
    else {
      uRam00267750 = 6;
      uRam002679f0 = uVar1;
      FUN_00126650();
      FUN_001266a0();
      FUN_00161310();
      FUN_00166ab0();
      FUN_001361f0(0x66,0xffa000,0xa17000);
      FUN_001361f0(0x65,0xffa000,0xa18000);
      FUN_00152ed0(0,0xa18000,0xa17000);
      FUN_0015ae30(0x3f000000,0x3e800000,0x3ec00000,0x3ec00000,0x10f,0x60,0x60);
      FUN_0015bcd0(0x10f,0x32d,0xd3d,0xcf);
      FUN_0015c040(0,0x43200000,0x47c35000,0x10f);
      FUN_0015bf20(0x10f);
      FUN_001dd9b0(uRam002679f0);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

