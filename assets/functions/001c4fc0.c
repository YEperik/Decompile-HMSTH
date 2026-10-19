
void FUN_001c4fc0(byte param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  uint *puVar4;
  
  cVar1 = *(char *)((param_1 + 0x1b) * 0x100 + 0x8340f0);
  FUN_0013e1b0(param_1 + 0x1b,0xff);
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x4000) == 0x4000) {
    (&gp0xffff8108)[param_1] = 1;
    FUN_0013e2a0(param_1 + 0x1b);
    if (*(char *)((param_1 + 0x1b) * 0x100 + 0x834056) == '\b') {
      FUN_00139920(param_1 + 0x1b,9);
      (&gp0xffff8108)[param_1] = 0;
    }
    else {
      FUN_00139920(param_1 + 0x1b,8);
      *(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x834098) = 200;
    }
    if (((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 2) != 2) &&
       ((0x13 < bRam0085a2f5 || (bRam0085a2f5 < 6)))) {
      (&gp0xffff8108)[param_1] = 2;
      FUN_00139920(param_1 + 0x1b,10);
      FUN_0013e2a0(param_1 + 0x1b);
      puVar4 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
      *puVar4 = *puVar4 | 0x100;
    }
  }
  else {
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x1000) != 0x1000) {
      iVar3 = FUN_00148df0(0,0x26d6);
      switch(iVar3 % 6) {
      case 0:
        FUN_0013e1b0(param_1 + 0x1b,0xff);
        break;
      case 1:
        if (cVar1 != '\x04') {
          FUN_0013e1b0(param_1 + 0x1b,4);
        }
        break;
      case 2:
        if (cVar1 != '\x05') {
          FUN_0013e1b0(param_1 + 0x1b,5);
        }
        break;
      case 3:
      case 4:
        if (cVar1 != '\x06') {
          FUN_0013e1b0(param_1 + 0x1b,6);
        }
        break;
      case 5:
        if (cVar1 != '\a') {
          FUN_0013e1b0(param_1 + 0x1b,7);
        }
      }
    }
    if (((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 2) != 2) &&
       ((0x13 < bRam0085a2f5 || (bRam0085a2f5 < 6)))) {
      if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 0x200) == 0x200) {
        iVar3 = (param_1 + 0x1b) * 0x100;
        sVar2 = *(short *)(iVar3 + 0x8340a2);
        *(short *)(iVar3 + 0x8340a2) = sVar2 + 1;
        if (300 < (ushort)(sVar2 + 1U)) {
          FUN_0013e2a0(param_1 + 0x1b);
          puVar4 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
          *puVar4 = *puVar4 & 0xfffffdff;
          *(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x8340a2) = 0;
          (&gp0xffff8108)[param_1] = 2;
          FUN_00139920(param_1 + 0x1b,7);
        }
      }
      else if ((*(uint *)((uint)param_1 * 0x20 + 0x859e60) & 1) == 1) {
        (&gp0xffff8108)[param_1] = 2;
        FUN_00139920(param_1 + 0x1b,7);
        FUN_0013e2a0(param_1 + 0x1b);
        puVar4 = (uint *)((uint)param_1 * 0x20 + 0x859e60);
        *puVar4 = *puVar4 | 0x100;
      }
    }
  }
  return;
}

