
void FUN_001dc690(undefined1 param_1,undefined1 param_2)

{
  char cVar1;
  undefined1 *puStack_18;
  undefined1 auStack_14 [4];
  undefined1 uStack_10;
  undefined1 uStack_8;
  
  uStack_10 = param_1;
  uStack_8 = param_2;
  FUN_001dc230(param_1,param_2,auStack_14,&puStack_18);
  cVar1 = FUN_001df760(*puStack_18);
  FUN_001dc740(uStack_10,uStack_8);
  if (cVar1 != -1) {
    FUN_00152f40(0,cVar1,0x20);
    *puRam002679ec = 8;
  }
  return;
}

