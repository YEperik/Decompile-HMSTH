
void FUN_001bada0(void)

{
  bool bVar1;
  short sVar2;
  char cVar3;
  short sVar4;
  long lVar5;
  undefined8 uVar6;
  ushort uVar7;
  ushort uVar8;
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [2];
  float fStack_18;
  float afStack_10 [4];
  
  cVar3 = FUN_00123d60(sRam00835158);
  sVar2 = sRam00835158;
  if (((((uRam00859fc0 & 2) == 2) && (cGpffff8aa8 != '\x04')) && (cGpffff8aa8 != '\x05')) &&
     ((cGpffff8aa8 != '\a' && (cGpffff8aa8 != '\x02')))) {
    cGpffff8aa8 = '\x03';
  }
  switch(cGpffff8aa8) {
  case '\0':
    if ((uRam00859fc0 & 0x10000) == 0x10000) {
      uRam00859fc0 = uRam00859fc0 & 0xfffeffff;
      FUN_00139920(0x11,0x11);
      cGpffff8aa8 = '\x01';
    }
    else {
      if (cRam00835156 == '\x05') {
        if ((uint)uRam00835198 == bRam008351aa - 1) {
          FUN_00139920(0x11,6);
        }
      }
      else if (cRam00835156 == '\x06') {
        if ((uRam00835198 == 0) && ((uRam00835150 & 0x400000) == 0x400000)) {
          sVar4 = FUN_00124be0(0x42a00000,0x3f800000,sRam00834058,sRam00835158);
          if (sVar2 == sVar4) {
            FUN_001b9720(0x11);
            uRam00835150 = uRam00835150 & 0xffbfffdf;
            uRam00859fc0 = uRam00859fc0 & 0xfffeffff;
            uRam008351a6 = 0;
            FUN_0013a620(0x11,1,1);
          }
          else {
            uRam00835150 = uRam00835150 & 0xffbfffdf | 0x10;
            FUN_00139920(0x11,2);
            FUN_0013a620(0x11,1,1);
          }
        }
        if (cVar3 == '\0') {
          FUN_0013a620(0x11,1,1);
        }
        else {
          lVar5 = FUN_00123d10(sRam00835158);
          if (lVar5 != 0) {
            uRam00835150 = uRam00835150 & 0xffbfffff | 0x10;
            FUN_0013a620(0x11,1,1);
          }
        }
      }
      FUN_001be090();
      FUN_001beea0();
    }
    break;
  case '\x01':
    if (cRam00835156 == '\x15') {
      uRam00835198 = uRam00835198 - 1;
      if (uRam00835198 != 0) {
        FUN_00139920(0x11,0x16);
      }
    }
    else if ((cRam00835156 == '\x16') || (cRam00835156 == '\x13')) {
      if (cVar3 == '\0') {
        FUN_0013dff0(0x11,0x140,0,0x140);
        FUN_001c2c20();
        cGpffff8aa8 = '\0';
      }
    }
    else if (cRam00835156 == '\x11') {
      if (cVar3 == '\0') {
        if ((uRam00859fc0 & 0x10000) == 0x10000) {
          uRam00859fc0 = uRam00859fc0 & 0xfffeffff;
          FUN_0013dff0(0x11,0x140,0,0x140);
          FUN_001c2c20();
        }
        cGpffff8aa8 = '\0';
      }
    }
    else {
      cGpffff8aa8 = '\0';
    }
    break;
  case '\x02':
    if (cRam00835156 == '\x14') {
      if (cVar3 == '\0') {
        FUN_00139920(0x11,0x17);
      }
    }
    else if ((uRam00859fc0 & 0x200) == 0x200) {
      uRam008351a2 = uRam008351a2 + 1;
      if (400 < uRam008351a2) {
        uRam00859fc0 = uRam00859fc0 & 0xfffffdff;
        uRam008351a2 = 0;
        if ((cRam00835156 != '\x14') && (cRam00835156 != '\x17')) {
          FUN_00139920(0x11,0x14);
        }
      }
    }
    else if ((5 < bRam0085a2f5) && (bRam0085a2f5 < 0x14)) {
      uRam00859fc0 = uRam00859fc0 & 0xfffffeff;
      cGpffff8aa8 = '\0';
      FUN_0013dff0(0x11,0x140,0,0x140);
      FUN_001c2c20();
    }
    break;
  case '\x03':
    FUN_001be090();
    if ((((uRam00859fc0 & 0x100) != 0x100) && (cGpffff8aa8 != '\x05')) && (cGpffff8aa8 != '\a')) {
      if ((uRam00859fc0 & 2) == 2) {
        if ((uRam00859fc0 & 0x40000) == 0x40000) {
          if ((uRam00835150 & 4) != 4) {
            uRam00859fc0 = uRam00859fc0 & 0xfffbffff;
            FUN_00138ce0(0x11);
          }
        }
        else {
          FUN_0013e1b0(0x11,0xff);
          FUN_0013e2a0(0x11);
          if ((cRam00835156 != '\x18') && (cRam00835156 != '\x17')) {
            if (cRam00835156 == '\x14') {
              lVar5 = FUN_0013a2c0(0x11);
              if (lVar5 == 0) {
                FUN_00139920(0x11,0x17);
              }
            }
            else {
              FUN_00139920(0x11,0x14);
            }
          }
        }
      }
      else {
        uVar7 = uRam008351a2 - 1;
        bVar1 = uRam008351a2 == 1;
        uRam008351a2 = uVar7;
        if (bVar1) {
          cGpffff8aa8 = '\0';
          FUN_00139920(0x11,0x16);
          uVar6 = FUN_0013dff0(0x11,0x140,0,0x140);
          FUN_001c2c20(uVar6);
        }
      }
    }
    if ((0x13 < bRam0085a2f5) || (bRam0085a2f5 < 6)) {
      if (((uRam00859fc0 & 0x200) == 0x200) && ((uRam00859fc0 & 2) != 2)) {
        uVar7 = uRam008351a2 + 1;
        uVar8 = uRam008351a2 + 1;
        uRam008351a2 = uVar7;
        if (400 < uVar8) {
          FUN_0013e2a0(0x11);
          uRam00859fc0 = uRam00859fc0 & 0xfffffdff;
          uRam008351a2 = 0;
          cGpffff8aa8 = '\x02';
          FUN_00139920(0x11,0x14);
        }
      }
      else {
        if (((uRam00859fc0 & 0x40000) == 0x40000) && ((uRam00835150 & 4) != 4)) {
          uRam00859fc0 = uRam00859fc0 & 0xfffbffff;
        }
        if (((uRam00859fc0 & 1) == 1) && ((uRam00859fc0 & 0x40000) != 0x40000)) {
          cGpffff8aa8 = '\x02';
          if ((cRam00835156 != '\x14') && (cRam00835156 != '\x17')) {
            FUN_00139920(0x11,0x14);
          }
          FUN_0013e2a0(0x11);
          uRam00859fc0 = uRam00859fc0 | 0x100;
          uRam008351a2 = 400;
        }
      }
    }
    break;
  case '\x04':
    lVar5 = FUN_00151510(0x11);
    if (((lVar5 != 0) && ((uGpffff885c & 0x400) != 0x400)) &&
       (((uRam00859fc0 & 0x200000) != 0x200000 && (sRam00834058 != -1)))) {
      FUN_00124180(sRam00834058,afStack_30);
      FUN_00124180(sRam00835158,afStack_20);
      afStack_10[0] = afStack_20[0] - afStack_30[0];
      afStack_10[1] = 0.0;
      afStack_10[2] = fStack_18 - fStack_28;
      FUN_00128900(afStack_10);
      FUN_00137b90(0x11,afStack_10);
      FUN_0013e2a0(0x11);
      FUN_00138540(0x11,0x10);
    }
    if ((uRam00835150 & 4) != 4) {
      cGpffff8aa8 = '\0';
      if ((uRam00859fc0 & 0x200) == 0x200) {
        cGpffff8aa8 = '\x02';
      }
      else {
        FUN_0013dff0(0x11,0x140,0,0x140);
      }
      uRam00859fc0 = uRam00859fc0 & 0xffdfffff;
    }
    break;
  case '\x05':
    if ((uRam00835150 & 4) != 4) {
      FUN_00137930(0x11);
      uRam00859fc0 = uRam00859fc0 & 0xfffdffff;
      FUN_001b24b0();
      if (cGpffff8acc == '\x01') {
        FUN_00150200(2,1);
      }
      cGpffff8acc = cGpffff8acc + -1;
      cGpffff8aa8 = '\0';
    }
    break;
  case '\a':
    if ((uRam00835150 & 4) != 4) {
      FUN_00137930(0x11);
      uRam00859fc0 = uRam00859fc0 & 0xfff7ffff;
      FUN_001b25d0();
      if (cGpffff8acc == '\x01') {
        FUN_00150200(0x15,1);
      }
      cGpffff8acc = cGpffff8acc + -1;
      cGpffff8aa8 = '\0';
    }
    break;
  case '\t':
    FUN_001c9550();
    break;
  case '\f':
    if ((uRam00835150 & 4) != 4) {
      FUN_0013dff0(0x11,0x100,0,0x100);
      cGpffff8aa8 = '\0';
      uRam00859fc0 = uRam00859fc0 & 0xffdfffff;
    }
  }
  return;
}

