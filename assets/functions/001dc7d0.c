
void FUN_001dc7d0(void)

{
  undefined4 uVar1;
  ulong uVar2;
  byte bVar3;
  undefined1 auStack_8 [4];
  undefined1 auStack_4 [4];
  
  uVar2 = (long)((int)*(char *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0xc) << 2)
          & 0xff;
  FUN_001dc230(*(undefined1 *)((int)puRam002679ec + 5),*(undefined1 *)(puRam002679ec + 5),auStack_8,
               auStack_4);
  if (((long)*(char *)(puRam002679ec + 5) < (long)uVar2) ||
     ((long)((int)uVar2 + 0xc) <= (long)*(char *)(puRam002679ec + 5))) {
    uVar1 = *(undefined4 *)(puRam002679ec + *(char *)((int)puRam002679ec + 5) * 2 + 0xe);
    if (*(char *)(puRam002679ec + 5) + 8 <
        (int)(uint)*(byte *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0x10)) {
      *(char *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0xc) =
           *(char *)(puRam002679ec + 5) >> 2;
    }
    else {
      *(char *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0xc) =
           (char)((int)(*(byte *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0x10) -
                       0xc) >> 2);
    }
    bVar3 = *(byte *)(puRam002679ec + 5) & 3;
    if (((char)*(byte *)(puRam002679ec + 5) < '\0') && (bVar3 != 0)) {
      bVar3 = bVar3 - 4;
    }
    *(byte *)(puRam002679ec + 4) = bVar3 + *(char *)((int)puRam002679ec + 5) * '\x04';
    *(char *)((int)puRam002679ec + 9) =
         (*(char *)(puRam002679ec + 5) >> 2) -
         *(char *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0xc);
    *puRam002679ec = 4;
    puRam002679ec[1] = 3;
    *(undefined1 *)((int)puRam002679ec + 7) = 0;
    *(undefined4 *)(puRam002679ec + *(char *)((int)puRam002679ec + 5) * 2 + 0xe) =
         *(undefined4 *)(puRam002679ec + 0x12);
    *(undefined4 *)(puRam002679ec + 0x12) = uVar1;
    *(undefined1 *)(puRam002679ec + 0x28) = *(undefined1 *)((int)puRam002679ec + 5);
  }
  else {
    bVar3 = *(byte *)(puRam002679ec + 5) & 3;
    if (((char)*(byte *)(puRam002679ec + 5) < '\0') && (bVar3 != 0)) {
      bVar3 = bVar3 - 4;
    }
    *(byte *)(puRam002679ec + 4) = bVar3 + *(char *)((int)puRam002679ec + 5) * '\x04';
    *(char *)((int)puRam002679ec + 9) =
         (*(char *)(puRam002679ec + 5) >> 2) -
         *(char *)((int)puRam002679ec + *(char *)((int)puRam002679ec + 5) + 0xc);
    *puRam002679ec = 3;
    puRam002679ec[1] = 3;
  }
  *(undefined1 *)(puRam002679ec + 0x15) = *(undefined1 *)((int)puRam002679ec + 5);
  FUN_001dcf30();
  FUN_001dc4d0();
  return;
}

