
void FUN_001b7f40(byte param_1,byte param_2,byte param_3)

{
  byte *pbVar1;
  int iVar2;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  byte bStack_18;
  byte bStack_10;
  byte bStack_8;
  
  bStack_18 = param_1;
  bStack_10 = param_2;
  bStack_8 = param_3;
  uStack_50 = DAT_002443d0;
  uStack_4c = DAT_002443d4;
  uStack_48 = DAT_002443d8;
  uStack_44 = DAT_002443dc;
  uStack_40 = DAT_002443e0;
  uStack_3c = DAT_002443e4;
  uStack_38 = DAT_002443e8;
  uStack_34 = DAT_002443ec;
  uStack_30 = DAT_002443f0;
  pbVar1 = (byte *)0x0;
  if (param_1 == 3) {
    pbVar1 = (byte *)((uint)param_3 * 0x20 + 0x859f28);
  }
  else if (param_1 == 2) {
    pbVar1 = (byte *)((uint)param_3 * 0x20 + 0x859e68);
  }
  else if (param_1 == 1) {
    pbVar1 = (byte *)0x859fc8;
  }
  else if (param_1 == 0) {
    pbVar1 = (byte *)0x859ffa;
  }
  if ((((param_1 == 0) && (param_2 != 5)) && (param_2 != 6)) && ((uRam00859fe0 & 4) == 4)) {
    iVar2 = (uint)*pbVar1 + *(char *)((int)&uStack_50 + (uint)param_2) * 2;
  }
  else {
    iVar2 = (uint)*pbVar1 + (int)*(char *)((int)&uStack_50 + (uint)param_2 + (uint)param_1 * 10);
  }
  if (iVar2 < 0x100) {
    if (iVar2 < 0) {
      *pbVar1 = 0;
    }
    else {
      *pbVar1 = (byte)iVar2;
    }
  }
  else {
    *pbVar1 = 0xff;
  }
  return;
}

