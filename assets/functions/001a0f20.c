
void FUN_001a0f20(void)

{
  bool bVar1;
  long lVar2;
  char cVar3;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  switch(uGpffff8a68) {
  case 0:
    FUN_0013a620();
    uRam00834050 = uRam00834050 & 0xffffffef;
    FUN_00138760(0xc4108000,0,0x43840000);
    uGpffff8a68 = 1;
    break;
  case 1:
    if ((uRam00834050 & 4) != 4) {
      FUN_00218ea0(0x31);
      FUN_00123950(1,0xb);
      uStack_10 = 0;
      uStack_c = 0;
      uStack_8 = 0xbf800000;
      FUN_00137cc0(0x41a00000,0,&uStack_10);
      uGpffff8a68 = 2;
    }
    break;
  case 2:
    lVar2 = FUN_00137df0();
    if (lVar2 == 0) {
      FUN_00138360(0,0x40);
      uGpffff8a68 = 3;
    }
    break;
  case 3:
    if ((uRam00834050 & 4) != 4) {
      FUN_00123950(1,0xc);
      uStack_10 = 0;
      uStack_c = 0;
      uStack_8 = 0x3f800000;
      FUN_00137cc0(0x41a00000,0,&uStack_10);
      cRam008340b5 = 'x';
      uGpffff8a68 = 4;
    }
    break;
  case 4:
    if (cRam008340b5 == 'd') {
      FUN_00218ea0(0x32);
      FUN_00218ea0(0x15);
    }
    if (cRam008340b5 == '\x14') {
      FUN_00218ea0(0x31);
      FUN_00123950(1,0xb);
    }
    cVar3 = cRam008340b5 + -1;
    bVar1 = cRam008340b5 == '\x01';
    cRam008340b5 = cVar3;
    if (bVar1) {
      FUN_0013e710(0,2);
      FUN_00138360(0,0x40);
      uGpffff8a68 = 5;
    }
    break;
  case 5:
    if ((uRam00834050 & 4) != 4) {
      FUN_00123950(1,0xc);
      FUN_00138ce0();
      cRam008340b5 = '(';
      uGpffff8a68 = 0xff;
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
      uGpffff8a68 = 0;
      uGpffff8860 = 0;
      if ((uGpffff8998 & 0x400) != 0x400) {
        uGpffff8998 = uGpffff8998 | 0x400;
        if ((int)(uint)bGpffff8940 < (int)(bGpffff8941 - 2)) {
          bGpffff8940 = bGpffff8940 + 2;
        }
        else {
          bGpffff8940 = bGpffff8941;
        }
      }
    }
  }
  return;
}

