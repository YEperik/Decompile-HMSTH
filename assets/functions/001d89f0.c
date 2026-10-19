
/* WARNING: Removing unreachable block (ram,0x001d8a48) */

undefined4 FUN_001d89f0(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  long lVar3;
  float fVar4;
  
  fVar4 = (*(float *)(iGpffff8af8 + 0x1a0) + *(float *)(iGpffff8af8 + 0x1a4)) - 370.0;
  if (fVar4 < 0.0) {
    uVar2 = 0;
  }
  else if (1936.0 < fVar4) {
    uVar2 = 1;
  }
  else {
    fVar4 = (float)FUN_001d93e0(fVar4,0,0x44c3c000,0,0x44800000);
    uVar1 = FUN_0011d018((((float)(*(char *)(iGpffff8af8 + 0x17d) + 1) * 256.0) / 7.0 +
                          (float)((int)*(char *)(iGpffff8af8 + 0x17e) << 3) +
                          (1024.0 - fVar4) +
                          (float)(int)((3 - (uint)*(byte *)(iGpffff8af8 + 7)) * 0x100) + 7.0) / 8.0)
    ;
    lVar3 = FUN_00148df0(0,uVar1);
    if (lVar3 == 0) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

