
/* WARNING: Removing unreachable block (ram,0x001dcd10) */
/* WARNING: Removing unreachable block (ram,0x001dcd18) */
/* WARNING: Removing unreachable block (ram,0x001dce40) */
/* WARNING: Removing unreachable block (ram,0x001dce48) */

void FUN_001dcb80(undefined2 param_1,char param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  char cVar6;
  undefined1 auStack_20 [4];
  undefined1 *puStack_1c;
  undefined1 auStack_18 [4];
  char *pcStack_14;
  undefined2 uStack_10;
  char cStack_8;
  
  uVar2 = (int)*(char *)((int)puGpffff8afc + 5) + 1U & 1;
  uVar3 = ((int)*(char *)((int)puGpffff8afc + uVar2 + 0xc) & 0x3fU) * 4;
  uStack_10 = param_1;
  cStack_8 = param_2;
  FUN_001dc230(*(undefined1 *)((int)puGpffff8afc + 5),*(undefined1 *)(puGpffff8afc + 5),auStack_20,
               &puStack_1c);
  uVar4 = FUN_001df960(*(undefined1 *)((int)puGpffff8afc + uVar2 + 0x12),*puStack_1c);
  uVar4 = uVar4 & 0xff;
  if (uVar4 == 0xff) {
    if (cStack_8 == '\0') {
      *puGpffff8afc = uStack_10;
      puGpffff8afc[1] = uStack_10;
      return;
    }
    FUN_001dc230(*(undefined1 *)(puGpffff8afc + 2),*(undefined1 *)((int)puGpffff8afc + 0xb),
                 auStack_18,&pcStack_14);
    if (*pcStack_14 == -1) {
      uVar4 = (uint)*(byte *)((int)puGpffff8afc + 0xb);
    }
    else {
      uVar4 = FUN_001dfa50(*(undefined1 *)((int)puGpffff8afc + uVar2 + 0x12));
      uVar4 = uVar4 & 0xff;
    }
  }
  cVar6 = (char)uVar2;
  cVar5 = (char)((int)uVar4 >> 2);
  if ((uVar4 < uVar3) || (uVar3 + 0xc <= uVar4)) {
    uVar1 = *(undefined4 *)(puGpffff8afc + uVar2 * 2 + 0xe);
    if (uVar4 + 8 < (uint)*(byte *)((int)puGpffff8afc + uVar2 + 0x10)) {
      *(char *)((int)puGpffff8afc + uVar2 + 0xc) = cVar5;
    }
    else {
      *(char *)((int)puGpffff8afc + uVar2 + 0xc) =
           (char)((int)(*(byte *)((int)puGpffff8afc + uVar2 + 0x10) - 0xc) >> 2);
    }
    *(byte *)(puGpffff8afc + 4) = ((byte)uVar4 & 3) + cVar6 * '\x04';
    *(char *)((int)puGpffff8afc + 9) = cVar5 - *(char *)((int)puGpffff8afc + uVar2 + 0xc);
    *puGpffff8afc = 4;
    puGpffff8afc[1] = uStack_10;
    *(undefined1 *)((int)puGpffff8afc + 7) = 0;
    *(undefined4 *)(puGpffff8afc + uVar2 * 2 + 0xe) = *(undefined4 *)(puGpffff8afc + 0x12);
    *(undefined4 *)(puGpffff8afc + 0x12) = uVar1;
    *(char *)(puGpffff8afc + 0x28) = cVar6;
  }
  else {
    *(byte *)(puGpffff8afc + 4) = ((byte)uVar4 & 3) + cVar6 * '\x04';
    *(char *)((int)puGpffff8afc + 9) = cVar5 - *(char *)((int)puGpffff8afc + uVar2 + 0xc);
    *puGpffff8afc = uStack_10;
    puGpffff8afc[1] = uStack_10;
  }
  *(char *)(puGpffff8afc + 0x15) = cVar6;
  FUN_001dcf30();
  return;
}

