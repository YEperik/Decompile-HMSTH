
void FUN_001a2c70(char param_1)

{
  int iVar1;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [24];
  char cStack_8;
  
  cStack_8 = param_1;
  FUN_0013f0c0();
  FUN_00138ce0();
  FUN_00218ea0();
  uGpffff80b4 = 0xff;
  FUN_00116978(0x85a310,0xff,0x30);
  uGpffff8a94 = 0;
  FUN_001361f0(0,0x177f000,0x1941000);
  FUN_00148e20(auStack_70,0x1941000,0xd5,0xf8000,0xfa000);
  FUN_001361f0(1,0x177f000,0x1784800);
  FUN_00148f40(auStack_60,0x1941000,0xd6,0xf8000,0xfa100,0x1784800);
  FUN_001361f0(2,0x177f000,0x1784800);
  FUN_00148f40(auStack_50,0x1941000,0xd7,0xf8000,0xfa200,0x1784800);
  FUN_001361f0(3,0x177f000,0x1784800);
  FUN_00148f40(auStack_40,0x1941000,0xd8,0xf8000,0xfa300,0x1784800);
  FUN_001361f0(4,0x177f000,0x1784800);
  FUN_00148f40(auStack_30,0x1941000,0xd9,0xf8000,0xfa400,0x1784800);
  FUN_001361f0(5,0x177f000,0x1784800);
  FUN_00148f40(auStack_20,0x1941000,0xda,0xf8000,0xfa500,0x1784800);
  FUN_001361f0(6,0x177f000,0x1785000);
  FUN_001361f0(7,0x177f000,0x1786000);
  FUN_001361f0(8,0x177f000,0x1796000);
  FUN_001361f0(9,0x177f000,0x1797000);
  FUN_0015ee70(0x43100000,0x42800000,0x47c34f80);
  FUN_0015ae30(0x3e000000,0,0x3b800000,0x3e000000,0x111,0x50,0x50);
  FUN_0015bcd0(0x111,0x330,0xd43,0xda);
  FUN_0015c040(0,0x42c00000,0x47c35000,0x111);
  FUN_0015ae30(0x3f700000,0x3e040000,0x3b800000,0x3ec00000,0x110,0x248,0x80);
  FUN_0015bcd0(0x110,0x32f,0xd42,0xd8);
  FUN_0015c040(0,0x43100000,0x47c35000,0x110);
  FUN_0015ae30(0x3f100000,0,0x3ea20000,0x3e000000,0x112,0x90,0x40);
  FUN_0015bcd0(0x112,0x331,0xd44,0xd7);
  FUN_0015c040(0xc35c0000,0x42200000,0x47c35000,0x112);
  FUN_0015ae30(0x3ea00000,0,0x3e040000,0x3e000000,0x113,0x80,0x40);
  FUN_0015bcd0(0x113,0x332,0xd45,0xd8);
  FUN_0015c040(0xc35c0000,0xc2000000,0x47c35000,0x113);
  cGpffff8a74 = cStack_8;
  FUN_00138ce0();
  iVar1 = 0;
  if (cGpffff8a74 == '\x05') {
    if (((bGpffff89d8 & 1) == 1) || ((bGpffff89d8 & 0x20) == 0x20)) {
      iVar1 = 1;
    }
    if (((bGpffff89d8 & 2) == 2) || ((bGpffff89d8 & 0x40) == 0x40)) {
      iVar1 = iVar1 + 2;
    }
    if (iVar1 == 3) {
      iVar1 = 0xff;
    }
  }
  else if (cGpffff8a74 == '\a') {
    iVar1 = 0xff;
  }
  if (iVar1 != 0xff) {
    FUN_0015bf20(0x111);
    FUN_0015cd00(0xc2600000,0x42c00000,0x47c34f80,5);
    FUN_0015c550(5);
    uGpffff8a70 = 0;
  }
  else {
    FUN_0015bcd0(0x110,0x32f,0xd42,0xd9);
    FUN_0015c040(0,0x43100000,0x47c35000,0x110);
    FUN_0015bcd0(0x113,0x332,0xd45,0xd9);
    FUN_001a3420(1);
    FUN_0015bf20(0x110);
    FUN_0015bf20(0x112);
    FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,uGpffff8974);
    FUN_0015bf20(0x113);
    FUN_001ccc00(0xc3500000,0xc2200000,0x47c34f80,0x11d,0xd4f,0x33c,
                 *(undefined1 *)
                  (*(byte *)((((uint)uGpffff8a80 + (uint)bGpffff8a88) - (uint)uGpffff8a7c) +
                            0x85a380) + 0x85a2a0));
    uGpffff8a94 = 1;
  }
  uGpffff8a6c = iVar1 == 0xff;
  FUN_00152ed0(0,0x1786000,0x1785000);
  return;
}

