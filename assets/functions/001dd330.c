
void FUN_001dd330(void)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  undefined1 uStack_1;
  
  lVar4 = FUN_001536f0();
  if (((lVar4 == 0) && (lVar4 = FUN_0015ee20(), lVar4 == 0)) && (lVar4 = FUN_00167620(), lVar4 == 0)
     ) {
    lVar4 = FUN_0012e170(0,4);
    if (((lVar4 == 0) && (lVar4 = FUN_0012e170(0,0x8000), lVar4 == 0)) &&
       ((lVar4 = FUN_0012e170(0,0x40000), lVar4 == 0 &&
        ((lVar4 = FUN_0012e210(0,0x8000), lVar4 == 0 &&
         (lVar4 = FUN_0012e210(0,0x40000), lVar4 == 0)))))) {
      lVar4 = FUN_0012e170(0,8);
      if ((((lVar4 == 0) && (lVar4 = FUN_0012e170(0,0x2000), lVar4 == 0)) &&
          (lVar4 = FUN_0012e170(0,0x80000), lVar4 == 0)) &&
         ((lVar4 = FUN_0012e210(0,0x2000), lVar4 == 0 &&
          (lVar4 = FUN_0012e210(0,0x80000), lVar4 == 0)))) {
        lVar4 = FUN_0012e170(0,0x20);
        if (lVar4 == 0) {
          lVar4 = FUN_0012e170(0,0x100);
          if (lVar4 == 0) {
            lVar4 = FUN_0012e170(0,0x40);
            if (lVar4 != 0) {
              lVar4 = FUN_001dd8e0(bRam002679f0,&uStack_1);
              if (lVar4 != 0) {
                FUN_00218ea0();
                FUN_001ddb20(bRam002679f0,uStack_1);
              }
              FUN_001dd640();
            }
          }
          else if (bRam002679f0 != 0xff) {
            iVar3 = FUN_001df900();
            cVar2 = FUN_001df760(*(undefined1 *)(iVar3 + (uint)bRam002679f0));
            if (cVar2 != -1) {
              FUN_00218ea0();
              FUN_00152f40(0,cVar2,0x20,0);
            }
          }
        }
        else {
          FUN_00218ea0(1);
          FUN_001dd640();
        }
      }
      else {
        bVar1 = FUN_001dd6a0(bRam002679f0,&uStack_1);
        if (bVar1 != bRam002679f0) {
          FUN_00218ea0(2);
          bRam002679f0 = bVar1;
        }
        FUN_001dd9b0(bRam002679f0);
      }
    }
    else {
      bVar1 = FUN_001dd7b0(bRam002679f0,&uStack_1);
      if (bVar1 != bRam002679f0) {
        FUN_00218ea0(2);
        bRam002679f0 = bVar1;
      }
      FUN_001dd9b0(bRam002679f0);
    }
  }
  return;
}

