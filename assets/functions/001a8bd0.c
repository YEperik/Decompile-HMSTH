
void FUN_001a8bd0(byte param_1)

{
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  undefined1 auStack_20 [7];
  undefined1 auStack_19 [17];
  byte bStack_8;
  
  bVar5 = 0;
  for (bVar4 = 0; bVar6 = bVar5, bVar4 < 5; bVar4 = bVar4 + 1) {
    if (((((*(uint *)((uint)bVar4 * 0x20 + 0x859f20) & 1) == 1) &&
         ((*(uint *)((uint)bVar4 * 0x20 + 0x859f20) & 0x800) != 0x800)) &&
        ((*(uint *)((uint)bVar4 * 0x20 + 0x859f20) & 0x1000) != 0x1000)) &&
       ((*(uint *)((uint)bVar4 * 0x20 + 0x859f20) & 2) != 2)) {
      bVar6 = bVar4;
      if (bVar5 == param_1) break;
      bVar5 = bVar5 + 1;
    }
  }
  if (*(byte *)((uint)bVar6 * 0x20 + 0x859f28) < 100) {
    uVar2 = 3000;
    uVar3 = 0x6b;
  }
  else if (*(byte *)((uint)bVar6 * 0x20 + 0x859f28) < 200) {
    uVar2 = 4000;
    uVar3 = 0x6c;
  }
  else {
    uVar2 = 5000;
    uVar3 = 0x6d;
  }
  bStack_8 = param_1;
  uVar1 = FUN_001545a0(auStack_19 + 1,uVar2);
  FUN_00116978(auStack_20,0x10,8);
  FUN_001167c0(auStack_19 + -(uVar1 & 0xff),auStack_19 + 1,uVar1 & 0xff);
  auStack_19[0] = 0x21;
  FUN_00154290(cGpffff8a88 * '\x02' + '\x01',auStack_20);
  if (bGpffff80b4 != bVar6) {
    FUN_001532e0();
    FUN_00152f40(0,uVar3,0x4220,5);
    bGpffff80b4 = bVar6;
  }
  return;
}

