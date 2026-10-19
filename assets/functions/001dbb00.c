
void FUN_001dbb00(char param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 auStack_60 [80];
  char cStack_10;
  undefined1 uStack_8;
  
  cStack_10 = param_1;
  uStack_8 = param_2;
  if (param_1 == '\0') {
    FUN_001de160(4,4);
  }
  else {
    FUN_001cc310(param_2,2,1,0x24490c,0x70,0xc0,8,0x10);
    for (sVar1 = 0; sVar1 < 2; sVar1 = sVar1 + 1) {
      FUN_001cc050(&DAT_002448d0 + (sVar1 + 5) * 0xc,auStack_60 + sVar1 * 0x24,0,0,0xcf,0x100,0x100)
      ;
    }
    FUN_001ddec0(2,auStack_60);
    FUN_001ddff0(2,auStack_60);
    FUN_0015bf20(*(short *)(iGpffff8148 + 6) + 4);
  }
  return;
}

