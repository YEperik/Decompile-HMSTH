
void FUN_001c8860(void)

{
  byte bVar1;
  byte bVar2;
  float fStack_50;
  undefined4 uStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  float afStack_40 [2];
  float fStack_38;
  float afStack_30 [2];
  float fStack_28;
  float fStack_20;
  undefined4 uStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  float fStack_8;
  float fStack_4;
  
  bVar2 = 0xff;
  bGpffff8118 = 0xff;
  fStack_8 = 0.0;
  fStack_4 = 4096.0;
  for (bVar1 = 0; bVar1 < 5; bVar1 = bVar1 + 1) {
    if (((((*(uint *)((uint)bVar1 * 0x20 + 0x859f20) & 1) == 1) &&
         ((*(uint *)((uint)bVar1 * 0x20 + 0x859f20) & 0x80000) != 0x80000)) &&
        ((cGpffff8844 == '\0' || (cGpffff8844 == '\x01')))) &&
       ((cGpffff8844 == *(char *)((uint)bVar1 * 0x20 + 0x859f29) && (bGpffff8118 != bVar1)))) {
      FUN_00124180(uRam00835058,afStack_40);
      FUN_00124180(*(undefined2 *)((bVar1 + 0x12) * 0x100 + 0x834058),afStack_30);
      fStack_50 = afStack_40[0] - afStack_30[0];
      uStack_4c = 0;
      fStack_48 = fStack_38 - fStack_28;
      FUN_00128900(&fStack_50);
      FUN_00128b50(&fStack_8,afStack_40,afStack_30);
      if (fStack_8 < fStack_4) {
        fStack_4 = fStack_8;
        fStack_20 = fStack_50;
        uStack_1c = uStack_4c;
        fStack_18 = fStack_48;
        uStack_14 = uStack_44;
        bVar2 = bVar1;
      }
    }
  }
  if (bVar2 == 0xff) {
    uRam00859fe0 = uRam00859fe0 & 0xefffffff;
    uGpffff8aa4 = 0;
  }
  else {
    uRam00859fe0 = uRam00859fe0 & 0xfff8bfff;
    if (bRam00859ffa < 200) {
      uRam00859ff0 = 0x43c00000;
    }
    else {
      uRam00859ff0 = 0x44000000;
    }
    bGpffff8118 = bVar2;
    FUN_0013e2a0(0x10);
    FUN_00137b90(0x10,&fStack_20);
    FUN_00138540(0x10,0x40);
    uGpffff8aa4 = 8;
  }
  return;
}

