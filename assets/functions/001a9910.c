
void FUN_001a9910(void)

{
  undefined1 uVar1;
  ushort uVar2;
  long lVar3;
  
  if (cGpffff8a9c == '\x01') {
    lVar3 = FUN_00167620();
    if (((lVar3 == 0) && (lVar3 = FUN_00219750(3), lVar3 == 0)) &&
       (lVar3 = FUN_00219750(2), uVar1 = uGpffff884c, lVar3 == 0)) {
      if ((uRam00834050 & 0x400) == 0x400) {
        FUN_0013c060();
        FUN_001376f0(uVar1);
      }
      uRam00834050 = uRam00834050 & 0xfffa7fff;
      if ((uRam00835150 & 1) == 1) {
        FUN_00141cb0(0x11);
      }
      if ((uRam0083b850 & 1) == 1) {
        FUN_00141cb0(0x78);
      }
      if ((uRam0083b950 & 1) == 1) {
        FUN_00141cb0(0x79);
      }
      if ((uRam0083ba50 & 1) == 1) {
        FUN_00141cb0(0x7a);
      }
      for (uVar2 = 0; uVar2 < 0x40; uVar2 = uVar2 + 1) {
        FUN_001ef7f0(uVar2);
        FUN_001ef6f0(uVar2);
      }
      FUN_0015eca0();
      FUN_001532e0();
      FUN_0013e2a0();
      FUN_00151ec0(0,0xc3100000,0x47c35000);
      FUN_00152a20(0xc3780000,0xc2e00000,0x47c34f80);
      cGpffff8a9c = '\0';
    }
  }
  else {
    if ((uRam00834050 & 0x20) == 0x20) {
      FUN_00190880();
    }
    if ((((uGpffff8834 & 1) == 1) && (lVar3 = FUN_00167620(), lVar3 == 0)) &&
       (lVar3 = FUN_0012e120(0,0x800), lVar3 != 0)) {
      switch(uGpffff882c) {
      case 0xe:
        if ((((sGpffff8830 != 0x58) && (sGpffff8830 != 0x55)) &&
            ((sGpffff8830 != 0x52 &&
             (((sGpffff8830 != 0x4f && (sGpffff8830 != 0x4c)) && (sGpffff8830 != 0x49)))))) &&
           (((sGpffff8830 != 0x46 && (sGpffff8830 != 0x43)) &&
            ((sGpffff8830 != 0x40 && ((sGpffff8830 != 0x3d && (sGpffff8830 != 0)))))))) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0xf:
        if (((sGpffff8830 != 0x2d) && (sGpffff8830 != 0x2a)) &&
           ((sGpffff8830 != 0x27 && (sGpffff8830 != 0x15)))) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x10:
        if ((((sGpffff8830 != 0x30) && (sGpffff8830 != 0x2d)) && (sGpffff8830 != 0xc)) &&
           (sGpffff8830 != 0)) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x11:
        if (((sGpffff8830 != 99) && (sGpffff8830 != 0x60)) &&
           ((sGpffff8830 != 0xf && (sGpffff8830 != 0xc)))) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x12:
        if (((sGpffff8830 != 0x2a) && (sGpffff8830 != 0x27)) && (sGpffff8830 != 0x24)) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x13:
        if (((sGpffff8830 != 0x1e) && (sGpffff8830 != 0x1b)) && (sGpffff8830 != 0xc)) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x14:
        if ((sGpffff8830 != 0x1b) && (sGpffff8830 != 0x18)) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x15:
        if (((((sGpffff8830 != 0x2b) && (sGpffff8830 != 0x2a)) &&
             ((sGpffff8830 != 0x27 &&
              (((sGpffff8830 != 0x24 && (sGpffff8830 != 0x21)) && (sGpffff8830 != 0x1e)))))) &&
            ((sGpffff8830 != 0x1b && (sGpffff8830 != 0x18)))) && (sGpffff8830 != 9)) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x16:
        cGpffff8a9c = '\x01';
        break;
      case 0x17:
        if (sGpffff8830 != 0x27) {
          cGpffff8a9c = '\x01';
        }
        break;
      case 0x18:
        cGpffff8a9c = '\x01';
        break;
      case 0x19:
        cGpffff8a9c = '\x01';
        break;
      case 0x1a:
        if ((sGpffff8830 != 0xc) && (sGpffff8830 != 9)) {
          cGpffff8a9c = '\x01';
        }
      }
      if (cGpffff8a9c != '\0') {
        FUN_0013f0c0(0,0,0,0);
        FUN_0013e710();
        for (uVar2 = 0; uVar2 < 0x40; uVar2 = uVar2 + 1) {
          FUN_001ef860(uVar2);
        }
        FUN_002196d0(3);
        FUN_002196d0(2);
        FUN_00167330(0x1e);
      }
    }
    FUN_001862b0();
  }
  return;
}

