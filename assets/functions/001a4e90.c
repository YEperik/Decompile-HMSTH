
void FUN_001a4e90(void)

{
  byte bVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 uVar6;
  undefined4 auStack_8 [2];
  
  auStack_8[0] = 0x1ad5000;
  auStack_8[1] = 0x1ae6000;
  FUN_001532e0();
  bVar1 = *(byte *)((uint)bGpffff8a88 + ((uint)uGpffff8a80 - (uint)uGpffff8a7c) + 0x85a380);
  if (bGpffff8a78 == 0) {
    if (bGpffff8a74 == 5) {
      if (((bVar1 == 0xff) && ((bGpffff89d8 & 0x20) == 0x20)) ||
         ((bVar1 == 0xfe && ((bGpffff89d8 & 0x40) == 0x40)))) {
        FUN_00152f40(0,uRam00244024,0x4220,5);
      }
      else if (((bGpffff89d8 & 0x20) == 0x20) || ((bGpffff89d8 & 0x40) == 0x40)) {
        FUN_00152f40(0,0x114,0x4220,5);
      }
      else if ((bVar1 == 0xfe) && ((uRam00859fe0 & 1) != 1)) {
        FUN_00152f40(0,0x115,0x4220,5);
      }
      else {
        FUN_00152f40(0,*(undefined2 *)(((uint)bGpffff8a84 + (uint)bGpffff8a88) * 2 + 0x85a360),
                     0x4220,5);
      }
    }
    else if (bGpffff8a74 == 6) {
      if (bVar1 == 0xfd) {
        uVar3 = 0;
        while ((uVar3 < 5 && ((*(uint *)(uVar3 * 0x20 + 0x859f20) & 1) == 1))) {
          uVar3 = uVar3 + 1 & 0xff;
        }
        uVar5 = 0;
        for (uVar4 = 0; uVar4 < 5; uVar4 = uVar4 + 1 & 0xff) {
          if (((*(uint *)(uVar4 * 0x20 + 0x859f20) & 1) == 1) &&
             (((*(uint *)(uVar4 * 0x20 + 0x859f20) & 0x2000) == 0x2000 ||
              ((*(uint *)(uVar4 * 0x20 + 0x859f20) & 0x1000000) == 0x1000000)))) {
            uVar5 = uVar5 + 1 & 0xff;
          }
        }
        if (uVar3 + uVar5 < 5) {
          FUN_00152f40(0,*(undefined2 *)(((uint)bGpffff8a84 + (uint)bGpffff8a88) * 2 + 0x85a360),
                       0x4220,5);
        }
        else {
          FUN_00152f40(0,0x10d,0x4220,5);
        }
      }
      else if (bVar1 == 0xfc) {
        uVar3 = 0;
        while ((uVar3 < 6 && ((*(uint *)(uVar3 * 0x20 + 0x859e60) & 1) == 1))) {
          uVar3 = uVar3 + 1 & 0xff;
        }
        if ((bRam00859e10 & 1) == 1) {
          uVar3 = uVar3 + 1 & 0xff;
        }
        if (uVar3 < 6) {
          FUN_00152f40(0,*(undefined2 *)(((uint)bGpffff8a84 + (uint)bGpffff8a88) * 2 + 0x85a360),
                       0x4220,5);
        }
        else {
          FUN_00152f40(0,0x10d,0x4220,5);
        }
      }
      else {
        lVar2 = FUN_0016bc20(bVar1,1);
        if (lVar2 == 0) {
          if ((bVar1 == 0x58) || (bVar1 == 0x59)) {
            FUN_00152f40(0,*(undefined2 *)(&DAT_00244040 + (uint)bGpffff8a74 * 2),0x4220,5);
          }
          else {
            FUN_00152f40(0,*(undefined2 *)((uint)bGpffff8a78 * 2 + (uint)bGpffff8a74 * 4 + 0x244010)
                         ,0x4220,5);
          }
        }
        else {
          FUN_00152f40(0,*(undefined2 *)(((uint)bGpffff8a84 + (uint)bGpffff8a88) * 2 + 0x85a360),
                       0x4220,5);
        }
      }
    }
    else {
      lVar2 = FUN_0016bc20(bVar1,1);
      if (lVar2 == 0) {
        if ((bGpffff8a74 == 2) &&
           ((((bVar1 == 0x5b || (bVar1 == 0x56)) || (bVar1 == 0x57)) ||
            ((bVar1 == 0x4d || (bVar1 == 0x52)))))) {
          FUN_00152f40(0,uRam00244044,0x4220,5);
        }
        else if ((bGpffff8a74 == 1) && (bVar1 == 0x4f)) {
          FUN_00152f40(0,uRam00244042,0x4220,5);
        }
        else {
          FUN_00152f40(0,*(undefined2 *)((uint)bGpffff8a78 * 2 + (uint)bGpffff8a74 * 4 + 0x244010),
                       0x4220,5);
        }
      }
      else {
        FUN_00152f40(0,*(undefined2 *)(((uint)bGpffff8a84 + (uint)bGpffff8a88) * 2 + 0x85a360),
                     0x4220,5);
      }
    }
  }
  else if (bGpffff8a74 == 6) {
    if (bGpffff8a88 == 0) {
      uVar3 = 0;
      while ((uVar3 < 5 &&
             ((((*(uint *)(uVar3 * 0x20 + 0x859f20) & 1) != 1 ||
               ((*(uint *)(uVar3 * 0x20 + 0x859f20) & 0x800) == 0x800)) ||
              (((*(uint *)(uVar3 * 0x20 + 0x859f20) & 0x1000) == 0x1000 ||
               ((*(uint *)(uVar3 * 0x20 + 0x859f20) & 2) == 2))))))) {
        uVar3 = uVar3 + 1 & 0xff;
      }
      if (uVar3 == 5) {
        uVar3 = 0;
        while ((uVar3 < 5 && ((*(uint *)(uVar3 * 0x20 + 0x859f20) & 1) != 1))) {
          uVar3 = uVar3 + 1 & 0xff;
        }
        if (uVar3 == 5) {
          FUN_00152f40(0,*(undefined2 *)((uint)bGpffff8a78 * 2 + 0x244028),0x4220,5);
        }
        else {
          FUN_00152f40(0,0x117,0x4220,5);
        }
      }
    }
    else {
      uVar3 = 0;
      while ((uVar3 < 6 &&
             ((((*(uint *)(uVar3 * 0x20 + 0x859e60) & 1) != 1 ||
               ((*(uint *)(uVar3 * 0x20 + 0x859e60) & 0x800) == 0x800)) ||
              ((*(uint *)(uVar3 * 0x20 + 0x859e60) & 2) == 2))))) {
        uVar3 = uVar3 + 1 & 0xff;
      }
      if (uVar3 == 6) {
        uVar3 = 0;
        while ((uVar3 < 6 && ((*(uint *)(uVar3 * 0x20 + 0x859e60) & 1) != 1))) {
          uVar3 = uVar3 + 1 & 0xff;
        }
        if (uVar3 == 6) {
          FUN_00152f40(0,*(undefined2 *)((uint)bGpffff8a78 * 2 + 0x244028),0x4220,5);
        }
        else {
          FUN_00152f40(0,0x117,0x4220,5);
        }
      }
    }
  }
  else if (*(char *)(bVar1 + 0x85a2a0) == '\0') {
    FUN_00152f40(0,*(undefined2 *)((uint)bGpffff8a78 * 2 + (uint)bGpffff8a74 * 4 + 0x244010),0x4220,
                 5);
  }
  else {
    FUN_00152f40(0,*(undefined2 *)(((uint)bGpffff8a84 + (uint)bGpffff8a88) * 2 + 0x85a360),0x4220,5)
    ;
  }
  if ((bGpffff8a74 != 5) || (bGpffff8a78 != 0)) {
    if ((bGpffff8a74 == 6) && ((bVar1 == 0xfd || (bVar1 == 0xfc)))) {
      FUN_0015ab30();
      FUN_001cce50(0x11d);
      FUN_0015bfb0(0x113);
    }
    else {
      bGpffff8a8c = bGpffff8a8c ^ 1;
      FUN_0015a250(0,auStack_8[bGpffff8a8c]);
      if (((bGpffff8a74 == 3) || (bGpffff8a74 == 4)) && (bGpffff8a78 == 0)) {
        FUN_0015a6b0(0x3f800000,0,bVar1,1);
      }
      else {
        if ((bGpffff8a78 == 0) && (((bGpffff8a74 == 2 || (bGpffff8a74 == 6)) || (bGpffff8a74 == 1)))
           ) {
          if ((((bGpffff8a74 == 2) && (bVar1 != 0x25)) ||
              ((bGpffff8a74 == 6 && ((bVar1 == 0x58 || (bVar1 == 0x59)))))) ||
             ((bGpffff8a74 == 1 && (bVar1 == 0x4f)))) {
            FUN_0015a0e0(0xc3600000,0xc2600000,0x47c34000);
            FUN_001cce50(0x11d);
          }
          else {
            FUN_0015a0e0(0xc3700000,0xc2400000,0x47c34000);
          }
        }
        FUN_0015a290(0x3f800000,0,bVar1,1);
      }
      FUN_0015aab0();
      FUN_0015bf20(0x113);
      switch(bVar1) {
      default:
        uVar6 = *(undefined1 *)(bVar1 + 0x85a2a0);
        break;
      case 0x49:
      case 0x4a:
      case 0x4b:
      case 0x4c:
      case 0x4d:
      case 0x4e:
      case 0x4f:
      case 0x50:
      case 0x51:
      case 0x52:
      case 0x53:
      case 0x54:
      case 0x55:
      case 0x56:
      case 0x57:
      case 0x58:
      case 0x59:
      case 0x5a:
      case 0x5b:
      case 0x5c:
        lVar2 = FUN_0016bc20(bVar1,1);
        if (lVar2 == 0) {
          uVar6 = 1;
        }
        else {
          uVar6 = 0;
        }
      }
      if (((bGpffff8a78 != 0) ||
          (((bGpffff8a74 != 3 && (bGpffff8a74 != 4)) &&
           (((bGpffff8a74 != 2 || (bVar1 == 0x25)) &&
            ((bGpffff8a74 != 6 || ((bVar1 != 0x58 && (bVar1 != 0x59)))))))))) &&
         ((bGpffff8a74 != 1 || (bVar1 != 0x4f)))) {
        FUN_001ccc00(0xc3500000,0xc2200000,0x47c34f80,0x11d,0xd4f,0x33c,uVar6);
      }
    }
  }
  return;
}

