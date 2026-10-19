
void FUN_001a49d0(void)

{
  int iVar1;
  uint uVar2;
  
  for (uVar2 = 0; (int)uVar2 < 3; uVar2 = uVar2 + 1) {
    for (iVar1 = 0; iVar1 < 0xb; iVar1 = iVar1 + 1) {
      FUN_0015be60((uVar2 * 0xb + 0x120 & 0xffff) + iVar1 & 0xffff);
    }
    FUN_00154480((uVar2 & 0x7f) << 1);
    FUN_00154480(uVar2 * 2 + 1 & 0xff);
  }
  FUN_0015d1f0(3);
  FUN_0015d1f0(4);
  FUN_001532e0();
  FUN_00159fe0();
  FUN_001cd070(0x114);
  FUN_001cd0a0(0x114);
  FUN_001cce50(0x11d);
  FUN_001cce80(0x11d);
  return;
}

