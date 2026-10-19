
void FUN_001c8e90(void)

{
  char cVar1;
  float fStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  if (((((uRam00859fe0 & 0x100) != 0x100) && ((uRam00859fe0 & 2) != 2)) &&
      ((uRam00859fe0 & 0x4000) != 0x4000)) &&
     ((((uRam00859fe0 & 0x40000) != 0x40000 && ((uRam00835050 & 0x20) != 0x20)) &&
      ((bGpffff89d8 & 2) == 2)))) {
    FUN_00124180(uRam00835058,&fStack_10);
    cVar1 = FUN_0014f600(&fStack_10);
    if (cVar1 == '*') {
      uRam00859fe0 = uRam00859fe0 | 0x20000000;
      FUN_0013e2a0(0x10);
      FUN_0014fe50(0x11,7,&fStack_10);
      FUN_0013a620(0x10);
      fStack_10 = fStack_10 - 4.0;
      FUN_00138760(fStack_10,uStack_c,uStack_8,0x10);
      uRam00835050 = uRam00835050 & 0xffffffef;
      uGpffff8aa4 = 10;
    }
  }
  return;
}

