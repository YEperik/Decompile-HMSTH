
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_001b5a10(uint *param_1,undefined1 param_2)

{
  ulong uVar1;
  float fVar2;
  
  if ((*param_1 & 2) != 2) {
    uVar1 = FUN_00148df0(0,999999);
    if ((long)uVar1 < 0) {
      fVar2 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar2 = (float)(int)uVar1;
    }
    if (fVar2 / 10000.0 <= _DAT_00244380 * 100.0) {
      *(undefined1 *)((int)param_1 + 5) = param_2;
      *param_1 = *param_1 | 2;
      *param_1 = *param_1 & 0xfffffffb;
      *param_1 = *param_1 & 0xfffffff7;
      *(undefined1 *)(param_1 + 1) = 0;
    }
  }
  return;
}

