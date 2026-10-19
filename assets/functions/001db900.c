
void FUN_001db900(void)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined1 *puStack_10;
  char *pcStack_c;
  char *pcStack_8;
  undefined1 *puStack_4;
  
  cVar2 = FUN_001dc230(*(undefined1 *)((int)puGpffff8afc + 5),*(undefined1 *)(puGpffff8afc + 5),
                       &puStack_10,&pcStack_c);
  pcVar4 = (char *)FUN_001dfb10(*(undefined1 *)
                                 ((int)puGpffff8afc + *(char *)((int)puGpffff8afc + 5) + 0x12),
                                *pcStack_c);
  FUN_001dc230(*(undefined1 *)(puGpffff8afc + 2),*(undefined1 *)((int)puGpffff8afc + 0xb),&puStack_4
               ,&pcStack_8);
  pcVar5 = (char *)FUN_001dfb10(*(undefined1 *)
                                 ((int)puGpffff8afc + *(char *)(puGpffff8afc + 2) + 0x12),*pcStack_c
                               );
  cVar1 = *pcStack_8;
  if (cVar1 == -1) {
    *pcVar5 = '\0';
  }
  *pcVar4 = *pcVar4 - *(char *)((int)puGpffff8afc + 0x29);
  *pcVar5 = *pcVar5 + *(char *)((int)puGpffff8afc + 0x29);
  *pcStack_8 = *pcStack_c;
  if (*pcVar4 == '\0') {
    *pcStack_c = -1;
  }
  if (cVar2 != -1) {
    FUN_001dbed0(*puStack_10,*pcStack_c,cVar2);
  }
  uVar3 = FUN_001dc230(*(undefined1 *)(puGpffff8afc + 2),*(undefined1 *)((int)puGpffff8afc + 0xb),
                       &puStack_4,&pcStack_8);
  if (cVar1 == -1) {
    FUN_001dbda0(*puStack_4,*pcStack_8,uVar3);
  }
  *puGpffff8afc = 3;
  puGpffff8afc[1] = 3;
  return;
}

