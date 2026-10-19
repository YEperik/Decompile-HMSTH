
void FUN_001a5f90(void)

{
  if (bGpffff8a88 == 2) {
    if (uGpffff8a80 + 4 <= (uint)uGpffff8a7c + (uint)bGpffff8a90) {
      uGpffff8a80 = uGpffff8a80 + 1;
      FUN_001a4af0(0,uGpffff8a80);
      FUN_001a4af0(1,uGpffff8a80 + 1);
      FUN_001a4af0(2,uGpffff8a80 + 2);
      cGpffff8a84 = cGpffff8a84 + '\x01';
      FUN_001a4e90();
      if (uGpffff8a80 + 2 == (uint)uGpffff8a7c + (uint)bGpffff8a90 + -1) {
        FUN_0015d1f0(4);
      }
      if ((uGpffff8a80 != uGpffff8a7c) && ((bRam00833d14 & 1) != 1)) {
        FUN_0015c550(3);
      }
    }
  }
  else if ((uint)uGpffff8a80 + (uint)bGpffff8a88 + 1 < (uint)uGpffff8a7c + (uint)bGpffff8a90) {
    FUN_0015cf30(0,0xc2000000,0,5);
    bGpffff8a88 = bGpffff8a88 + 1;
    FUN_001a4e90();
  }
  return;
}

