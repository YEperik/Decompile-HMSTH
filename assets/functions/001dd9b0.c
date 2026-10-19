
void FUN_001dd9b0(undefined1 param_1)

{
  long lVar1;
  undefined4 uVar2;
  undefined1 auStack_11 [9];
  undefined1 uStack_8;
  
  uStack_8 = param_1;
  lVar1 = FUN_001dd8e0(param_1,auStack_11);
  if (lVar1 == 0) {
    FUN_0015ab30();
    FUN_0015ab30(1);
  }
  else {
    FUN_0015ab30(bGpffff8b04);
    FUN_00159ce0(bGpffff8b04,bGpffff8b04 + 0x32e,(uint)bGpffff8b04 * 0x10 + 0xd3e,
                 (uint)bGpffff8b04 * 0x11000 + 0x1ad5000);
    uVar2 = FUN_001dfce0(0x42b00000,auStack_11[0]);
    FUN_0015a290(uVar2,bGpffff8b04,auStack_11[0],1);
    FUN_0015a0e0(0,0x43040000,0x47c34000,bGpffff8b04);
    FUN_0015aab0(bGpffff8b04);
    bGpffff8b04 = bGpffff8b04 + 1 & 1;
    FUN_0015ab30(bGpffff8b04);
  }
  return;
}

