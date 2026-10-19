
byte FUN_001deee0(void)

{
  long lVar1;
  
  pbGpffff8148[1] = 0;
  lVar1 = FUN_0012e120(0,0x40000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 0x10;
  }
  lVar1 = FUN_0012e120(0,0x80000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 0x20;
  }
  lVar1 = FUN_0012e120(0,0x10000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 0x40;
  }
  lVar1 = FUN_0012e120(0,0x20000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 0x80;
  }
  lVar1 = FUN_0012e120(0,0x8000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 1;
  }
  lVar1 = FUN_0012e120(0,0x2000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 2;
  }
  lVar1 = FUN_0012e120(0,0x1000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 4;
  }
  lVar1 = FUN_0012e120(0,0x4000);
  if (lVar1 != 0) {
    pbGpffff8148[1] = pbGpffff8148[1] | 8;
  }
  pbGpffff8148[2] = 0;
  lVar1 = FUN_0012e170(0,0x40000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 0x10;
  }
  lVar1 = FUN_0012e170(0,0x80000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 0x20;
  }
  lVar1 = FUN_0012e170(0,0x10000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 0x40;
  }
  lVar1 = FUN_0012e170(0,0x20000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 0x80;
  }
  lVar1 = FUN_0012e170(0,0x8000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 1;
  }
  lVar1 = FUN_0012e170(0,0x2000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 2;
  }
  lVar1 = FUN_0012e170(0,0x1000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 4;
  }
  lVar1 = FUN_0012e170(0,0x4000);
  if (lVar1 != 0) {
    pbGpffff8148[2] = pbGpffff8148[2] | 8;
  }
  *pbGpffff8148 = 0;
  lVar1 = FUN_0012e210(0,0x40000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 0x10;
  }
  lVar1 = FUN_0012e210(0,0x80000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 0x20;
  }
  lVar1 = FUN_0012e210(0,0x10000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 0x40;
  }
  lVar1 = FUN_0012e210(0,0x20000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 0x80;
  }
  lVar1 = FUN_0012e210(0,0x8000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 1;
  }
  lVar1 = FUN_0012e210(0,0x2000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 2;
  }
  lVar1 = FUN_0012e210(0,0x1000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 4;
  }
  lVar1 = FUN_0012e210(0,0x4000);
  if (lVar1 != 0) {
    *pbGpffff8148 = *pbGpffff8148 | 8;
  }
  *pbGpffff8148 = *pbGpffff8148 | pbGpffff8148[2];
  return *pbGpffff8148;
}

