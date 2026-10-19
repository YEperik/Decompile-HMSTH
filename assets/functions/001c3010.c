
undefined4 FUN_001c3010(byte param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 1) == 1) {
    if (((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x800) == 0x800) ||
       ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x1000) == 0x1000)) {
      uRam00833f10 = 0x28;
      uRam00833f11 = 0x43;
      uRam00833f12 = 0xff;
    }
    else if (*(byte *)((uint)param_1 * 0x20 + 0x859f28) < 0x5a) {
      uRam00833f10 = 0x2d;
      uRam00833f11 = 0xff;
    }
    else if (*(byte *)((uint)param_1 * 0x20 + 0x859f28) < 0x96) {
      uRam00833f10 = 0x27;
      uRam00833f11 = 0xff;
    }
    else if (*(byte *)((uint)param_1 * 0x20 + 0x859f28) < 0xdc) {
      uRam00833f10 = 0x26;
      uRam00833f11 = 0xff;
    }
    else {
      uRam00833f10 = 0x26;
      uRam00833f11 = 0xff;
    }
    uVar1 = 1;
  }
  return uVar1;
}

