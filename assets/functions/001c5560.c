
void FUN_001c5560(byte param_1)

{
  char cVar1;
  char cVar2;
  
  cVar2 = FUN_00123d60(*(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x834058));
  cVar1 = *(char *)((param_1 + 0x1b) * 0x100 + 0x834056);
  if (cVar1 == '\x05') {
    if (cVar2 == '\0') {
      FUN_0013dff0(param_1 + 0x1b,0x140,0,0x140);
      FUN_001c5730(param_1);
    }
  }
  else if (cVar1 == '\x04') {
    FUN_0013e2a0(param_1 + 0x1b);
    if (cVar2 == '\0') {
      FUN_00139920(param_1 + 0x1b,2);
      (&DAT_00266ff8)[param_1] = 2;
    }
  }
  else if (cVar1 == '\x03') {
    if ((*(uint *)((param_1 + 0x1b) * 0x100 + 0x834050) & 0x4000) == 0x4000) {
      FUN_0013e2a0(param_1 + 0x1b);
    }
    if (cVar2 == '\0') {
      FUN_0013dff0(param_1 + 0x1b,0x140,0,0x140);
      FUN_001c5730(param_1);
    }
  }
  else {
    FUN_001c5730(param_1);
  }
  return;
}

