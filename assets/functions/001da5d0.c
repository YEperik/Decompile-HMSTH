
void FUN_001da5d0(void)

{
  byte bVar1;
  byte bVar2;
  undefined1 *puStack_10;
  undefined1 auStack_c [4];
  undefined1 *puStack_8;
  undefined1 auStack_4 [4];
  
  FUN_001dbc70(puRam002679ec + 2,(int)puRam002679ec + 0xb);
  FUN_001dc230(*(undefined1 *)(puRam002679ec + 2),*(undefined1 *)((int)puRam002679ec + 0xb),
               auStack_c,&puStack_10);
  bVar1 = FUN_001dfbb0(*(undefined1 *)((int)puRam002679ec + *(char *)(puRam002679ec + 2) + 0x12),
                       *puStack_10);
  FUN_001dc230(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5),auStack_4,
               &puStack_8);
  bVar2 = FUN_001dfbb0(*(undefined1 *)
                        ((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0x12),*puStack_8);
  if (bVar1 < 99) {
    if ((uint)bVar2 + (uint)bVar1 < 100) {
      *(byte *)(puRam002679ec + 0x14) = bVar2;
    }
    else {
      *(byte *)(puRam002679ec + 0x14) = 'c' - bVar1;
    }
    *(undefined1 *)((int)puRam002679ec + 0x29) = *(undefined1 *)(puRam002679ec + 0x14);
    *(undefined1 *)((int)puRam002679ec + 0xf) = 0;
    *(bool *)((int)puRam002679ec + 0x2b) = 9 < *(byte *)(puRam002679ec + 0x14);
    puRam002679ec[1] = 7;
    *puRam002679ec = 7;
    FUN_001dbfc0(1,1);
  }
  else {
    FUN_00218ea0(3);
    FUN_001df680();
    FUN_00152f40(0,*(char *)(puRam002679ec + 2) + 3,0,5);
    *puRam002679ec = 8;
    *(undefined1 *)((int)puRam002679ec + 0x51) = 1;
  }
  return;
}

