
void FUN_001ab900(void)

{
  char cVar1;
  uint uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  byte bVar7;
  ulong uVar8;
  ulong unaff_s0;
  ulong unaff_s1;
  char unaff_s3_lo;
  char cVar9;
  char unaff_s5_lo;
  char cVar10;
  
  cVar1 = -1;
  cVar9 = -1;
  lVar6 = 0;
  uVar4 = 0;
  lVar3 = FUN_00219750(2);
  if (lVar3 != 0) {
    return;
  }
  lVar3 = FUN_00219750(3);
  if (lVar3 != 0) {
    return;
  }
  if (sGpffff882c == -1) {
    cVar1 = cVar9;
    switch(sGpffff8830) {
    case 0:
      unaff_s5_lo = '\x1a';
      unaff_s3_lo = '\f';
      lVar6 = 1;
      FUN_00149860(0xc1);
      cVar1 = '\0';
      break;
    case 1:
      unaff_s5_lo = '\x1a';
      unaff_s3_lo = '\x0f';
      lVar6 = 1;
      FUN_00149860(0xc2);
      cVar1 = '\0';
      break;
    case 2:
      bVar7 = bGpffff89d8 & 1;
      unaff_s5_lo = '\x10';
      unaff_s3_lo = '\x18';
      lVar6 = 1;
      FUN_00149860(0x39);
      FUN_0018ae90();
      cVar1 = bVar7 == 1;
      break;
    case 3:
      if (cGpffff89cc == '\0') {
        unaff_s5_lo = '\x10';
        unaff_s3_lo = '\x12';
        lVar6 = 1;
        FUN_00149860(0x37);
        cVar1 = '\b';
      }
      else if (cGpffff89cc == '\x01') {
        unaff_s5_lo = '\x10';
        unaff_s3_lo = '\x15';
        lVar6 = 1;
        FUN_00149860(0x38);
        cVar1 = '\b';
      }
      else if (cGpffff89cc == '\x02') {
        unaff_s5_lo = '\x10';
        unaff_s3_lo = '\x15';
        lVar6 = 1;
        FUN_00149860(0x38);
        cVar1 = '\b';
      }
      break;
    case 4:
      if (cGpffff89cc == '\0') {
        unaff_s5_lo = '\x10';
        unaff_s3_lo = '\x1b';
        lVar6 = 1;
        FUN_00149860(0x3b);
        FUN_0018ae90();
        uRam00859960 = 0;
        bRam00859962 = bRam00859962 | 0x40;
        cVar1 = '\b';
      }
      else if (cGpffff89cc == '\x01') {
        unaff_s5_lo = '\x10';
        unaff_s3_lo = '\x1e';
        lVar6 = 1;
        FUN_00149860(0x3c);
        cVar1 = '\b';
      }
      else if (cGpffff89cc == '\x02') {
        unaff_s5_lo = '\x10';
        unaff_s3_lo = '\x1e';
        lVar6 = 1;
        FUN_00149860(0x3c);
        cVar1 = '\b';
      }
      break;
    case 5:
      if (cGpffff89cc == '\0') {
        unaff_s5_lo = '\x15';
        unaff_s3_lo = '\x15';
        lVar6 = 1;
        FUN_00149860(0x91);
        cVar1 = '\x05';
      }
      else if (cGpffff89cc == '\x01') {
        unaff_s5_lo = '\x15';
        unaff_s3_lo = '\x12';
        lVar6 = 1;
        FUN_00149860(0x90);
        cVar1 = '\x05';
      }
      else {
        unaff_s5_lo = '\x15';
        unaff_s3_lo = '\x0f';
        lVar6 = 1;
        FUN_00149860(0x8f);
        cVar1 = '\x05';
      }
    }
  }
  else {
    if (sGpffff882c == 0x1c) {
      FUN_00223200();
      return;
    }
    if (sGpffff882c == 0x1b) {
      if (sGpffff8830 != 0) {
        uVar4 = FUN_00219830(3);
        FUN_00216d80(uVar4);
        return;
      }
      FUN_00216d40();
      return;
    }
    if (sGpffff882c == 0x1a) {
      unaff_s5_lo = '\x1a';
      if (sGpffff8830 == 0xf) {
        FUN_0014e740();
        FUN_001659a0();
        FUN_00161330(0,2);
        uVar4 = FUN_001613c0(6);
        FUN_00161310(uVar4);
        bGpffff89dc = bGpffff89dc & 0xfd;
        return;
      }
      if (sGpffff8830 == 0xc) {
        if (sRam0080dc7e == 3) {
          FUN_00178aa0(9,0xf);
          FUN_00178aa0(3,0xf);
          FUN_00178aa0(7,0xf);
          FUN_00178aa0(8,0xf);
          FUN_00178aa0(0x18,0xf);
        }
        else if (sRam0080dc7e == 2) {
          FUN_00178aa0(4,0xf);
          FUN_00178aa0(6,0xf);
          FUN_00178aa0(5,0xf);
          FUN_00178aa0(0x17,0xf);
        }
        else if (sRam0080dc7e == 1) {
          FUN_00178aa0(1,0xf);
          FUN_00178aa0(2,0xf);
          FUN_00178aa0(10,0xf);
          FUN_00178aa0(0x19,0xf);
        }
        FUN_00116978(0x833f40,0xff,8);
        uVar4 = FUN_0015e790();
        FUN_001e8ce0(0x1e,0x833f40,uVar4);
        sGpffff882c = 0xffff;
        sGpffff8830 = 1;
        return;
      }
      if (sGpffff8830 == 9) {
        if (cRam00833de8 != '\x01') {
          FUN_00116978(0x833e50,0xff,8);
          uVar4 = FUN_0015e790();
          FUN_001e8ce0(0,0x833e50,uVar4);
          sGpffff882c = 0xffff;
          sGpffff8830 = 0;
          return;
        }
        lVar6 = 3;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        unaff_s3_lo = '\t';
        lVar6 = 1;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        unaff_s3_lo = '\x06';
        lVar6 = 1;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          unaff_s3_lo = '\x03';
          lVar6 = 1;
        }
      }
    }
    else if (sGpffff882c == 0x19) {
      unaff_s5_lo = '\x19';
      if (sGpffff8830 == 6) {
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        unaff_s0 = 6;
        unaff_s1 = 10;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          uVar4 = FUN_00217e50();
          FUN_001e3a90(uVar4);
          return;
        }
      }
    }
    else if (sGpffff882c == 0x18) {
      unaff_s5_lo = '\x18';
      if (sGpffff8830 == 3) {
        FUN_00178aa0(7,5);
        FUN_00178aa0(6,5);
        if (bRam00859ffa < 0xf6) {
          bRam00859ffa = bRam00859ffa + 10;
        }
        else {
          bRam00859ffa = 0xff;
        }
        FUN_001b2160();
        uRam00859fe0 = uRam00859fe0 & 0xfc0fffff;
        FUN_00149760(0x9e);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          FUN_00178aa0(0xc,5);
          FUN_00178aa0(7,5);
          FUN_00178aa0(6,5);
          FUN_00149760(0x9d);
          unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
          unaff_s1 = 0x12;
        }
      }
    }
    else if (sGpffff882c == 0x17) {
      unaff_s5_lo = '\x17';
      if (sGpffff8830 == 0x1b) {
        FUN_00178b90(8);
        if ((bGpffff89d8 & 1) == 1) {
          unaff_s0 = 0xc;
        }
        else {
          unaff_s0 = 0xb;
        }
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x2a) {
        if ((uGpffff8998 & 0x100) == 0x100) {
          FUN_00149760(0x9b);
          uGpffff8998 = uGpffff8998 & 0xfeff;
        }
        if ((uGpffff8998 & 0x200) == 0x200) {
          FUN_00149760(0x9c);
          uGpffff8998 = uGpffff8998 & 0xfdff;
        }
        FUN_00149760(0x12);
        FUN_00178aa0(2,0xfffffffffffffff6);
        FUN_00178aa0(9,0xfffffffffffffff6);
        FUN_00178aa0(1,0xfffffffffffffffb);
        FUN_00178aa0(4,0xfffffffffffffffb);
        FUN_00178aa0(3,0xfffffffffffffffb);
        FUN_00178aa0(5,0xfffffffffffffffb);
        FUN_00178aa0(8,0xfffffffffffffffb);
        FUN_00178aa0(6,0xfffffffffffffffb);
        FUN_00178aa0(7,0xfffffffffffffffb);
        FUN_00178aa0(10,0xfffffffffffffffb);
        FUN_00178aa0(0xb,0xfffffffffffffffb);
        FUN_00178aa0(0xc,0xfffffffffffffffb);
        FUN_00178aa0(0xd,0xfffffffffffffffb);
        FUN_00178aa0(0xe,0xfffffffffffffffb);
        FUN_00178aa0(0xf,0xfffffffffffffffb);
        FUN_00178aa0(0x17,0xfffffffffffffffb);
        FUN_00178aa0(0x18,0xfffffffffffffffb);
        FUN_00178aa0(0x19,0xfffffffffffffffb);
        FUN_00178aa0(0x1a,0xfffffffffffffffb);
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 0x40;
        uVar4 = 0xc5;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x27) {
        uVar4 = FUN_00178aa0(2,0xffffffffffffffec);
        FUN_00178aa0(9,0xffffffffffffffec,uVar4);
        FUN_00178aa0(1,0xfffffffffffffff8);
        FUN_00178aa0(4,0xfffffffffffffff8);
        FUN_00178aa0(3,0xfffffffffffffff8);
        FUN_00178aa0(5,0xfffffffffffffff8);
        FUN_00178aa0(8,0xfffffffffffffff8);
        FUN_00178aa0(6,0xfffffffffffffff8);
        FUN_00178aa0(7,0xfffffffffffffff8);
        FUN_00178aa0(10,0xfffffffffffffff8);
        FUN_00178aa0(0xb,0xfffffffffffffff8);
        FUN_00178aa0(0xc,0xfffffffffffffff8);
        FUN_00178aa0(0xd,0xfffffffffffffff8);
        FUN_00178aa0(0xe,0xfffffffffffffff8);
        uVar4 = FUN_00178aa0(0xf,0xfffffffffffffff8);
        FUN_00178aa0(0x17,0xfffffffffffffff8,uVar4);
        FUN_00178aa0(0x18,0xfffffffffffffff8);
        FUN_00178aa0(0x19,0xfffffffffffffff8);
        FUN_00178aa0(0x1a,0xfffffffffffffff8);
        if ((uGpffff8998 & 0x40) == 0x40) {
          FUN_001497c0(0x94);
          uVar4 = FUN_001497c0(0x95);
          FUN_001497c0(0x96,uVar4);
          FUN_001497c0(0x97);
          FUN_001497c0(0xb6);
          FUN_00149760(0x99);
          FUN_001497c0(0x9a);
          FUN_00149760(0xbd);
          uGpffff8998 = uGpffff8998 & 0xffbf;
        }
        if ((uGpffff8998 & 0x80) == 0x80) {
          FUN_001497c0(0x6a);
          uVar4 = FUN_001497c0(0x6b);
          FUN_00149760(0x9a,uVar4);
          FUN_001497c0(0x69);
          FUN_00149760(0xbe);
          uGpffff8998 = uGpffff8998 & 0xff7f;
        }
        if ((uGpffff8998 & 0x100) == 0x100) {
          FUN_00149760(0x9b);
          uGpffff8998 = uGpffff8998 & 0xfeff;
        }
        uVar8 = (ulong)uGpffff8998 & 0x200;
        if (uVar8 == 0x200) {
          uVar8 = FUN_00149760(0x9c);
          uGpffff8998 = uGpffff8998 & 0xfdff;
        }
        FUN_00149760(0x12,uVar8);
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 0x40;
        uVar4 = 0xc5;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x15) {
        FUN_001c3df0();
        uGpffff8942 = 0;
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x12) {
        if (bRam00859ffa < 0xfc) {
          bRam00859ffa = bRam00859ffa + 4;
        }
        else {
          bRam00859ffa = 0xff;
        }
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        if (bRam00859ffa < 0xfe) {
          bRam00859ffa = bRam00859ffa + 2;
        }
        else {
          bRam00859ffa = 0xff;
        }
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        if (bRam00859ffa < 0xfb) {
          bRam00859ffa = bRam00859ffa + 5;
        }
        else {
          bRam00859ffa = 0xff;
        }
        FUN_00178aa0(9,5);
        uVar5 = FUN_001497c0(0x96);
        FUN_001497c0(0x97,uVar5);
        uRam00859fe0 = uRam00859fe0 & 0xf00ffffd | 0x20;
        FUN_001b2160();
        if ((bGpffff89d8 & 1) == 1) {
          unaff_s0 = 0xc;
        }
        else {
          unaff_s0 = 0xb;
        }
        unaff_s1 = 0x4d;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x24) {
        if (bRam00859ffa < 0xf6) {
          bRam00859ffa = bRam00859ffa + 10;
        }
        else {
          bRam00859ffa = 0xff;
        }
        FUN_00178aa0(9,0xfffffffffffffff8);
        uVar5 = FUN_001497c0(0x96);
        FUN_001497c0(0x97,uVar5);
        uRam00859fe0 = uRam00859fe0 & 0xf00ffffd | 0x20;
        FUN_001b2160();
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x21) {
        if (bRam00859ffa < 0xf6) {
          bRam00859ffa = bRam00859ffa + 10;
        }
        else {
          bRam00859ffa = 0xff;
        }
        uVar5 = FUN_00178aa0(2,0xfffffffffffffff8);
        FUN_001497c0(0x96,0x96,uVar5);
        FUN_001497c0(0x97);
        uRam00859fe0 = uRam00859fe0 & 0xf3fffffd | 0x20;
        FUN_001b2160();
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1e) {
        if (bRam00859ffa < 0xb) {
          bRam00859ffa = 0;
        }
        else {
          bRam00859ffa = bRam00859ffa - 10;
        }
        FUN_001497c0(0xb6);
        uRam00859fe0 = uRam00859fe0 & 0xfcffffff | 0x20;
        FUN_001b2160();
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x18) {
        if (bRam00859ffa < 0xfb) {
          bRam00859ffa = bRam00859ffa + 5;
        }
        else {
          bRam00859ffa = 0xff;
        }
        FUN_00178aa0(0x17,5);
        FUN_00178aa0(0x18,5);
        FUN_00178aa0(0x19,5);
        FUN_00149760(0x98);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xc) {
        if (bRam00859ffa < 9) {
          bRam00859ffa = 0;
        }
        else {
          bRam00859ffa = bRam00859ffa - 8;
        }
        FUN_00178aa0(9,0xfffffffffffffffb);
        FUN_001497c0(0x96);
        FUN_001497c0(0x97);
        FUN_001b2160();
        uRam00859fe0 = uRam00859fe0 & 0xf00ffffd | 0x20;
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        uRam00859fe0 = uRam00859fe0 & 0xff3fffff;
        FUN_001b2160();
        uRam00859fe0 = uRam00859fe0 & 0xfc0fffff;
        if (bRam00859ffa < 0xb) {
          bRam00859ffa = 0;
        }
        else {
          bRam00859ffa = bRam00859ffa - 10;
        }
        FUN_001497c0(0x95);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        uRam00859fe0 = uRam00859fe0 & 0xffcfffff;
        FUN_001b2160();
        uRam00859fe0 = uRam00859fe0 & 0xfc0fffff;
        if (bRam00859ffa < 0xb) {
          bRam00859ffa = 0;
        }
        else {
          bRam00859ffa = bRam00859ffa - 10;
        }
        FUN_001497c0(0x94);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          if (bRam00859ffa < 0xf5) {
            bRam00859ffa = bRam00859ffa + 5;
          }
          else {
            bRam00859ffa = 0xff;
          }
          FUN_001497c0(0x94);
          uRam00859fe0 = uRam00859fe0 & 0xffcfffff;
          unaff_s0 = 2;
          unaff_s1 = 1;
        }
      }
    }
    else if (sGpffff882c == 0x16) {
      unaff_s5_lo = '\x16';
      if (sGpffff8830 == 0x1e) {
        uGpffff8942 = 0;
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1b) {
        FUN_00178aa0(10,3);
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x18) {
        FUN_00178aa0(7,3);
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x15) {
        FUN_00178aa0(6,3);
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x12) {
        FUN_00178aa0(9,3);
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        FUN_00178aa0(8,3);
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xc) {
        uVar2 = FUN_00141840(5);
        if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x65) {
          FUN_00178aa0(5,3);
        }
        else {
          FUN_00178aa0(5,5);
        }
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        uVar2 = FUN_00141840(4);
        if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x65) {
          FUN_00178aa0(4,3);
        }
        else {
          FUN_00178aa0(4,5);
        }
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        uVar2 = FUN_00141840(3);
        if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x65) {
          FUN_00178aa0(3,3);
        }
        else {
          FUN_00178aa0(3,5);
        }
        uGpffff8942 = 0;
        FUN_001c3df0();
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        uVar2 = FUN_00141840(2);
        if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x65) {
          uVar4 = FUN_00178aa0(2,3);
        }
        else {
          uVar4 = FUN_00178aa0(2,5);
        }
        uGpffff8942 = 0;
        FUN_001c3df0(uVar4);
        lVar6 = 2;
        uGpffff8998 = uGpffff8998 & 0xffef;
        bRam0085996d = bRam0085996d | 1;
        uVar4 = 0xc4;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          uVar2 = FUN_00141840(1);
          if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x65) {
            FUN_00178aa0(1,3);
          }
          else {
            FUN_00178aa0(1,5);
          }
          uGpffff8942 = 0;
          FUN_001c3df0();
          lVar6 = 2;
          uGpffff8998 = uGpffff8998 & 0xffef;
          bRam0085996d = bRam0085996d | 1;
          uVar4 = 0xc4;
        }
      }
    }
    else if (sGpffff882c == 0x15) {
      unaff_s5_lo = '\x15';
      if ((((((sGpffff8830 == 0x2b) || (sGpffff8830 == 0x2a)) || (sGpffff8830 == 0x27)) ||
           ((sGpffff8830 == 0x24 || (sGpffff8830 == 0x21)))) || (sGpffff8830 == 0x1e)) ||
         (sGpffff8830 == 0x1b)) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x18) {
        uVar4 = FUN_00178d20(0x40);
        FUN_00222d90(6,uVar4);
        return;
      }
      if (sGpffff8830 == 0x15) {
        FUN_00178aa0(8,0xfffffffffffffffb);
        FUN_00149760(0x90);
        unaff_s0 = 5;
        unaff_s1 = 8;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x12) {
        uVar5 = FUN_00178aa0(8,2);
        FUN_00149760(0x90,uVar5);
        unaff_s0 = 5;
        unaff_s1 = 8;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        FUN_00178aa0(8,5);
        FUN_00149760(0x91);
        unaff_s0 = 5;
        unaff_s1 = 8;
        uRam00859969 = 0;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        if (cRam00833de8 == '\0') {
          FUN_00178aa0(8,3);
          uVar4 = FUN_001497c0(0x90);
          FUN_00219830(1,uVar4);
          FUN_00219830(2);
          uVar4 = FUN_00219830(3);
          uGpffff89e0 = FUN_0015e790(uVar4);
          FUN_0021b390();
          sGpffff882c = 0xffff;
          sGpffff8830 = 5;
          return;
        }
        uVar5 = FUN_00178aa0(8,0xfffffffffffffffb);
        FUN_00149760(0x90,uVar5);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        FUN_00178aa0(8,3);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        FUN_00178aa0(8,5);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          FUN_00178aa0(8,3);
          FUN_00149760(0x8f);
          FUN_0016bff0(0x5a,1);
          unaff_s0 = 5;
          unaff_s1 = (ulong)bGpffff8846;
        }
      }
    }
    else if (sGpffff882c == 0x14) {
      unaff_s5_lo = '\x14';
      if (sGpffff8830 == 0x1b) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x18) {
        FUN_00178aa0(2,3);
        uVar4 = FUN_00178aa0(8,2);
        uVar4 = FUN_00178d20(0x100,uVar4);
        FUN_00222d90(8,uVar4);
        return;
      }
      if (sGpffff8830 == 0xc) {
        uVar5 = FUN_00178aa0(2,4);
        FUN_001497c0(0x8a,uVar5);
        unaff_s3_lo = '\x0f';
        lVar6 = 1;
        FUN_00149860(0x85);
        uRam00859967 = 0;
        bRam0085996d = bRam0085996d & 0xf7;
        cVar1 = '\x04';
      }
      else if (sGpffff8830 == 0x12) {
        FUN_00178aa0(2,4);
        uVar5 = FUN_001497c0(0x8b);
        FUN_00149760(0x8d,uVar5);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        uVar5 = FUN_00178aa0(2,3);
        FUN_00149760(0x8a,uVar5);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        FUN_00178aa0(2,5);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x15) {
        FUN_00178aa0(2,4);
        uVar5 = FUN_001497c0(0x8d);
        FUN_00149760(0x8e,uVar5);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0;
        bRam0085996d = bRam0085996d & 0xf7;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        FUN_00149760(0x8b);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        FUN_00178aa0(0x17,3);
        FUN_00178aa0(0x18,3);
        FUN_00178aa0(0x19,3);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          unaff_s3_lo = '\x03';
          lVar6 = 1;
          FUN_00149860(0x81);
          cVar1 = '\x06';
        }
      }
    }
    else if (sGpffff882c == 0x13) {
      unaff_s5_lo = '\x13';
      if (sGpffff8830 == 0x1e) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x1b) {
        uVar4 = FUN_00178d20(8);
        FUN_00222d90(3,uVar4);
        return;
      }
      if (sGpffff8830 == 0x12) {
        FUN_00149760(0xb8);
        FUN_0016bff0(0x5c,1);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        FUN_00149760(0x88);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        FUN_00178aa0(0x1a,3);
        FUN_00178aa0(0x17,3);
        FUN_00178aa0(0x18,3);
        FUN_00178aa0(0x19,3);
        unaff_s0 = 4;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x18) {
        FUN_00178aa0(6,5);
        FUN_00178aa0(7,5);
        FUN_00178aa0(0x1a,3);
        FUN_00178aa0(0x17,3);
        FUN_00178aa0(0x18,3);
        uVar5 = FUN_00178aa0(0x19,3);
        FUN_00149760(0x89,uVar5);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        FUN_00149860(0x7d);
        uRam00859966 = 0;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x15) {
        FUN_00178aa0(6,3);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        FUN_00178aa0(6,5);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xc) {
        FUN_00178aa0(6,3);
        FUN_00178aa0(7,5);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        bRam0085996f = bRam0085996f | 1;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        FUN_00178aa0(6,5);
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          uVar5 = FUN_00178aa0(6,3);
          FUN_00149760(0x86,uVar5);
          FUN_0016bff0(0x55,1);
          unaff_s0 = 5;
          unaff_s1 = (ulong)bGpffff8846;
        }
      }
    }
    else if (sGpffff882c == 0x12) {
      unaff_s5_lo = '\x12';
      if (sGpffff8830 == 0x27) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x2a) {
        FUN_00178d20(0x10);
        FUN_00222d90(4);
        return;
      }
      if (sGpffff8830 == 0x24) {
        bVar7 = bGpffff89d8 & 1;
        unaff_s3_lo = '*';
        lVar6 = 1;
        FUN_00149860(0x73);
        cVar1 = bVar7 == 1;
      }
      else if (sGpffff8830 == 0x1b) {
        FUN_00178aa0(7,3);
        unaff_s3_lo = '\x1e';
        lVar6 = 1;
        FUN_00149860(0x6f);
        cVar1 = '\t';
      }
      else if (sGpffff8830 == 0x18) {
        FUN_00178aa0(3,3);
        unaff_s3_lo = '\x1e';
        lVar6 = 1;
        FUN_00149860(0x6f);
        cVar1 = '\t';
      }
      else if (sGpffff8830 == 0x2d) {
        uVar2 = FUN_00141840(3);
        bVar7 = *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30);
        uVar2 = FUN_00141840(7);
        if ((*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < bVar7) ||
           (uVar2 = FUN_00141840(7), *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x79)) {
          unaff_s3_lo = '\x18';
          FUN_00149860(0x6d);
        }
        else {
          uVar2 = FUN_00141840(7);
          if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x78) {
            unaff_s3_lo = '\x1e';
            FUN_00149860(0x6f);
          }
          else {
            unaff_s3_lo = '\x1b';
            FUN_00149860(0x6e);
          }
        }
        lVar6 = 1;
        cVar1 = '\t';
      }
      else if (sGpffff8830 == 0x15) {
        unaff_s3_lo = '-';
        lVar6 = 1;
        FUN_00149860(0x74);
        cVar1 = '\t';
      }
      else if (sGpffff8830 == 0x1e) {
        FUN_00178aa0(3,2);
        FUN_00178aa0(5,2);
        FUN_00178aa0(4,2);
        FUN_00178aa0(7,2);
        unaff_s0 = 9;
        unaff_s1 = 0x25;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x12) {
        FUN_00178aa0(5,5);
        uVar5 = FUN_001497c0(0x83);
        FUN_00149760(0x84,uVar5);
        FUN_0016c7b0(0x4e,1);
        unaff_s0 = 9;
        unaff_s1 = 0x25;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        FUN_00178aa0(0x1a,3);
        FUN_00178aa0(0x17,2);
        FUN_00178aa0(0x18,2);
        FUN_00178aa0(0x19,2);
        FUN_001497c0(0x82);
        FUN_00149760(0x83);
        FUN_0016bff0(0x4e,1);
        if ((bGpffff89d8 & 1) == 1) {
          unaff_s0 = 0xc;
        }
        else {
          unaff_s0 = 0xb;
        }
        unaff_s1 = 0x4d;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xc) {
        uVar5 = FUN_00178aa0(0x1a,5);
        FUN_001497c0(0x80,0x80,uVar5);
        FUN_00149760(0x82);
        FUN_0016c7b0(0x4d,1);
        unaff_s0 = 6;
        unaff_s1 = 10;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        FUN_001497c0(0x7f);
        FUN_00178aa0(0x1a,3);
        unaff_s0 = 6;
        unaff_s1 = 10;
        bRam0085996d = bRam0085996d | 0x80;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        unaff_s0 = 9;
        unaff_s1 = 0xf;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x21) {
        FUN_001497c0(0x84);
        FUN_00178aa0(5,5);
        FUN_00149760(0x85);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 3) {
        FUN_00178aa0(4,2);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          FUN_00178aa0(5,5);
          FUN_00149760(0x7f);
          unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
          unaff_s1 = 0x12;
        }
      }
    }
    else if (sGpffff882c == 0x11) {
      unaff_s5_lo = '\x11';
      if (sGpffff8830 == 99) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x60) {
        FUN_00178d20(0x20);
        FUN_001497c0(0x7e);
        FUN_00222d90(5);
        return;
      }
      if (sGpffff8830 == 0x5a) {
        FUN_001497c0(0xbf);
        unaff_s3_lo = ']';
        lVar6 = 1;
        FUN_00149860(0x62);
        uRam00859964 = 0;
        cVar1 = '\x05';
      }
      else if (sGpffff8830 == 0x57) {
        FUN_001497c0(0xbf);
        unaff_s3_lo = ']';
        lVar6 = 1;
        FUN_00149860(0x62);
        uRam00859964 = 0;
        cVar1 = '\x05';
      }
      else if ((((sGpffff8830 == 0x45) || (sGpffff8830 == 0x3f)) || (sGpffff8830 == 0x39)) ||
              ((sGpffff8830 == 0x33 || (sGpffff8830 == 0x2d)))) {
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x42) {
        FUN_00178aa0(5,3);
        uVar5 = FUN_00149760(0x76);
        FUN_001497c0(0x75,uVar5);
        unaff_s3_lo = 'E';
        lVar6 = 1;
        FUN_00149860(0x5a);
        cVar1 = '\t';
      }
      else if (sGpffff8830 == 0x3c) {
        FUN_00178aa0(3,3);
        uVar5 = FUN_00149760(0x76);
        FUN_001497c0(0x74,uVar5);
        unaff_s3_lo = '?';
        lVar6 = 1;
        FUN_00149860(0x58);
        cVar1 = '\t';
      }
      else if (sGpffff8830 == 0x36) {
        FUN_00178aa0(2,3);
        uVar5 = FUN_00149760(0x76);
        FUN_001497c0(0x73,uVar5);
        unaff_s3_lo = '9';
        lVar6 = 1;
        FUN_00149860(0x56);
        cVar1 = '\x04';
      }
      else if (sGpffff8830 == 0x30) {
        uVar5 = FUN_00178aa0(1,3);
        FUN_00149760(0x76,uVar5);
        FUN_001497c0(0x72);
        unaff_s3_lo = '3';
        lVar6 = 1;
        FUN_00149860(0x54);
        cVar1 = '\x03';
      }
      else if (sGpffff8830 == 0x2a) {
        uVar5 = FUN_00178aa0(4,3);
        FUN_00149760(0x76,0x76,uVar5);
        FUN_001497c0(0x71);
        unaff_s3_lo = '-';
        lVar6 = 1;
        FUN_00149860(0x52);
        cVar1 = '\x05';
      }
      else if (sGpffff8830 == 0x24) {
        FUN_0016bff0(0x4b,1);
        uVar5 = FUN_00178aa0(5,5);
        FUN_00149760(0x70,uVar5);
        FUN_001497c0(0x6e);
        unaff_s0 = 9;
        unaff_s1 = 0x25;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x21) {
        uVar2 = FUN_00141840(3);
        if (0x31 < *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30)) {
          FUN_0016bff0(0x4b,1);
          FUN_00178aa0(3,5);
        }
        FUN_00149760(0x70);
        FUN_001497c0(0x6e);
        unaff_s0 = 9;
        unaff_s1 = 0x25;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1e) {
        unaff_s0 = 3;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1b) {
        unaff_s3_lo = '\x1e';
        lVar6 = 1;
        FUN_00149860(0x4d);
        cVar1 = '\x03';
      }
      else if (sGpffff8830 == 0x18) {
        uVar5 = FUN_00149760(0x6f);
        unaff_s3_lo = '\x1b';
        lVar6 = 1;
        FUN_00149860(0x4c,0x1b,uVar5);
        cVar1 = '\x12';
      }
      else if (sGpffff8830 == 0x15) {
        unaff_s0 = 5;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x5d) {
        FUN_00149760(0x7e);
        unaff_s0 = 5;
        unaff_s1 = 0x1f;
        cVar1 = cVar9;
      }
      else if ((sGpffff8830 == 0x12) || (sGpffff8830 == 3)) {
        unaff_s0 = 5;
        unaff_s1 = 0x1f;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x54) {
        FUN_00178aa0(9,3);
        FUN_00149760(0x76);
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x51) {
        FUN_00178aa0(7,3);
        FUN_00149760(0x76);
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x4e) {
        FUN_00178aa0(6,3);
        FUN_00149760(0x76);
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x4b) {
        FUN_00178aa0(8,3);
        FUN_00149760(0x76);
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x27) {
        uVar5 = FUN_00178aa0(4,3);
        FUN_001497c0(0x70,uVar5);
        FUN_0016c7b0(0x4b,1);
        cVar1 = FUN_00178600();
        if (cVar1 == '\x05') {
          uVar2 = FUN_00141840(5);
          if (99 < *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30)) {
            FUN_00149760(0x75);
          }
        }
        else if (cVar1 == '\x03') {
          uVar2 = FUN_00141840(3);
          if (99 < *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30)) {
            FUN_00149760(0x74);
          }
        }
        else if (cVar1 == '\x02') {
          uVar2 = FUN_00141840(2);
          if (99 < *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30)) {
            FUN_00149760(0x73);
          }
        }
        else if (cVar1 == '\x01') {
          uVar2 = FUN_00141840(1);
          if (99 < *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30)) {
            FUN_00149760(0x72);
          }
        }
        else if ((cVar1 == '\x04') &&
                (uVar2 = FUN_00141840(4), 99 < *(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30))) {
          FUN_00149760(0x71);
        }
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        cVar1 = cVar9;
      }
      else if ((sGpffff8830 == 0xf) || (sGpffff8830 == 0xc)) {
        if (cRam00833de8 == '\0') {
          FUN_00178aa0(4,5);
          if (bGpffff8940 < 0x14) {
            bGpffff8940 = 0;
          }
          else {
            bGpffff8940 = bGpffff8940 - 0x14;
          }
        }
        else {
          FUN_00178aa0(4,0xfffffffffffffffd);
        }
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        if (sGpffff8830 == 0xc) {
          uRam0085996e = 0;
          cVar1 = cVar9;
        }
        else {
          uRam0085996e = 0xff;
          cVar1 = cVar9;
        }
      }
      else if (sGpffff8830 == 9) {
        uVar5 = FUN_00178aa0(4,2);
        FUN_00149760(0xa0,uVar5);
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        uRam0085996e = 0;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        FUN_0016c7b0(0x4a,1);
        FUN_00178aa0(4,3);
        uVar5 = FUN_00149760(0x6e);
        FUN_00149760(0xbf,uVar5);
        unaff_s0 = 0x17;
        unaff_s1 = 0x33;
        uRam0085996e = 0;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          FUN_00178aa0(4,2);
          FUN_00149760(0x6d);
          unaff_s3_lo = '\x03';
          lVar6 = 1;
          FUN_00149860(0x44);
          cVar1 = '\x05';
        }
      }
    }
    else if (sGpffff882c == 0x10) {
      unaff_s5_lo = '\x10';
      if (sGpffff8830 == 0x30) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x2d) {
        FUN_00178d20(0x80);
        FUN_0018ae90();
        FUN_00222d90(7);
        return;
      }
      if (sGpffff8830 == 0x18) {
        FUN_001b24b0();
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1e) {
        uVar5 = FUN_00178aa0(2,0xfffffffffffffffe);
        FUN_00149760(0x6b,uVar5);
        unaff_s0 = 8;
        unaff_s1 = 0xe;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1b) {
        FUN_00178aa0(2,5);
        FUN_001497c0(0x6b);
        FUN_00149760(0xb3);
        unaff_s0 = 8;
        unaff_s1 = 0xe;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x15) {
        FUN_00178aa0(9,0xfffffffffffffffe);
        FUN_00149760(0x6a);
        unaff_s0 = 8;
        unaff_s1 = 0xe;
        cVar1 = cVar9;
      }
      else {
        if (sGpffff8830 == 0x12) {
          FUN_00178aa0(9,3);
          FUN_001497c0(0x6a);
          FUN_00149760(0xb2);
          FUN_0014e740();
          FUN_0014d170(8);
          FUN_0014e450();
          FUN_001378a0();
          FUN_00219830(1);
          FUN_00219830(2);
          FUN_00219830(3);
          uGpffff89e0 = FUN_0015e790();
          FUN_0021eb70(2);
          sGpffff882c = 0xffff;
          sGpffff8830 = 4;
          return;
        }
        if (sGpffff8830 == 0xf) {
          FUN_0014e740();
          FUN_0014d170(8);
          FUN_0014e450();
          FUN_001378a0();
          FUN_00219830(1);
          uVar4 = FUN_00219830(2);
          uVar4 = FUN_00219830(3,uVar4);
          uGpffff89e0 = FUN_0015e790(uVar4);
          FUN_0021eb70(9);
          sGpffff882c = 0xffff;
          sGpffff8830 = 3;
          return;
        }
        if (sGpffff8830 == 0xc) {
          if (cRam00833de8 == '\0') {
            FUN_001497c0(0x6a);
            unaff_s3_lo = '\x0f';
            lVar6 = 1;
            FUN_00149860(0x35);
            cVar1 = '\b';
          }
          else {
            FUN_00149760(0x6a);
            unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
            unaff_s1 = 0x12;
            cVar1 = cVar9;
          }
        }
        else if (sGpffff8830 == 9) {
          unaff_s0 = 7;
          unaff_s1 = (ulong)bGpffff8846;
          cVar1 = cVar9;
        }
        else if (sGpffff8830 == 0x2a) {
          if (bRam00859fc8 < 200) {
            if (bRam00859fc8 < 0x97) {
              FUN_00178aa0(9,2);
            }
            else {
              FUN_00178aa0(9,6);
            }
          }
          else {
            FUN_00178aa0(9,10);
          }
          FUN_00149760(0x6c);
          unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
          unaff_s1 = 0x12;
          cVar1 = cVar9;
        }
        else if (sGpffff8830 == 0x27) {
          FUN_0016bff0(0x4c,1);
          unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
          unaff_s1 = 0x12;
          cVar1 = cVar9;
        }
        else {
          if (sGpffff8830 != 0x24) {
            if ((sGpffff8830 != 6) && (sGpffff8830 != 3)) {
              cVar1 = cVar9;
              if (sGpffff8830 == 0) {
                if (cRam00833de8 != '\x01') {
                  FUN_00178aa0(9,5);
                  FUN_00149760(0x69);
                  FUN_001497c0(0xb1);
                  FUN_00116978(0x833e60,0xff,8);
                  uVar4 = FUN_0015e790();
                  FUN_001e8ce0(2,0x833e60,uVar4);
                  sGpffff882c = 0xffff;
                  sGpffff8830 = 2;
                  FUN_00149860(0x30);
                  return;
                }
                FUN_00178aa0(9,0xfffffffffffffffd);
                FUN_00149760(0xb1);
                uRam00859960 = 0;
                uRam00859fc0 = 0;
                unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
                unaff_s1 = 0x12;
              }
              goto switchD_001b1724_default;
            }
            FUN_00178aa0(9,2);
          }
          unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
          unaff_s1 = 0x12;
          cVar1 = cVar9;
        }
      }
    }
    else if (sGpffff882c == 0xf) {
      unaff_s5_lo = '\x0f';
      if (((sGpffff8830 == 0x2e) || (sGpffff8830 == 0x2d)) || (sGpffff8830 == 0x2a)) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x27) {
        FUN_00178d20(4);
        FUN_00222d90(2);
        return;
      }
      if (sGpffff8830 == 0x1b) {
        unaff_s0 = 6;
        unaff_s1 = 10;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x18) {
        unaff_s0 = 0x13;
        unaff_s1 = 0x2e;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x24) {
        FUN_001497c0(0x66);
        FUN_00149760(0x68);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x21) {
        FUN_001497c0(0x67);
        FUN_00149760(0xc0);
        unaff_s0 = 6;
        unaff_s1 = 10;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x1e) {
        FUN_00178aa0(1,3);
        FUN_00178aa0(8,3);
        FUN_00149760(0x68);
        FUN_001497c0(0x66);
        unaff_s0 = 6;
        unaff_s1 = 10;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x12) {
        FUN_00178aa0(1,3);
        FUN_00178aa0(8,3);
        FUN_00178aa0(7,3);
        FUN_00178aa0(0x17,3);
        FUN_00178aa0(0x18,3);
        FUN_00178aa0(0x19,3);
        FUN_00178aa0(0x1a,3);
        FUN_00178aa0(4,1);
        FUN_00178aa0(2,1);
        FUN_00178aa0(3,1);
        FUN_00178aa0(5,1);
        FUN_00178aa0(6,1);
        FUN_00178aa0(9,1);
        FUN_00178aa0(10,1);
        FUN_00178aa0(0xb,1);
        FUN_00178aa0(0xc,1);
        FUN_00178aa0(0xd,1);
        FUN_00178aa0(0xe,1);
        FUN_00178aa0(0xf,1);
        FUN_00149760(0x66);
        bRam0085996d = bRam0085996d | 2;
        unaff_s0 = 6;
        unaff_s1 = 10;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xf) {
        unaff_s0 = 4;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0xc) {
        FUN_00149760(0xb7);
        FUN_0016bff0(0x4f,1);
        bRam0085996d = bRam0085996d & 0xfd;
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 0x15) {
        FUN_00149760(0x67);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 9) {
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
      }
      else if (sGpffff8830 == 6) {
        FUN_001497c0(99);
        FUN_00178aa0(0xf,5);
        FUN_00178aa0(1,2);
        bRam0085996d = bRam0085996d | 2;
        uVar2 = FUN_00141840(8);
        if (*(byte *)(((uVar2 & 0xff) - 1) * 2 + 0x859e30) < 0x50) {
          unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
          unaff_s1 = 0x12;
          cVar1 = cVar9;
        }
        else {
          bVar7 = bGpffff89d8 & 1;
          unaff_s3_lo = '\t';
          lVar6 = 1;
          FUN_00149860(0x22);
          cVar1 = bVar7 == 1;
        }
      }
      else if (sGpffff8830 == 3) {
        FUN_00178aa0(1,3);
        FUN_001497c0(0x62);
        FUN_00149760(99);
        unaff_s0 = 3;
        unaff_s1 = 0x1a;
        cVar1 = cVar9;
      }
      else {
        cVar1 = cVar9;
        if (sGpffff8830 == 0) {
          FUN_00149760(0x62);
          unaff_s0 = 4;
          unaff_s1 = (ulong)bGpffff8846;
        }
      }
    }
    else if (sGpffff882c == 0xe) {
      unaff_s5_lo = '\x0e';
      cVar10 = '\x0e';
      if ((sGpffff8830 == 0x43) || (sGpffff8830 == 0x40)) {
        FUN_00223260();
        return;
      }
      if (sGpffff8830 == 0x58) {
        FUN_00178d20(1);
        FUN_0018aec0();
        uVar4 = FUN_00137930(0x10);
        FUN_00222d90(0,uVar4);
        return;
      }
      if (sGpffff8830 == 0x55) {
        FUN_00178d20(2);
        FUN_00222d90(1);
        return;
      }
      if (sGpffff8830 == 0x49) {
        lVar6 = 1;
        lVar3 = FUN_00149940(10);
        cVar1 = '\x04';
        if (lVar3 == 0) {
          unaff_s3_lo = 'U';
          FUN_00149860(0x1d);
          unaff_s5_lo = cVar10;
        }
        else {
          unaff_s3_lo = 'X';
          FUN_00149860(0x1e);
          unaff_s5_lo = cVar10;
        }
      }
      else if (sGpffff8830 == 0x46) {
        unaff_s3_lo = 'I';
        lVar6 = 1;
        FUN_00149860(0x19);
        cVar1 = '\x04';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x3d) {
        unaff_s3_lo = 'F';
        lVar6 = 1;
        FUN_00149860(0x18);
        cVar1 = '\x04';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x52) {
        unaff_s3_lo = '=';
        lVar6 = 1;
        FUN_00149860(0x15);
        cVar1 = '\x04';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x4f) {
        unaff_s3_lo = 'R';
        lVar6 = 1;
        FUN_00149860(0x1c);
        cVar1 = '\x04';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x4c) {
        unaff_s3_lo = 'O';
        lVar6 = 1;
        FUN_00149860(0x1b);
        cVar1 = '\x04';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x37) {
        unaff_s3_lo = ':';
        lVar6 = 1;
        FUN_00149860(0x14);
        cVar1 = '\x03';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x31) {
        FUN_00149760(0x60);
        unaff_s3_lo = '4';
        lVar6 = 1;
        FUN_00149860(0x12);
        cVar1 = '\x03';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x25) {
        unaff_s3_lo = '(';
        lVar6 = 1;
        FUN_00149860(0xe);
        cVar1 = '\n';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x22) {
        unaff_s3_lo = '%';
        lVar6 = 1;
        FUN_00149860(0xd);
        cVar1 = '\t';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x1f) {
        FUN_00178aa0(3,3);
        FUN_00149760(0x5e);
        unaff_s0 = 9;
        unaff_s1 = 0x25;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x19) {
        unaff_s3_lo = '\x1c';
        lVar6 = 1;
        FUN_00149860(10);
        cVar1 = '\x03';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x1c) {
        FUN_001497c0(0x5c);
        FUN_00149760(0x5d);
        bRam0085996d = bRam0085996d & 0xdf;
        unaff_s0 = 3;
        unaff_s1 = 4;
        uGpffff88d2 = 6;
        FUN_00137930(0x41);
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x3a) {
        FUN_001497c0(0x60);
        FUN_00149760(0x61);
        bRam0085996d = bRam0085996d & 0xef;
        unaff_s0 = 3;
        unaff_s1 = 4;
        uGpffff88d2 = 6;
        FUN_00137930(0x41);
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if ((sGpffff8830 == 0x34) || (sGpffff8830 == 0x16)) {
        unaff_s0 = 3;
        unaff_s1 = 4;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x13) {
        FUN_00149760(0x5c);
        unaff_s3_lo = '\x16';
        lVar6 = 1;
        FUN_00149860(8);
        cVar1 = '\x03';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x2e) {
        unaff_s0 = 3;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x10) {
        unaff_s0 = 3;
        unaff_s1 = (ulong)bGpffff8846;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x2b) {
        FUN_00178aa0(3,5);
        FUN_00149760(0x5f);
        bGpffff88d0 = bGpffff88d0 | 8;
        uGpffff88d2 = 0;
        uGpffff88d3 = 3;
        bRam0085996d = bRam0085996d | 0x10;
        unaff_s0 = 10;
        unaff_s1 = 0x11;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0xd) {
        FUN_00178aa0(10,5);
        FUN_00149760(0x5b);
        bGpffff88d0 = bGpffff88d0 | 8;
        uGpffff88d2 = 0;
        uGpffff88d3 = 3;
        bRam0085996d = bRam0085996d | 0x20;
        unaff_s0 = 10;
        unaff_s1 = 0x11;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0x28) {
        FUN_001497c0(0x5a);
        FUN_001497c0(0x5e);
        unaff_s0 = 10;
        unaff_s1 = 0x11;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 10) {
        FUN_001497c0(0x5a);
        FUN_001497c0(0x5e);
        unaff_s0 = 10;
        unaff_s1 = 0x11;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 9) {
        unaff_s3_lo = '\n';
        lVar6 = 1;
        FUN_00149860(4);
        FUN_0018aec0();
        cVar1 = '\n';
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 6) {
        FUN_00149760(0x5a);
        FUN_0016bff0(0x49,1);
        unaff_s0 = (ulong)((bGpffff89d8 & 1) == 1);
        unaff_s1 = 0x12;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 3) {
        unaff_s0 = 5;
        unaff_s1 = 8;
        cVar1 = cVar9;
        unaff_s5_lo = cVar10;
      }
      else if (sGpffff8830 == 0) {
        if (cRam00833de8 == '\0') {
          FUN_00178aa0(10,5);
        }
        else {
          FUN_00178aa0(10,0xfffffffffffffffd);
        }
        unaff_s3_lo = '\x03';
        lVar6 = 1;
        FUN_00149860(1);
        cVar1 = '\x05';
      }
    }
  }
switchD_001b1724_default:
  if (lVar6 == 1) {
    uGpffff8834 = uGpffff8834 | 1;
    if (cVar1 != -1) {
      FUN_0014e740();
      uVar4 = FUN_0014d170(cVar1);
      uVar4 = FUN_0017c050(uVar4);
      if (bGpffff8844 < 0xb) {
        FUN_00164680(bGpffff8844,uVar4);
        uVar4 = FUN_001ff9b0(0x19);
        FUN_001ff9b0(0x1a,uVar4);
      }
    }
    FUN_0014e450();
    FUN_001fad00(unaff_s5_lo,unaff_s3_lo,0x17);
    if ((unaff_s5_lo == '\x10') && (unaff_s3_lo == '\x15')) {
      if (cGpffff89cc == '\0') {
        sRam0080dc7e = 0;
      }
      else if (cGpffff89cc == '\x01') {
        sRam0080dc7e = 0;
      }
      else if (cGpffff89cc == '\x02') {
        sRam0080dc7e = 1;
      }
    }
    if ((unaff_s5_lo == '\x10') && (unaff_s3_lo == '\x1e')) {
      if (cGpffff89cc == '\0') {
        sRam0080dc7e = 0;
        uRam00859960 = 0;
      }
      else if (cGpffff89cc == '\x01') {
        sRam0080dc7e = 0;
      }
      else if (cGpffff89cc == '\x02') {
        sRam0080dc7e = 1;
      }
    }
    FUN_00161620(0,10);
  }
  else if (lVar6 == 2) {
    FUN_00219830(1);
    uVar5 = FUN_00219830(2);
    FUN_00219830(3,uVar5);
    if ((bRam0085a2f5 < 0x18) && (bRam0085a2f6 = bRam0085a2f6 + 1, 0x1e < bRam0085a2f6)) {
      cRam0085a2f7 = cRam0085a2f7 + '\x01';
      bRam0085a2f6 = 1;
    }
    FUN_001c3df0();
    bGpffff8990 = bRam0085a2f5;
    uGpffff8991 = uRam0085a2f4;
    uGpffff885c = uGpffff885c | 1;
    uVar5 = FUN_0015e770(0x14);
    uGpffff8860 = 0;
    FUN_00161310(uVar5);
    uVar5 = FUN_0021a780();
    uGpffff8a98 = 0;
    FUN_0014b770(uRam0083c4c0,uRam0083c4c4,uRam0083c4c8,0x83c490,uVar5);
    FUN_0014b770(uRam0083c480,uRam0083c484,uRam0083c488,0x83c450);
    FUN_0016cc90(uVar4);
    uGpffff8998 = uGpffff8998 & 0xbfff;
  }
  else if (lVar6 == 3) {
    uVar4 = FUN_00219830(1);
    FUN_00219830(2,uVar4);
    FUN_00219830(3);
    FUN_00219a10();
    FUN_00216ce0();
    uGpffff8a98 = 0;
    uGpffff8998 = uGpffff8998 & 0xbfff;
  }
  else {
    FUN_00219830(1);
    FUN_00219830(2);
    FUN_00219830(3);
    if ((uRam00859fc0 & 0x100000) == 0x100000) {
      uRam00859fc0 = uRam00859fc0 & 0xffefffff;
      FUN_0018ae90();
      FUN_00141a90(0,0x11);
      uRam0083d070 = 1;
      uRam0083d071 = 0;
      uRam0083d020 = uRam00835158;
      uRam0083d044 = 0x431c0000;
    }
    bGpffff8844 = 0xff;
    FUN_00150460(unaff_s0,unaff_s1);
    uGpffff89e0 = 0;
    FUN_001378a0();
    FUN_00161620(0,10);
    uGpffff8a98 = 0;
    uGpffff8998 = uGpffff8998 & 0xbfff;
  }
  return;
}

