
void FUN_001be400(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  ulong uVar4;
  ushort uVar5;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  cVar1 = cRam008350f0;
  if ((uRam00859fe0 & 0x10000) == 0x10000) {
    uRam00267994 = 1;
    iVar2 = FUN_00148df0(0,0x23be);
    iVar2 = iVar2 % 5;
    if (iVar2 == 4) {
      if (cRam00835056 != '&') {
        FUN_00139920(0x10,0x26);
        uRam00835098 = 0x5a;
      }
    }
    else if (iVar2 == 3) {
      FUN_00139920(0x10,0x27);
      uRam00267994 = 0;
    }
    else if (iVar2 == 2) {
      FUN_00139920(0x10,0x2d);
    }
    else if (iVar2 == 1) {
      FUN_00139920(0x10,0x2c);
    }
    else if (iVar2 == 0) {
      if (cVar1 == '*') {
        FUN_00139920(0x10,0x2b);
      }
      else if (cVar1 == '+') {
        FUN_00139920(0x10,0x2a);
      }
      else {
        uVar3 = FUN_00148df0(0,0x80);
        FUN_00139920(0x10,(uVar3 & 1) + 0x2a);
      }
    }
  }
  else if ((uRam00859fe0 & 0x20000) == 0x20000) {
    uRam00267994 = 1;
    uVar4 = FUN_00148df0(0,0x23bc);
    uVar4 = uVar4 & 3;
    if (uVar4 == 3) {
      if (cRam00835056 != '\x1b') {
        FUN_00139920(0x10,0x1b);
        uRam00835098 = 0x5a;
      }
    }
    else if (uVar4 == 2) {
      FUN_00139920(0x10,0x1c);
      uRam00267994 = 0;
    }
    else if (uVar4 == 1) {
      FUN_00139920(0x10,0x22);
    }
    else if (uVar4 == 0) {
      FUN_00139920(0x10,0x20);
    }
  }
  else {
    FUN_0013e1b0(0x10,0xff);
    uVar3 = FUN_00148df0(0,0x20c0);
    switch(uVar3 & 7) {
    case 0:
      FUN_0013e1b0(0x10,0xff);
      break;
    case 1:
      if (((bRam00859fe4 & 1) == 1) && (cVar1 != '%')) {
        FUN_0013e1b0(0x10,0x25);
      }
      break;
    case 2:
      if (0x1e < bRam00859ffa) {
        if (cVar1 == '\a') {
          FUN_0013e1b0(0x10,8);
        }
        else if (cVar1 == '\b') {
          FUN_0013e1b0(0x10,7);
        }
        else {
          uVar3 = FUN_00148df0(0,0x80);
          FUN_0013e1b0(0x10,(uVar3 & 1) + 7);
        }
      }
      break;
    case 3:
      if (0x50 < bRam00859ffa) {
        if (cVar1 == '\t') {
          FUN_0013e1b0(0x10,10);
        }
        else if (cVar1 == '\n') {
          FUN_0013e1b0(0x10,9);
        }
        else {
          uVar3 = FUN_00148df0(0,0x80);
          FUN_0013e1b0(0x10,(uVar3 & 1) + 9);
        }
      }
      break;
    case 4:
      if ((0x8c < bRam00859ffa) && (cVar1 != '\x15')) {
        FUN_0013e1b0(0x10,0x15);
      }
      break;
    case 5:
      if (((bRam00859fe4 & 2) == 2) && (cVar1 != '\x1a')) {
        FUN_0013e1b0(0x10,0x1a);
      }
      break;
    case 6:
      if (((bRam00859fe4 & 0x20) == 0x20) && (cVar1 != '\x19')) {
        FUN_0013e1b0(0x10,0x19);
      }
      break;
    case 7:
      if ((cVar1 != '\x13') && (cVar1 != '\x14')) {
        if ((uRam00859fe0 & 8) == 8) {
          FUN_0013e1b0(0x10,0x14);
        }
        else {
          FUN_0013e1b0(0x10,0x13);
        }
      }
    }
  }
  if (((uRam00859fe0 & 2) != 2) && ((0x14 < bRam0085a2f5 || (bRam0085a2f5 < 6)))) {
    if ((uRam00859fe0 & 0x200) == 0x200) {
      uVar5 = sRam008350a2 + 1;
      sRam008350a2 = sRam008350a2 + 1;
      if (400 < uVar5) {
        uRam00859fe0 = uRam00859fe0 & 0xfffffdff;
        sRam008350a2 = 0;
      }
    }
    else if ((uRam00859fe0 & 1) == 1) {
      uRam00267994 = 2;
      FUN_00139920(0x10,0x1d);
      FUN_0013e2a0(0x10);
      if ((uRam00859fe0 & 0x4000) == 0x4000) {
        FUN_00124180(uRam00834058,&uStack_10);
        uRam0085a010 = uStack_10;
        uRam0085a014 = uStack_c;
        uRam0085a018 = uStack_8;
        uRam0085a01c = uStack_4;
      }
      uRam00859fe0 = uRam00859fe0 & 0xdfffbfff | 0x100;
    }
  }
  if ((uRam00859fe0 & 2) == 2) {
    FUN_0013e2a0(0x10);
    uRam00267994 = 3;
    FUN_0013e1b0(0x10,0xff);
  }
  return;
}

