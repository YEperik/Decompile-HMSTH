
void FUN_001d1640(void)

{
  undefined4 uVar1;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_4;
  
  uStack_4 = FUN_001136a0(*(float *)(iRam002679e8 + 0x50) - *(float *)(iRam002679e8 + 0x60),
                          *(float *)(iRam002679e8 + 0x58) - *(float *)(iRam002679e8 + 0x68));
  uVar1 = FUN_001d1bc0(uStack_4,0);
  *(undefined4 *)(iRam002679e8 + 0xf0) = uVar1;
  *(undefined4 *)(iRam002679e8 + 0xf4) = *(undefined4 *)(iRam002679e8 + 0xf0);
  *(undefined4 *)(iRam002679e8 + 0xf8) = 0;
  uStack_20 = FUN_00112f70(*(undefined4 *)(iRam002679e8 + 0xf0));
  uStack_18 = FUN_00112bf8(*(undefined4 *)(iRam002679e8 + 0xf0));
  uStack_1c = 0;
  FUN_00137cc0(0x41800000,0,&uStack_20);
  return;
}

