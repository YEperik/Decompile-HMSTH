
void FUN_001d0af0(void)

{
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  *puGpffff8af8 = 0xd;
  FUN_001d1b10();
  switch(*(undefined1 *)(puGpffff8af8 + 0xbe)) {
  case 0:
    FUN_00152f40(0,0xd,0x220,0);
    break;
  case 1:
    FUN_00152f40(0,0xe,0x220,0);
    break;
  case 2:
    FUN_00152f40(0,0xf,0x20,0);
    break;
  case 5:
    FUN_0013e710(0,2);
    if (uGpffff8964 < 999) {
      uGpffff8964 = uGpffff8964 + 1;
    }
  case 3:
  case 4:
    FUN_001d9460();
    FUN_00152f40(0,10,0x20,0);
    if (uGpffff8960 < 999) {
      uGpffff8960 = uGpffff8960 + 1;
    }
    if (uGpffff8968 < 999) {
      uGpffff8968 = uGpffff8968 + 1;
    }
    break;
  case 6:
    FUN_0013e710(0,2);
    FUN_00152f40(0,0xb,0x20,0);
    break;
  case 7:
    FUN_0013e710(0,2);
    FUN_00152f40(0,0xc,0x20,0);
    break;
  case 8:
    FUN_0013e710(0,2);
    FUN_00124180(uRam00836758,&uStack_10);
    FUN_001ff4f0(uStack_10,uStack_c,uStack_8,8,0,uRam00836758);
  }
  return;
}

