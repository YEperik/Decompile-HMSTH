
void FUN_001a1790(void)

{
  byte bVar1;
  long lVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  lVar2 = FUN_00167620();
  if (lVar2 == 0) {
    if ((iRam002678e4 == 0xfe) || (iRam002678e4 == 0xff)) {
      uRam00267750 = 0;
      FUN_0014e620();
      if (iRam002678e4 == 0xfe) {
        uRam002678b8 = 1;
        uRam002678d0 = 0x14;
        FUN_001e3970();
        iRam002678e4 = 0;
        return;
      }
      if (iRam002678e4 == 0xff) {
        iRam002678e4 = 0;
      }
    }
    if (iRam002678e4 == 0xfd) {
      FUN_0014e620();
      uRam002678d0 = FUN_0015e790();
      FUN_00218070();
      uRam00267750 = 0x12;
      iRam002678e4 = 0;
      iRam002678e8 = 2;
      iRam002678ec = 0;
    }
    else {
      if ((iRam002678e4 == 1) || (iRam002678e4 == 2)) {
        lVar2 = FUN_0012e170(0,0x1000);
        if (((lVar2 != 0) || (lVar2 = FUN_0012e170(0,0x10000), lVar2 != 0)) &&
           (FUN_00218ea0(2), 0 < iRam002678e8)) {
          FUN_0015cf30(0,0x41c00000,0,5);
          iRam002678e8 = iRam002678e8 + -1;
        }
        lVar2 = FUN_0012e170(0,0x4000);
        if (((lVar2 != 0) || (lVar2 = FUN_0012e170(0,0x20000), lVar2 != 0)) &&
           (FUN_00218ea0(2), iRam002678e8 < 2)) {
          FUN_0015cf30(0,0xc1c00000,0,5);
          iRam002678e8 = iRam002678e8 + 1;
        }
        lVar2 = FUN_0012e170(0,0x40);
        if (lVar2 != 0) {
          FUN_00218ea0();
          if (iRam002678e8 == 0) {
            if (iRam002678e4 != 1) {
              FUN_001532e0(1);
              FUN_00152000(1);
              FUN_0015d1f0(5);
              FUN_001532e0(2);
              FUN_00152000(2);
              iRam002678e4 = 0;
              iRam002678e8 = 0;
              iRam002678ec = 0;
              bRam00267880 = bRam0085a2f5;
              uRam00267881 = uRam0085a2f4;
              if ((5 < bRam0085a2f5) &&
                 (bVar1 = cRam0085a2f6 + 1, cRam0085a2f6 = cRam0085a2f6 + '\x01', 0x1e < bVar1)) {
                cRam0085a2f6 = '\x01';
                cRam0085a2f7 = cRam0085a2f7 + '\x01';
              }
              FUN_00167330(0x1e);
              iRam002678e4 = 0xfe;
              return;
            }
            FUN_00151df0(0x43100000,0x42900000,0x3f480000,0x3dc00000,0x3ec80000,0x3e000000,2,0x1e1,
                         0x753,3);
            FUN_00151ec0(0x43200000,0,0x47c34f00,2);
            FUN_00152040(2,0x26b,0x7db,0x88,2,6,3,0);
            fVar3 = (fRam00833f94 - 72.0) + 12.0 + 2.0;
            fVar4 = (fRam00833f98 + 36.0) - 12.0;
            fVar5 = fRam00833f9c - 1.0;
            FUN_00152a20(fVar3,fVar4,fVar5,2);
            FUN_00152ed0(2,0xa18000,0xa17000);
            FUN_00152f40(2,6,0x420);
            FUN_0015cd00((fVar3 - 24.0) - 2.0,fVar4 - 12.0,fVar5,5);
            iRam002678e4 = 2;
          }
          else if (iRam002678e8 == 1) {
            FUN_001532e0(1);
            FUN_00152000(1);
            FUN_0015d1f0(5);
            if (iRam002678e4 == 1) {
              FUN_001532e0(1);
              FUN_00152000(1);
              iRam002678e4 = 0;
              iRam002678e8 = 1;
              iRam002678ec = 0;
              uRam00267750 = 0x11;
              FUN_00167330(0x1e);
              return;
            }
            FUN_001532e0(2);
            FUN_00152000(2);
            iRam002678e4 = 0;
            iRam002678e8 = 0;
            iRam002678ec = 0;
            bRam00267880 = bRam0085a2f5;
            uRam00267881 = uRam0085a2f4;
            if ((5 < bRam0085a2f5) &&
               (bVar1 = cRam0085a2f6 + 1, cRam0085a2f6 = cRam0085a2f6 + '\x01', 0x1e < bVar1)) {
              cRam0085a2f6 = '\x01';
              cRam0085a2f7 = cRam0085a2f7 + '\x01';
            }
            uRam0026774c = uRam0026774c | 1;
            FUN_0015e770(0x14);
            uRam00267750 = 0;
            FUN_00167330(0x1e);
            FUN_0021a780();
          }
          else {
            if (iRam002678e4 == 1) {
              FUN_001532e0(1);
              FUN_00152000(1);
              FUN_0015d1f0(5);
              iRam002678e4 = 0xfd;
              FUN_00167330(0x1e);
              return;
            }
            FUN_001532e0(2);
            FUN_00152000(2);
            FUN_0015cd00((((fRam00833f84 - 72.0) + 12.0 + 2.0) - 24.0) - 2.0,
                         (((fRam00833f88 + 36.0) - 12.0) - 12.0) - (float)iRam002678ec * 24.0,
                         uRam00833f8c,5);
            iRam002678e8 = iRam002678ec;
            iRam002678e4 = 1;
          }
          iRam002678ec = iRam002678e8;
          return;
        }
        lVar2 = FUN_0012e170(0,0x20);
        if (lVar2 != 0) {
          FUN_00218ea0(1);
          if (iRam002678e4 == 1) {
            FUN_001532e0(1);
            FUN_00152000(1);
            FUN_0015d1f0(5);
            iRam002678e4 = 0;
            iRam002678e8 = 0;
            iRam002678ec = 0;
            uRam00267750 = 0;
            FUN_00166c00();
            return;
          }
          FUN_001532e0(2);
          FUN_00152000(2);
          FUN_0015cd00((((fRam00833f84 - 72.0) + 12.0 + 2.0) - 24.0) - 2.0,
                       (((fRam00833f88 + 36.0) - 12.0) - 12.0) - (float)iRam002678ec * 24.0,
                       uRam00833f8c,5);
          iRam002678e4 = 1;
          iRam002678e8 = iRam002678ec;
          return;
        }
      }
      if (iRam002678e4 == 0) {
        FUN_001a2230();
      }
    }
  }
  return;
}

