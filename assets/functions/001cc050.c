
void FUN_001cc050(short *param_1,int param_2,char param_3,char param_4,undefined1 param_5,
                 short param_6,short param_7)

{
  *(char *)(param_2 + 1) = *(char *)((int)param_1 + 7) + param_3;
  *(undefined1 *)(param_2 + 2) = param_5;
  *(undefined1 *)(param_2 + 3) = 7;
  *(float *)(param_2 + 4) =
       (float)((int)*param_1 + ((int)((uint)*(byte *)(param_1 + 5) << 2) >> 1) + -0x140);
  *(float *)(param_2 + 8) =
       (float)-((int)param_1[1] + ((int)((uint)*(byte *)((int)param_1 + 0xb) << 2) >> 1) + -0xe0);
  *(float *)(param_2 + 0xc) = (float)((int)(char)param_1[3] + (int)param_4) + 100000.0;
  *(float *)(param_2 + 0x10) =
       ((float)((uint)*(byte *)(param_1 + 2) << 2) + (float)((uint)*(byte *)(param_1 + 4) << 2)) /
       (float)(int)param_6;
  *(float *)(param_2 + 0x14) =
       ((float)((uint)*(byte *)((int)param_1 + 5) << 2) + 1.0) / (float)(int)param_7;
  *(float *)(param_2 + 0x18) =
       ((float)((uint)*(byte *)(param_1 + 2) << 2) + 1.0) / (float)(int)param_6;
  *(float *)(param_2 + 0x1c) =
       ((float)((uint)*(byte *)((int)param_1 + 5) << 2) +
       (float)((uint)*(byte *)((int)param_1 + 9) << 2)) / (float)(int)param_7;
  *(ushort *)(param_2 + 0x20) = (ushort)*(byte *)(param_1 + 5) << 2;
  *(ushort *)(param_2 + 0x22) = (ushort)*(byte *)((int)param_1 + 0xb) << 2;
  return;
}

