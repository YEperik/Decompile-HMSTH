
void FUN_001bdb30(byte param_1)

{
  char cVar1;
  uint *puVar2;
  undefined1 auStack_40 [16];
  float afStack_30 [2];
  float fStack_28;
  undefined4 uStack_14;
  byte bStack_8;
  
  bStack_8 = param_1;
  if ((*(uint *)((param_1 + 0x12) * 0x100 + 0x834050) & 4) == 4) {
    FUN_00124180(*(undefined2 *)((param_1 + 0x12) * 0x100 + 0x834058),auStack_40);
    cVar1 = FUN_0014f600(auStack_40);
    if (cVar1 == -0x1a) {
      if (((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x100000) == 0x100000) ||
         ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x80000) == 0x80000)) {
        puVar2 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
        *puVar2 = *puVar2 | 0x80000;
        puVar2 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
        *puVar2 = *puVar2 & 0xffefffff;
        FUN_0013e2a0(bStack_8 + 0x12);
        FUN_00138760(0x44900000,0,0x45400000,bStack_8 + 0x12);
        (&gp0xffff8110)[bStack_8] = 5;
      }
      else {
        FUN_0013e2a0(bStack_8 + 0x12);
        FUN_001244b0(*(undefined2 *)((bStack_8 + 0x12) * 0x100 + 0x834058),afStack_30);
        afStack_30[0] = -afStack_30[0];
        fStack_28 = -fStack_28;
        FUN_00137b90(bStack_8 + 0x12,afStack_30);
        FUN_0013e2a0(bStack_8 + 0x12);
        FUN_00138760(0x4484a000,0,0x44bd4000,bStack_8 + 0x12);
        (&gp0xffff8110)[bStack_8] = 0xd;
      }
    }
    else if ((cVar1 == -0x18) &&
            (((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x100000) == 0x100000 ||
             ((*(uint *)((uint)bStack_8 * 0x20 + 0x859f20) & 0x200000) == 0x200000)))) {
      puVar2 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar2 = *puVar2 | 0x200000;
      puVar2 = (uint *)((uint)bStack_8 * 0x20 + 0x859f20);
      *puVar2 = *puVar2 & 0xffefffff;
      (&gp0xffff8110)[bStack_8] = 7;
      FUN_0013e2a0(bStack_8 + 0x12);
      FUN_00138760(0,0,0xc4800000,bStack_8 + 0x12);
      if (cGpffff8acc == '\0') {
        FUN_00150200(0x15);
      }
      cGpffff8acc = cGpffff8acc + '\x01';
      uStack_14 = FUN_00141880(bStack_8 + 0x12);
      FUN_0013a3e0(0,uStack_14,0,uStack_14,bStack_8 + 0x12,2);
    }
  }
  else if (((((*(uint *)((param_1 + 0x12) * 0x100 + 0x834050) & 0x4000) != 0x4000) &&
            ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x800000) != 0x800000)) &&
           ((*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x100000) == 0x100000)) &&
          (puVar2 = (uint *)((uint)param_1 * 0x20 + 0x859f20), *puVar2 = *puVar2 & 0xffefffff,
          (*(uint *)((uint)param_1 * 0x20 + 0x859f20) & 0x100) != 0x100)) {
    FUN_0013dff0(param_1 + 0x12,0x100,0,0x100);
  }
  return;
}

