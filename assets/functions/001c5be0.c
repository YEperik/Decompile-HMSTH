
void FUN_001c5be0(float *param_1)

{
  ulong uVar1;
  float fVar2;
  float fVar3;
  float afStack_40 [4];
  float afStack_30 [2];
  float fStack_28;
  undefined2 uStack_16;
  undefined2 uStack_14;
  byte abStack_11 [9];
  float *pfStack_8;
  
  fVar3 = *param_1;
  fVar2 = param_1[2];
  if (((((cGpffff8944 != '\0') && (cGpffff8944 != '\x04')) &&
       ((cRam0085a2f7 == '\0' || (cRam0085a2f7 == '\x01')))) &&
      (((7 < bRam0085a2f5 && (bRam0085a2f5 < 0x13)) &&
       (pfStack_8 = param_1, uVar1 = FUN_00148df0(0,99), uVar1 < 0x19)))) &&
     (FUN_001c72b0(abStack_11,&uStack_16,&uStack_14), abStack_11[0] != 0xff)) {
    FUN_001c5940(abStack_11[0],uStack_16,uStack_14,0xc4,0x1788000);
    FUN_00137ae0(fVar3,0,fVar2,abStack_11[0]);
    FUN_001378a0(abStack_11[0]);
    FUN_00139920(abStack_11[0]);
    FUN_00124180(uRam00834058,afStack_30);
    afStack_40[0] = afStack_30[0] - fVar3;
    afStack_40[1] = 0.0;
    afStack_40[2] = fStack_28 - fVar2;
    FUN_00128900(afStack_40);
    FUN_00137b90(abStack_11[0],afStack_40);
    FUN_00138360(abStack_11[0],0x40);
    *(undefined1 *)((abStack_11[0] - 0x21) * 8 + 0x859930) = 1;
    *(undefined1 *)((abStack_11[0] - 0x21) * 8 + 0x859934) = 3;
    *(ushort *)((abStack_11[0] - 0x21) * 8 + 0x859932) = (ushort)abStack_11[0];
    *(undefined1 *)((abStack_11[0] - 0x21) * 8 + 0x859935) = 0;
  }
  return;
}

