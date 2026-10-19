
void FUN_001b9d10(void)

{
  bool bVar1;
  char cVar2;
  ulong uVar3;
  long lVar4;
  undefined8 uVar5;
  short sVar6;
  ushort uVar7;
  float afStack_40 [2];
  float fStack_38;
  float afStack_30 [2];
  float fStack_28;
  float afStack_20 [6];
  float fStack_8;
  float fStack_4;
  
  fStack_8 = 0.0;
  fStack_4 = 0.0;
  cVar2 = FUN_00123d60(uRam00835058);
  if ((uRam00859fe0 & 0x100) == 0x100) {
    cGpffff8aa4 = '\x02';
  }
  if ((cGpffff884c != '\x10') || (cGpffff8aa4 == '\x02')) {
    switch(cGpffff8aa4) {
    case '\0':
      if (((uRam00859fe0 & 0x8000) == 0x8000) && ((uRam00859fe0 & 0x4000) != 0x4000)) {
        FUN_00139920(0x10,9);
        cGpffff8aa4 = '\x01';
      }
      else {
        FUN_001c8b80();
        FUN_001c8e90();
        if ((uRam00859fe0 & 0x40000) == 0x40000) {
          if ((uRam00835050 & 0x200) != 0x200) {
            FUN_001bf160();
          }
        }
        else {
          FUN_001beb90();
        }
      }
      if (((((uRam00859fe0 & 0x4000) == 0x4000) && ((uRam00859fe0 & 0x10000) != 0x10000)) &&
          ((uRam00835050 & 0x20) != 0x20)) && ((uRam00835050 & 0x400000) != 0x400000)) {
        FUN_001c0970();
        FUN_001c1f10(0x10);
      }
      else {
        lVar4 = FUN_00151510(0x10);
        if (((lVar4 != 0) && ((uGpffff885c & 0x400) != 0x400)) && (sRam00834058 != -1)) {
          FUN_00124180(sRam00834058,afStack_40);
          FUN_00124180(uRam00835058,afStack_30);
          afStack_20[0] = afStack_30[0] - afStack_40[0];
          afStack_20[1] = 0.0;
          afStack_20[2] = fStack_28 - fStack_38;
          FUN_00128900(afStack_20);
          FUN_00137b90(0x10,afStack_20);
          FUN_0013e2a0(0x10);
          FUN_00138360(0x10,0x80);
          cGpffff8aa4 = '\f';
        }
      }
      if ((uRam00859fe0 & 0x80000) == 0x80000) {
        FUN_001c0fa0();
      }
      if (((cGpffff8aa4 != '\n') && ((uRam00859fe0 & 0x20000000) == 0x20000000)) &&
         (lVar4 = FUN_00148df0(0,999), lVar4 == 0)) {
        cGpffff8898 = '\x05';
        FUN_001c9020(1);
      }
      break;
    case '\x01':
      if ((((cRam00835056 == '\x14') || (cRam00835056 == '\x13')) || (cRam00835056 == '(')) ||
         (cRam00835056 == '\x0f')) {
        if (cVar2 == '\0') {
          if ((uRam00859fe0 & 0x10000000) == 0x10000000) {
            FUN_001c8860();
          }
          else {
            FUN_0013dff0(0x10,0x140,0,0x140);
            FUN_001be400();
            cGpffff8aa4 = '\0';
          }
        }
      }
      else if (cRam00835056 == '\x0e') {
        sRam00835098 = sRam00835098 + -1;
        if (sRam00835098 == 0) {
          FUN_00139920(0x10,0xf);
        }
      }
      else if (cRam00835056 == '\r') {
        if (cVar2 == '\0') {
          FUN_00139920(0x10,0xe);
          sRam00835098 = 0xf0;
        }
      }
      else if (cRam00835056 == '\x1b') {
        sRam00835098 = sRam00835098 + -1;
        if (sRam00835098 == 0) {
          FUN_001be400();
        }
      }
      else if ((((cRam00835056 == '\"') || (cRam00835056 == ' ')) ||
               ((cRam00835056 == '-' || ((cRam00835056 == ',' || (cRam00835056 == '+')))))) ||
              (cRam00835056 == '*')) {
        if (cVar2 == '\0') {
          FUN_001be400();
        }
      }
      else if (cRam00835056 == '&') {
        sRam00835098 = sRam00835098 + -1;
        if (sRam00835098 == 0) {
          if ((uRam00859fe0 & 0x4000) == 0x4000) {
            FUN_00139920(0x10,0x27);
            cGpffff8aa4 = '\0';
          }
          else {
            FUN_001be400();
          }
        }
      }
      else if (cRam00835056 == '\t') {
        if (cVar2 == '\0') {
          if ((uRam00859fe0 & 0x8000) == 0x8000) {
            uRam00859fe0 = uRam00859fe0 & 0xffff7fff;
            FUN_0013dff0(0x10,0x140,0,0x140);
            FUN_001be400();
          }
          cGpffff8aa4 = '\0';
        }
      }
      else {
        cGpffff8aa4 = '\0';
      }
      break;
    case '\x02':
      if (cRam00835056 == '1') {
        if ((cRam00834056 == '\a') || (cRam00834056 == '\b')) {
          uRam00859fe0 = (uint)((ulong)((long)(int)uRam00859fe0 << 0x21) >> 0x21);
        }
        if (((cRam00834056 == '\t') && ((uGpffff885c & 0x400) != 0x400)) &&
           ((uRam00859fe0 & 0x80000000) != 0x80000000)) {
          uRam00859fe0 = uRam00859fe0 | 0x80000000;
          if (bRam0085a000 < 0x15) {
            fStack_8 = 75.0;
          }
          else if (bRam0085a000 < 0x3d) {
            fStack_8 = 50.0;
          }
          else {
            fStack_8 = 12.5;
          }
          uVar3 = FUN_00148df0(0,999999);
          if ((long)uVar3 < 0) {
            fStack_4 = (float)(uVar3 & 0xffffffff);
          }
          else {
            fStack_4 = (float)(int)uVar3;
          }
          fStack_4 = fStack_4 / 10000.0;
          if (fStack_4 <= fStack_8) {
            uRam00859fe0 = uRam00859fe0 | 0x200;
            FUN_00139920(0x10,0x30);
            sRam008350a2 = 0;
            FUN_001b7f40(0,6);
            FUN_001ff4f0(0,0x42b00000,0,0x18,0,uRam00835058);
            uRam00859fe0 = uRam00859fe0 & 0xfffffffb | 0x88;
          }
        }
      }
      else if (cRam00835056 == '0') {
        if ((cRam00834056 == '\a') || (cRam00834056 == '\b')) {
          sVar6 = sRam008350a2 + 1;
          uVar7 = sRam008350a2 + 1;
          sRam008350a2 = sVar6;
          if (400 < uVar7) {
            FUN_00139920(0x10,0x31);
            uRam00859fe0 = (uint)((ulong)((long)(int)(uRam00859fe0 & 0xfffffdff) << 0x21) >> 0x21);
          }
        }
        else {
          sRam008350a2 = 0;
        }
      }
      else if (cRam00835056 == '.') {
        if (cVar2 == '\0') {
          if ((uRam00859fe0 & 0x200) == 0x200) {
            FUN_00139920(0x10,0x30);
          }
          else {
            FUN_00139920(0x10,0x31);
          }
        }
      }
      else if (cRam00835056 == '\x1f') {
        if (cVar2 == '\0') {
          FUN_00138ce0(0x10);
        }
      }
      else if (cRam00835056 == '\x1e') {
        if ((bRam0085a2f5 < 6) || (0x14 < bRam0085a2f5)) {
          FUN_0013e2a0(0x10);
        }
        else {
          uRam00859fe0 = uRam00859fe0 & 0xfffffeff;
          cGpffff8aa4 = '\0';
          FUN_0013dff0(0x10,0x140,0,0x140);
          FUN_001be400();
        }
      }
      else if (cRam00835056 == '\x1d') {
        if (cVar2 == '\0') {
          FUN_00139920(0x10,0x1e);
        }
      }
      else if ((uRam00859fe0 & 0x200) == 0x200) {
        uVar7 = sRam008350a2 + 1;
        sRam008350a2 = sRam008350a2 + 1;
        if (400 < uVar7) {
          uRam00859fe0 = uRam00859fe0 & 0xfffffdff;
          sRam008350a2 = 0;
        }
      }
      else if ((uRam00859fe0 & 0x100) == 0x100) {
        FUN_0013e2a0(0x10);
        FUN_00139920(0x10,0x1d);
      }
      break;
    case '\x03':
      if ((uRam00859fe0 & 2) == 2) {
        FUN_0013e2a0(0x10);
        if (cRam00835056 != '$') {
          FUN_00139920(0x10,0x24);
        }
      }
      else {
        sVar6 = sRam008350a2 + -1;
        bVar1 = sRam008350a2 == 1;
        sRam008350a2 = sVar6;
        if (bVar1) {
          FUN_00139920(0x10,0x28);
          cGpffff8aa4 = '\x01';
        }
      }
      break;
    case '\x04':
      lVar4 = FUN_00151510(0x10);
      if (((lVar4 != 0) && ((uGpffff885c & 0x400) != 0x400)) &&
         ((uRam00859fe0 & 0x40000000) != 0x40000000)) {
        if (sRam00834058 != -1) {
          FUN_00124180(sRam00834058,afStack_40);
          FUN_00124180(uRam00835058,afStack_30);
          afStack_20[0] = afStack_30[0] - afStack_40[0];
          afStack_20[1] = 0.0;
          afStack_20[2] = fStack_28 - fStack_38;
          FUN_00128900(afStack_20);
          FUN_00137b90(0x10,afStack_20);
          FUN_0013e2a0(0x10);
          FUN_00138540(0x10,0x20);
        }
        uRam00859fe0 = uRam00859fe0 | 0x40000000;
      }
      if ((uRam00835050 & 4) != 4) {
        cGpffff8aa4 = '\0';
        if ((uRam00859fe0 & 2) == 2) {
          FUN_00139920(0x10,0x1a);
        }
        else if ((uRam00859fe0 & 0x200) != 0x200) {
          FUN_0013dff0(0x10,0x140,0,0x140);
        }
        uRam00859fe0 = uRam00859fe0 & 0xbfffffff;
      }
      break;
    case '\b':
      lVar4 = FUN_001c8b80();
      if ((lVar4 == 0) && (FUN_001c1f10(0x10), (uRam00835050 & 0x20) != 0x20)) {
        FUN_001c90f0();
      }
      break;
    case '\n':
      if ((uRam00835050 & 4) != 4) {
        FUN_00128870(afStack_20);
        afStack_20[2] = 1.0;
        FUN_00137b90(0x10,afStack_20);
        cGpffff8aa4 = '\0';
      }
      break;
    case '\v':
      if ((uRam00835050 & 4) != 4) {
        uRam00859fe0 = uRam00859fe0 & 0xdfffffff;
        cGpffff8aa4 = '\0';
        uVar5 = FUN_0013a620(0x10,1,1);
        if (cGpffff8898 == '\x05') {
          FUN_0013dff0(0x10,0x100,0,0x100);
          FUN_001be400();
        }
        else if (cGpffff8898 == '\x04') {
          FUN_001c9bf0(4,uVar5);
        }
        else if (cGpffff8898 == '\x03') {
          FUN_001c99c0();
        }
        else if (cGpffff8898 == '\x02') {
          FUN_0013e2a0(0x10);
          uRam00859fe0 = uRam00859fe0 & 0xffff3fff | 0x40000;
          FUN_001b9230(0xc499c000,0,0x451c4000);
        }
        else if (cGpffff8898 == '\x01') {
          FUN_001c9e00();
        }
        cGpffff8898 = '\0';
      }
      break;
    case '\f':
      if ((uRam00835050 & 4) != 4) {
        FUN_0013dff0(0x10,0x100,0,0x100);
        cGpffff8aa4 = '\0';
        uRam00859fe0 = uRam00859fe0 & 0xbfffffff;
      }
    }
  }
  return;
}

