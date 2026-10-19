
void FUN_001a4540(byte param_1)

{
  undefined8 unaff_s0;
  undefined8 unaff_s1;
  
  if (param_1 == 2) {
    unaff_s1 = 0x17a8700;
    unaff_s0 = 0xfc600;
  }
  else if (param_1 == 1) {
    unaff_s1 = 0x17a7b80;
    unaff_s0 = 0xfb600;
  }
  else if (param_1 == 0) {
    unaff_s1 = 0x17a7000;
    unaff_s0 = 0xfa600;
  }
  FUN_0011e4d0(param_1 + 0xdb,unaff_s1,unaff_s0,0x14,0,0,0x100,0x10);
  return;
}

