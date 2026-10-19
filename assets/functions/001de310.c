
void FUN_001de310(ushort param_1,byte param_2)

{
  short sVar1;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  ushort uStack_10;
  byte bStack_8;
  
  uStack_60 = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80dd90);
  uStack_5c = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80dd94);
  uStack_50 = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80ddb0);
  uStack_4c = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80ddb4);
  uStack_40 = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80ddc0);
  uStack_3c = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80ddc4);
  uStack_30 = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80dda0);
  uStack_2c = *(undefined4 *)(((uint)param_1 * 0x12 + (uint)param_1) * 0x10 + 0x80dda4);
  bStack_8 = param_2 & 3;
  uStack_10 = param_1;
  for (sVar1 = 0; sVar1 < (short)(ushort)bStack_8; sVar1 = sVar1 + 1) {
    uStack_20 = uStack_60;
    uStack_1c = uStack_5c;
    uStack_18 = uStack_58;
    uStack_14 = uStack_54;
    FUN_00116870(&uStack_60,&uStack_50,0x30);
    uStack_30 = uStack_20;
    uStack_2c = uStack_1c;
    uStack_28 = uStack_18;
    uStack_24 = uStack_14;
  }
  FUN_001de840(uStack_10,&uStack_60,&uStack_30,&uStack_50,&uStack_40);
  return;
}

