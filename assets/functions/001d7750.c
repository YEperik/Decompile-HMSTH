
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_001d7750(float param_1,undefined2 param_2,float *param_3,float *param_4,float *param_5,
            char param_6)

{
  long lVar1;
  undefined4 uVar2;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  undefined1 auStack_80 [4];
  float fStack_7c;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  undefined2 uStack_30;
  float fStack_28;
  float *pfStack_20;
  float *pfStack_18;
  float *pfStack_10;
  char cStack_8;
  
  fStack_3c = *(float *)(iRam002679e8 + 100) - param_1;
  fStack_38 = 0.0;
  fStack_50 = (float)_DAT_002448b0;
  fStack_4c = (float)((ulong)_DAT_002448b0 >> 0x20);
  fStack_48 = (float)_DAT_002448b8;
  uStack_44 = (undefined4)((ulong)_DAT_002448b8 >> 0x20);
  uVar2 = 1;
  fStack_60 = *param_4;
  fStack_5c = param_4[1];
  fStack_58 = param_4[2];
  fStack_54 = param_4[3];
  uStack_30 = param_2;
  fStack_28 = param_1;
  pfStack_20 = param_3;
  pfStack_18 = param_4;
  pfStack_10 = param_5;
  cStack_8 = param_6;
  FUN_00124180(param_2,param_3);
  fStack_a0 = fStack_60 + *pfStack_10;
  fStack_9c = fStack_5c + pfStack_10[1];
  fStack_98 = fStack_58 + pfStack_10[2];
  FUN_00128b50(&fStack_40,&fStack_a0,pfStack_20);
  fStack_b0 = fStack_a0 - *pfStack_20;
  fStack_ac = fStack_9c - pfStack_20[1];
  fStack_a8 = fStack_98 - pfStack_20[2];
  FUN_00128900(&fStack_b0);
  fStack_28 = fStack_28 / 2.0;
  do {
    fStack_40 = fStack_40 - fStack_38;
    fStack_34 = fStack_40;
    if (fStack_28 <= fStack_40) {
      fStack_34 = fStack_28;
    }
    fStack_38 = fStack_34;
    fStack_90 = fStack_b0 * fStack_34;
    fStack_8c = fStack_ac * fStack_34;
    fStack_88 = fStack_a8 * fStack_34;
    fStack_50 = fStack_50 + fStack_90;
    fStack_4c = fStack_4c + fStack_8c;
    fStack_48 = fStack_48 + fStack_88;
    lVar1 = FUN_00124d90(fStack_50,fStack_4c,fStack_48,uStack_30,auStack_80);
    if (lVar1 != 0) {
      if (cStack_8 == '\x02') {
        uVar2 = 0;
      }
      else if (fStack_7c == 1.0) {
        if (cStack_8 == '\x01') {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
      }
      else {
        uVar2 = 0;
      }
      break;
    }
    if (cStack_8 != '\x02') {
      if (fStack_3c < pfStack_20[1]) {
        pfStack_20[1] = fStack_3c;
        if (cStack_8 == '\x01') {
          uVar2 = 0;
        }
        else {
          uVar2 = 1;
        }
        break;
      }
      fStack_70 = *pfStack_20 + fStack_90;
      fStack_6c = pfStack_20[1] + fStack_8c;
      fStack_68 = pfStack_20[2] + fStack_88;
      lVar1 = FUN_001d7b50(&fStack_70);
      if (lVar1 == 0) {
        uVar2 = 0;
        break;
      }
    }
  } while (0.0 < fStack_40);
  *pfStack_20 = *pfStack_20 + fStack_50;
  pfStack_20[1] = pfStack_20[1] + fStack_4c;
  pfStack_20[2] = pfStack_20[2] + fStack_48;
  FUN_00123f50(*pfStack_20,pfStack_20[1],pfStack_20[2],uStack_30);
  return uVar2;
}

