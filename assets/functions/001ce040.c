
undefined4 FUN_001ce040(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = *(char *)(iRam002679e4 + 4);
  if (cVar1 == '\x02') {
    if ((((*(char *)(iRam002679e4 + 7) < '\x02') || (*param_1 != -4)) || (param_1[1] != '\x10')) ||
       ((param_1[2] != -1 ||
        (((*(char *)(iRam002679e4 + 8) != '\x14' && (*(char *)(iRam002679e4 + 9) != '\x14')) &&
         (*(char *)(iRam002679e4 + 10) != '\x14')))))) {
      uVar2 = 0xff;
    }
    else {
      uVar2 = 0x33;
    }
  }
  else if (cVar1 == '\0') {
    if (((*(char *)(iRam002679e4 + 7) == '\x03') && (*param_1 == -5)) &&
       (((param_1[1] == -4 && (param_1[2] == '\x10')) &&
        (((*(char *)(iRam002679e4 + 8) == '\x14' || (*(char *)(iRam002679e4 + 9) == '\x14')) ||
         (*(char *)(iRam002679e4 + 10) == '\x14')))))) {
      uVar2 = 0x32;
    }
    else {
      uVar2 = 0xff;
    }
  }
  else if (cVar1 == '\x01') {
    uVar2 = 0xff;
  }
  else {
    uVar2 = 0xff;
  }
  return uVar2;
}

