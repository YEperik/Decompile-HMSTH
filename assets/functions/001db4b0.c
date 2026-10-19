
void FUN_001db4b0(void)

{
  byte *pbVar1;
  char cVar2;
  undefined1 uVar3;
  byte *pbStack_10;
  byte *pbStack_c;
  byte *pbStack_8;
  byte *pbStack_4;
  
  cVar2 = FUN_001dc230(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5),
                       &pbStack_10,&pbStack_c);
  uVar3 = FUN_001dc230(*(undefined1 *)(puRam002679ec + 2),*(undefined1 *)((int)puRam002679ec + 0xb),
                       &pbStack_8,&pbStack_4);
  if (cVar2 == -1) {
    pbVar1 = *(byte **)(puRam002679ec + 0x12);
    FUN_001dbdf0(*pbVar1,*pbStack_c);
    pbStack_10 = pbVar1;
    FUN_0015ab30(*pbStack_8);
  }
  *pbStack_8 = *pbStack_8 ^ *pbStack_10;
  *pbStack_10 = *pbStack_10 ^ *pbStack_8;
  *pbStack_8 = *pbStack_8 ^ *pbStack_10;
  *pbStack_4 = *pbStack_4 ^ *pbStack_c;
  *pbStack_c = *pbStack_c ^ *pbStack_4;
  *pbStack_4 = *pbStack_4 ^ *pbStack_c;
  FUN_001dbed0(*pbStack_8,*pbStack_4,uVar3);
  FUN_001dbed0(*pbStack_10,*pbStack_c,cVar2);
  *puRam002679ec = 3;
  puRam002679ec[1] = 3;
  return;
}

