
void FUN_001db270(void)

{
  char cVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  
  bVar4 = *(byte *)(puRam002679ec + 0x28);
  cVar1 = *(char *)((int)puRam002679ec + bVar4 + 0xc);
  cVar2 = *(char *)((int)puRam002679ec + 7);
  iVar5 = *(int *)(puRam002679ec + (uint)bVar4 * 2 + 10);
  cVar3 = *(char *)((int)puRam002679ec + 7);
  iVar6 = *(int *)(puRam002679ec + (uint)bVar4 * 2 + 0xe);
  for (sVar7 = 0; sVar7 < 4; sVar7 = sVar7 + 1) {
    FUN_001dbdf0(*(undefined1 *)(iVar6 + cVar3 * 4 + (int)sVar7),
                 *(undefined1 *)(iVar5 + ((int)cVar1 + (int)cVar2) * 4 + (int)sVar7));
  }
  *(char *)((int)puRam002679ec + 7) = *(char *)((int)puRam002679ec + 7) + '\x01';
  if ('\x02' < *(char *)((int)puRam002679ec + 7)) {
    puVar8 = (undefined1 *)
             (*(int *)(puRam002679ec + (uint)bVar4 * 2 + 10) +
             *(char *)((int)puRam002679ec + bVar4 + 0xc) * 4);
    puVar9 = *(undefined1 **)(puRam002679ec + (uint)bVar4 * 2 + 0xe);
    for (sVar7 = 0; sVar7 < 0xc; sVar7 = sVar7 + 1) {
      FUN_0015ab30(*(undefined1 *)(*(int *)(puRam002679ec + 0x12) + (int)sVar7));
      FUN_001dbed0(*puVar9,*puVar8,((uint)bVar4 * 0xc & 0xff) + (int)sVar7 & 0xff);
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    *puRam002679ec = puRam002679ec[1];
  }
  return;
}

