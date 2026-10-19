
undefined4 FUN_001dd8e0(byte param_1,byte *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  
  bVar1 = FUN_001df930(0);
  if (param_1 < bVar1) {
    iVar3 = FUN_001df900(0);
    *param_2 = *(byte *)(iVar3 + (uint)param_1);
    if ((*param_2 < 0x51) && (*(char *)(*param_2 + 0x85a2a0) != '\0')) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

