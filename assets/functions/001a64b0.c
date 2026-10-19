
/* WARNING: Removing unreachable block (ram,0x001a7b0c) */
/* WARNING: Removing unreachable block (ram,0x001a7bc0) */
/* WARNING: Removing unreachable block (ram,0x001a809c) */

void FUN_001a64b0(void)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  iVar3 = 0;
  switch(cRam0026795c) {
  case '\0':
    lVar4 = FUN_0012e170(0,0x1000);
    if ((((lVar4 != 0) || (lVar4 = FUN_0012e170(0,0x4000), lVar4 != 0)) ||
        (lVar4 = FUN_0012e170(0,0x10000), lVar4 != 0)) ||
       (lVar4 = FUN_0012e170(0,0x20000), lVar4 != 0)) {
      FUN_00218ea0(2);
      if (cRam00267960 == '\0') {
        FUN_0015cd00(0xc2600000,0x42600000,0x47c34f80,5);
        cRam00267960 = '\x01';
      }
      else {
        FUN_0015cd00(0xc2600000,0x42c00000,0x47c34f80,5);
        cRam00267960 = '\0';
      }
    }
    lVar4 = FUN_0012e170(0,0x40);
    if (lVar4 == 0) {
      lVar4 = FUN_0012e170(0,0x20);
      if (lVar4 != 0) {
        uVar5 = FUN_00218ea0(1);
        FUN_0015d1f0(5,uVar5);
        FUN_0015be60(0x110);
        FUN_0015be60(0x111);
        FUN_0015be60(0x112);
        FUN_0015be60(0x113);
        uRam00267750 = 0;
        FUN_0015ef10();
      }
    }
    else {
      FUN_00218ea0();
      cRam0026795c = '\x01';
      FUN_0015bfb0(0x111);
      if (cRam00267960 == '\0') {
        lVar4 = FUN_001a3420();
        if (lVar4 == 0) {
          cRam0026795c = 0;
          FUN_0015bf20(0x111);
          return;
        }
        FUN_0015bcd0(0x110,0x32f,0xd42,0xd8);
        FUN_0015c040(0,0x43100000,0x47c35000,0x110);
        FUN_0015bcd0(0x113,0x332,0xd45,0xd8);
      }
      else {
        FUN_0015bcd0(0x110,0x32f,0xd42,0xd9);
        FUN_0015c040(0,0x43100000,0x47c35000,0x110);
        FUN_0015bcd0(0x113,0x332,0xd45,0xd9);
        FUN_001a3420(1);
      }
      FUN_0015bf20(0x110);
      FUN_0015bf20(0x112);
      FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,iRam00267864);
      if (((bRam00267964 != 5) || (cRam00267968 != '\0')) &&
         ((bRam00267964 != 6 || (cRam00267968 != '\x01')))) {
        FUN_0015bf20(0x113);
        uVar7 = (uint)*(byte *)((((uint)uRam00267970 + (uint)bRam00267978) - (uint)uRam0026796c) +
                               0x85a380);
        if ((cRam00267968 != '\0') ||
           ((((bRam00267964 != 3 && (bRam00267964 != 4)) && ((bRam00267964 != 2 || (uVar7 == 0x25)))
             ) && (((bRam00267964 != 6 || ((uVar7 != 0x58 && (uVar7 != 0x59)))) &&
                   ((bRam00267964 != 1 || (uVar7 != 0x4f)))))))) {
          FUN_001ccc00(0xc3500000,0xc2200000,0x47c34f80,0x11d,0xd4f,0x33c,
                       *(undefined1 *)(uVar7 + 0x85a2a0));
        }
      }
    }
    break;
  case '\x01':
    lVar4 = FUN_0012e210(0,0x1000);
    if ((lVar4 != 0) || (lVar4 = FUN_0012e210(0,0x10000), lVar4 != 0)) {
      uVar5 = FUN_001a5e30();
      FUN_00218ea0(2,uVar5);
    }
    lVar4 = FUN_0012e210(0,0x4000);
    if ((lVar4 != 0) || (lVar4 = FUN_0012e210(0,0x20000), lVar4 != 0)) {
      FUN_001a5f90();
      FUN_00218ea0(2);
    }
    bVar2 = *(byte *)((((uint)uRam00267970 + (uint)bRam00267978) - (uint)uRam0026796c) + 0x85a380);
    lVar4 = FUN_0012e170(0,0x40);
    if (lVar4 == 0) {
      lVar4 = FUN_0012e170(0,0x20);
      if (lVar4 == 0) {
        return;
      }
      FUN_00218ea0(1);
      FUN_0015d1f0(5);
      FUN_0015bfb0(0x110);
      FUN_0015bfb0(0x111);
      FUN_0015bfb0(0x112);
      uVar5 = FUN_0015bfb0(0x113);
      if (cRam00267984 == '\0') {
        cRam0026795c = '\0';
        bVar1 = cRam00267968 != '\x01';
        if (bVar1) {
          FUN_0015cd00(0xc2600000,0x42c00000,0x47c34f80,5);
        }
        else {
          FUN_0015cd00(0xc2600000,0x42600000,0x47c34f80,5,uVar5);
        }
        cRam00267960 = !bVar1;
        FUN_0015c550(5);
        FUN_0015c040(0,0x42c00000,0x47c35000,0x111);
        FUN_0015bf20(0x111);
      }
      else {
        FUN_0015d1f0(5);
        FUN_0015be60(0x110);
        uVar5 = FUN_0015be60(0x111);
        FUN_0015be60(0x112,uVar5);
        FUN_0015be60(0x113);
        uRam00267750 = 0;
        FUN_0015ef10();
      }
      FUN_001a49d0();
      return;
    }
    FUN_00218ea0();
    if (cRam00267968 == '\0') {
      if ((((bRam00267964 == 5) || (bRam00267964 == 2)) ||
          ((bRam00267964 == 6 || ((bRam00267964 == 3 || (bRam00267964 == 4)))))) ||
         ((bRam00267964 == 1 && (bVar2 == 0x4f)))) {
        if (((bRam00267964 == 5) &&
            (((bRam002678c8 & 0x20) == 0x20 || ((bRam002678c8 & 0x40) == 0x40)))) ||
           ((bVar2 == 0xfe && ((uRam00859fe0 & 1) != 1)))) {
          uVar5 = FUN_00218fc0();
          FUN_00218ea0(3,uVar5);
          return;
        }
        if (((((bVar2 == 0x4f) || (bVar2 == 0x4d)) || (bVar2 == 0x59)) ||
            (((bVar2 == 0x58 || (bVar2 == 0x25)) ||
             ((bVar2 == 0x57 || ((bVar2 == 0x5b || (bVar2 == 0x56)))))))) || (bVar2 == 0x52)) {
          lVar4 = FUN_0016bc20(bVar2,1);
          if (lVar4 == 0) {
            FUN_00218fc0();
            FUN_00218ea0(3);
            return;
          }
          if (bVar2 != 0x25) goto LAB_001a7018;
        }
        else if ((bVar2 == 0x3a) || (bVar2 == 0x48)) {
          lVar4 = FUN_0016bc20(bVar2,1);
          if (lVar4 == 0) {
            FUN_00218fc0();
            FUN_00218ea0(3);
            return;
          }
        }
        else {
          if (bVar2 == 0xfc) {
            uVar7 = 0;
            while ((uVar7 < 6 && ((*(uint *)(uVar7 * 0x20 + 0x859e60) & 1) == 1))) {
              uVar7 = uVar7 + 1 & 0xff;
            }
            if ((bRam00859e10 & 1) == 1) {
              uVar7 = uVar7 + 1 & 0xff;
            }
            if (5 < uVar7) {
              uVar5 = FUN_00218fc0();
              FUN_00218ea0(3,uVar5);
              return;
            }
            DAT_00266fa0 = 1;
            FUN_0015e9b0(0,0,0x1797000,0x1796000);
            FUN_0015eaa0(0,cRam00267968,0x30);
            cRam0026795c = 3;
            return;
          }
          if (bVar2 == 0xfd) {
            uVar7 = 0;
            while ((uVar7 < 5 && ((*(uint *)(uVar7 * 0x20 + 0x859f20) & 1) == 1))) {
              uVar7 = uVar7 + 1 & 0xff;
            }
            uVar8 = 0;
            for (uVar9 = 0; uVar9 < 5; uVar9 = uVar9 + 1 & 0xff) {
              if (((*(uint *)(uVar9 * 0x20 + 0x859f20) & 1) == 1) &&
                 (((*(uint *)(uVar9 * 0x20 + 0x859f20) & 0x2000) == 0x2000 ||
                  ((*(uint *)(uVar9 * 0x20 + 0x859f20) & 0x1000000) == 0x1000000)))) {
                uVar8 = uVar8 + 1 & 0xff;
              }
            }
            if (4 < uVar7 + uVar8) {
              FUN_00218fc0();
              FUN_00218ea0(3);
              return;
            }
            DAT_00266fa0 = 1;
            FUN_0015e9b0(0,0,0x1797000,0x1796000);
            FUN_0015eaa0(0,cRam00267968,0x30);
            cRam0026795c = 3;
            return;
          }
LAB_001a7018:
          if ((bRam00267964 != 1) || (bVar2 == 0x4f)) {
            DAT_00266fa0 = 1;
            FUN_0015e9b0(0,0,0x1797000,0x1796000);
            FUN_0015eaa0(0,cRam00267968,0x30);
            cRam0026795c = 3;
            return;
          }
        }
      }
      else {
        lVar4 = FUN_0016bc20(bVar2,1);
        if (lVar4 == 0) {
          uVar5 = FUN_00218fc0();
          FUN_00218ea0(3,uVar5);
          return;
        }
      }
    }
    else {
      if (bRam00267964 == 6) {
        uVar7 = 0;
        if (bVar2 == 0xfd) {
          FUN_001167c0(0x85a310,0x833e90,0x28);
          for (uVar8 = 0; uVar8 < 5; uVar8 = uVar8 + 1 & 0xff) {
            if ((((*(uint *)(uVar8 * 0x20 + 0x859f20) & 1) == 1) &&
                ((*(uint *)(uVar8 * 0x20 + 0x859f20) & 0x800) != 0x800)) &&
               (((*(uint *)(uVar8 * 0x20 + 0x859f20) & 0x1000) != 0x1000 &&
                ((*(uint *)(uVar8 * 0x20 + 0x859f20) & 2) != 2)))) {
              FUN_001167c0((uVar7 + 8) * 8 + 0x833e50,(uVar8 + 8) * 8 + 0x833e50,8);
              uVar7 = uVar7 + 1 & 0xff;
            }
          }
          if (uVar7 != 0) {
            iVar3 = 4;
            cRam0026795c = '\x06';
          }
        }
        else {
          FUN_001167c0(0x85a310,0x833ec8,0x30);
          for (uVar8 = 0; uVar8 < 6; uVar8 = uVar8 + 1 & 0xff) {
            if ((((*(uint *)(uVar8 * 0x20 + 0x859e60) & 1) == 1) &&
                ((*(uint *)(uVar8 * 0x20 + 0x859e60) & 0x800) != 0x800)) &&
               ((*(uint *)(uVar8 * 0x20 + 0x859e60) & 2) != 2)) {
              FUN_001167c0((uVar7 + 0xf) * 8 + 0x833e50,(uVar8 + 0xf) * 8 + 0x833e50,8);
              uVar7 = uVar7 + 1 & 0xff;
            }
          }
          if (uVar7 != 0) {
            iVar3 = 9;
            cRam0026795c = '\a';
          }
        }
        if (uVar7 == 0) {
          return;
        }
        DAT_00266fa0 = 1;
        FUN_00152ed0(1,0x1786000,0x1785000);
        FUN_0015e9b0(0,1,0x1797000,0x1796000);
        FUN_0015eaa0(0,iVar3 + (uVar7 - 1) & 0xffff,0x30);
        return;
      }
      if (*(char *)(bVar2 + 0x85a2a0) == '\0') {
        FUN_00218fc0();
        FUN_00218ea0(3);
        return;
      }
    }
    FUN_0015cf30(0x43800000,0,0,5);
    cRam0026795c = '\x02';
    DAT_00266fa0 = '\x01';
    break;
  case '\x02':
    lVar4 = FUN_0012e210(0,0x1000);
    if ((lVar4 != 0) || (lVar4 = FUN_0012e210(0,0x10000), lVar4 != 0)) {
      FUN_001a6140(1);
      FUN_00218ea0(2);
    }
    lVar4 = FUN_0012e210(0,0x4000);
    if ((lVar4 != 0) || (lVar4 = FUN_0012e210(0,0x20000), lVar4 != 0)) {
      FUN_001a6140(0xffffffffffffffff);
      FUN_00218ea0(2);
    }
    lVar4 = FUN_0012e210(0,0x8000);
    if ((lVar4 != 0) || (lVar4 = FUN_0012e210(0,0x40000), lVar4 != 0)) {
      uVar5 = FUN_001a6140(10);
      FUN_00218ea0(2,uVar5);
    }
    lVar4 = FUN_0012e210(0,0x2000);
    if ((lVar4 != 0) || (lVar4 = FUN_0012e210(0,0x80000), lVar4 != 0)) {
      uVar5 = FUN_001a6140(0xfffffffffffffff6);
      FUN_00218ea0(2,uVar5);
    }
    lVar4 = FUN_0012e170(0,0x40);
    if (lVar4 == 0) {
      lVar4 = FUN_0012e170(0,0x20);
      if (lVar4 != 0) {
        FUN_00218ea0(1);
        cRam0026795c = '\x01';
        FUN_0015cf30(0xc3800000,0,0,5);
        FUN_001a4af0(bRam00267978,uRam00267970 + bRam00267978);
        DAT_00266fa0 = '\x01';
      }
    }
    else {
      FUN_00218ea0();
      FUN_0015e9b0(0,0,0x1797000,0x1796000);
      FUN_0015eaa0(0,cRam00267968,0x30);
      cRam0026795c = '\x03';
    }
    break;
  case '\x03':
    lVar4 = FUN_0015ee20();
    if (lVar4 == 0) {
      bVar2 = *(byte *)((((uint)uRam00267970 + (uint)bRam00267978) - (uint)uRam0026796c) + 0x85a380)
      ;
      if (cRam00833de8 == -1) {
        if (((((bRam00267964 == 5) && (cRam00267968 == '\0')) ||
             ((bRam00267964 == 2 && ((cRam00267968 == '\0' && (bVar2 != 0x25)))))) ||
            ((bRam00267964 == 6 &&
             ((cRam00267968 == '\0' &&
              ((((bVar2 == 0xfd || (bVar2 == 0xfc)) || (bVar2 == 0x58)) || (bVar2 == 0x59)))))))) ||
           (((bRam00267964 == 3 || (bRam00267964 == 4)) && (cRam00267968 == '\0')))) {
          uVar5 = FUN_0015cd00(0xc3880000,0x43200000,0x47c34e80,5);
          FUN_0015c550(5,5,uVar5);
          FUN_0015cf30(0,(float)bRam00267978 * -32.0,0,5);
          cRam0026795c = '\x01';
        }
        else {
          FUN_0015cd00(0xc3880000,0x43200000,0x47c34e80,5);
          FUN_0015c550(5);
          FUN_0015cf30(0x43800000,(float)bRam00267978 * -32.0,0,5);
          cRam0026795c = '\x02';
        }
      }
      else {
        if (cRam00833de8 == '\0') {
          uVar7 = (int)DAT_00266fa0 *
                  (uint)*(ushort *)
                         (((uint)bRam00267978 + ((uint)uRam00267970 - (uint)uRam0026796c)) * 2 +
                         0x85a390) & 0xffff;
          if (cRam00267968 == '\0') {
            if (iRam00267864 < (int)uVar7) {
              FUN_001532e0();
              FUN_00152f40(0,*(undefined2 *)(&DAT_00244030 + (uint)bRam00267964 * 2),0x4220,5);
            }
            else {
              uVar5 = FUN_0016ce30(-uVar7);
              FUN_00218ea0(0x6b,uVar5);
              if (bRam00267964 == 5) {
                if (bVar2 == 0xff) {
                  bRam002678c8 = bRam002678c8 | 0x20;
                }
                else {
                  bRam002678c8 = bRam002678c8 | 0x40;
                }
              }
              else if (bRam00267964 == 6) {
                if (bVar2 == 0xfd) {
                  FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,iRam00267864);
                  FUN_00167330(0x1e);
                  cRam0026795c = 4;
                  return;
                }
                if (bVar2 == 0xfc) {
                  FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,iRam00267864);
                  FUN_00167330(0x1e);
                  cRam0026795c = 5;
                  return;
                }
                FUN_0016bff0(bVar2,DAT_00266fa0);
              }
              else {
                if (bVar2 == 0x5b) {
                  FUN_001497c0(0x86);
                  FUN_001497c0(0x87);
                }
                if ((bRam00267964 == 3) || (bRam00267964 == 4)) {
                  bRam002678a4 = bVar2;
                  uVar5 = FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,
                                       iRam00267864);
                  FUN_0015d1f0(5,uVar5);
                  FUN_0015be60(0x110);
                  uVar5 = FUN_0015be60(0x111);
                  FUN_0015be60(0x112,uVar5);
                  FUN_0015be60(0x113);
                  uRam00267750 = 0x22;
                  FUN_001a49d0();
                  FUN_0015ef10();
                  return;
                }
                FUN_0016bff0(bVar2,DAT_00266fa0);
              }
              FUN_001a4e90();
              FUN_001a9260();
            }
          }
          else {
            FUN_0016c7b0(bVar2,DAT_00266fa0);
            FUN_0016ce30(uVar7);
            FUN_001a4e90();
            FUN_001a9260();
            FUN_00218ea0(0x6b);
          }
        }
        cRam0026795c = '\x01';
        uVar5 = FUN_0015cd00(0xc3880000,0x43200000,0x47c34e80,5);
        uVar5 = FUN_0015c550(5,uVar5);
        FUN_0015cf30(0,(float)bRam00267978 * -32.0,0,5,uVar5);
        FUN_001a4af0(bRam00267978,uRam00267970 + bRam00267978);
        DAT_00266fa0 = '\x01';
        FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,iRam00267864);
        if ((((bRam00267964 != 5) || (cRam00267968 != '\0')) &&
            (((bRam00267964 != 6 || (cRam00267968 != '\0')) || ((bVar2 != 0xfd && (bVar2 != 0xfc))))
            )) && ((cRam00267968 != '\0' ||
                   (((((bRam00267964 != 3 && (bRam00267964 != 4)) &&
                      ((bRam00267964 != 2 || (bVar2 == 0x25)))) &&
                     ((bRam00267964 != 6 || ((bVar2 != 0x58 && (bVar2 != 0x59)))))) &&
                    ((bRam00267964 != 1 || (bVar2 != 0x4f)))))))) {
          FUN_001ccc00(0xc3500000,0xc2200000,0x47c34f80,0x11d,0xd4f,0x33c,
                       *(undefined1 *)(bVar2 + 0x85a2a0));
        }
      }
    }
    break;
  case '\x04':
  case '\x05':
    lVar4 = FUN_00167620();
    if (lVar4 == 0) {
      FUN_0015d1f0(5);
      FUN_0015bfb0(0x110);
      FUN_0015bfb0(0x111);
      FUN_0015bfb0(0x112);
      FUN_0015bfb0(0x113);
      FUN_0015be60(0x110);
      FUN_0015be60(0x111);
      FUN_0015be60(0x112);
      FUN_0015be60(0x113);
      FUN_001a49d0();
      uRam00267750 = 0;
      if (cRam0026795c == '\x04') {
        uVar7 = 0;
        while ((uVar7 < 5 && ((*(uint *)(uVar7 * 0x20 + 0x859f20) & 1) == 1))) {
          uVar7 = uVar7 + 1 & 0xff;
        }
        if ((*(uint *)(uVar7 * 0x20 + 0x859f20) & 0x40) == 0x40) {
          *(undefined4 *)(uVar7 * 0x20 + 0x859f20) = 0x60;
        }
        else {
          *(undefined4 *)(uVar7 * 0x20 + 0x859f20) = 0;
        }
        *(undefined1 *)(uVar7 * 0x20 + 0x859f28) = 0;
        puVar6 = (uint *)(uVar7 * 0x20 + 0x859f20);
        *puVar6 = *puVar6 | 1;
        puVar6 = (uint *)(uVar7 * 0x20 + 0x859f20);
        *puVar6 = *puVar6 | 0x1000;
        *(undefined1 *)(uVar7 * 0x20 + 0x859f24) = 7;
        *(undefined1 *)(uVar7 * 0x20 + 0x859f25) = 0;
        iVar3 = FUN_00148df0(0,0x3039);
        iVar3 = iVar3 % 5;
        if (iVar3 == 4) {
          puVar6 = (uint *)(uVar7 * 0x20 + 0x859f20);
          *puVar6 = *puVar6 | 0x40000;
        }
        else if (iVar3 == 3) {
          puVar6 = (uint *)(uVar7 * 0x20 + 0x859f20);
          *puVar6 = *puVar6 | 0x20000;
        }
        else if (iVar3 == 2) {
          puVar6 = (uint *)(uVar7 * 0x20 + 0x859f20);
          *puVar6 = *puVar6 | 0x10000;
        }
        else if (iVar3 == 1) {
          puVar6 = (uint *)(uVar7 * 0x20 + 0x859f20);
          *puVar6 = *puVar6 | 0x8000;
        }
        FUN_001b2510(uVar7);
        cRam002678b4 = (char)uVar7 + '\b';
        FUN_0015ef10();
        FUN_00116978((uVar7 + 8) * 8 + 0x833e50,0xff,8);
        uVar5 = FUN_0015e790();
        FUN_001e8ce0(uVar7 + 8 & 0xff,(uVar7 + 8) * 8 + 0x833e50,uVar5);
        uRam00267750 = 0x15;
        uRam00267888 = uRam00267888 | 0x2000;
      }
      else {
        uVar7 = 0;
        while ((uVar7 < 6 && ((*(uint *)(uVar7 * 0x20 + 0x859e60) & 1) == 1))) {
          uVar7 = uVar7 + 1 & 0xff;
        }
        if ((*(uint *)(uVar7 * 0x20 + 0x859e60) & 0x40) == 0x40) {
          *(undefined4 *)(uVar7 * 0x20 + 0x859e60) = 0x60;
        }
        else {
          *(undefined4 *)(uVar7 * 0x20 + 0x859e60) = 0;
        }
        *(undefined1 *)(uVar7 * 0x20 + 0x859e68) = 0;
        *(undefined1 *)(uVar7 * 0x20 + 0x859e64) = 0;
        *(undefined1 *)(uVar7 * 0x20 + 0x859e65) = 0;
        puVar6 = (uint *)(uVar7 * 0x20 + 0x859e60);
        *puVar6 = *puVar6 | 1;
        FUN_001b21f0(uVar7);
        cRam002678b4 = (char)uVar7 + '\x0f';
        FUN_0015ef10();
        uVar5 = FUN_00116978((uVar7 + 0xf) * 8 + 0x833e50,0xff,8);
        uVar5 = FUN_0015e790(uVar5);
        FUN_001e8ce0(uVar7 + 0xf & 0xff,(uVar7 + 0xf) * 8 + 0x833e50,uVar5);
        uRam00267750 = 0x15;
        uRam00267888 = uRam00267888 | 0x2000;
      }
    }
    break;
  case '\x06':
    lVar4 = FUN_0015ee20();
    if (lVar4 == 0) {
      DAT_00266fa4 = -1;
      if (cRam00833de8 == -1) {
        FUN_001a9310();
      }
      else {
        DAT_00266ff0 = cRam00833de8;
        FUN_0015e9b0(0,0,0x1797000,0x1796000);
        FUN_0015eaa0(0,cRam00267968,0x30);
        cRam0026795c = '\b';
      }
    }
    else {
      FUN_001a8bd0(cRam00833de8);
    }
    break;
  case '\a':
    lVar4 = FUN_0015ee20();
    if (lVar4 == 0) {
      DAT_00266fa4 = -1;
      if (cRam00833de8 == -1) {
        FUN_001a9420();
      }
      else {
        DAT_00266ff0 = cRam00833de8;
        FUN_0015e9b0(0,0,0x1797000,0x1796000);
        FUN_0015eaa0(0,cRam00267968,0x30);
        cRam0026795c = '\t';
      }
    }
    else if (DAT_00266fa4 == -1) {
      FUN_001532e0();
      FUN_00152f40(0,0x74,0x4220,5);
      DAT_00266fa4 = '\0';
    }
    break;
  case '\b':
    lVar4 = FUN_0015ee20();
    if (lVar4 == 0) {
      if (cRam00833de8 == '\0') {
        FUN_001a8e60(DAT_00266ff0);
        FUN_001a9310();
        FUN_00152f40(0,*(undefined2 *)(&DAT_00244050 + (uint)bRam00267964 * 2),0x4220,5);
      }
      else {
        FUN_001a9310();
      }
    }
    break;
  case '\t':
    lVar4 = FUN_0015ee20();
    if (lVar4 == 0) {
      if (cRam00833de8 == '\0') {
        uVar5 = FUN_001a90b0(DAT_00266ff0);
        FUN_001a9420(uVar5);
        FUN_00152f40(0,*(undefined2 *)(&DAT_00244050 + (uint)bRam00267964 * 2),0x4220,5);
      }
      else {
        FUN_001a9420();
      }
    }
    break;
  default:
    FUN_0015ef10();
    uRam00267750 = 0;
  }
  return;
}

