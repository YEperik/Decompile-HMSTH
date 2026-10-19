
char FUN_001cdf00(void)

{
  char cVar1;
  char cVar2;
  short sVar3;
  
  if (*(char *)(iGpffff8af4 + 7) < '\x02') {
    cVar2 = -1;
  }
  else {
    cVar2 = *(char *)(iGpffff8af4 + 8);
    for (sVar3 = 0; (long)sVar3 < (long)*(char *)(iGpffff8af4 + 7); sVar3 = sVar3 + 1) {
      cVar1 = FUN_001cdc90(*(undefined1 *)(iGpffff8af4 + sVar3 + 8));
      if (cVar1 != -3) {
        return -1;
      }
      if (cVar2 != *(char *)(iGpffff8af4 + sVar3 + 8)) {
        return ')';
      }
    }
    if (*(char *)(iGpffff8af4 + 7) < '\x03') {
      cVar2 = -1;
    }
    else {
      cVar2 = cVar2 + '\x1c';
    }
  }
  return cVar2;
}

