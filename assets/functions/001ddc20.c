
void FUN_001ddc20(uint param_1,undefined4 param_2,short param_3,int param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  short sVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  short sVar8;
  undefined1 auStack_48 [16];
  undefined1 auStack_38 [16];
  uint uStack_28;
  int iStack_24;
  uint uStack_20;
  undefined4 uStack_18;
  short sStack_10;
  int iStack_8;
  
  uStack_20 = param_1;
  uStack_18 = param_2;
  sStack_10 = param_3;
  iStack_8 = param_4;
  for (sVar8 = 0; sVar8 < sStack_10; sVar8 = sVar8 + 1) {
    *(int *)(iStack_8 + 0xc) = *(int *)(iStack_8 + 0xc) + *(int *)(iGpffff8148 + 0x10);
    *(int *)(iStack_8 + 8) = *(int *)(iStack_8 + 8) + *(int *)(iGpffff8148 + 0x10);
    sVar3 = (short)*(char *)(iStack_8 + 7);
    uVar1 = FUN_001361f0(uStack_20 & 0xffff,uStack_18,0x1941000);
    FUN_00148e20(auStack_48,uVar1,sVar3 + *(short *)(iGpffff8148 + 4),*(undefined4 *)(iStack_8 + 8),
                 *(undefined4 *)(iStack_8 + 0xc));
    uStack_20 = uStack_20 + 1;
    if ('\x01' < *(char *)(iStack_8 + 5)) {
      if (*(char *)(iStack_8 + 4) == '\0') {
        uVar7 = 0x100;
      }
      else {
        uVar7 = 0x400;
      }
      iVar6 = (int)uVar1 + 0x10000;
      sVar4 = 1;
      uVar5 = uVar7;
      uStack_28 = uVar7;
      while( true ) {
        sVar3 = sVar3 + 1;
        if ((long)*(char *)(iStack_8 + 5) <= (long)sVar4) break;
        uVar2 = FUN_001361f0(uStack_20 & 0xffff,uStack_18,iVar6);
        FUN_00148f40(auStack_38,uVar1,sVar3 + *(short *)(iGpffff8148 + 4),
                     *(undefined4 *)(iStack_8 + 8),*(int *)(iStack_8 + 0xc) + (uVar5 >> 2),uVar2);
        uStack_20 = uStack_20 + 1;
        uVar5 = uVar5 + uVar7;
        iVar6 = iVar6 + uVar7;
        sVar4 = sVar4 + 1;
      }
    }
    iStack_24 = iStack_8;
    iStack_8 = iStack_8 + 0x10;
  }
  return;
}

