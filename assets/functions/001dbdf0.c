
void FUN_001dbdf0(byte param_1,char param_2)

{
  undefined4 uVar1;
  
  if (param_2 != -1) {
    FUN_00159ce0(param_1,param_1 + 0xd + *(short *)(iGpffff8148 + 10),
                 *(short *)(iGpffff8148 + 8) + (ushort)param_1 * 4 + 0xd,
                 *(int *)(iGpffff8148 + 0xc) + 0x54 + (uint)param_1 * 0x11000);
    uVar1 = FUN_001dfce0(0x42800000,param_2);
    FUN_0015a290(uVar1,param_1,param_2,1);
  }
  return;
}

