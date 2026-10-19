
void FUN_001dbc70(char *param_1,char *param_2)

{
  char cVar1;
  
  if (*(char *)(iGpffff8afc + 8) < '\x04') {
    *param_1 = '\0';
    cVar1 = *(char *)(iGpffff8afc + 8);
  }
  else {
    *param_1 = '\x01';
    cVar1 = *(char *)(iGpffff8afc + 8) + -4;
  }
  *param_2 = cVar1 + (*(char *)(iGpffff8afc + *param_1 + 0xc) + *(char *)(iGpffff8afc + 9)) * '\x04'
  ;
  return;
}

