
void FUN_001c4590(byte param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  uint *puVar6;
  
  cVar1 = *(char *)((param_1 + 0x12) * 0x100 + 0x8340f0);
  FUN_0013e1b0(param_1 + 0x12,0xff);
  if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x800000) != 0x800000) {
    iVar3 = FUN_00148df0(0,0x26d9);
    switch(iVar3 % 9) {
    case 0:
      FUN_0013e1b0(param_1 + 0x12,0xff);
      break;
    case 1:
      if ((((cVar1 != '\x03') && (cVar1 != '\x04')) && (cVar1 != '\x05')) && (cVar1 != '\x06')) {
        uVar4 = FUN_00148df0(0,0x80);
        FUN_0013e1b0(param_1 + 0x12,(uVar4 & 3) + 3);
      }
      break;
    case 3:
      if (cVar1 != '\b') {
        FUN_0013e1b0(param_1 + 0x12,8);
      }
      break;
    case 4:
      if (cVar1 != '\t') {
        FUN_0013e1b0(param_1 + 0x12,9);
      }
      break;
    case 5:
      if ((cVar1 != '\n') && (cVar1 != '\v')) {
        uVar4 = FUN_00148df0(0,0x80);
        FUN_0013e1b0(param_1 + 0x12,(uVar4 & 1) + 10);
      }
      break;
    case 6:
      if (cVar1 != '\f') {
        FUN_0013e1b0(param_1 + 0x12,0xc);
      }
      break;
    case 7:
      if ((cVar1 != '\r') && (cVar1 != '\x0e')) {
        if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 8) == 8) {
          FUN_0013e1b0(param_1 + 0x12,0xe);
        }
        else {
          FUN_0013e1b0(param_1 + 0x12,0xd);
        }
      }
      break;
    case 8:
      if (cVar1 != '\x11') {
        FUN_0013e1b0(param_1 + 0x12,0x11);
      }
      break;
    case 9:
      if (cVar1 != '\x18') {
        FUN_0013e1b0(param_1 + 0x12,0x18);
      }
    }
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 2) == 2) {
      return;
    }
    if ((bRam0085a2f5 < 0x14) && (5 < bRam0085a2f5)) {
      return;
    }
    if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x200) != 0x200) {
      if ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 1) != 1) {
        return;
      }
      (&DAT_00267000)[param_1] = 2;
      FUN_00139920(param_1 + 0x12,0x11);
      FUN_0013e2a0(param_1 + 0x12);
      puVar6 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
      *puVar6 = *puVar6 | 0x100;
      return;
    }
    iVar3 = (param_1 + 0x12) * 0x100;
    sVar2 = *(short *)(iVar3 + 0x8340a2);
    *(short *)(iVar3 + 0x8340a2) = sVar2 + 1;
    if ((ushort)(sVar2 + 1U) < 0x191) {
      return;
    }
    FUN_0013e2a0(param_1 + 0x12);
    puVar6 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
    *puVar6 = *puVar6 & 0xfffffdff;
    *(undefined2 *)((param_1 + 0x12) * 0x100 + 0x8340a2) = 0;
    (&DAT_00267000)[param_1] = 2;
    FUN_00139920(param_1 + 0x12,0x11);
    return;
  }
  (&DAT_00267000)[param_1] = 1;
  FUN_0013e2a0(param_1 + 0x12);
  uVar5 = FUN_00148df0(0,0x23be);
  if ((uVar5 & 1) != 1) {
    if ((uVar5 & 1) != 0) goto LAB_001c4724;
    if (*(char *)((param_1 + 0x12) * 0x100 + 0x834056) != '\x12') {
      FUN_00139920(param_1 + 0x12,0x12);
      *(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834098) = 0xb4;
      goto LAB_001c4724;
    }
  }
  FUN_00139920(param_1 + 0x12,0x13);
  (&DAT_00267000)[param_1] = 0;
LAB_001c4724:
  if (((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 2) != 2) &&
     ((0x13 < bRam0085a2f5 || (bRam0085a2f5 < 6)))) {
    (&DAT_00267000)[param_1] = 2;
    FUN_00139920(param_1 + 0x12,0x14);
    FUN_0013e2a0(param_1 + 0x12);
    puVar6 = (uint *)((uint)param_1 * 0x20 + 0x859f20);
    *puVar6 = *puVar6 | 0x100;
  }
  return;
}

