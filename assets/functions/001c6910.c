
void FUN_001c6910(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ulong uVar3;
  undefined8 uVar4;
  int iVar5;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined2 uStack_6;
  undefined2 uStack_4;
  byte bStack_1;
  
  if ((((cGpffff8944 == '\0') && (cRam0085a2f7 == '\x01')) &&
      (((0x11 < bRam0085a2f5 && (bRam0085a2f5 < 0x18)) || (bRam0085a2f5 == 0)))) &&
     ((uVar3 = FUN_00148df0(0,99), uVar3 < 0x32 &&
      (FUN_001c72b0(&bStack_1,&uStack_6,&uStack_4), bStack_1 != 0xff)))) {
    FUN_001c5940(bStack_1,uStack_6,uStack_4,200,0x17ac000);
    FUN_00123930(0xbf800000,*(undefined2 *)((uint)bStack_1 * 0x100 + 0x834058));
    if (cGpffff8844 == '\b') {
      uVar1 = FUN_00148df0(10,0x2d);
      uVar2 = FUN_00148df0(0x1b,0x30);
      FUN_0014fe50(uVar1,uVar2,&uStack_20);
      uStack_1c = 0x43000000;
    }
    else if (cGpffff8844 == '\t') {
      uVar3 = FUN_00148df0(0,99);
      if (uVar3 < 0x32) {
        uVar1 = FUN_00148df0(7,0xc);
        uVar2 = FUN_00148df0(6,0x13);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uVar1 = FUN_00148df0(0x14,0x1e);
        uVar2 = FUN_00148df0(0x18,0x28);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43000000;
      }
    }
    else if (cGpffff8844 == '\x06') {
      uVar3 = FUN_00148df0(0,99);
      if (uVar3 < 0x32) {
        uVar1 = FUN_00148df0(0xd,0x1a);
        uVar2 = FUN_00148df0(4,0x1d);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uVar1 = FUN_00148df0(1,9);
        uVar2 = FUN_00148df0(0x11,0x1c);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43200000;
      }
    }
    else if (cGpffff8844 == '\x05') {
      uVar3 = FUN_00148df0(0,99);
      if (uVar3 < 0x32) {
        uVar1 = FUN_00148df0(8,0xe);
        uVar2 = FUN_00148df0(0x10,0x1c);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uVar1 = FUN_00148df0(0x1b,0x20);
        uVar2 = FUN_00148df0(0xe,0x19);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43200000;
      }
    }
    else if (cGpffff8844 == '\x04') {
      uVar3 = FUN_00148df0(0,99);
      if (uVar3 < 0x32) {
        uVar1 = FUN_00148df0(0xb,0x12);
        uVar2 = FUN_00148df0(5,0x19);
        FUN_0014fe50(uVar1,uVar2,&uStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        FUN_00148df0(0x16,0x1c);
        FUN_00148df0(0x1a,0x20);
        uStack_1c = 0x43bb0000;
      }
    }
    FUN_00137ae0(uStack_20,uStack_1c,uStack_18,bStack_1);
    FUN_001378a0(bStack_1);
    FUN_00139920(bStack_1,1);
    iVar5 = (uint)bStack_1 * 0x100;
    *(undefined4 *)(iVar5 + 0x8340d0) = uStack_20;
    *(undefined4 *)(iVar5 + 0x8340d4) = uStack_1c;
    *(undefined4 *)(iVar5 + 0x8340d8) = uStack_18;
    *(undefined4 *)(iVar5 + 0x8340dc) = uStack_14;
    *(undefined4 *)((uint)bStack_1 * 0x100 + 0x8340e0) = 0x43800000;
    *(undefined4 *)((uint)bStack_1 * 0x100 + 0x8340e4) = 0x42800000;
    *(undefined4 *)((uint)bStack_1 * 0x100 + 0x8340e8) = 0x43800000;
    uVar4 = FUN_0011d018(*(undefined4 *)((uint)bStack_1 * 0x100 + 0x8340e0));
    uVar3 = FUN_00148df0(0,uVar4);
    if ((long)uVar3 < 0) {
      fStack_30 = (float)(uVar3 & 0xffffffff);
    }
    else {
      fStack_30 = (float)(int)uVar3;
    }
    uVar4 = FUN_0011d018(*(undefined4 *)((uint)bStack_1 * 0x100 + 0x8340e4));
    uVar3 = FUN_00148df0(0,uVar4);
    if ((long)uVar3 < 0) {
      fStack_2c = (float)(uVar3 & 0xffffffff);
    }
    else {
      fStack_2c = (float)(int)uVar3;
    }
    uVar4 = FUN_0011d018(*(undefined4 *)((uint)bStack_1 * 0x100 + 0x8340e8));
    uVar3 = FUN_00148df0(0,uVar4);
    if ((long)uVar3 < 0) {
      fStack_28 = (float)(uVar3 & 0xffffffff);
    }
    else {
      fStack_28 = (float)(int)uVar3;
    }
    uVar3 = FUN_00148df0(0,99);
    if (uVar3 < 0x32) {
      fStack_30 = fStack_30 + *(float *)((uint)bStack_1 * 0x100 + 0x8340d0);
    }
    else {
      fStack_30 = *(float *)((uint)bStack_1 * 0x100 + 0x8340d0) - fStack_30;
    }
    uVar3 = FUN_00148df0(0,99);
    if (uVar3 < 0x32) {
      fStack_2c = fStack_2c + *(float *)((uint)bStack_1 * 0x100 + 0x8340d4);
    }
    else {
      fStack_2c = *(float *)((uint)bStack_1 * 0x100 + 0x8340d4) - fStack_2c;
    }
    uVar3 = FUN_00148df0(0,99);
    if (uVar3 < 0x32) {
      fStack_28 = fStack_28 + *(float *)((uint)bStack_1 * 0x100 + 0x8340d8);
    }
    else {
      fStack_28 = *(float *)((uint)bStack_1 * 0x100 + 0x8340d8) - fStack_28;
    }
    uVar4 = FUN_00138310(fStack_30,fStack_2c,fStack_28,0x3f800000,bStack_1);
    FUN_00128900(&fStack_30,uVar4);
    FUN_00137cc0(0x41f00000,bStack_1,&fStack_30);
    *(undefined1 *)((bStack_1 - 0x21) * 8 + 0x859930) = 1;
    *(undefined1 *)((bStack_1 - 0x21) * 8 + 0x859934) = 6;
    *(ushort *)((bStack_1 - 0x21) * 8 + 0x859932) = (ushort)bStack_1;
    *(undefined1 *)((bStack_1 - 0x21) * 8 + 0x859935) = 0;
  }
  return;
}

