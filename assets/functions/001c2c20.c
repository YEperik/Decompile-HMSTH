
void FUN_001c2c20(void)

{
  char cVar1;
  int iVar2;
  short sVar3;
  ushort uVar4;
  
  cVar1 = cRam008351f0;
  FUN_0013e1b0(0x11,0xff);
  iVar2 = FUN_00148df0(0,0x20bb);
  switch(iVar2 % 9) {
  case 0:
    FUN_0013e1b0(0x11,0xff);
    break;
  case 1:
    if (((((cVar1 != '\a') && (cVar1 != '\b')) && (cVar1 != '\t')) &&
        ((cVar1 != '\n' && (cVar1 != '\v')))) && (cVar1 != '\f')) {
      iVar2 = FUN_00148df0(0,0x80);
      FUN_0013e1b0(0x11,iVar2 % 6 + 7U & 0xff);
    }
    break;
  case 3:
    if (cVar1 != '\r') {
      FUN_0013e1b0(0x11,0xd);
    }
    break;
  case 4:
    if (cVar1 != '\x0e') {
      FUN_0013e1b0(0x11,0xe);
    }
    break;
  case 5:
    if (cVar1 != '\x0f') {
      FUN_0013e1b0(0x11,0xf);
    }
    break;
  case 6:
    if (cVar1 != '\x10') {
      FUN_0013e1b0(0x11,0x10);
    }
    break;
  case 7:
    if ((cVar1 != '\x11') && (cVar1 != '\x12')) {
      if ((uRam00859fc0 & 8) == 8) {
        FUN_0013e1b0(0x11,0x12);
      }
      else {
        FUN_0013e1b0(0x11,0x11);
      }
    }
    break;
  case 8:
    if (cVar1 != '\x14') {
      FUN_0013e1b0(0x11,0x14);
    }
  }
  if (((uRam00859fc0 & 2) != 2) && ((0x13 < bRam0085a2f5 || (bRam0085a2f5 < 6)))) {
    if ((uRam00859fc0 & 0x200) == 0x200) {
      sVar3 = sRam008351a2 + 1;
      uVar4 = sRam008351a2 + 1;
      sRam008351a2 = sVar3;
      if (400 < uVar4) {
        FUN_0013e2a0(0x11);
        uRam00859fc0 = uRam00859fc0 & 0xfffffdff;
        sRam008351a2 = 0;
        uGpffff8aa8 = 2;
        FUN_00139920(0x11,0x14);
        uRam00859fc0 = uRam00859fc0 | 0x100;
      }
    }
    else if ((uRam00859fc0 & 1) == 1) {
      uGpffff8aa8 = 2;
      FUN_00139920(0x11,0x14);
      FUN_0013e2a0(0x11);
      uRam00859fc0 = uRam00859fc0 | 0x100;
    }
  }
  return;
}

