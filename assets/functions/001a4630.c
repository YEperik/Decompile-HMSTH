
/* WARNING: Removing unreachable block (ram,0x001a4890) */
/* WARNING: Removing unreachable block (ram,0x001a48dc) */

void FUN_001a4630(byte param_1)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  undefined4 uStack_18;
  
  sVar1 = (ushort)param_1 * 10 + (ushort)param_1 + 0x120;
  if (param_1 == 2) {
    uStack_18 = 112.0;
  }
  else if (param_1 == 1) {
    uStack_18 = 144.0;
  }
  else if (param_1 == 0) {
    uStack_18 = 176.0;
  }
  sVar2 = 0;
  for (uVar3 = 0; uVar3 < 0xb; uVar3 = uVar3 + 1 & 0xffff) {
    FUN_0015ae30((float)((uVar3 + 1) * 0x10) / 256.0,0,(float)(uVar3 << 4) / 256.0,0x3f800000,
                 sVar1 + sVar2,0x18,0x18);
    FUN_0015bcd0(sVar1 + sVar2,(ushort)param_1 * 10 + (ushort)param_1 + 0x33f + sVar2,
                 (ushort)param_1 * 10 + (ushort)param_1 + 0xd52 + sVar2,param_1 + 0xdb);
    FUN_0015c040((float)uVar3 * 23.0 + -248.0,uStack_18 + -0.0,0x47c34f80,sVar1 + sVar2);
    sVar2 = sVar2 + 1;
  }
  FUN_00154110(0x40a00000,uStack_18,0x47c34f80,(param_1 & 0x7f) << 1);
  FUN_00154110(0x42940000,uStack_18,0x47c34f80,param_1 * '\x02' + '\x01');
  return;
}

