
void FUN_001b3220(void)

{
  bool bVar1;
  ulong uVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  uint uVar6;
  char cVar7;
  uint uVar8;
  uint *puVar9;
  float fVar10;
  float fStack_4;
  
  if ((uRam00859fe0 & 1) == 1) {
    if ((uRam00859fe0 & 2) == 2) {
      uRam00267994 = 3;
    }
    else {
      uRam00267994 = 0;
    }
    uVar8 = uRam00859fe0 & 0xdff8fe73;
    DAT_00267008 = 0xff;
    uVar6 = uRam00859fe0 & 0x100000;
    uRam00859fe0 = uVar8;
    if (uVar6 == 0x100000) {
      uRam00859fe0 = uVar8 | 0x200000;
    }
    if ((uRam00859fe0 & 0x400000) == 0x400000) {
      uRam00859fe0 = uRam00859fe0 | 0x800000;
    }
    if ((uRam00859fe0 & 0x1000000) == 0x1000000) {
      uRam00859fe0 = uRam00859fe0 | 0x2000000;
    }
    if ((uRam00859fe0 & 0x4000000) == 0x4000000) {
      uRam00859fe0 = uRam00859fe0 | 0x8000000;
    }
    if ((((((uRam00859fe0 & 2) != 2) && ((uRam00859fe0 & 0x100000) != 0x100000)) &&
         ((uRam00859fe0 & 0x400000) != 0x400000)) &&
        (((uRam00859fe0 & 0x4000000) != 0x4000000 && (bRam0085a004 != 0xb)))) &&
       (bRam0085a004 != 0xc)) {
      if (bRam0085a000 < 0x3d) {
        if ((0x14 < bRam0085a000) && (uVar2 = FUN_00148df0(0,99), uVar2 < 0x32)) {
          FUN_001b2160();
          uRam00859fe0 = uRam00859fe0 & 0xfcffffff;
          FUN_001497c0(0xb6);
        }
      }
      else {
        FUN_001b2160();
        uRam00859fe0 = uRam00859fe0 & 0xfcffffff;
        FUN_001497c0(0xb6);
      }
    }
    if (((((uRam00859fe0 & 0x400) == 0x400) && ((uRam00859fe0 & 2) != 2)) && (bRam0085a004 < 0xb))
       && ((bRam00859ffa < 0x32 ||
           ((0x31 < bRam00859ffa && (uVar2 = FUN_00148df0(0,99), uVar2 < 0x32)))))) {
      uRam00859fe0 = uRam00859fe0 & 0xfffffff3 | 2;
      uRam00859fe5 = 0;
      cRam00859fe6 = '\v';
      uRam00267994 = 3;
      FUN_00149760(0x97);
    }
    uVar6 = uRam00859fe0 & 0xfffffbff;
    if ((uRam00859fe0 & 2) == 2) {
      cVar7 = cRam00859fe6 + -1;
      bVar1 = cRam00859fe6 == '\x01';
      cRam00859fe6 = cVar7;
      if (bVar1) {
        uRam00859fe0 = uRam00859fe0 & 0xfffffbfc | 0x10;
        FUN_001376f0(0x10);
        uRam00267888 = uRam00267888 | 0x40;
        FUN_00149760(0x99);
        uVar6 = uRam00859fe0;
      }
    }
    else {
      uRam00859fe0 = uVar6;
      if (bRam0085a004 < 0xb) {
        FUN_001b58b0();
      }
      if ((((uRam00859fe0 & 0x4000) == 0x4000) && (bRam0085a004 != 0xb)) && (bRam0085a004 != 0xc)) {
        FUN_001b2160();
      }
      uRam00859ff0 = 0;
      if ((uRam00859fe0 & 0x20) == 0x20) {
        cRam00859fe6 = '\0';
        uRam00859fe0 = uRam00859fe0 & 0xffffbfff;
      }
      else {
        uRam00859fe0 = uRam00859fe0 & 0xffffbfff;
        FUN_001b7f40(0,5);
        uRam00859fe0 = uRam00859fe0 & 0xfffffffb | 8;
        cRam00859fe6 = cRam00859fe6 + '\x01';
        FUN_001c1690();
        if (((((uRam00859fe0 & 2) == 2) || (lVar3 = FUN_00149940(0xa7), lVar3 != 0)) ||
            (lVar3 = FUN_00149940(0xa8), lVar3 != 0)) ||
           ((0x32 < bRam00859ffa || (cRam00267834 != '\0')))) {
          if (((uRam00859fe0 & 2) != 2) &&
             ((bRam0085a002 < 0x3d && (uVar2 = FUN_00148df0(0,99), uVar2 < 0x1e)))) {
            uRam00859fe0 = uRam00859fe0 | 0x4000002;
            cRam00859fe6 = '\n';
            uRam00267994 = 3;
            FUN_00149760(0x96);
          }
        }
        else {
          if ((bRam0085a004 == 0xb) || (bRam0085a004 == 0xc)) {
            FUN_001376f0(0x10);
          }
          bRam0085a004 = 2;
          uRam0085a010 = 0x43f30000;
          uRam0085a014 = 0;
          uRam0085a018 = 0x42400000;
          uRam00859fe0 = uRam00859fe0 | 0x100000;
          FUN_00149760(0x94);
        }
      }
      if ((uRam00859fe0 & 2) != 2) {
        if ((((((uRam00859fe0 & 0x400000) != 0x400000) && (bRam0085a000 < 0x32)) &&
             ((cRam00267834 == '\0' || (cRam00267834 == '\x04')))) &&
            ((((bRam0085a004 != 0 && (bRam0085a004 != 1)) && (bRam0085a004 != 0xb)) &&
             ((bRam0085a004 != 0xc && (bRam0085a004 != 0xe)))))) && (bRam0085a004 != 0xd)) {
          uVar2 = FUN_00148df0(0,999999);
          if ((long)uVar2 < 0) {
            fVar10 = (float)(uVar2 & 0xffffffff);
          }
          else {
            fVar10 = (float)(int)uVar2;
          }
          if ((uRam00859fe0 & 8) == 8) {
            fStack_4 = 25.0;
          }
          else {
            fStack_4 = 12.5;
          }
          if (fVar10 / 10000.0 <= fStack_4) {
            if ((bRam0085a004 == 0xb) || (bRam0085a004 == 0xc)) {
              FUN_001376f0(0x10);
            }
            lVar3 = FUN_00148df0(0,3);
            if (lVar3 == 3) {
              bRam0085a004 = 9;
              uRam0085a010 = 0x44a54000;
              uRam0085a014 = 0;
              uRam0085a018 = 0xc4c64000;
            }
            else if (lVar3 == 2) {
              bRam0085a004 = 4;
              uRam0085a010 = 0xc3d50000;
              uRam0085a014 = 0;
              uRam0085a018 = 0x44724000;
            }
            else if (lVar3 == 1) {
              bRam0085a004 = 5;
              uRam0085a010 = 0xc4cd6000;
              uRam0085a014 = 0;
              uRam0085a018 = 0x448bc000;
            }
            else if (lVar3 == 0) {
              bRam0085a004 = 4;
              uRam0085a010 = 0xc4a00000;
              uRam0085a014 = 0;
              uRam0085a018 = 0x43200000;
            }
            uRam00859fe0 = uRam00859fe0 | 0x1000000;
            FUN_00149760(0xb6);
          }
        }
        if ((((((uRam00859fe0 & 0x1000000) != 0x1000000) && (bRam0085a004 != 0)) &&
             (bRam0085a004 != 1)) &&
            (((bRam0085a004 != 0xb && (bRam0085a004 != 0xc)) &&
             ((bRam0085a004 != 0xe && ((bRam0085a004 != 0xd && (bRam00859ffc < 0x33)))))))) &&
           (uVar2 = FUN_00148df0(0,99), uVar2 < 0x19)) {
          if ((bRam0085a004 == 0xb) || (bRam0085a004 == 0xc)) {
            FUN_001376f0(0x10);
          }
          bRam0085a004 = 6;
          uRam0085a010 = 0xc2c00000;
          uRam0085a014 = 0;
          uRam0085a018 = 0xc44b0000;
          uRam00859fe0 = uRam00859fe0 | 0x400000;
          FUN_00149760(0x95);
        }
      }
      uRam00859fe8 = 0;
      FUN_001c1a90();
      uVar6 = uRam00859fe0;
    }
    uRam00859fe0 = uVar6;
    if ((uRam00859fe0 & 2) == 2) {
      FUN_0013e2a0(0x10);
      uRam00267994 = 3;
    }
  }
  else if (((uRam00859fe0 & 0x10) != 0x10) && ((uRam00859fe0 & 0x40) == 0x40)) {
    uVar2 = FUN_00148df0(0,99);
    if (uVar2 < 0x32) {
      cRam0026782c = cRam0026782c + '\x02';
    }
    else {
      cRam00267828 = cRam00267828 + '\x02';
    }
  }
  uRam00859fe0 = uRam00859fe0 & 0xffffff9f;
  uRam0026799c = 0;
  uRam002679a4 = 0;
  uRam002679a0 = 0;
  uRam002679ac = 0;
  if ((uRam00859fc0 & 1) == 1) {
    if ((uRam00859fc0 & 2) == 2) {
      uRam00267998 = 3;
    }
    else {
      uRam00267998 = 0;
    }
    uVar6 = uRam00859fc0 & 0xfff1fe73;
    uVar8 = uRam00859fc0 & 0x80000000;
    uRam00859fc0 = uVar6;
    if (uVar8 == 0x80000000) {
      FUN_0014f4c0(3);
      uRam00859fc0 = (uint)((ulong)((long)(int)uRam00859fc0 << 0x21) >> 0x21);
    }
    if ((((uRam00859fc0 & 0x400) == 0x400) && ((uRam00859fc0 & 2) != 2)) && (bRam00859fc9 < 0xb)) {
      uRam00859fc0 = uRam00859fc0 & 0xfffffff3 | 2;
      uRam00859fc4 = 0;
      cRam00859fc5 = '\b';
      uRam00267998 = 3;
    }
    uVar6 = uRam00859fc0 & 0xfffffbff;
    if ((uRam00859fc0 & 2) == 2) {
      cVar7 = cRam00859fc5 + -1;
      bVar1 = cRam00859fc5 == '\x01';
      cRam00859fc5 = cVar7;
      if (bVar1) {
        uRam00859fc0 = uRam00859fc0 & 0xfffffbfc | 0x10;
        uRam00267888 = uRam00267888 | 0x80;
        FUN_00149760(0x9a);
        uVar6 = uRam00859fc0;
      }
    }
    else {
      uRam00859fc0 = uVar6;
      if (bRam00859fc9 < 0xb) {
        FUN_001b5740(0x859fc0);
      }
      if ((uRam00859fc0 & 0x20) == 0x20) {
        FUN_001b7f40(1,4);
        cRam00859fc5 = '\0';
        uVar6 = uRam00859fc0;
      }
      else {
        FUN_001b7f40(1,5);
        uRam00859fc0 = uRam00859fc0 & 0xfffffffb | 8;
        cRam00859fc5 = cRam00859fc5 + '\x01';
        FUN_001c18d0();
        uVar6 = uRam00859fc0;
      }
    }
    uRam00859fc0 = uVar6;
    uRam00859fc6 = 0;
    if (bRam00859fc9 == 0xd) {
      FUN_001b24b0();
    }
  }
  uRam00859fc0 = uRam00859fc0 & 0xffffff9f;
  for (uVar6 = 0; (int)uVar6 < 6; uVar6 = uVar6 + 1) {
    *(undefined1 *)(uVar6 * 0x20 + 0x859d50) = 0;
    *(undefined2 *)(uVar6 * 2 + 0x85a3b0) = 0;
    if ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 1) == 1) {
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xfffffffb;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xfffffff7;
      if ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 2) == 2) {
        (&DAT_00266ff8)[uVar6] = 3;
      }
      else {
        (&DAT_00266ff8)[uVar6] = 0;
      }
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xfffffeff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xffffff7f;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xffffefff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xffffbfff;
      if ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 0x800) == 0x800) {
        cVar7 = *(char *)(uVar6 * 0x20 + 0x859e64);
        *(char *)(uVar6 * 0x20 + 0x859e64) = cVar7 + -1;
        if (cVar7 == '\x01') {
          *(undefined1 *)(uVar6 * 0x20 + 0x859e64) = 0;
          *(undefined1 *)(uVar6 * 0x20 + 0x859e65) = 0;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 & 0xfffff7ff;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 & 0xfffffbff;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 & 0xfffffffd;
          FUN_00186a70(uVar6 & 0xff);
        }
      }
      else {
        if ((((*(uint *)(uVar6 * 0x20 + 0x859e60) & 0x400) == 0x400) &&
            ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 2) != 2)) &&
           (*(byte *)(uVar6 * 0x20 + 0x859e69) < 0xb)) {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 | 2;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 & 0xfffffffb;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 & 0xfffffff7;
          *(undefined1 *)(uVar6 * 0x20 + 0x859e64) = 0;
          *(undefined1 *)(uVar6 * 0x20 + 0x859e65) = 4;
          (&DAT_00266ff8)[uVar6] = 3;
        }
        puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
        *puVar9 = *puVar9 & 0xfffffbff;
        if ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 2) == 2) {
          cVar7 = *(char *)(uVar6 * 0x20 + 0x859e65);
          *(char *)(uVar6 * 0x20 + 0x859e65) = cVar7 + -1;
          if (cVar7 == '\x01') {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
            *puVar9 = *puVar9 & 0xfffffffe;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
            *puVar9 = *puVar9 & 0xfffffffd;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
            *puVar9 = *puVar9 | 0x10;
            uVar4 = FUN_001376f0(uVar6 + 0x1b & 0xff);
            uRam00267888 = uRam00267888 | 0x200;
            FUN_00149760(0x9c,uRam00267888,uVar4);
          }
        }
        else {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar9 = *puVar9 & 0xffffff7f;
          if ((*(char *)(uVar6 * 0x20 + 0x859e69) == '\0') ||
             (*(char *)(uVar6 * 0x20 + 0x859e69) == '\x01')) {
            FUN_001b5740(uVar6 * 0x20 + 0x859e60);
          }
          if ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 0x20) == 0x20) {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
            *puVar9 = *puVar9 & 0xffffffdf;
            *(undefined1 *)(uVar6 * 0x20 + 0x859e65) = 0;
            if (((*(uint *)(uVar6 * 0x20 + 0x859e60) & 2) != 2) &&
               ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 8) != 8)) {
              if (((*(uint *)(uVar6 * 0x20 + 0x859e60) & 4) == 4) &&
                 (0xdb < *(byte *)(uVar6 * 0x20 + 0x859e68))) {
                uVar2 = FUN_00148df0(0,999999);
                if ((long)uVar2 < 0) {
                  fVar10 = (float)(uVar2 & 0xffffffff);
                }
                else {
                  fVar10 = (float)(int)uVar2;
                }
                if (fVar10 / 10000.0 <= 12.5) {
                  *(undefined1 *)(uVar6 * 0x20 + 0x859d50) = 2;
                }
              }
              puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
              *puVar9 = *puVar9 | 0x1000;
              puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
              *puVar9 = *puVar9 | 0x4000;
            }
          }
          else {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
            *puVar9 = *puVar9 & 0xfffffffb;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
            *puVar9 = *puVar9 | 8;
            *(char *)(uVar6 * 0x20 + 0x859e65) = *(char *)(uVar6 * 0x20 + 0x859e65) + '\x01';
            FUN_001b5a10(uVar6 * 0x20 + 0x859e60,3);
          }
        }
        *(undefined2 *)(uVar6 * 0x20 + 0x859e66) = 0;
      }
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xffffffbf;
      if (*(char *)(uVar6 * 0x20 + 0x859e69) == '\x0e') {
        FUN_001b21f0(uVar6 & 0xff);
      }
    }
    else {
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859e60);
      *puVar9 = *puVar9 & 0xffffffbf;
    }
  }
  if (((bRam00859e10 & 1) == 1) && ((bRam00859e10 & 4) == 4)) {
    if ((bRam00859e10 & 8) == 8) {
      bRam00859e10 = bRam00859e10 & 0xf7 | 0x10;
    }
    else if ((bRam00859e10 & 0x10) == 0x10) {
      bRam00859e10 = bRam00859e10 & 0xef | 0x20;
    }
    else if ((bRam00859e10 & 0x20) == 0x20) {
      iVar5 = 0;
      while ((iVar5 < 6 && ((*(uint *)(iVar5 * 0x20 + 0x859e60) & 1) == 1))) {
        iVar5 = iVar5 + 1;
      }
      if (iVar5 != 6) {
        bRam00859e10 = bRam00859e10 & 0xdf | 0x40;
      }
    }
  }
  for (uVar6 = 0; (int)uVar6 < 5; uVar6 = uVar6 + 1) {
    *(undefined2 *)(uVar6 * 2 + 0x85a3c0) = 0;
    if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 1) == 1) {
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xfffffffb;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xfffffff7;
      if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 2) == 2) {
        (&DAT_00267000)[uVar6] = 3;
      }
      else {
        (&DAT_00267000)[uVar6] = 0;
      }
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xfffffeff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xfff7ffff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xffefffff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xffdfffff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xff7fffff;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xffffff7f;
      if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x80000000) == 0x80000000) {
        FUN_0014f4c0(3);
        puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
        *puVar9 = (uint)((ulong)((long)(int)*puVar9 << 0x21) >> 0x21);
      }
      if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x1000000) == 0x1000000) {
        puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
        *puVar9 = *puVar9 | 0x2000;
        puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
        *puVar9 = *puVar9 & 0xfeffffff;
      }
      else if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x2000) == 0x2000) {
        if (((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x4000) != 0x4000) &&
           (cVar7 = *(char *)(uVar6 * 0x20 + 0x859f24),
           *(char *)(uVar6 * 0x20 + 0x859f24) = cVar7 + -1, cVar7 == '\x01')) {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 | 0x4000;
        }
      }
      else if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x1000) == 0x1000) {
        if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x20) == 0x20) {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 & 0xffffffdf;
          cVar7 = *(char *)(uVar6 * 0x20 + 0x859f24);
          *(char *)(uVar6 * 0x20 + 0x859f24) = cVar7 + -1;
          if (cVar7 == '\x01') {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xffffefff;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xfffffbff;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xfffffffd;
            *(undefined1 *)(uVar6 * 0x20 + 0x859f24) = 0;
          }
        }
      }
      else if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x800) == 0x800) {
        if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x20) == 0x20) {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 & 0xffffffdf;
          cVar7 = *(char *)(uVar6 * 0x20 + 0x859f24);
          *(char *)(uVar6 * 0x20 + 0x859f24) = cVar7 + -1;
          if (cVar7 == '\x01') {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xfffff7ff;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 | 0x1000;
            *(undefined1 *)(uVar6 * 0x20 + 0x859f24) = 7;
          }
        }
      }
      else {
        if ((((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x400) == 0x400) &&
            ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 2) != 2)) &&
           (*(byte *)(uVar6 * 0x20 + 0x859f29) < 0xb)) {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 | 2;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 & 0xfffffffb;
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 & 0xfffffff7;
          *(undefined1 *)(uVar6 * 0x20 + 0x859f24) = 0;
          *(undefined1 *)(uVar6 * 0x20 + 0x859f25) = 8;
          (&DAT_00267000)[uVar6] = 3;
        }
        puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
        *puVar9 = *puVar9 & 0xfffffbff;
        if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 2) == 2) {
          cVar7 = *(char *)(uVar6 * 0x20 + 0x859f25);
          *(char *)(uVar6 * 0x20 + 0x859f25) = cVar7 + -1;
          if (cVar7 == '\x01') {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xfffffffe;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xfffffffd;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 | 0x10;
            uRam00267888 = uRam00267888 | 0x100;
            FUN_00149760(0x9b);
          }
        }
        else {
          puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar9 = *puVar9 & 0xffffff7f;
          if ((*(char *)(uVar6 * 0x20 + 0x859f29) == '\0') ||
             (*(char *)(uVar6 * 0x20 + 0x859f29) == '\x01')) {
            FUN_001b5740(uVar6 * 0x20 + 0x859f20);
          }
          if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x20) == 0x20) {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xffffffdf;
            *(undefined1 *)(uVar6 * 0x20 + 0x859f25) = 0;
          }
          else {
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 & 0xfffffffb;
            puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar9 = *puVar9 | 8;
            *(char *)(uVar6 * 0x20 + 0x859f25) = *(char *)(uVar6 * 0x20 + 0x859f25) + '\x01';
            FUN_001b5a10(uVar6 * 0x20 + 0x859f20,7);
            if ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 2) == 2) {
              (&DAT_00267000)[uVar6] = 3;
            }
          }
        }
      }
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xffffffbf;
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xffffffdf;
      *(undefined2 *)(uVar6 * 0x20 + 0x859f26) = 0;
      if (*(char *)(uVar6 * 0x20 + 0x859f29) == '\r') {
        FUN_001b2510(uVar6 & 0xff);
      }
    }
    else {
      puVar9 = (uint *)(uVar6 * 0x20 + 0x859f20);
      *puVar9 = *puVar9 & 0xffffffbf;
    }
  }
  if (((((uRam00267888 & 0x40) == 0x40) || ((uRam00267888 & 0x80) == 0x80)) ||
      ((uRam00267888 & 0x100) == 0x100)) || ((uRam00267888 & 0x200) == 0x200)) {
    bRam002678c8 = bRam002678c8 | 4;
  }
  return;
}

