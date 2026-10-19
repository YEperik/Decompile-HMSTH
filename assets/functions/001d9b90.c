
void FUN_001d9b90(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  short sVar3;
  
  FUN_001df470();
  FUN_00161310();
  FUN_00126650();
  FUN_001266a0();
  FUN_001de930(0,0x24);
  FUN_001dfe60();
  puGpffff8afc = *(undefined2 **)(iGpffff8148 + 0xc);
  *puGpffff8afc = 1;
  puGpffff8afc[1] = 0;
  *(undefined1 *)(puGpffff8afc + 0x15) = 0;
  *(undefined1 *)(puGpffff8afc + 2) = 0;
  *(undefined1 *)((int)puGpffff8afc + 5) = 0;
  *(undefined1 *)(puGpffff8afc + 3) = 0;
  *(undefined1 *)((int)puGpffff8afc + 7) = 0;
  *(undefined1 *)(puGpffff8afc + 4) = 0;
  *(undefined1 *)((int)puGpffff8afc + 9) = 0;
  *(undefined1 *)(puGpffff8afc + 5) = 0;
  *(undefined1 *)((int)puGpffff8afc + 0xb) = 0;
  *(undefined1 *)(puGpffff8afc + 6) = 0;
  *(undefined1 *)((int)puGpffff8afc + 0xd) = 0;
  *(undefined1 *)(puGpffff8afc + 7) = 0;
  *(undefined1 *)((int)puGpffff8afc + 0xf) = 0;
  uVar1 = FUN_001df930();
  *(undefined1 *)(puGpffff8afc + 8) = uVar1;
  uVar1 = FUN_001df930(3);
  *(undefined1 *)((int)puGpffff8afc + 0x11) = uVar1;
  *(undefined1 *)(puGpffff8afc + 9) = 0;
  *(undefined1 *)((int)puGpffff8afc + 0x13) = 3;
  uVar2 = FUN_001df900();
  *(undefined4 *)(puGpffff8afc + 10) = uVar2;
  uVar2 = FUN_001df900(3);
  *(undefined4 *)(puGpffff8afc + 0xc) = uVar2;
  *(undefined2 **)(puGpffff8afc + 0xe) = puGpffff8afc + 0x16;
  *(undefined2 **)(puGpffff8afc + 0x10) = puGpffff8afc + 0x1c;
  *(undefined2 **)(puGpffff8afc + 0x12) = puGpffff8afc + 0x22;
  *(undefined1 *)(puGpffff8afc + 0x14) = 0;
  for (sVar3 = 0; sVar3 < 0x24; sVar3 = sVar3 + 1) {
    *(char *)((int)puGpffff8afc + sVar3 + 0x2c) = (char)sVar3;
  }
  FUN_0015e770(5);
  return;
}

