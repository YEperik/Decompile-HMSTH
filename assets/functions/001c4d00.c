
void FUN_001c4d00(byte param_1)

{
  char cVar1;
  char cVar2;
  uint *puVar3;
  
  cVar2 = FUN_00123d60(*(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x834058));
  cVar1 = *(char *)((param_1 + 0x1b) * 0x100 + 0x834056);
  if (cVar1 == '\t') {
    if (cVar2 == '\0') {
      puVar3 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
      *puVar3 = *puVar3 & 0xffffbfff;
      FUN_0013dff0(param_1 + 0x1b,0x140,0,0x140);
      FUN_001c4fc0(param_1);
    }
  }
  else if (cVar1 == '\a') {
    FUN_0013e2a0(param_1 + 0x1b);
    if (cVar2 == '\0') {
      puVar3 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
      *puVar3 = *puVar3 | 0x4000;
      if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x100) == 0x100) {
        FUN_00139920(param_1 + 0x1b,10);
        (&gp0xffff8108)[param_1] = 2;
      }
      else {
        FUN_00139920(param_1 + 0x1b,8);
        *(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x834098) = 200;
        (&gp0xffff8108)[param_1] = 1;
      }
    }
  }
  else if (((cVar1 == '\x06') || (cVar1 == '\x05')) || (cVar1 == '\x04')) {
    if ((*(uint *)((param_1 + 0x1b) * 0x100 + 0x834050) & 0x4000) == 0x4000) {
      FUN_0013e2a0(param_1 + 0x1b);
    }
    if (cVar2 == '\0') {
      FUN_0013dff0(param_1 + 0x1b,0x140,0,0x140);
      FUN_001c4fc0(param_1);
    }
  }
  else {
    FUN_001c4fc0(param_1);
  }
  return;
}

