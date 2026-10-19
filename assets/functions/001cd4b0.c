
ushort FUN_001cd4b0(void)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  byte *pbVar5;
  
  uVar2 = *(byte *)(iRam002679e4 + 5) + 1;
  bVar1 = false;
  uVar3 = FUN_001df930(0);
  iVar4 = FUN_001df900(0);
  pbVar5 = (byte *)(iVar4 + (short)uVar2);
  while( true ) {
    if ((short)(uVar3 & 0xff) <= (short)uVar2) {
      if (bVar1) {
        return 0xff;
      }
      bVar1 = true;
      uVar2 = 0;
      pbVar5 = (byte *)FUN_001df900(0);
    }
    if ((*pbVar5 < 0x3a) && (*(char *)(*pbVar5 + 0x85a2a0) != '\0')) break;
    uVar2 = uVar2 + 1;
    pbVar5 = pbVar5 + 1;
  }
  return uVar2 & 0xff;
}

