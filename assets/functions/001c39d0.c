
void FUN_001c39d0(void)

{
  uint uVar1;
  
  uGpffff8ac0 = (uint)bGpffff8928;
  for (uVar1 = 0; uVar1 < 5; uVar1 = uVar1 + 1 & 0xff) {
    uGpffff8ac0 = uGpffff8ac0 + (byte)(&gp0xffff8930)[uVar1];
  }
  uGpffff8ac4 = uRam0085a2f5;
  uGpffff8ac8 = uRam0085a2f4;
  bGpffff89dc = bGpffff89dc | 8;
  FUN_00116978(&gp0xffff89a8,0,6);
  uGpffff89b0 = 1;
  return;
}

