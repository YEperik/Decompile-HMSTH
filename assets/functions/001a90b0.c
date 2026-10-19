
void FUN_001a90b0(byte param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  for (uVar1 = 0; uVar3 = uVar2, uVar1 < 6; uVar1 = uVar1 + 1 & 0xff) {
    if ((((*(uint *)(uVar1 * 0x20 + 0x859e60) & 1) == 1) &&
        ((*(uint *)(uVar1 * 0x20 + 0x859e60) & 0x800) != 0x800)) &&
       ((*(uint *)(uVar1 * 0x20 + 0x859e60) & 2) != 2)) {
      uVar3 = uVar1;
      if (uVar2 == param_1) break;
      uVar2 = uVar2 + 1 & 0xff;
    }
  }
  FUN_00218ea0(0x6b);
  FUN_0016ce30(300);
  *(undefined4 *)(uVar3 * 0x20 + 0x859e60) = 0;
  *(undefined1 *)(uVar3 * 0x20 + 0x859e68) = 0;
  FUN_00116978(uVar3 * 8 + 0x85a310,0xff,8);
  FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,uRam00267864);
  return;
}

