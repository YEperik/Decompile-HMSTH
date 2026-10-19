
void FUN_001a9530(void)

{
  uint uVar1;
  undefined4 uVar2;
  
  for (uVar1 = 0; uVar1 < 0x80; uVar1 = uVar1 + 1 & 0xff) {
    if ((*(uint *)(uVar1 * 0x100 + 0x834050) & 1) == 1) {
      uVar2 = FUN_00141880(uVar1);
      FUN_0013a3e0(0,uVar2,0,uVar2,uVar1,0);
    }
  }
  return;
}

