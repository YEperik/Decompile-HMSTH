
void FUN_001ddb20(byte param_1,undefined1 param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  byte bStack_10;
  undefined1 uStack_8;
  
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0xbf800000;
  bStack_10 = param_1;
  uStack_8 = param_2;
  pcVar1 = (char *)FUN_001dfb10(0,param_2);
  *pcVar1 = *pcVar1 + -1;
  if (*pcVar1 == '\0') {
    iVar2 = FUN_001df900();
    *(undefined1 *)(iVar2 + (uint)bStack_10) = 0xff;
  }
  FUN_0014bd30(uStack_8);
  FUN_00139920(0x27);
  FUN_00137b90(0x27,&uStack_20);
  uGpffff8950 = uStack_8;
  FUN_0013b4e0(0,0x27,uStack_8);
  FUN_001378a0(0x27);
  return;
}

