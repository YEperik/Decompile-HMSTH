
void FUN_001c9020(char param_1)

{
  float fStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  char cStack_8;
  
  if (cRam00267994 != '\v') {
    cStack_8 = param_1;
    FUN_0013e2a0(0x10);
    if (cStack_8 == '\0') {
      FUN_0014fe50(0x11,8,&fStack_20);
    }
    else {
      FUN_0014fe50(0x11,9,&fStack_20);
    }
    FUN_0013a620(0x10);
    fStack_20 = fStack_20 - 4.0;
    FUN_00138760(fStack_20,uStack_1c,uStack_18,0x10);
    cRam00267994 = '\v';
  }
  return;
}

