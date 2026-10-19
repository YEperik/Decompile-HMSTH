
/* WARNING: Removing unreachable block (ram,0x001cafd4) */
/* WARNING: Removing unreachable block (ram,0x001cafdc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_001cac40(undefined2 param_1,undefined4 param_2)

{
  byte bVar1;
  uint uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  uint uVar9;
  short sVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  uint auStack_e0 [24];
  float afStack_80 [4];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined8 uStack_60;
  undefined1 auStack_58 [16];
  undefined1 auStack_48 [16];
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  uint uStack_18;
  undefined2 uStack_14;
  byte bStack_12;
  undefined1 uStack_11;
  undefined2 uStack_10;
  undefined4 uStack_8;
  
  bVar1 = bRam0085a2f6;
  uStack_14 = 0;
  auStack_e0[0] = (uint)_DAT_00244400;
  auStack_e0[1] = (uint)((ulong)_DAT_00244400 >> 0x20);
  auStack_e0[2] = (uint)_DAT_00244408;
  auStack_e0[3] = (uint)((ulong)_DAT_00244408 >> 0x20);
  auStack_e0[4] = DAT_00244410;
  auStack_e0[5] = DAT_00244414;
  auStack_e0[6] = (uint)_DAT_00244418;
  auStack_e0[7] = (uint)((ulong)_DAT_00244418 >> 0x20);
  auStack_e0[8] = DAT_00244420;
  auStack_e0[9] = DAT_00244424;
  auStack_e0[10] = (uint)_DAT_00244428;
  auStack_e0[0xb] = (uint)((ulong)_DAT_00244428 >> 0x20);
  auStack_e0[0xc] = DAT_00244430;
  auStack_e0[0xd] = DAT_00244434;
  auStack_e0[0xe] = DAT_00244438;
  auStack_e0[0xf] = DAT_0024443c;
  auStack_e0[0x10] = DAT_00244440;
  auStack_e0[0x11] = DAT_00244444;
  auStack_e0[0x12] = DAT_00244448;
  auStack_e0[0x13] = DAT_0024444c;
  auStack_e0[0x14] = DAT_00244450;
  auStack_e0[0x15] = DAT_00244454;
  auStack_e0[0x16] = (uint)_DAT_00244458;
  auStack_e0[0x17] = (uint)((ulong)_DAT_00244458 >> 0x20);
  afStack_80[0] = (float)_DAT_00244460;
  afStack_80[1] = (float)((ulong)_DAT_00244460 >> 0x20);
  afStack_80[2] = (float)_DAT_00244468;
  afStack_80[3] = (float)((ulong)_DAT_00244468 >> 0x20);
  uStack_70 = DAT_00244470;
  uStack_6c = DAT_00244474;
  uStack_68 = (undefined4)_DAT_00244478;
  uStack_64 = (undefined4)((ulong)_DAT_00244478 >> 0x20);
  uStack_60 = DAT_00244480;
  if (cRam0085a2f7 == '\x03') {
    uVar12 = 3;
  }
  else if (cRam0085a2f7 == '\x02') {
    uVar12 = 2;
  }
  else if (cRam0085a2f7 == '\x01') {
    uVar12 = 1;
  }
  else if (cRam0085a2f7 == '\0') {
    uVar12 = 0;
  }
  else {
    uVar12 = 0;
  }
  bStack_12 = 1;
  uStack_10 = param_1;
  uStack_8 = param_2;
  FUN_001ca260();
  FUN_001ca290(0x42e00000,0xc3000000);
  FUN_001361f0(auStack_e0[uVar12 * 6 + 1] & 0xffff,0x10ff000,0x1101000);
  FUN_001361f0(6,0x10ff000,0x1101800);
  FUN_001361f0(auStack_e0[uVar12 * 6] & 0xffff,0x10ff000,0x1941000);
  FUN_00148f40(auStack_58,0x1941000,0xd5,0xc2200,0xc6200,0x1101000);
  FUN_00148f40(auStack_48,0x1941000,0xd6,0xc4200,0xc7200,0x1101800);
  fStack_28 = 0.0;
  fStack_24 = 64.0;
  fStack_20 = 100000.0;
  fStack_38 = (float)auStack_e0[uVar12 * 6 + 2];
  fStack_34 = (float)auStack_e0[uVar12 * 6 + 3];
  fStack_30 = (float)auStack_e0[uVar12 * 6 + 4];
  fStack_2c = (float)auStack_e0[uVar12 * 6 + 5];
  FUN_001ca2c0(0,0x42800000,0x47c35000,fStack_38,fStack_34,fStack_30,fStack_2c,0x43400000,0x10f,
               0x32d,0xd3d,0xd5);
  FUN_0015bf20(0x10f);
  fStack_28 = -104.0;
  fStack_24 = 152.0;
  fStack_20 = 99999.8;
  fStack_38 = (float)((int)uVar12 >> 1) * 40.0;
  fStack_34 = (float)(uVar12 & 1) * 16.0 + 160.0 + 0.1;
  fStack_30 = fStack_38 + 39.0;
  fStack_2c = fStack_34 + 15.0;
  FUN_001ca2c0(0xc2d00000,0x43180000,0x47c34fe6,fStack_38,fStack_34,fStack_30,fStack_2c,0x43800000,
               0x110,0x32e,0xd3e,0xcf);
  FUN_0015bf20(0x110);
  sVar3 = 0x111;
  sVar4 = 0x32f;
  sVar5 = 0xd3f;
  fStack_28 = 1.0;
  fStack_24 = 115.5;
  fStack_20 = 99999.8;
  fStack_38 = 0.0;
  fStack_34 = 192.0;
  fStack_2c = 207.0;
  for (iVar13 = 0; iVar13 < 7; iVar13 = iVar13 + 1) {
    fStack_30 = fStack_38 + 15.0;
    FUN_001ca2c0(-126.0 - fStack_28,fStack_24,fStack_20,fStack_38,fStack_34,fStack_30,fStack_2c,
                 0x43800000,sVar3,sVar4,sVar5,0xcf);
    FUN_0015bf20(sVar3);
    sVar3 = sVar3 + 1;
    sVar4 = sVar4 + 1;
    sVar5 = sVar5 + 1;
    fStack_28 = fStack_28 - 42.0;
    fStack_38 = fStack_38 + 16.0;
    fStack_1c = fStack_38;
  }
  if (bVar1 == 0) {
    uStack_18 = 0x1e;
  }
  else {
    uStack_18 = (uint)bVar1 % 0x1f;
  }
  uVar2 = uStack_18;
  fStack_28 = (float)(((uint)bStack_12 + uVar12 * 0x1e) % 7) * 42.0;
  fStack_24 = 84.0;
  fStack_20 = 99999.8;
  for (uVar11 = 1; (int)uVar11 < 0x1f; uVar11 = uVar11 + 1) {
    uVar8 = FUN_001640c0(uVar12,uVar11 & 0xff,&uStack_11);
    fStack_38 = afStack_80[(uVar8 & 0xff) * 2];
    fStack_30 = fStack_38 + 7.0;
    fStack_34 = afStack_80[(uVar8 & 0xff) * 2 + 1];
    fStack_2c = fStack_34 + 7.0;
    FUN_001ca610(fStack_28 + -126.0,fStack_24,fStack_20 + 0.1,0x41b00000,0x41700000,fStack_38,
                 fStack_34,fStack_38 + 7.0,sVar3,sVar4,sVar5,0xcf);
    FUN_0015bf20(sVar3);
    sVar6 = sVar3 + 1;
    sVar7 = sVar4 + 1;
    sVar10 = sVar5 + 1;
    if (9 < (int)uVar11) {
      uVar8 = (int)uVar11 / 10 & 3;
      if (((int)uVar11 / 10 < 0) && (uVar8 != 0)) {
        uVar8 = uVar8 - 4;
      }
      fStack_38 = (float)(int)uVar8 * 8.0 + 160.0;
      fStack_34 = 0.0;
      fStack_30 = fStack_38 + 7.0;
      fStack_2c = 15.0;
      FUN_001ca2c0((fStack_28 + -126.0) - 8.0,fStack_24,fStack_20,fStack_38,0,fStack_30,0x41700000,
                   0x43800000,sVar6,sVar7,sVar10,0xd6);
      FUN_0015bf20(sVar6);
      sVar6 = sVar3 + 2;
      sVar7 = sVar4 + 2;
      sVar10 = sVar5 + 2;
    }
    uVar8 = (int)uVar11 % 10;
    uVar9 = uVar8 & 3;
    if (((int)uVar8 < 0) && (uVar9 != 0)) {
      uVar9 = uVar9 - 4;
    }
    fStack_38 = (float)(int)uVar9 * 8.0 + 160.0;
    fStack_34 = (float)((int)uVar8 >> 2) * 16.0;
    fStack_30 = fStack_38 + 7.0;
    fStack_2c = fStack_34 + 15.0;
    FUN_001ca2c0(fStack_28 + -126.0 + 8.0,fStack_24,fStack_20,fStack_38,fStack_34,fStack_30,
                 fStack_2c,0x43800000,sVar6,sVar7,sVar10,0xd6);
    FUN_0015bf20(sVar6);
    sVar3 = sVar6 + 1;
    sVar4 = sVar7 + 1;
    sVar5 = sVar10 + 1;
    if (uVar11 == uVar2) {
      FUN_001ca610(fStack_28 + -126.0,fStack_24,fStack_20 - 0.2,0x41c00000,0x41c00000,0x43700000,
                   0x42000000,0x437f0000,sVar3,sVar4,sVar5,0xcf);
      FUN_0015bf20(sVar3);
      sVar3 = sVar6 + 2;
      sVar4 = sVar7 + 2;
      sVar5 = sVar10 + 2;
    }
    fStack_28 = fStack_28 + 42.0;
    if (294.0 <= fStack_28) {
      fStack_28 = 0.0;
      fStack_24 = fStack_24 - 28.0;
    }
  }
  sGpffff8af0 = sVar3;
  FUN_001ca930(8,0x1cb870,uStack_10,uStack_8);
  return;
}

