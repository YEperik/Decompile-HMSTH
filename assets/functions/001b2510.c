
void FUN_001b2510(byte param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 1) == 1) {
    iVar1 = (uint)param_1 * 0x10;
    iVar2 = (uint)param_1 * 0x20;
    uVar5 = *(undefined4 *)(&DAT_00244334 + iVar1);
    uVar3 = *(undefined4 *)(&DAT_00244338 + iVar1);
    uVar4 = *(undefined4 *)(&DAT_0024433c + iVar1);
    *(undefined4 *)(iVar2 + 0x859f30) = *(undefined4 *)(&DAT_00244330 + iVar1);
    *(undefined4 *)(iVar2 + 0x859f34) = uVar5;
    *(undefined4 *)(iVar2 + 0x859f38) = uVar3;
    *(undefined4 *)(iVar2 + 0x859f3c) = uVar4;
    *(undefined1 *)((uint)param_1 * 0x20 + 0x859f29) = 0xd;
  }
  return;
}

