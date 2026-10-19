
void FUN_001cef30(void)

{
  char cVar1;
  
  cVar1 = FUN_00137df0();
  if (cVar1 == '\0') {
    if (*(char *)((int)puGpffff8af4 + 0x11) == '\0') {
      *(undefined1 *)((int)puGpffff8af4 + 0x11) = 1;
      puGpffff8af4[1] = 0;
    }
    else {
      *puGpffff8af4 = puGpffff8af4[1];
    }
  }
  return;
}

