
void FUN_001b78e0(undefined1 param_1)

{
  undefined1 auStack_20 [24];
  undefined1 uStack_8;
  
  if ((uRam00835250 & 0x80000000) != 0x80000000) {
    uStack_8 = param_1;
    FUN_001ff4f0(0,0x43200000,0,0x17,0,uRam00835258);
    FUN_00178c00(uStack_8);
    FUN_0013e2a0(0x12);
    FUN_001244b0(uRam00834058,auStack_20);
    FUN_00137b90(0x12,auStack_20);
    FUN_00138360(0x12,0x80);
    if ((int)(bGpffff8928 - 0x14) < 0) {
      bGpffff8928 = 0;
    }
    else {
      bGpffff8928 = (byte)(bGpffff8928 - 0x14);
    }
    uRam00835250 = uRam00835250 | 0x80000000;
  }
  return;
}

