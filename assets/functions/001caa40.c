
void FUN_001caa40(void)

{
  undefined8 uVar1;
  undefined2 unaff_s0_lo;
  undefined2 unaff_s1_lo;
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  uVar1 = FUN_00136db0(0xcd,0x19e1000);
  FUN_001167c0(0x10ff000,0x19e1000,uVar1);
  if (cRam0085a2f7 == '\x03') {
    unaff_s0_lo = 1;
    unaff_s1_lo = 5;
  }
  else if (cRam0085a2f7 == '\x02') {
    unaff_s0_lo = 1;
    unaff_s1_lo = 4;
  }
  else if (cRam0085a2f7 == '\x01') {
    unaff_s0_lo = 0;
    unaff_s1_lo = 3;
  }
  else if (cRam0085a2f7 == '\0') {
    unaff_s0_lo = 0;
    unaff_s1_lo = 2;
  }
  FUN_001361f0(unaff_s1_lo,0x10ff000,0x1101000);
  FUN_001361f0(6,0x10ff000,0x1101800);
  FUN_001361f0(unaff_s0_lo,0x10ff000,0x1941000);
  FUN_00148f40(auStack_20,0x1941000,0xd5,0xc2200,0xc6200,0x1101000);
  FUN_00148f40(auStack_10,0x1941000,0xd6,0xc4200,0xc7200,0x1101800);
  return;
}

