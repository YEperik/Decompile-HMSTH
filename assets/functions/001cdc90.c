
undefined4 FUN_001cdc90(char param_1)

{
  undefined4 uVar1;
  
  if (param_1 == '\x18') {
    uVar1 = 0xfe;
  }
  else if ((((param_1 == '\t') || (param_1 == '\b')) || (param_1 == '\a')) || (param_1 == '\x06')) {
    uVar1 = 0xfb;
  }
  else if (((param_1 == '\f') || (param_1 == '\v')) || (param_1 == '\n')) {
    uVar1 = 0xfd;
  }
  else if ((param_1 == '\x05') || (param_1 == '\x04')) {
    uVar1 = 0xfa;
  }
  else if (((param_1 == '\x14') || (param_1 == '\x13')) || (param_1 == '\x12')) {
    uVar1 = 0xfc;
  }
  else {
    uVar1 = 0xff;
  }
  return uVar1;
}

