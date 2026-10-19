
uint FUN_001dc230(char param_1,char param_2,int *param_3,undefined4 *param_4)

{
  uint uVar1;
  undefined4 uVar2;
  ulong uVar3;
  ulong uVar4;
  
  uVar3 = (long)((int)param_2 >> 2) & 0xff;
  uVar4 = (long)param_2 & 3;
  uVar1 = (uint)uVar4;
  if (((long)param_2 < 0) && (uVar4 != 0)) {
    uVar1 = uVar1 - 4;
  }
  uVar2 = FUN_001dbd60(param_1,param_2);
  *param_4 = uVar2;
  if (((long)uVar3 < (long)*(char *)(iRam002679ec + param_1 + 0xc)) ||
     ((long)(*(char *)(iRam002679ec + param_1 + 0xc) + 3) <= (long)uVar3)) {
    *param_3 = 0;
    uVar1 = 0xff;
  }
  else {
    *param_3 = *(int *)(iRam002679ec + param_1 * 4 + 0x1c) +
               ((int)uVar3 - (int)*(char *)(iRam002679ec + param_1 + 0xc)) * 4 + (uVar1 & 0xff);
    uVar1 = param_1 * 0xc +
            (uVar1 & 0xff) + ((int)uVar3 - (int)*(char *)(iRam002679ec + param_1 + 0xc)) * 4 & 0xff;
  }
  return uVar1;
}

