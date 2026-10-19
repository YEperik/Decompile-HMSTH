
void FUN_001a4af0(byte param_1,undefined2 param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  ushort *puVar4;
  int iVar5;
  undefined8 unaff_s7;
  undefined1 uStack_30;
  undefined1 uStack_2f;
  undefined1 uStack_2e;
  undefined1 uStack_2d;
  undefined1 uStack_2c;
  undefined1 uStack_2b;
  undefined1 uStack_2a;
  undefined1 auStack_29 [9];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  byte bStack_12;
  byte bStack_11;
  byte bStack_10;
  ushort uStack_8;
  
  if (param_1 == 2) {
    unaff_s7 = 0x17a8700;
  }
  else if (param_1 == 1) {
    unaff_s7 = 0x17a7b80;
  }
  else if (param_1 == 0) {
    unaff_s7 = 0x17a7000;
  }
  bStack_10 = param_1;
  uStack_8 = param_2;
  FUN_00116978(unaff_s7,0,0x800);
  bStack_11 = (char)uStack_8 - (char)uGpffff8a7c;
  uStack_8 = *(ushort *)((uint)bStack_11 * 2 + 0x85a340);
  uStack_20 = 0x1785000;
  uStack_1c = 0x1786000;
  iVar5 = *(int *)((uint)uStack_8 * 4 + 0x1785000);
  uVar3 = 0x80;
  puVar4 = (ushort *)(iVar5 + 0x1786001);
  uVar2 = (uint)*(byte *)(iVar5 + 0x1786000);
  iVar5 = 0;
  do {
    if ((uVar2 & uVar3) == 0) {
      uVar1 = (ushort)(byte)*puVar4;
      puVar4 = (ushort *)((int)puVar4 + 1);
    }
    else {
      uVar1 = *puVar4;
      puVar4 = puVar4 + 1;
    }
    if ((uVar3 & 1) == 0) {
      uVar3 = uVar3 >> 1;
    }
    else {
      uVar3 = 0x80;
      uVar2 = (uint)(byte)*puVar4;
      puVar4 = (ushort *)((int)puVar4 + 1);
    }
    if (0xf < uVar1) {
      FUN_00154e10(uVar1 - 0x10,0x100,0xa02000,(int)unaff_s7 + iVar5 * 8);
      FUN_0011e9e0(bStack_10 + 0xdb);
      FUN_0015bf20((uint)param_1 * 10 + (uint)param_1 + 0x120 + iVar5 & 0xffff);
      iVar5 = iVar5 + 1;
    }
  } while (uVar1 != 2);
  uStack_30 = 0xf9;
  uStack_2f = 0x11;
  uStack_2e = 0x12;
  uStack_2d = 0xff;
  uStack_2c = 0xff;
  uStack_2b = 0xff;
  uStack_2a = 0xff;
  auStack_29[0] = 0xff;
  FUN_00154290((bStack_10 & 0x7f) << 1,&uStack_30);
  uStack_18 = 0x85a390;
  bStack_12 = FUN_001545a0(auStack_29 + 1,*(undefined2 *)((uint)bStack_11 * 2 + 0x85a390));
  FUN_00116978(&uStack_30,0x10,8);
  FUN_001167c0(auStack_29 + -(uint)bStack_12,auStack_29 + 1,bStack_12);
  auStack_29[0] = 0x21;
  FUN_00154290(bStack_10 * '\x02' + '\x01',&uStack_30);
  return;
}

