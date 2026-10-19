
void FUN_001cf0d0(void)

{
  long lVar1;
  
  lVar1 = FUN_00123d10(uRam00834058);
  if (lVar1 != 0) {
    *puRam002679e4 = 5;
    FUN_00123950(1,(uint)*(byte *)(puRam002679e4 + 2) * 2 + 0x15);
    FUN_00139ac0();
  }
  return;
}

