
undefined4 FUN_001d7470(char param_1)

{
  undefined4 uVar1;
  
  if (param_1 == '\x03') {
    if (*(char *)(iRam002679e8 + 0x13) < '@') {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else if (param_1 == '\x02') {
    if (*(char *)(iRam002679e8 + 0x12) < '@') {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else if (param_1 == '\x01') {
    if (*(char *)(iRam002679e8 + 0x13) < -0x3f) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else if (param_1 == '\0') {
    if (*(char *)(iRam002679e8 + 0x12) < -0x3f) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

