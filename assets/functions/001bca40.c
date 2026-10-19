
void FUN_001bca40(byte param_1)

{
  char cVar1;
  short sVar2;
  char cVar3;
  uint *puVar4;
  ushort uVar5;
  int iVar6;
  undefined1 auStack_30 [28];
  undefined4 uStack_14;
  byte bStack_8;
  
  bStack_8 = param_1;
  cVar3 = FUN_00123d60(*(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834058));
  if (((((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 2) == 2) &&
       ((&gp0xffff8110)[bStack_8] != '\x04')) && ((&gp0xffff8110)[bStack_8] != '\x05')) &&
     ((((&gp0xffff8110)[bStack_8] != '\a' && ((&gp0xffff8110)[bStack_8] != '\x06')) &&
      (((&gp0xffff8110)[bStack_8] != '\x02' && ((&gp0xffff8110)[bStack_8] != '\r')))))) {
    (&gp0xffff8110)[bStack_8] = 3;
  }
  switch((&gp0xffff8110)[bStack_8]) {
  case 0:
    FUN_001bdb30(bStack_8);
    if (((((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x100000) != 0x100000) &&
         ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x80000) != 0x80000)) &&
        ((&gp0xffff8110)[bStack_8] != '\x05')) && ((&gp0xffff8110)[bStack_8] != '\a')) {
      FUN_001c4200(bStack_8);
    }
    break;
  case 1:
    cVar1 = *(char *)((bStack_8 + 0x12) * 0x100 + 0x834056);
    if (cVar1 == '\x13') {
      if (cVar3 == '\0') {
        puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
        *puVar4 = *puVar4 & 0xff7fffff;
        FUN_0013dff0(bStack_8 + 0x12,0x140,0,0x140);
        FUN_001c4590(bStack_8);
      }
    }
    else if (cVar1 == '\x19') {
      if (cVar3 == '\0') {
        FUN_0013dff0(bStack_8 + 0x12,0x100,0,0x100);
        FUN_001c4590(bStack_8);
        (&gp0xffff8110)[bStack_8] = 0;
      }
    }
    else if (cVar1 == '\a') {
      iVar6 = (bStack_8 + 0x12) * 0x100;
      sVar2 = *(short *)(iVar6 + 0x834098);
      *(short *)(iVar6 + 0x834098) = sVar2 + -1;
      if (sVar2 == 1) {
        FUN_00139920(bStack_8 + 0x12,0x19);
      }
    }
    else if (cVar1 == '\x12') {
      iVar6 = (bStack_8 + 0x12) * 0x100;
      sVar2 = *(short *)(iVar6 + 0x834098);
      *(short *)(iVar6 + 0x834098) = sVar2 + -1;
      if (sVar2 == 1) {
        (&gp0xffff8110)[bStack_8] = 0;
      }
    }
    else if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) != 4) {
      FUN_0013dff0(bStack_8 + 0x12,0x100,0,0x100);
      (&gp0xffff8110)[bStack_8] = 0;
    }
    break;
  case 2:
    cVar1 = *(char *)((bStack_8 + 0x12) * 0x100 + 0x834056);
    if (cVar1 == '\x14') {
      if (cVar3 == '\0') {
        FUN_00139920(bStack_8 + 0x12,0x15);
      }
    }
    else if (cVar1 == '\x11') {
      if (cVar3 == '\0') {
        puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
        *puVar4 = *puVar4 | 0x800000;
        FUN_00139920(bStack_8 + 0x12,0x14);
      }
    }
    else if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x200) == 0x200) {
      iVar6 = (bStack_8 + 0x12) * 0x100;
      sVar2 = *(short *)(iVar6 + 0x8340a2);
      *(short *)(iVar6 + 0x8340a2) = sVar2 + 1;
      if (400 < (ushort)(sVar2 + 1U)) {
        puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
        *puVar4 = *puVar4 & 0xfffffdff;
        *(undefined2 *)((bStack_8 + 0x12) * 0x100 + 0x8340a2) = 0;
        FUN_00139920(bStack_8 + 0x12,0x11);
      }
    }
    else if ((5 < bRam0085a2f5) && (bRam0085a2f5 < 0x14)) {
      puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar4 = *puVar4 & 0xff7fffff;
      puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar4 = *puVar4 & 0xfffffeff;
      (&gp0xffff8110)[bStack_8] = 0;
      FUN_0013dff0(bStack_8 + 0x12,0x140,0,0x140);
      FUN_001c4590(bStack_8);
    }
    break;
  case 3:
    FUN_001bdb30(bStack_8);
    if ((((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x100) != 0x100) &&
        ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x100000) != 0x100000)) &&
       (((&gp0xffff8110)[bStack_8] != '\x05' &&
        (((&gp0xffff8110)[bStack_8] != '\a' && ((&gp0xffff8110)[bStack_8] != '\r')))))) {
      if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 2) == 2) {
        if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x100000) == 0x100000) {
          if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) != 4) {
            puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
            *puVar4 = *puVar4 & 0xffefffff;
            FUN_00138ce0(bStack_8 + 0x12);
          }
        }
        else {
          FUN_0013e1b0(bStack_8 + 0x12,0xff);
          if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 0x4000) != 0x4000) {
            FUN_0013dff0(bStack_8 + 0x12,0x140,0,0x140);
          }
        }
      }
      else {
        iVar6 = (bStack_8 + 0x12) * 0x100;
        sVar2 = *(short *)(iVar6 + 0x8340a2);
        *(short *)(iVar6 + 0x8340a2) = sVar2 + -1;
        if (sVar2 == 1) {
          (&gp0xffff8110)[bStack_8] = 0;
          FUN_0013dff0(bStack_8 + 0x12,0x140,0,0x140);
          FUN_001c4590(bStack_8);
        }
      }
    }
    if ((0x13 < bRam0085a2f5) || (bRam0085a2f5 < 6)) {
      if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x200) == 0x200) {
        iVar6 = (bStack_8 + 0x12) * 0x100;
        uVar5 = *(short *)(iVar6 + 0x8340a2) + 1;
        *(ushort *)(iVar6 + 0x8340a2) = uVar5;
        if (400 < uVar5) {
          FUN_0013e2a0(bStack_8 + 0x12);
          puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
          *puVar4 = *puVar4 & 0xfffffdff;
          *(undefined2 *)((bStack_8 + 0x12) * 0x100 + 0x8340a2) = 0;
          (&gp0xffff8110)[bStack_8] = 2;
          FUN_00139920(bStack_8 + 0x12,0x11);
        }
      }
      else if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 1) == 1) {
        (&gp0xffff8110)[bStack_8] = 2;
        FUN_00139920(bStack_8 + 0x12,0x11);
        FUN_0013e2a0(bStack_8 + 0x12);
        puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
        *puVar4 = *puVar4 | 0x100;
      }
    }
    break;
  case 4:
    FUN_001bdb30(bStack_8);
    if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) != 4) {
      (&gp0xffff8110)[bStack_8] = 0;
      if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x80000) == 0x80000) {
        FUN_00138760(0x44900000,0,0x44d80000,bStack_8 + 0x12);
      }
      else if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x200) == 0x200) {
        (&gp0xffff8110)[bStack_8] = 2;
      }
      else {
        FUN_0013dff0(bStack_8 + 0x12,0x140,0,0x140);
      }
    }
    break;
  case 5:
    FUN_00124180(*(undefined2 *)((bStack_8 + 0x12) * 0x100 + 0x834058),auStack_30);
    cVar3 = FUN_0014f600(auStack_30);
    if (cVar3 == -0x19) {
      if (cGpffff8acc == '\0') {
        FUN_00150200(2);
      }
      cGpffff8acc = cGpffff8acc + '\x01';
      uStack_14 = FUN_00141880(bStack_8 + 0x12);
      FUN_0013a3e0(0,uStack_14,0,uStack_14,bStack_8 + 0x12,2);
      (&gp0xffff8110)[bStack_8] = 6;
    }
    break;
  case 6:
    if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) != 4) {
      FUN_00137930(bStack_8 + 0x12);
      puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar4 = *puVar4 & 0xfff7ffff;
      FUN_001b2510(bStack_8);
      if (cGpffff8acc == '\x01') {
        FUN_00150200(2,1);
      }
      cGpffff8acc = cGpffff8acc + -1;
      (&gp0xffff8110)[bStack_8] = 0;
    }
    break;
  case 7:
    if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) != 4) {
      FUN_00137930(bStack_8 + 0x12);
      puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar4 = *puVar4 & 0xffdfffff;
      FUN_001b2b30(bStack_8);
      if (cGpffff8acc == '\x01') {
        FUN_00150200(0x15,1);
      }
      cGpffff8acc = cGpffff8acc + -1;
      (&gp0xffff8110)[bStack_8] = 0;
    }
    break;
  case 9:
    if (*(char *)((bStack_8 + 0x12) * 0x100 + 0x834056) == '\x13') {
      if (cVar3 != '\0') {
        return;
      }
      puVar4 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar4 = *puVar4 & 0xff7fffff;
    }
    FUN_001bdb30(bStack_8);
    FUN_001c96f0(bStack_8);
    break;
  case 0xd:
    if ((*(uint *)((bStack_8 + 0x12) * 0x100 + 0x834050) & 4) != 4) {
      FUN_0013dff0(bStack_8 + 0x12,0x100,0,0x100);
      (&gp0xffff8110)[bStack_8] = 0;
    }
  }
  return;
}

