
void FUN_001c3aa0(void)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar2 = uGpffff8ac0;
  bVar1 = false;
  uVar4 = (uint)bGpffff8928;
  for (uVar3 = 0; uVar3 < 5; uVar3 = uVar3 + 1 & 0xff) {
    uVar4 = uVar4 + (byte)(&gp0xffff8930)[uVar3];
  }
  iVar5 = uVar4 - uGpffff8ac0;
  iVar6 = (uint)bRam0085a2f5 - (uint)bGpffff8ac4;
  if (((int)((uint)bRam0085a2f4 - (uint)bGpffff8ac8) < 0) && (iVar6 = iVar6 + -1, iVar6 < 0)) {
    iVar6 = 0;
  }
  iVar6 = iVar6 * 0x32;
  for (uVar3 = 0; uVar3 < 6; uVar3 = uVar3 + 1 & 0xff) {
    if ((((&gp0xffff89a8)[uVar3] ^ (&gp0xffff89a0)[uVar3]) & 2) == 2) {
      iVar6 = iVar6 + 0x14;
    }
    if ((((&gp0xffff89a8)[uVar3] ^ (&gp0xffff89a0)[uVar3]) & 4) == 4) {
      bVar1 = true;
    }
    (&gp0xffff89a0)[uVar3] = (&gp0xffff89a8)[uVar3] | (&gp0xffff89a0)[uVar3];
  }
  FUN_0016ce30(iVar6);
  FUN_00154550(0x19,iVar6);
  if ((int)uGpffff8ac0 < 0x47) {
    if (uVar4 == uVar2) {
      FUN_00152f40(0,10,0,5);
    }
    else if (iVar5 < 0x10) {
      FUN_00152f40(0,9,0,5);
    }
    else if (bVar1) {
      FUN_00152f40(0,0x11,0,5);
    }
    else {
      FUN_00152f40(0,8,0,5);
    }
  }
  else if (iVar5 < 0x10) {
    FUN_00152f40(0,0x13,0,5);
  }
  else if (bVar1) {
    FUN_00152f40(0,0x11,0,5);
  }
  else {
    FUN_00152f40(0,0x12,0,5);
  }
  bGpffff89dc = bGpffff89dc & 0xf7;
  uGpffff8954 = 0xff;
  return;
}

