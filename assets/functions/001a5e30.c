
void FUN_001a5e30(void)

{
  if (cGpffff8a88 == '\0') {
    if (uGpffff8a80 != uGpffff8a7c) {
      uGpffff8a80 = uGpffff8a80 - 1;
      FUN_001a4af0(0,uGpffff8a80);
      FUN_001a4af0(1,uGpffff8a80 + 1);
      FUN_001a4af0(2,uGpffff8a80 + 2);
      cGpffff8a84 = cGpffff8a84 + -1;
      FUN_001a4e90();
      if (uGpffff8a80 == uGpffff8a7c) {
        FUN_0015d1f0(3);
      }
      if ((uGpffff8a80 + 2 != (uint)uGpffff8a7c + (uint)bGpffff8a90 + -1) &&
         ((bRam00833d30 & 1) != 1)) {
        FUN_0015c550(4);
      }
    }
  }
  else {
    FUN_0015cf30(0,0x42000000,0,5);
    cGpffff8a88 = cGpffff8a88 + -1;
    FUN_001a4e90();
  }
  return;
}

