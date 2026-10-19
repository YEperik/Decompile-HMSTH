
void FUN_001a2230(void)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  
  FUN_001361f0(0,0x1226000,0xa17000);
  FUN_001361f0(1,0x1226000,0xa18000);
  FUN_00151df0(0x43100000,0x42900000,0x3f480000,0x3dc00000,0x3ec80000,0x3e000000,1,0x1e0,0x752,1);
  FUN_00151ec0(0x43200000,0x42a00000,0x47c34f80,1);
  FUN_00152040(1,0x229,0x799,0x46,1,6,3,0);
  uVar1 = uRam00833f8c;
  fVar2 = (fRam00833f84 - 72.0) + 12.0 + 2.0;
  fVar3 = (fRam00833f88 + 36.0) - 12.0;
  FUN_00152a20(fVar2,fVar3,uRam00833f8c,1);
  FUN_00152ed0(1,0xa18000,0xa17000);
  FUN_00152f40(1,5,0x420);
  FUN_0015cd00((fVar2 - 24.0) - 2.0,(fVar3 - 12.0) - (float)iRam002678e8 * 24.0,uVar1,5);
  FUN_0015c550(5);
  uRam002678e4 = 1;
  return;
}

