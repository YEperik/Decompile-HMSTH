
void FUN_001b21f0(byte param_1)

{
  ulong uVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 1) == 1) {
    uVar1 = FUN_00148df0(0,0xe0);
    if ((long)uVar1 < 0) {
      fVar4 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar4 = (float)(int)uVar1;
    }
    iVar2 = (uint)param_1 * 0x10;
    iVar3 = (uint)param_1 * 0x20;
    uVar7 = *(undefined4 *)(&DAT_00244274 + iVar2);
    uVar5 = *(undefined4 *)(&DAT_00244278 + iVar2);
    uVar6 = *(undefined4 *)(&DAT_0024427c + iVar2);
    *(undefined4 *)(iVar3 + 0x859e70) = *(undefined4 *)(&DAT_00244270 + iVar2);
    *(undefined4 *)(iVar3 + 0x859e74) = uVar7;
    *(undefined4 *)(iVar3 + 0x859e78) = uVar5;
    *(undefined4 *)(iVar3 + 0x859e7c) = uVar6;
    *(float *)((uint)param_1 * 0x20 + 0x859e78) =
         *(float *)((uint)param_1 * 0x20 + 0x859e78) + (fVar4 - 112.0);
    *(undefined1 *)((uint)param_1 * 0x20 + 0x859e69) = 0xe;
  }
  return;
}

