
ushort FUN_001dd7b0(byte param_1,undefined4 param_2)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  long lVar4;
  
  uVar2 = (ushort)param_1;
  bVar1 = false;
  uVar3 = FUN_001df930();
  FUN_001df900();
  do {
    uVar2 = uVar2 - 1;
    if ((short)uVar2 < 0) {
      if (bVar1) {
        return 0xff;
      }
      bVar1 = true;
      uVar2 = (uVar3 & 0xff) - 1;
      FUN_001df900();
    }
    lVar4 = FUN_001dd8e0(uVar2 & 0xff,param_2);
  } while (lVar4 == 0);
  return uVar2 & 0xff;
}

