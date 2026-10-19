
void FUN_001cefa0(void)

{
  long lVar1;
  
  lVar1 = FUN_001df5e0();
  if ((lVar1 != 0) && (*puGpffff8af4 = puGpffff8af4[1], *(char *)(puGpffff8af4 + 8) == '\0')) {
    *puGpffff8af4 = 7;
    FUN_00152f40(0,*(byte *)(puGpffff8af4 + 2) + 6,0x220,0);
    FUN_0015bfb0(0x108);
  }
  return;
}

