
void FUN_001c5e40(void)

{
  undefined1 uVar1;
  ulong uVar2;
  undefined8 uVar3;
  int iVar4;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_20;
  undefined4 uStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  undefined2 uStack_8;
  undefined2 uStack_6;
  byte bStack_3;
  undefined1 uStack_2;
  undefined1 uStack_1;
  
  if (((cGpffff8944 == '\0') &&
      (((cRam0085a2f7 == '\0' || (cRam0085a2f7 == '\x01')) && (5 < bRam0085a2f5)))) &&
     (((bRam0085a2f5 < 0x11 && (uVar2 = FUN_00148df0(0,99), uVar2 < 0x32)) &&
      (FUN_001c72b0(&bStack_3,&uStack_8,&uStack_6), bStack_3 != 0xff)))) {
    FUN_001c5940(bStack_3,uStack_8,uStack_6,0xc4,0x1791000);
    FUN_00123930(0xbf800000,*(undefined2 *)((uint)bStack_3 * 0x100 + 0x834058));
    switch(uGpffff8844) {
    case 0:
    case 1:
      uVar2 = FUN_00148df0(0,99);
      if (uVar2 < 0x32) {
        uVar1 = FUN_00148df0(0,0x3f);
        FUN_00183c70(uVar1,&uStack_2,&uStack_1);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uVar2 = FUN_00148df0(0,0xa00);
        if ((long)uVar2 < 0) {
          fStack_20 = (float)(uVar2 & 0xffffffff);
        }
        else {
          fStack_20 = (float)(int)uVar2;
        }
        fStack_20 = fStack_20 + 192.0;
        uStack_1c = 0x43000000;
        uVar2 = FUN_00148df0(0,0xa00);
        if ((long)uVar2 < 0) {
          fStack_18 = (float)(uVar2 & 0xffffffff);
        }
        else {
          fStack_18 = (float)(int)uVar2;
        }
        fStack_18 = 1600.0 - fStack_18;
      }
      break;
    case 4:
      uVar2 = FUN_00148df0(0,99);
      if (uVar2 < 0x32) {
        uStack_2 = FUN_00148df0(0xb,0x12);
        uStack_1 = FUN_00148df0(5,0x19);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uStack_2 = FUN_00148df0(0x16,0x1c);
        uStack_1 = FUN_00148df0(0x1a,0x20);
        uStack_1c = 0x43bb0000;
      }
      break;
    case 5:
      uVar2 = FUN_00148df0(0,99);
      if (uVar2 < 0x32) {
        uStack_2 = FUN_00148df0(8,0xe);
        uStack_1 = FUN_00148df0(0x10,0x1c);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uStack_2 = FUN_00148df0(0x1b,0x20);
        uStack_1 = FUN_00148df0(0xe,0x19);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43200000;
      }
      break;
    case 6:
      uVar2 = FUN_00148df0(0,99);
      if (uVar2 < 0x32) {
        uStack_2 = FUN_00148df0(0xd,0x1a);
        uStack_1 = FUN_00148df0(4,0x1d);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uStack_2 = FUN_00148df0(1,9);
        uStack_1 = FUN_00148df0(0x11,0x1c);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43200000;
      }
      break;
    case 8:
      uStack_2 = FUN_00148df0(10,0x2d);
      uStack_1 = FUN_00148df0(0x1b,0x30);
      FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
      uStack_1c = 0x43000000;
      break;
    case 9:
      uVar2 = FUN_00148df0(0,99);
      if (uVar2 < 0x32) {
        uStack_2 = FUN_00148df0(7,0xc);
        uStack_1 = FUN_00148df0(6,0x13);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43000000;
      }
      else {
        uStack_2 = FUN_00148df0(0x14,0x1e);
        uStack_1 = FUN_00148df0(0x18,0x28);
        FUN_0014fe50(uStack_2,uStack_1,&fStack_20);
        uStack_1c = 0x43000000;
      }
    }
    FUN_00137ae0(fStack_20,uStack_1c,fStack_18,bStack_3);
    FUN_001378a0(bStack_3);
    FUN_00139920(bStack_3,1);
    iVar4 = (uint)bStack_3 * 0x100;
    *(float *)(iVar4 + 0x8340d0) = fStack_20;
    *(undefined4 *)(iVar4 + 0x8340d4) = uStack_1c;
    *(float *)(iVar4 + 0x8340d8) = fStack_18;
    *(undefined4 *)(iVar4 + 0x8340dc) = uStack_14;
    *(undefined4 *)((uint)bStack_3 * 0x100 + 0x8340e0) = 0x43800000;
    *(undefined4 *)((uint)bStack_3 * 0x100 + 0x8340e4) = 0x42800000;
    *(undefined4 *)((uint)bStack_3 * 0x100 + 0x8340e8) = 0x43800000;
    uVar3 = FUN_0011d018(*(undefined4 *)((uint)bStack_3 * 0x100 + 0x8340e0));
    uVar2 = FUN_00148df0(0,uVar3);
    if ((long)uVar2 < 0) {
      fStack_30 = (float)(uVar2 & 0xffffffff);
    }
    else {
      fStack_30 = (float)(int)uVar2;
    }
    uVar3 = FUN_0011d018(*(undefined4 *)((uint)bStack_3 * 0x100 + 0x8340e4));
    uVar2 = FUN_00148df0(0,uVar3);
    if ((long)uVar2 < 0) {
      fStack_2c = (float)(uVar2 & 0xffffffff);
    }
    else {
      fStack_2c = (float)(int)uVar2;
    }
    uVar3 = FUN_0011d018(*(undefined4 *)((uint)bStack_3 * 0x100 + 0x8340e8));
    uVar2 = FUN_00148df0(0,uVar3);
    if ((long)uVar2 < 0) {
      fStack_28 = (float)(uVar2 & 0xffffffff);
    }
    else {
      fStack_28 = (float)(int)uVar2;
    }
    uVar2 = FUN_00148df0(0,99);
    if (uVar2 < 0x32) {
      fStack_30 = fStack_30 + *(float *)((uint)bStack_3 * 0x100 + 0x8340d0);
    }
    else {
      fStack_30 = *(float *)((uint)bStack_3 * 0x100 + 0x8340d0) - fStack_30;
    }
    uVar2 = FUN_00148df0(0,99);
    if (uVar2 < 0x32) {
      fStack_2c = fStack_2c + *(float *)((uint)bStack_3 * 0x100 + 0x8340d4);
    }
    else {
      fStack_2c = *(float *)((uint)bStack_3 * 0x100 + 0x8340d4) - fStack_2c;
    }
    uVar2 = FUN_00148df0(0,99);
    if (uVar2 < 0x32) {
      fStack_28 = fStack_28 + *(float *)((uint)bStack_3 * 0x100 + 0x8340d8);
    }
    else {
      fStack_28 = *(float *)((uint)bStack_3 * 0x100 + 0x8340d8) - fStack_28;
    }
    FUN_00138310(fStack_30,fStack_2c,fStack_28,0x3f800000,bStack_3);
    FUN_00128900(&fStack_30);
    FUN_00137cc0(0x41f00000,bStack_3,&fStack_30);
    *(undefined1 *)((bStack_3 - 0x21) * 8 + 0x859930) = 1;
    *(undefined1 *)((bStack_3 - 0x21) * 8 + 0x859934) = 2;
    *(ushort *)((bStack_3 - 0x21) * 8 + 0x859932) = (ushort)bStack_3;
    *(undefined1 *)((bStack_3 - 0x21) * 8 + 0x859935) = 0;
  }
  return;
}

