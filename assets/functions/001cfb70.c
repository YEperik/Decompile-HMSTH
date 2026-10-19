
void FUN_001cfb70(void)

{
  char cVar1;
  char cVar2;
  
  cVar1 = FUN_00136a20();
  cVar2 = FUN_00136d70();
  if (cVar1 == '\0' && cVar2 == '\0') {
    *puGpffff8af8 = 2;
    FUN_001612e0();
  }
  return;
}

