
void FUN_001d9fb0(void)

{
  undefined1 *puVar1;
  ushort uVar2;
  
  for (uVar2 = 0; (short)uVar2 < 0xc; uVar2 = uVar2 + 1) {
    puVar1 = (undefined1 *)FUN_001dbd60(0,(char)uVar2);
    FUN_001dbda0(*(undefined1 *)(*(int *)(iGpffff8afc + 0x1c) + (int)(short)uVar2),*puVar1,
                 uVar2 & 0xff);
    puVar1 = (undefined1 *)FUN_001dbd60(1,(char)uVar2);
    FUN_001dbda0(*(undefined1 *)(*(int *)(iGpffff8afc + 0x20) + (int)(short)uVar2),*puVar1,
                 (int)(short)uVar2 + 0xcU & 0xff);
  }
  return;
}

