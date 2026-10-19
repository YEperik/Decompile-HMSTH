
/* WARNING: Removing unreachable block (ram,0x001dedd8) */

float FUN_001deda0(float param_1,float param_2,int param_3,char param_4,byte param_5)

{
  undefined4 uStack_34;
  
  if (param_4 == '\0') {
    uStack_34 = (*(float *)(param_3 + 4) - (float)((int)(uint)*(ushort *)(param_3 + 0x20) >> 1)) -
                param_2 * ((float)param_5 + param_1);
  }
  else {
    uStack_34 = *(float *)(param_3 + 4) + (float)((int)(uint)*(ushort *)(param_3 + 0x20) >> 1) +
                param_1 * param_2;
  }
  return uStack_34 + param_2 / 2.0;
}

