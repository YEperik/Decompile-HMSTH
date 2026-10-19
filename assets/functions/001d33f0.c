
void FUN_001d33f0(ushort param_1,short param_2,float *param_3)

{
  ulong uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fStack_50;
  float fStack_48;
  undefined1 auStack_40 [24];
  float fStack_28;
  undefined4 auStack_24 [3];
  ushort uStack_18;
  short sStack_10;
  float *pfStack_8;
  
  uStack_18 = param_1;
  sStack_10 = param_2;
  pfStack_8 = param_3;
  if (968.0 < *(float *)(iRam002679e8 + 0x1a0)) {
    fVar2 = (float)FUN_00112f70(*(undefined4 *)(iRam002679e8 + 0xf0));
    fStack_50 = *(float *)(iRam002679e8 + 0x90) + (float)((int)sStack_10 >> 1) * fVar2;
    fVar2 = (float)FUN_00112bf8(*(undefined4 *)(iRam002679e8 + 0xf0));
    fStack_48 = *(float *)(iRam002679e8 + 0x98) + (float)((int)sStack_10 >> 1) * fVar2;
  }
  else {
    fStack_50 = *(float *)(iRam002679e8 + 0x90);
    fStack_48 = *(float *)(iRam002679e8 + 0x98);
  }
  uVar1 = FUN_00148df0(0,0x274);
  if ((long)uVar1 < 0) {
    fVar2 = (float)(uVar1 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)uVar1;
  }
  fStack_28 = fVar2 / 100.0 + *(float *)(iRam002679e8 + 0xf0);
  FUN_001dff50(&fStack_28);
  fVar2 = (float)FUN_00112f70(fStack_28);
  *pfStack_8 = fStack_50 - (float)((int)(uint)uStack_18 >> 1) * fVar2;
  fVar2 = (float)FUN_00112bf8(fStack_28);
  pfStack_8[2] = fStack_48 - (float)((int)(uint)uStack_18 >> 1) * fVar2;
  pfStack_8[1] = *(float *)(iRam002679e8 + 0xfc);
  FUN_00128b50(auStack_24,iRam002679e8 + 0x90,pfStack_8);
  FUN_001d54d0(auStack_40,pfStack_8,iRam002679e8 + 0x90);
  fVar4 = *(float *)(iRam002679e8 + 0x94);
  fVar2 = *(float *)(iRam002679e8 + 0x98);
  fVar3 = *(float *)(iRam002679e8 + 0x9c);
  *pfStack_8 = *(float *)(iRam002679e8 + 0x90);
  pfStack_8[1] = fVar4;
  pfStack_8[2] = fVar2;
  pfStack_8[3] = fVar3;
  FUN_001d7670(0x41f00000,auStack_24[0],0x32e,pfStack_8,iRam002679e8 + 0x90,auStack_40,2);
  *(undefined4 *)(iRam002679e8 + 0x100) = 0;
  uVar1 = FUN_00148df0(1,4);
  if ((long)uVar1 < 0) {
    fVar2 = (float)(uVar1 & 0xffffffff);
  }
  else {
    fVar2 = (float)(int)uVar1;
  }
  *(float *)(iRam002679e8 + 0x104) = fVar2;
  return;
}

