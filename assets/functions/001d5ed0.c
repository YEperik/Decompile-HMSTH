
void FUN_001d5ed0(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined4 uVar6;
  float fVar7;
  
  cVar1 = *(char *)(iGpffff8af8 + 0x12) - *(char *)(iGpffff8af8 + 0x10);
  iVar3 = (int)cVar1;
  cVar2 = *(char *)(iGpffff8af8 + 0x13) - *(char *)(iGpffff8af8 + 0x11);
  iVar4 = (int)cVar2;
  *(undefined4 *)(iGpffff8af8 + 0x20) = *(undefined4 *)(iGpffff8af8 + 0x1c);
  if (((float)(int)cVar1 == 0.0) &&
     (0x7e < (int)*(char *)(iGpffff8af8 + 0x12) * (int)*(char *)(iGpffff8af8 + 0x16))) {
    cVar1 = FUN_0011cf88((float)(int)*(char *)(iGpffff8af8 + 0x16) * 8.0);
    iVar3 = (int)cVar1;
  }
  if (((float)(int)cVar2 == 0.0) &&
     (0x7e < (int)*(char *)(iGpffff8af8 + 0x13) * (int)*(char *)(iGpffff8af8 + 0x17))) {
    cVar1 = FUN_0011cf88((float)(int)*(char *)(iGpffff8af8 + 0x17) * 8.0);
    iVar4 = (int)cVar1;
  }
  fVar5 = (float)FUN_001d8d50();
  if (0.25 <= fVar5) {
    cVar1 = *(char *)(iGpffff8af8 + 0x184);
    if (cVar1 == '\x03') {
      if ((char)iVar4 < '\0') {
        return;
      }
      iVar3 = 0;
    }
    else if (cVar1 == '\x02') {
      if ((char)iVar3 < '\0') {
        return;
      }
      iVar4 = 0;
    }
    else if (cVar1 == '\x01') {
      if ('\0' < (char)iVar4) {
        return;
      }
      iVar3 = 0;
    }
    else if (cVar1 == '\0') {
      if ('\0' < (char)iVar3) {
        return;
      }
      iVar4 = 0;
    }
  }
  *(float *)(iGpffff8af8 + 0x1c) =
       *(float *)(iGpffff8af8 + 0x1c) +
       (((float)iVar3 * 128.0) / (*(float *)(iGpffff8af8 + 0x18c) + 1024.0)) / 4.0;
  FUN_001d6890(-((((float)iVar4 * 128.0) / (*(float *)(iGpffff8af8 + 0x18c) + 1024.0)) / -4.0));
  fVar5 = (float)FUN_001d87a0(*(float *)(iGpffff8af8 + 0x1a0) + *(float *)(iGpffff8af8 + 0x1a4));
  FUN_001d7d20(-fVar5,fVar5,iGpffff8af8 + 0x1c);
  *(float *)(iGpffff8af8 + 0x30) = *(float *)(iGpffff8af8 + 0x30) + (float)iVar4 / -4.0;
  *(float *)(iGpffff8af8 + 0x2c) = *(float *)(iGpffff8af8 + 0x2c) + (float)iVar3 / 4.0;
  FUN_001d7d20(0xc2000000,0x42000000,iGpffff8af8 + 0x30);
  FUN_001d7d20(0xc2000000,0x42000000,iGpffff8af8 + 0x2c);
  uVar6 = *(undefined4 *)(iGpffff8af8 + 0x30);
  fVar5 = *(float *)(iGpffff8af8 + 0x2c);
  fVar7 = *(float *)(iGpffff8af8 + 0x1c);
  FUN_00120d30(0,0,0,0,sRam0083405a + 4);
  FUN_00121840(0,0x3f800000,0,fVar5,sRam0083405a + 4);
  FUN_00121840(0x3f800000,0,0,uVar6,sRam0083405a + 4);
  FUN_001d6f70(uVar6,-fVar5,0,iGpffff8af8 + 0x70);
  FUN_001d6f70(0,-fVar7,0,iGpffff8af8 + 0xa0);
  if ((1.0 < ((float)iVar4 / -4.0) * (float)(int)*(char *)(iGpffff8af8 + 0x15) * -1.0) ||
     (1.0 < ((float)iVar3 / 4.0) * (float)(int)*(char *)(iGpffff8af8 + 0x14))) {
    *(undefined1 *)(iGpffff8af8 + 0x1b9) = 1;
  }
  return;
}

