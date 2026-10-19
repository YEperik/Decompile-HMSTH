
void FUN_001d9ac0(void)

{
  if ((uGpffff8998 & 0x20) == 0x20) {
    FUN_001d5670();
    FUN_001e0070();
    FUN_0013e710();
    FUN_00137930(0x68);
    FUN_00137930(0x27);
    FUN_00123750(0x32e);
    FUN_001d2100();
    FUN_001376f0(0x68);
    FUN_00123780(0x32e);
    FUN_001222a0(0x32e);
    FUN_001d8740();
    FUN_001ff950();
    FUN_001d9810(0,4);
    uGpffff8998 = uGpffff8998 & 0xffdf;
  }
  return;
}

