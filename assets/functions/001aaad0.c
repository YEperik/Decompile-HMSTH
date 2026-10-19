
void FUN_001aaad0(void)

{
  bool bVar1;
  ushort uVar2;
  char cVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  lVar4 = FUN_001536f0();
  if (lVar4 == 0) {
    if (cGpffff8aa0 == '\0') {
      if ((cGpffff89c8 == '\0') || (cVar3 = FUN_001e3960(), cVar3 != '\0')) {
        cGpffff89c8 = '\0';
        uGpffff89c0 = 0;
        lVar4 = FUN_00167620();
        if ((lVar4 == 0) && (lVar4 = FUN_0021a800(cGpffff8844), lVar4 == 0)) {
          if (sGpffff8860 == 0) {
            if ((bGpffff89d8 & 0x20) == 0x20) {
              bGpffff89d8 = bGpffff89d8 & 0xdf | 1;
              if (cGpffff8844 == '\v') {
                FUN_0014e740();
              }
              if ((uRam00859fe0 & 1) == 1) {
                if (cRam0085a004 == '\0') {
                  FUN_001b2160();
                  cRam0085a004 = '\x01';
                }
                else if (cRam0085a004 == '\v') {
                  cRam0085a004 = '\f';
                }
              }
              if (((uRam00859fc0 & 1) == 1) && (cRam00859fc9 == '\0')) {
                FUN_001b25d0();
                cRam00859fc9 = '\x01';
              }
              for (uVar7 = 0; (int)uVar7 < 6; uVar7 = uVar7 + 1) {
                if ((*(uint *)(uVar7 * 0x20 + 0x859e60) & 1) == 1) {
                  if (*(char *)(uVar7 * 0x20 + 0x859e69) == '\0') {
                    FUN_001b2330(uVar7 & 0xff);
                  }
                  else if (*(char *)(uVar7 * 0x20 + 0x859e69) == '\v') {
                    *(undefined1 *)(uVar7 * 0x20 + 0x859e69) = 0xc;
                  }
                }
              }
              for (iVar6 = 0; iVar6 < 5; iVar6 = iVar6 + 1) {
                if (((*(uint *)(iVar6 * 0x20 + 0x859f20) & 1) == 1) &&
                   (*(char *)(iVar6 * 0x20 + 0x859f29) == '\0')) {
                  *(undefined1 *)(iVar6 * 0x20 + 0x859f29) = 1;
                }
              }
            }
            if ((bGpffff89d8 & 0x40) == 0x40) {
              bGpffff89d8 = bGpffff89d8 & 0xbf | 2;
              if (((uRam00859fe0 & 1) == 1) && ((cRam0085a004 == '\0' || (cRam0085a004 == '\x01'))))
              {
                FUN_001b2160();
              }
              for (uVar7 = 0; (int)uVar7 < 6; uVar7 = uVar7 + 1) {
                if (((*(uint *)(uVar7 * 0x20 + 0x859e60) & 1) == 1) &&
                   ((*(char *)(uVar7 * 0x20 + 0x859e69) == '\0' ||
                    (*(char *)(uVar7 * 0x20 + 0x859e69) == '\x01')))) {
                  FUN_001b21f0(uVar7 & 0xff);
                }
              }
            }
            if ((cGpffff8844 != '\v') && (cGpffff8844 != '\f')) {
              if (cGpffff8844 != -1) {
                FUN_001d9ac0();
                if ((uRam00834050 & 0x80) == 0x80) {
                  uRam0083d020 = uRam00834058;
                  uRam0083d044 = 0x42a00000;
                  FUN_00126650();
                  FUN_001266a0();
                  FUN_00126700(0x3f800000);
                  FUN_00141cb0(0x11);
                  FUN_001b24b0();
                }
                uVar2 = uRam00834054;
                if ((uRam00834050 & 0x400) == 0x400) {
                  FUN_0013c060();
                  if (uVar2 == 0x73) {
                    FUN_001b2160();
                  }
                  else if ((uVar2 == 0x74) || (uVar2 == 0x75)) {
                    FUN_001b21f0(cGpffff884c + -0x1b);
                  }
                  else {
                    lVar4 = FUN_0016bc20(uVar2 & 0xff,1);
                    if (lVar4 != 0) {
                      FUN_0016bff0(uVar2 & 0xff,1);
                    }
                  }
                }
                FUN_0014e740();
                FUN_0013f0c0(0,uRam00834120,0,0);
                for (uVar7 = 0; (int)uVar7 < 0x80; uVar7 = uVar7 + 1) {
                  if (uVar7 != 0) {
                    FUN_001376f0(uVar7 & 0xff);
                  }
                }
                FUN_001ff950();
                return;
              }
              uGpffff8846 = 0x26;
              if ((bGpffff89d8 & 1) == 1) {
                FUN_0014d170(0xc);
              }
              else {
                FUN_0014d170(0xb);
              }
              FUN_00139c00();
              FUN_0013a0b0(0,1);
              FUN_001a9530();
              FUN_00185ad0();
            }
            FUN_0014b770(0,0,0,0x83c510);
            FUN_0014b770(0,0,0,0x83c4d0);
            FUN_0014b770(0,0,0,0x83c390);
            FUN_0014b770(0,0,0,0x83c350);
            FUN_0014b770(0,0,0,0x83c310);
            FUN_0014b770(0,0,0,0x83c2d0);
            FUN_0014b770(0,0,0,0x83c490);
            FUN_0014b770(0,0,0,0x83c450);
            FUN_0014b770(0,0,0,0x83c410);
            FUN_0014b770(0,0,0,0x83c3d0);
            FUN_0014b770(0,0,0,0x83c290);
            FUN_0014b770(0,0,0,0x83c250);
            FUN_0014b770(0,0,0,0x83c210);
            FUN_0014b770(0,0,0,0x83c1d0);
            FUN_0014b770(0,0,0,0x83c190);
            FUN_0014b770(0,0,0,0x83c150);
            FUN_0014b770(0,0,0,0x83c110);
            FUN_0014b770(0,0,0,0x83c0d0);
            FUN_0014b770(0,0,0,0x83c090);
            FUN_0014b770(0,0,0,0x83c050);
            uRam00859fe0 = uRam00859fe0 & 0xbfffffff;
            uRam00859fc0 = uRam00859fc0 & 0xbfffffff;
            bVar1 = (uGpffff8998 & 0x40) == 0x40;
            bVar8 = bVar1;
            if ((uGpffff8998 & 0x80) == 0x80) {
              bVar8 = 2;
            }
            if ((uGpffff8998 & 0x100) == 0x100) {
              bVar8 = bVar8 | 4;
            }
            if ((uGpffff8998 & 0x200) == 0x200) {
              bVar8 = bVar8 | 8;
            }
            uGpffff8998 = 0;
            if (bVar1) {
              uGpffff8998 = 0x40;
            }
            if ((bVar8 & 2) == 2) {
              uGpffff8998 = uGpffff8998 | 0x80;
            }
            if ((bVar8 & 4) == 4) {
              uGpffff8998 = uGpffff8998 | 0x100;
            }
            if ((bVar8 & 8) == 8) {
              uGpffff8998 = uGpffff8998 | 0x200;
            }
            uRam00834050 = 0x13;
            FUN_00137ae0(0x42880000,0x41400000,0x42100000);
            uStack_10 = 0;
            uStack_c = 0;
            uStack_8 = 0x3f800000;
            FUN_00137b90(0,&uStack_10);
            FUN_00139920();
            FUN_001378a0();
            FUN_0013e710();
            uGpffff8998 = uGpffff8998 & 0xf3ff;
            cGpffff89b0 = '\0';
            for (iVar6 = 0; iVar6 < 6; iVar6 = iVar6 + 1) {
              (&gp0xffff89a8)[iVar6] = 0;
              if ((cGpffff89b0 != '\0') && (((&gp0xffff89a0)[iVar6] & 0x10) == 0x10)) {
                if (iVar6 == 0) {
                  if (bGpffff8928 < 3) {
                    bGpffff8928 = 0;
                  }
                  else {
                    bGpffff8928 = bGpffff8928 - 3;
                  }
                }
                else if ((byte)(&gp0xffff892f)[iVar6] < 3) {
                  (&gp0xffff892f)[iVar6] = 0;
                }
                else {
                  (&gp0xffff892f)[iVar6] = (&gp0xffff892f)[iVar6] + -3;
                }
              }
              (&gp0xffff89a0)[iVar6] = 0;
            }
            uGpffff889c = 8;
            uGpffff898c = 0;
            uGpffff8988 = 0;
            for (iVar6 = 0; iVar6 < 5; iVar6 = iVar6 + 1) {
              (&gp0xffff8980)[iVar6] = 0;
            }
            FUN_00148700(cRam0085a2f7);
            FUN_0014e450();
            FUN_001613c0(6);
            FUN_001640c0(cRam0085a2f7,cRam0085a2f6,0x85a2f8);
            FUN_00151010();
            uVar5 = FUN_00164cb0();
            FUN_00167880(uVar5);
            uVar5 = FUN_00170110();
            FUN_00170a90(uVar5);
            FUN_0016cfb0();
            FUN_00167a60();
            uGpffff8888 = 0xff;
            cVar3 = FUN_00170db0();
            FUN_0017d090();
            FUN_001b3220();
            FUN_00207f30();
            FUN_001eb6c0();
            uGpffff885c = uGpffff885c & 0xfffe;
            FUN_00166c00();
            FUN_001a9530();
            if (cVar3 == '\0') {
              FUN_002199d0();
              FUN_00219a60(cGpffff8844);
              FUN_0021a400();
              FUN_00166d90(0x1e,1);
              sGpffff8860 = 1;
            }
            else {
              if ((uRam00835050 & 1) == 1) {
                FUN_00137930(0x10);
              }
              for (iVar6 = 0; iVar6 < 6; iVar6 = iVar6 + 1) {
                if ((uRam00835b50 & 1) == 1) {
                  FUN_00137930(iVar6 + 0x1bU & 0xff);
                }
              }
              FUN_0015e770(0x1a);
            }
          }
          else {
            FUN_0015e770();
            sGpffff8860 = 0;
          }
        }
      }
      else {
        if ((5 < bRam0085a2f5) &&
           (bVar1 = cRam0085a2f6 == '\x01', cRam0085a2f6 = cRam0085a2f6 + -1, bVar1)) {
          cRam0085a2f6 = '\x1e';
          cRam0085a2f7 = cRam0085a2f7 + -1;
        }
        cGpffff89c8 = '\0';
        FUN_0015e770();
        sGpffff8860 = 0x12;
      }
    }
    else {
      cGpffff8aa0 = '\0';
    }
  }
  else {
    cGpffff8aa0 = '\x01';
    FUN_00218e70(0x4c0);
  }
  return;
}

