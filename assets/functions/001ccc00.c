
/* WARNING: Removing unreachable block (ram,0x001ccce4) */
/* WARNING: Removing unreachable block (ram,0x001ccd38) */

void FUN_001ccc00(float param_1,undefined4 param_2,undefined4 param_3,short param_4,short param_5,
                 short param_6,undefined4 param_7)

{
  byte *pbVar1;
  short sVar2;
  undefined1 auStack_50 [5];
  char acStack_4b [7];
  float fStack_44;
  short sStack_38;
  short sStack_30;
  short sStack_28;
  float fStack_20;
  undefined4 uStack_18;
  undefined4 uStack_10;
  undefined4 uStack_8;
  
  sStack_38 = param_4;
  sStack_30 = param_5;
  sStack_28 = param_6;
  fStack_20 = param_1;
  uStack_18 = param_2;
  uStack_10 = param_3;
  uStack_8 = param_7;
  FUN_001547b0(auStack_50,param_7,1,8);
  acStack_4b[0] = '\x1b';
  for (sVar2 = 0; sVar2 < 3; sVar2 = sVar2 + 1) {
    pbVar1 = (byte *)FUN_001cc770(acStack_4b[sVar2] + -0x11);
    FUN_001cc990(0x41800000,0x41a00000,(float)(*pbVar1 + 8) / 256.0,(float)pbVar1[1] / 256.0,
                 (float)*pbVar1 / 256.0,(float)(pbVar1[1] + 10) / 256.0,fStack_20,uStack_18,
                 sStack_38 + sVar2,sStack_30 + sVar2,sStack_28 + sVar2);
    fStack_44 = fStack_20 + 16.0;
    fStack_20 = fStack_44;
  }
  return;
}

