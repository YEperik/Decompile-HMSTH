
undefined4 FUN_001c24b0(void)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 uVar4;
  undefined1 auStack_10 [16];
  
  uVar4 = 0;
  uVar1 = FUN_0013a880(0x42800000,0,auStack_10);
  uVar1 = uVar1 & 0xff;
  uVar2 = uVar1 - 0x12 & 0xff;
  if (((((0x11 < uVar1) && (uVar1 < 0x17)) && ((&DAT_00267000)[uVar2] != '\x05')) &&
      (((&DAT_00267000)[uVar2] != '\x06' && ((&DAT_00267000)[uVar2] != '\a')))) &&
     ((&DAT_00267000)[uVar2] != '\r')) {
    if (bRam002679a8 < 0x1f) {
      bRam002679a8 = bRam002679a8 + 1;
    }
    else {
      uVar4 = 1;
      if ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x100) == 0x100) {
        if ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x200) != 0x200) {
          FUN_001b7f40(3,6,uVar2);
          if (((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x800) == 0x800) ||
             ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x1000) == 0x1000)) {
            FUN_001ff4f0(0,0x43000000,0,0x18,0,*(undefined2 *)((uVar2 + 0x12) * 0x100 + 0x834058));
          }
          else {
            FUN_001ff4f0(0,0x43200000,0,0x18,0,*(undefined2 *)((uVar2 + 0x12) * 0x100 + 0x834058));
          }
          puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
          *puVar3 = *puVar3 & 0xfffffffb;
          puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
          *puVar3 = *puVar3 | 8;
          puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
          *puVar3 = *puVar3 | 0x80;
        }
        *(undefined2 *)((uVar2 + 0x12) * 0x100 + 0x8340a2) = 0;
        puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
        *puVar3 = *puVar3 | 0x200;
      }
      puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
      *puVar3 = *puVar3 | 0x100000;
      puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
      *puVar3 = *puVar3 & 0xff7fffff;
      if (((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x80000) == 0x80000) ||
         ((*(uint *)(uVar2 * 0x20 + 0x859f20) & 0x200000) == 0x200000)) {
        FUN_0013e2a0(uVar1);
        puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
        *puVar3 = *puVar3 & 0xfff7ffff;
        puVar3 = (uint *)(uVar2 * 0x20 + 0x859f20);
        *puVar3 = *puVar3 & 0xffdfffff;
      }
      if ((*(uint *)(uVar1 * 0x100 + 0x834050) & 0x4000) == 0x4000) {
        FUN_0013e2a0(uVar1);
      }
      if ((*(uint *)(uVar1 * 0x100 + 0x834050) & 4) == 4) {
        FUN_00137b90(uVar1,auStack_10);
        *(undefined2 *)(uVar1 * 0x100 + 0x834098) = 0x40;
        *(undefined4 *)(uVar1 * 0x100 + 0x834090) = 0x40000000;
        (&DAT_00267000)[uVar2] = 0;
      }
      else {
        FUN_00137b90(uVar1,auStack_10);
        FUN_00138360(uVar1,0x40);
        (&DAT_00267000)[uVar2] = 0;
      }
    }
    if ((&DAT_00267000)[uVar2] == '\t') {
      (&DAT_00267000)[uVar2] = 0;
    }
  }
  return uVar4;
}

