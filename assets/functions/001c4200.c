
void FUN_001c4200(byte param_1)

{
  char cVar1;
  uint *puVar2;
  
  cVar1 = FUN_00123d60(*(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834058));
  switch(*(undefined1 *)((param_1 + 0x12) * 0x100 + 0x834056)) {
  case 3:
  case 4:
  case 5:
  case 6:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    if ((*(uint *)((param_1 + 0x12) * 0x100 + 0x834050) & 0x4000) == 0x4000) {
      FUN_0013e2a0(param_1 + 0x12);
    }
    if (cVar1 == '\0') {
      FUN_0013dff0(param_1 + 0x12,0x140,0,0x140);
      FUN_001c4590(param_1);
    }
    break;
  default:
    FUN_001c4590(param_1);
    break;
  case 0x11:
    FUN_0013e2a0(param_1 + 0x12);
    if (cVar1 == '\0') {
      puVar2 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
      *puVar2 = *puVar2 | 0x800000;
      if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x100) == 0x100) {
        FUN_00139920(param_1 + 0x12,0x14);
      }
      else {
        FUN_00139920(param_1 + 0x12,0x12);
      }
      *(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834098) = 0xb4;
      (&DAT_00267000)[param_1] = 1;
    }
    break;
  case 0x13:
    if (cVar1 == '\0') {
      puVar2 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
      *puVar2 = *puVar2 & 0xff7fffff;
      FUN_0013dff0(param_1 + 0x12,0x140,0,0x140);
      FUN_001c4590(param_1);
    }
    break;
  case 0x14:
    FUN_0013e2a0(param_1 + 0x12);
    if (cVar1 == '\0') {
      FUN_00139920(param_1 + 0x12,0x15);
      (&DAT_00267000)[param_1] = 2;
    }
    break;
  case 0x17:
    if (cVar1 == '\0') {
      FUN_001c4590(param_1);
    }
    break;
  case 0x18:
    FUN_0013e2a0(param_1 + 0x12);
    if (cVar1 == '\0') {
      FUN_00139920(param_1 + 0x12,7);
      *(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834098) = 0xf0;
      (&DAT_00267000)[param_1] = 1;
    }
  }
  return;
}

