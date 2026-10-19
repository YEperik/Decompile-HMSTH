
void FUN_001a1300(void)

{
  bool bVar1;
  long lVar2;
  char cVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  switch(uRam00267958) {
  case 0:
    FUN_0013a620();
    uRam00834050 = uRam00834050 & 0xffffffef;
    FUN_00138760(0xc43d8000,0,0x43840000);
    uRam00267958 = 1;
    break;
  case 1:
    if ((uRam00834050 & 4) != 4) {
      FUN_00218ea0(0x31);
      FUN_00123950(1,0xf);
      uStack_10 = 0;
      uStack_c = 0;
      uStack_8 = 0xbf800000;
      FUN_00137cc0(0x41a00000,0,&uStack_10);
      uRam00267958 = 2;
    }
    break;
  case 2:
    lVar2 = FUN_00137df0();
    if (lVar2 == 0) {
      FUN_00138360(0,0x40);
      uRam00267958 = 3;
    }
    break;
  case 3:
    if ((uRam00834050 & 4) != 4) {
      FUN_00123950(1,0x10);
      uStack_10 = 0x3f800000;
      uStack_c = 0;
      uStack_8 = 0;
      FUN_00137cc0(0x41a00000,0,&uStack_10);
      cRam008340b5 = -0x10;
      uRam00267958 = 4;
    }
    break;
  case 4:
    if (cRam008340b5 == -0x24) {
      FUN_00218ea0(0x32);
      FUN_00218ea0(0x22);
    }
    if (cRam008340b5 == -0x4c) {
      FUN_00218ea0(0x25);
    }
    if (cRam008340b5 == -0x60) {
      FUN_00218ea0(0x25);
    }
    if (cRam008340b5 == 'd') {
      FUN_00218ea0(0x24);
    }
    if (cRam008340b5 == '<') {
      FUN_00218ea0(0x22);
    }
    if (cRam008340b5 == '\x14') {
      FUN_00218ea0(0x31);
      FUN_00123950(1,0xf);
      uStack_10 = 0;
      uStack_c = 0;
      uStack_8 = 0x3f800000;
      FUN_00137b90(0,&uStack_10);
    }
    cVar3 = cRam008340b5 + -1;
    bVar1 = cRam008340b5 == '\x01';
    cRam008340b5 = cVar3;
    if (bVar1) {
      FUN_0013e710(0,10);
      FUN_00138360(0,0x40);
      uRam00267958 = 5;
    }
    break;
  case 5:
    if ((uRam00834050 & 4) != 4) {
      FUN_00123950(1,0x10);
      FUN_00138ce0();
      cRam008340b5 = '(';
      uRam00267958 = 0xff;
    }
    break;
  default:
    if (cRam008340b5 == '\x14') {
      FUN_00218ea0(0x32);
    }
    cVar3 = cRam008340b5 + -1;
    bVar1 = cRam008340b5 == '\x01';
    cRam008340b5 = cVar3;
    if (bVar1) {
      FUN_0013e710();
      FUN_0013a620(0,1,1);
      uRam00834050 = uRam00834050 | 0x10;
      uRam00267958 = 0;
      uRam00267750 = 0;
      if ((uRam00267888 & 0x800) != 0x800) {
        uRam00267888 = uRam00267888 | 0x800;
        if (bRam00267832 < 0x1f) {
          bRam00267832 = 0;
        }
        else {
          bRam00267832 = bRam00267832 - 0x1e;
        }
      }
    }
  }
  return;
}

