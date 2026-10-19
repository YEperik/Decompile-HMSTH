
void FUN_001bc3e0(byte param_1)

{
  short sVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  uint *puVar5;
  undefined1 auStack_30 [16];
  float afStack_20 [2];
  float fStack_18;
  byte bStack_8;
  
  if ((uint)bRam0026773c != param_1 + 0x1b) {
    bStack_8 = param_1;
    cVar2 = FUN_00123d60(*(undefined2 *)((param_1 + 0x1b) * 0x100 + 0x834058));
    cVar3 = (&DAT_00266ff8)[bStack_8];
    if (cVar3 == '\x04') {
      FUN_00124180(*(undefined2 *)((bStack_8 + 0x1b) * 0x100 + 0x834058),auStack_30);
      cVar3 = FUN_0014f600(auStack_30);
      if (cVar3 == '\t') {
        FUN_0013e2a0(bStack_8 + 0x1b);
        FUN_001244b0(*(undefined2 *)((bStack_8 + 0x1b) * 0x100 + 0x834058),afStack_20);
        afStack_20[0] = -afStack_20[0];
        fStack_18 = -fStack_18;
        FUN_00137b90(bStack_8 + 0x1b,afStack_20);
        FUN_0013e2a0(bStack_8 + 0x1b);
        FUN_00138360(bStack_8 + 0x1b,0x80);
        (&DAT_00266ff8)[bStack_8] = 1;
      }
      if ((*(uint *)((bStack_8 + 0x1b) * 0x100 + 0x834050) & 4) != 4) {
        (&DAT_00266ff8)[bStack_8] = 0;
        if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859e60) & 0x200) == 0x200) {
          (&DAT_00266ff8)[bStack_8] = 2;
        }
        else {
          FUN_0013dff0(bStack_8 + 0x1b,0x140,0,0x140);
        }
      }
    }
    else if (cVar3 == '\x02') {
      if (*(char *)((bStack_8 + 0x1b) * 0x100 + 0x834056) == '\x04') {
        if (cVar2 == '\0') {
          FUN_00139920(bStack_8 + 0x1b,2);
        }
      }
      else if ((*(uint *)((uint)bStack_8 * 0x20 + 0x859e60) & 0x200) == 0x200) {
        iVar4 = (bStack_8 + 0x1b) * 0x100;
        sVar1 = *(short *)(iVar4 + 0x8340a2);
        *(short *)(iVar4 + 0x8340a2) = sVar1 + 1;
        if (400 < (ushort)(sVar1 + 1U)) {
          puVar5 = (uint *)((uint)bStack_8 * 0x20 + 0x859e60);
          *puVar5 = *puVar5 & 0xfffffdff;
          *(undefined2 *)((bStack_8 + 0x1b) * 0x100 + 0x8340a2) = 0;
          FUN_00139920(bStack_8 + 0x1b,4);
        }
      }
      else if ((5 < bRam0085a2f5) && (bRam0085a2f5 < 0x14)) {
        puVar5 = (uint *)((uint)bStack_8 * 0x20 + 0x859e60);
        *puVar5 = *puVar5 & 0xffffbfff;
        puVar5 = (uint *)((uint)bStack_8 * 0x20 + 0x859e60);
        *puVar5 = *puVar5 & 0xfffffeff;
        (&DAT_00266ff8)[bStack_8] = 0;
        FUN_0013dff0(bStack_8 + 0x1b,0x140,0,0x140);
        FUN_001c4fc0(bStack_8);
      }
    }
    else if (cVar3 == '\x01') {
      if ((*(uint *)((bStack_8 + 0x1b) * 0x100 + 0x834050) & 4) != 4) {
        FUN_0013dff0(bStack_8 + 0x1b,0x100,0,0x100);
        (&DAT_00266ff8)[bStack_8] = 0;
      }
    }
    else if (cVar3 == '\0') {
      if ((*(uint *)((bStack_8 + 0x1b) * 0x100 + 0x834050) & 4) == 4) {
        FUN_00124180(*(undefined2 *)((bStack_8 + 0x1b) * 0x100 + 0x834058),auStack_30);
        cVar3 = FUN_0014f600(auStack_30);
        if (cVar3 == '\t') {
          FUN_0013e2a0(bStack_8 + 0x1b);
          FUN_001244b0(*(undefined2 *)((bStack_8 + 0x1b) * 0x100 + 0x834058),afStack_20);
          afStack_20[0] = -afStack_20[0];
          fStack_18 = -fStack_18;
          FUN_00137b90(bStack_8 + 0x1b,afStack_20);
          FUN_0013e2a0(bStack_8 + 0x1b);
          FUN_00138360(bStack_8 + 0x1b,0x80);
          (&DAT_00266ff8)[bStack_8] = 1;
        }
      }
      FUN_001c5560(bStack_8);
    }
  }
  return;
}

