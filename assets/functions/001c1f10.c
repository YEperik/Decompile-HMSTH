
void FUN_001c1f10(byte param_1)

{
  char cVar1;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float afStack_30 [2];
  float fStack_28;
  float afStack_14 [3];
  byte bStack_8;
  
  afStack_14[0] = 0.0;
  if ((param_1 != 0x10) || ((bRam00859fe4 & 0x10) == 0x10)) {
    bStack_8 = param_1;
    cVar1 = FUN_0013b260(param_1);
    FUN_001244b0(*(undefined2 *)((uint)bStack_8 * 0x100 + 0x834058),afStack_30);
    if (cVar1 == '\x02') {
      uStack_40 = 0x3f800000;
      uStack_3c = 0;
      uStack_38 = 0;
      if (afStack_30[0] < 0.0) {
        uStack_40 = 0xbf800000;
      }
      FUN_00128980(afStack_14,afStack_30,&uStack_40);
      if (afStack_14[0] <= 0.35) {
        if (((bStack_8 == 0x10) && ((bRam00859fe4 & 0x10) == 0x10)) || (bStack_8 == 0x11)) {
          FUN_001c2a90(bStack_8);
        }
        else {
          FUN_001b9720(bStack_8);
        }
      }
    }
    else if (((cVar1 == -0x10) || (cVar1 == '\x01')) && ((cVar1 != -0x10 || (bStack_8 == 0x11)))) {
      uStack_40 = 0;
      uStack_3c = 0;
      uStack_38 = 0x3f800000;
      if (fStack_28 < 0.0) {
        uStack_38 = 0xbf800000;
      }
      FUN_00128980(afStack_14,afStack_30,&uStack_40);
      if (afStack_14[0] <= 0.35) {
        if (((bStack_8 == 0x10) && ((bRam00859fe4 & 0x10) == 0x10)) || (bStack_8 == 0x11)) {
          FUN_001c2a90(bStack_8);
        }
        else {
          FUN_001b9720(bStack_8);
        }
      }
    }
  }
  return;
}

