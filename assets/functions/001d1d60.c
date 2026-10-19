
void FUN_001d1d60(void)

{
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  uStack_10 = 0;
  uStack_c = 0;
  uStack_8 = 0x3f800000;
  FUN_00158b50(0x442f0000,0x44fa0000,0x32e,0,0xc4d000,0xd4d,0xab,0x10,2,1);
  FUN_001222e0(0x32e);
  FUN_00123e80(0,0,0,0x32e);
  FUN_00122370(0x32e,0xd4d);
  FUN_00122760(0x32e);
  FUN_00122300(0x32e);
  FUN_001223b0(0x32e);
  FUN_00128ab0(&uStack_10,iGpffff8af8 + 0xb0,&uStack_10);
  FUN_00124510(uStack_10,uStack_c,uStack_8,0x3f800000,0x32e);
  FUN_00123f50(*(undefined4 *)(iGpffff8af8 + 0x90),*(undefined4 *)(iGpffff8af8 + 0x94),
               *(undefined4 *)(iGpffff8af8 + 0x98),0x32e);
  FUN_00122680(0,0,0,0x41700000,0x32e);
  FUN_001226f0(0x32e,uRam0083cd30,uRam0083cd3c,uRam0083cd40,uRam0083cd34,uRam0083cd38,uRam0083cd44);
  FUN_001d75a0(0x32e,1,2);
  *(undefined4 *)(iGpffff8af8 + 0x174) = 0x40a95555;
  FUN_00124010((float)(int)*(short *)(*(int *)(iGpffff8af8 + 0x178) + 0x10) / 42.0,0x3f800000,
               (float)(int)*(short *)(*(int *)(iGpffff8af8 + 0x178) + 0x12) / 42.0,0x32e);
  FUN_00123780(0x32e,0x80);
  FUN_00122780(0x32e);
  FUN_001236f0(0x32e);
  FUN_001234c0();
  return;
}

