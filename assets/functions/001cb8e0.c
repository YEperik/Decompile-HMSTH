
void FUN_001cb8e0(undefined1 param_1,undefined1 param_2)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  undefined1 auStack_1c0 [432];
  undefined1 uStack_10;
  undefined1 uStack_8;
  
  DAT_002444a1 = (undefined1)((int)((bRam0085a2f7 & 1) * 0x10 + 0xa0) >> 2);
  DAT_002444a0 = (undefined1)(((int)(bRam0085a2f7 & 2) >> 1) * 0x28 >> 2);
  uStack_10 = param_1;
  uStack_8 = param_2;
  FUN_001cc310(uRam0085a2f6,2,2,0x2444a8,0xb0,0xa0,8,0x10);
  if (bRam0085a2f5 / 0xc == 0) {
    iVar3 = 0xe0;
  }
  else {
    iVar3 = 0xf0;
  }
  DAT_002444d0 = (undefined1)(iVar3 >> 2);
  DAT_002444d1 = 0x34;
  FUN_001cc310((uint)bRam0085a2f5 % 0xc,2,2,0x2444d8,0x70,0xc0,8,0x10);
  FUN_001cc310(uRam0085a2f4,2,1,0x2444fc,0x70,0xc0,8,0x10);
  uVar1 = FUN_001cc720(bRam0085a2f7,uRam0085a2f6);
  DAT_00244518 = (undefined1)((int)((uVar1 & 0xff) << 4) >> 2);
  for (sVar2 = 0; sVar2 < 0xc; sVar2 = sVar2 + 1) {
    FUN_001cc050(sVar2 * 0xc + 0x244490,auStack_1c0 + sVar2 * 0x24,uStack_8,uStack_10,0xcf,0x100,
                 0x100);
  }
  FUN_001ddec0(0xc,auStack_1c0);
  FUN_001ddff0(0xc,auStack_1c0);
  return;
}

