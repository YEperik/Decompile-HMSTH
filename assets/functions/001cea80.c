
void FUN_001cea80(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  long lVar4;
  
  lVar4 = FUN_0012e170(0,0x800);
  if (lVar4 == 0) {
    lVar4 = FUN_0012e170(0,0x20);
    if (lVar4 == 0) {
      if ((*(char *)((int)puGpffff8af4 + 5) != -1) && (*(char *)((int)puGpffff8af4 + 7) < '\x03')) {
        lVar4 = FUN_0012e170(0,0x100);
        if (lVar4 == 0) {
          lVar4 = FUN_0012e170(0,4);
          if ((((lVar4 == 0) && (lVar4 = FUN_0012e170(0,0x8000), lVar4 == 0)) &&
              (lVar4 = FUN_0012e170(0,0x40000), lVar4 == 0)) &&
             ((lVar4 = FUN_0012e210(0,0x8000), lVar4 == 0 &&
              (lVar4 = FUN_0012e210(0,0x40000), lVar4 == 0)))) {
            lVar4 = FUN_0012e170(0,8);
            if ((((lVar4 == 0) &&
                 ((lVar4 = FUN_0012e170(0,0x2000), lVar4 == 0 &&
                  (lVar4 = FUN_0012e170(0,0x80000), lVar4 == 0)))) &&
                (lVar4 = FUN_0012e210(0,0x2000), lVar4 == 0)) &&
               (lVar4 = FUN_0012e210(0,0x80000), lVar4 == 0)) {
              lVar4 = FUN_0012e170(0,0x40);
              if (lVar4 != 0) {
                FUN_00218ea0(0x20);
                FUN_001cdc10(*(undefined1 *)((int)puGpffff8af4 + 5));
                FUN_00139920(0,7);
                FUN_001cd3f0(0x41f00000,*(char *)(puGpffff8af4 + 2) + '\x01');
                *puGpffff8af4 = 2;
                puGpffff8af4[1] = 3;
              }
            }
            else {
              cVar1 = FUN_001cd4b0();
              if (cVar1 != *(char *)((int)puGpffff8af4 + 5)) {
                FUN_00218ea0(2);
              }
              uVar2 = FUN_001cd4b0();
              *(undefined1 *)((int)puGpffff8af4 + 5) = uVar2;
              FUN_001cd9b0(*(undefined1 *)((int)puGpffff8af4 + 5));
            }
          }
          else {
            cVar1 = FUN_001cd5e0();
            if (cVar1 != *(char *)((int)puGpffff8af4 + 5)) {
              FUN_00218ea0(2);
            }
            uVar2 = FUN_001cd5e0();
            *(undefined1 *)((int)puGpffff8af4 + 5) = uVar2;
            FUN_001cd9b0(*(undefined1 *)((int)puGpffff8af4 + 5));
          }
        }
        else {
          iVar3 = FUN_001df900();
          cVar1 = FUN_001df760(*(undefined1 *)(iVar3 + (uint)*(byte *)((int)puGpffff8af4 + 5)));
          if (cVar1 != -1) {
            FUN_00218ea0();
            FUN_00152f40(0,cVar1,0x220,0);
            puGpffff8af4[1] = *puGpffff8af4;
            *puGpffff8af4 = 6;
          }
        }
      }
    }
    else {
      FUN_00218ea0(1);
      FUN_001cd820();
      *puGpffff8af4 = 0xc;
    }
  }
  else if (*(char *)((int)puGpffff8af4 + 7) != '\0') {
    FUN_00123950(1,(uint)*(byte *)(puGpffff8af4 + 2) * 2 + 0x16);
    *puGpffff8af4 = 8;
    if ((*(char *)(puGpffff8af4 + 2) == '\0') || (*(char *)(puGpffff8af4 + 2) == '\x01')) {
      FUN_00218ea0(99);
    }
    puGpffff8af4[7] = 0;
    FUN_0015bfb0(0x10f);
    FUN_0015ab30(*(char *)(puGpffff8af4 + 3) + 1U & 1);
    FUN_001532e0();
  }
  return;
}

