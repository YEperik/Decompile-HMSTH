
void FUN_001d40e0(void)

{
  undefined1 uVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  short *psVar5;
  undefined1 uStack_1;
  
  iVar4 = (uint)*(byte *)(iRam002679e8 + 0x17f) * 8;
  psVar5 = (short *)(&DAT_002447d0 + iVar4);
  switch(*(undefined1 *)(iRam002679e8 + 0x17f)) {
  case 0:
    FUN_001d53f0(iRam002679e8 + 0x160);
    FUN_001d48a0(psVar5);
    break;
  case 1:
    FUN_001d54d0(iRam002679e8 + 0x160,iRam002679e8 + 0x90,iRam002679e8 + 0x150);
    FUN_001d4730(psVar5);
    FUN_001d9810(*(undefined1 *)(*(int *)(iRam002679e8 + 0x178) + 2),
                 *(undefined2 *)(iRam002679e8 + 0x180));
    break;
  case 2:
    FUN_001d75a0(0x32e);
    if (*(char *)(iRam002679e8 + 0x1b3) == '\0') {
      FUN_001d54d0(iRam002679e8 + 0x160,iRam002679e8 + 0x90,iRam002679e8 + 0x150);
      FUN_001d48a0(psVar5);
      if (*(char *)(iRam002679e8 + 0x17c) < '\x03') {
        *(float *)(iRam002679e8 + 0x170) = (float)(int)*psVar5;
      }
    }
    else {
      FUN_001d48a0(psVar5);
      *(undefined4 *)(iRam002679e8 + 0x150) = *(undefined4 *)(iRam002679e8 + 0x90);
      *(undefined4 *)(iRam002679e8 + 0x158) = *(undefined4 *)(iRam002679e8 + 0x98);
      *(undefined4 *)(iRam002679e8 + 0x170) = 0;
    }
    break;
  case 3:
    FUN_001d54d0(iRam002679e8 + 0x160,iRam002679e8 + 0x90,iRam002679e8 + 0x150);
    FUN_001d46e0(psVar5);
    FUN_001d48a0(psVar5);
    break;
  case 4:
    FUN_001d54d0(iRam002679e8 + 0x160,iRam002679e8 + 0x90,iRam002679e8 + 0x150);
    break;
  case 5:
    FUN_001d75a0(0x32e,1,2);
    uVar3 = FUN_00148df0((int)*(short *)(&DAT_002447d4 + iVar4) +
                         (*(char *)(iRam002679e8 + 0x17d) + 1) * -2,
                         (int)*(short *)(&DAT_002447d6 + iVar4) +
                         (*(char *)(iRam002679e8 + 0x17d) + 1) * -2);
    *(undefined2 *)(iRam002679e8 + 0x180) = uVar3;
    uVar1 = FUN_001d49c0(1,&uStack_1);
    *(undefined1 *)(iRam002679e8 + 0x184) = uVar1;
    FUN_001d4520(psVar5,uStack_1);
    *(undefined1 *)(iRam002679e8 + 0x1b8) = 0;
    *(undefined1 *)(iRam002679e8 + 0x1b9) = 2;
    break;
  case 6:
    *(undefined1 *)(iRam002679e8 + 0x184) = 3;
    uVar1 = FUN_001d49c0(0,&uStack_1);
    *(undefined1 *)(iRam002679e8 + 0x184) = uVar1;
    FUN_001d48a0(psVar5);
    sVar2 = *(short *)(iRam002679e8 + 0x180) << 1;
    *(short *)(iRam002679e8 + 0x182) = sVar2;
    *(short *)(iRam002679e8 + 0x180) = sVar2;
    FUN_001d4520(psVar5,uStack_1);
    FUN_00218ea0(0x25);
    FUN_001ff4f0(*(undefined4 *)(iRam002679e8 + 0x150),*(undefined4 *)(iRam002679e8 + 0x154),
                 *(undefined4 *)(iRam002679e8 + 0x158),0xb);
    FUN_001d9810(*(char *)(*(int *)(iRam002679e8 + 0x178) + 2) + '\x03',0x3c);
    break;
  case 7:
    FUN_001d7db0();
    FUN_001d54d0(iRam002679e8 + 0x160,iRam002679e8 + 0xa0,iRam002679e8 + 0x150);
    FUN_001d75a0(0x32e);
    FUN_001d46e0(psVar5);
    FUN_001d48a0(psVar5);
    FUN_001d9810(*(char *)(*(int *)(iRam002679e8 + 0x178) + 2) + '\x03',0x3c);
  }
  return;
}

