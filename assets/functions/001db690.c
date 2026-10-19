
void FUN_001db690(void)

{
  byte *pbStack_10;
  undefined1 auStack_c [4];
  char *pcStack_8;
  undefined1 auStack_4 [4];
  
  FUN_001dc230(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5),auStack_c,
               &pbStack_10);
  FUN_001dc230(*(undefined1 *)(puRam002679ec + 2),*(undefined1 *)((int)puRam002679ec + 0xb),
               auStack_4,&pcStack_8);
  if ((*pbStack_10 == 0xff) && (*pcStack_8 == -1)) {
    FUN_00218ea0(3);
  }
  else {
    if (*pbStack_10 == 0xff) {
      *(byte *)(puRam002679ec + 2) =
           *(byte *)(puRam002679ec + 2) ^ *(byte *)((int)puRam002679ec + 5);
      *(byte *)((int)puRam002679ec + 5) =
           *(byte *)((int)puRam002679ec + 5) ^ *(byte *)(puRam002679ec + 2);
      *(byte *)(puRam002679ec + 2) =
           *(byte *)(puRam002679ec + 2) ^ *(byte *)((int)puRam002679ec + 5);
      *(byte *)((int)puRam002679ec + 0xb) =
           *(byte *)((int)puRam002679ec + 0xb) ^ *(byte *)(puRam002679ec + 5);
      *(byte *)(puRam002679ec + 5) =
           *(byte *)(puRam002679ec + 5) ^ *(byte *)((int)puRam002679ec + 0xb);
      *(byte *)((int)puRam002679ec + 0xb) =
           *(byte *)((int)puRam002679ec + 0xb) ^ *(byte *)(puRam002679ec + 5);
      FUN_001dc230(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5),
                   auStack_c,&pbStack_10);
      FUN_001dc230(*(undefined1 *)(puRam002679ec + 2),*(undefined1 *)((int)puRam002679ec + 0xb),
                   auStack_4,&pcStack_8);
    }
    if ((*(char *)((int)puRam002679ec + 5) == '\0') && (0x39 < *pbStack_10)) {
      FUN_00218ea0(3);
      FUN_001dc740(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5));
      FUN_00152f40(0,5,0,5);
      *puRam002679ec = 8;
      *(undefined1 *)((int)puRam002679ec + 0x51) = 1;
    }
    else {
      FUN_00218ea0();
      FUN_001dcb80(6,1);
    }
  }
  return;
}

