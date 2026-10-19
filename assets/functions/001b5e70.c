
void FUN_001b5e70(void)

{
  long lVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  
  for (uVar7 = 0; uVar7 < 5; uVar7 = uVar7 + 1 & 0xff) {
    if ((*(uint *)(uVar7 * 0x20 + 0x859f20) & 0x4000) == 0x4000) {
      uVar5 = 0;
      while ((uVar6 = 0xff, uVar5 < 5 &&
             (uVar6 = uVar5, (*(uint *)(uVar5 * 0x20 + 0x859f20) & 1) == 1))) {
        uVar5 = uVar5 + 1 & 0xff;
      }
      if (uVar6 != 0xff) {
        *(undefined4 *)(uVar6 * 0x20 + 0x859f20) = 0x400801;
        *(undefined1 *)(uVar6 * 0x20 + 0x859f24) = 5;
        iVar2 = uVar6 * 0x10;
        iVar3 = uVar6 * 0x20;
        uVar10 = *(undefined4 *)(&DAT_00244334 + iVar2);
        uVar8 = *(undefined4 *)(&DAT_00244338 + iVar2);
        uVar9 = *(undefined4 *)(&DAT_0024433c + iVar2);
        *(undefined4 *)(iVar3 + 0x859f30) = *(undefined4 *)(&DAT_00244330 + iVar2);
        *(undefined4 *)(iVar3 + 0x859f34) = uVar10;
        *(undefined4 *)(iVar3 + 0x859f38) = uVar8;
        *(undefined4 *)(iVar3 + 0x859f3c) = uVar9;
        *(undefined1 *)(uVar6 * 0x20 + 0x859f29) = 0xd;
        *(undefined1 *)(uVar6 * 0x20 + 0x859f28) = 0;
        *(undefined1 *)(uVar6 * 0x20 + 0x859f25) = 0;
        lVar1 = FUN_00148df0(0,4);
        if (lVar1 != 4) {
          if (lVar1 == 3) {
            puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar4 = *puVar4 | 0x40000;
          }
          else if (lVar1 == 2) {
            puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar4 = *puVar4 | 0x20000;
          }
          else if (lVar1 == 1) {
            puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar4 = *puVar4 | 0x10000;
          }
          else if (lVar1 == 0) {
            puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
            *puVar4 = *puVar4 | 0x8000;
          }
        }
        puVar4 = (uint *)(uVar7 * 0x20 + 0x859f20);
        *puVar4 = *puVar4 & 0xffffbfff;
        puVar4 = (uint *)(uVar7 * 0x20 + 0x859f20);
        *puVar4 = *puVar4 & 0xffffdfff;
      }
    }
  }
  return;
}

