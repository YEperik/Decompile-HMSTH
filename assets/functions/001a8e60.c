
void FUN_001a8e60(byte param_1)

{
  undefined8 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  for (uVar2 = 0; uVar4 = uVar3, uVar2 < 5; uVar2 = uVar2 + 1 & 0xff) {
    if (((((*(uint *)(uVar2 * 0x20 + 0x859f20) & 1) == 1) &&
         ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x800) != 0x800)) &&
        ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x1000) != 0x1000)) &&
       ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 2) != 2)) {
      uVar4 = uVar2;
      if (uVar3 == param_1) break;
      uVar3 = uVar3 + 1 & 0xff;
    }
  }
  if (*(byte *)(uVar4 * 0x20 + 0x859f28) < 100) {
    uVar1 = 3000;
  }
  else if (*(byte *)(uVar4 * 0x20 + 0x859f28) < 200) {
    uVar1 = 4000;
  }
  else {
    uVar1 = 5000;
  }
  FUN_00218ea0(0x6b);
  FUN_0016ce30(uVar1);
  *(undefined4 *)(uVar4 * 0x20 + 0x859f20) = 0;
  *(undefined1 *)(uVar4 * 0x20 + 0x859f28) = 0;
  FUN_00116978(uVar4 * 8 + 0x85a310,0xff,8);
  FUN_001cceb0(0xc38a0000,0x42200000,0x47c34f80,0x114,0xd46,0x333,uGpffff8974);
  return;
}

