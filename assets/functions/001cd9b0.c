
void FUN_001cd9b0(byte param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_1 != 0xff) {
    iVar3 = FUN_001df900();
    cVar1 = *(char *)(iVar3 + (uint)param_1);
    if (cVar1 != -1) {
      bVar2 = *(byte *)(iGpffff8af4 + 6);
      FUN_0015ab30(bVar2);
      FUN_00159ce0(bVar2,bVar2 + 0x32e,(uint)bVar2 * 0x10 + 0xd3e,
                   ((uint)bVar2 * 10 + (uint)bVar2) * 0x2000 + 0x1ad5014);
      uVar4 = FUN_001dfce0(0x42b00000,cVar1);
      FUN_0015a290(uVar4,bVar2,cVar1,1);
      FUN_0015a0e0(0,0x43040000,0x47c34000,bVar2);
      FUN_0015aab0(bVar2);
      *(byte *)(iGpffff8af4 + 6) = *(char *)(iGpffff8af4 + 6) + 1U & 1;
      FUN_0015ab30(*(undefined1 *)(iGpffff8af4 + 6));
      return;
    }
  }
  FUN_0015ab30();
  FUN_0015ab30(1);
  return;
}

