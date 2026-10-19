
ushort FUN_001dd6a0(byte param_1,undefined4 param_2)

{
  bool bVar1;
  ushort uVar2;
  long lVar3;
  ushort uVar4;
  
  uVar4 = (ushort)param_1;
  bVar1 = false;
  uVar2 = FUN_001df930();
  FUN_001df900();
  do {
    uVar4 = uVar4 + 1;
    if ((short)(uVar2 & 0xff) <= (short)uVar4) {
      if (bVar1) {
        return 0xff;
      }
      bVar1 = true;
      uVar4 = 0;
      FUN_001df900();
    }
    lVar3 = FUN_001dd8e0(uVar4 & 0xff,param_2);
  } while (lVar3 == 0);
  return uVar4 & 0xff;
}

