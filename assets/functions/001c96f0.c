
void FUN_001c96f0(byte param_1)

{
  int iVar1;
  float *pfVar2;
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float afStack_14 [3];
  byte bStack_8;
  
  afStack_14[0] = 0.0;
  if ((&DAT_00267000)[param_1] != '\r') {
    bStack_8 = param_1;
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x800000) == 0x800000) {
      FUN_00139920(param_1 + 0x12,0x13);
    }
    else {
      FUN_00124180(uRam00834058,&uStack_30);
      FUN_00124180(*(undefined2 *)((bStack_8 + 0x12) * 0x100 + 0x834058),auStack_40);
      FUN_00128b50(afStack_14,auStack_40,&uStack_30);
      if (128.0 < afStack_14[0]) {
        if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) == 4) {
          uStack_2c = 0;
          iVar1 = (bStack_8 + 0x12) * 0x100;
          *(undefined4 *)(iVar1 + 0x834080) = uStack_30;
          *(undefined4 *)(iVar1 + 0x834084) = 0;
          *(undefined4 *)(iVar1 + 0x834088) = uStack_28;
          *(undefined4 *)(iVar1 + 0x83408c) = uStack_24;
        }
        else {
          FUN_00138760(uStack_30,0,uStack_28,bStack_8 + 0x12);
        }
      }
      else {
        FUN_0013e2a0(bStack_8 + 0x12);
        FUN_00138ce0(bStack_8 + 0x12);
      }
      pfVar2 = (float *)((uint)bStack_8 * 4 + 0x85a3d0);
      *pfVar2 = *pfVar2 - 2.4;
      if (*(float *)((uint)bStack_8 * 4 + 0x85a3d0) <= 0.0) {
        *(undefined4 *)((uint)bStack_8 * 4 + 0x85a3d0) = 0;
        (&DAT_00267000)[bStack_8] = 0;
        FUN_0013dff0(bStack_8 + 0x12,0x140,0,0x140);
        FUN_001c4590(bStack_8);
      }
    }
  }
  return;
}

