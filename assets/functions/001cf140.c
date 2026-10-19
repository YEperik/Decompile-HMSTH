
void FUN_001cf140(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  long lVar4;
  
  lVar4 = FUN_00123d60(1);
  if (lVar4 == 0) {
    FUN_00139b60();
    FUN_00139a20();
    FUN_0013c060();
    FUN_0014c0c0();
    iVar3 = FUN_001df900();
    uVar2 = *(undefined1 *)(iVar3 + (uint)*(byte *)((int)puRam002679e4 + 5));
    *(undefined1 *)((int)puRam002679e4 + *(char *)((int)puRam002679e4 + 7) + 8) = uVar2;
    uRam00267840 = 0xff;
    uRam00834050 = uRam00834050 & 0xfffffbff;
    uRam00834054 = 0xff;
    uRam00836750 = uRam00836750 & 0xffffefff;
    FUN_00139920();
    FUN_001cd720(*(undefined1 *)((int)puRam002679e4 + 5));
    if (((*(char *)((int)puRam002679e4 + 7) < '\x03') && (*(char *)((int)puRam002679e4 + 5) != -1))
       && (cVar1 = FUN_001dfbb0(0,uVar2), cVar1 == '\0')) {
      uVar2 = FUN_001cd4b0();
      *(undefined1 *)((int)puRam002679e4 + 5) = uVar2;
    }
    *puRam002679e4 = 1;
    if (*(char *)((int)puRam002679e4 + 7) < '\x03') {
      if (*(char *)((int)puRam002679e4 + 5) == -1) {
        FUN_00152f40(0,9,0x20,0);
        *puRam002679e4 = 6;
        puRam002679e4[1] = 1;
      }
      else {
        FUN_0015bf20(0x10f);
        FUN_001cd9b0(*(undefined1 *)((int)puRam002679e4 + 5));
      }
    }
  }
  return;
}

