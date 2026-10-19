
/* WARNING: Removing unreachable block (ram,0x001d9648) */
/* WARNING: Removing unreachable block (ram,0x001d9574) */
/* WARNING: Removing unreachable block (ram,0x001d94cc) */
/* WARNING: Removing unreachable block (ram,0x001d9530) */
/* WARNING: Removing unreachable block (ram,0x001d95e4) */
/* WARNING: Removing unreachable block (ram,0x001d968c) */

void FUN_001d9460(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  byte bStack_2;
  byte bStack_1;
  
  bStack_1 = FUN_00148df0(0,9);
  uVar3 = FUN_001d93e0((float)(int)*(char *)(iRam002679e8 + 0x17d),
                       (float)*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xc),
                       (float)(*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xd) + 1),
                       (float)*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xe),
                       (float)*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xf));
  uVar4 = FUN_001d93e0((float)(*(char *)(iRam002679e8 + 0x17d) + 1),
                       (float)*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xc),
                       (float)(*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xd) + 1),
                       (float)*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xe),
                       (float)*(byte *)(*(int *)(iRam002679e8 + 0x178) + 0xf));
  uVar1 = FUN_0011d018(uVar3);
  uVar2 = FUN_0011d018(uVar4);
  bStack_2 = FUN_00148df0(uVar1,uVar2);
  if ((ushort)((ushort)bRam002677a4 + (ushort)bRam002677a8 * 10) <
      (ushort)((ushort)bStack_1 + (ushort)bStack_2 * 10)) {
    bRam002677a4 = bStack_1;
    bRam002677a8 = bStack_2;
  }
  FUN_001e0290(bStack_2,bStack_1,&bStack_2,&bStack_1);
  FUN_001547b0(0x833eb8,bStack_2,2,2);
  FUN_001547b0(0x833ec0,bStack_1,1,1);
  return;
}

