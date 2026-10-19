
void FUN_001b5bd0(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (((cGpffff8844 == '\x0e') && ((bRam00859e10 & 1) == 1)) && ((bRam00859e10 & 4) == 4)) {
    if ((bRam00859e10 & 0x40) == 0x40) {
      uVar3 = 0;
      while ((uVar4 = 0xff, uVar3 < 6 &&
             (uVar4 = uVar3, (*(uint *)(uVar3 * 0x20 + 0x859e60) & 1) == 1))) {
        uVar3 = uVar3 + 1 & 0xff;
      }
      if (uVar4 != 0xff) {
        *(undefined4 *)(uVar4 * 0x20 + 0x859e60) = 0x2801;
        *(undefined1 *)(uVar4 * 0x20 + 0x859e64) = 5;
        iVar1 = uVar4 * 0x10;
        iVar2 = uVar4 * 0x20;
        uVar7 = *(undefined4 *)(&DAT_00244274 + iVar1);
        uVar5 = *(undefined4 *)(&DAT_00244278 + iVar1);
        uVar6 = *(undefined4 *)(&DAT_0024427c + iVar1);
        *(undefined4 *)(iVar2 + 0x859e70) = *(undefined4 *)(&DAT_00244270 + iVar1);
        *(undefined4 *)(iVar2 + 0x859e74) = uVar7;
        *(undefined4 *)(iVar2 + 0x859e78) = uVar5;
        *(undefined4 *)(iVar2 + 0x859e7c) = uVar6;
        *(undefined1 *)(uVar4 * 0x20 + 0x859e69) = 0xe;
        *(undefined1 *)(uVar4 * 0x20 + 0x859e68) = 0;
        *(undefined1 *)(uVar4 * 0x20 + 0x859e65) = 0;
        bRam00859e10 = 0;
      }
    }
    else {
      FUN_001b67f0();
    }
  }
  return;
}

