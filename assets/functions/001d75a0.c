
void FUN_001d75a0(undefined2 param_1,char param_2,char param_3)

{
  undefined8 uVar1;
  undefined1 uStack_10;
  
  uStack_10 = param_2;
  if (param_2 == '\x01') {
    if (param_3 == '\x01') {
      uVar1 = 1;
    }
    else if (param_3 == '\x02') {
      uVar1 = 2;
      uStack_10 = '\0';
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  FUN_00122530(param_1,uVar1);
  FUN_001224c0(param_1,uStack_10);
  return;
}

