
void FUN_001cdb40(undefined1 param_1)

{
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined1 uStack_8;
  
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0xbf800000;
  uStack_8 = param_1;
  FUN_0014bd30(param_1);
  FUN_00139920(0x27);
  FUN_00137b90(0x27,&uStack_20);
  uGpffff8950 = uStack_8;
  FUN_0013b4e0(0,0x27,uStack_8);
  FUN_001378a0(0x27);
  FUN_0015bfb0(0x10f);
  FUN_0015ab30(*(char *)(iGpffff8af4 + 6) + 1U & 1);
  return;
}

