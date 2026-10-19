
void FUN_001d0910(void)

{
  long lVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  puGpffff8af8[1] = puGpffff8af8[1] + 1;
  lVar1 = FUN_00123d10(uRam00834058);
  if (lVar1 == 0) {
    fVar3 = (*(float *)(puGpffff8af8 + 0xa0) *
            (float)(int)(short)puGpffff8af8[1] * (float)(int)(short)puGpffff8af8[1]) / 2.0;
    *(float *)(puGpffff8af8 + 0x98) =
         *(float *)(puGpffff8af8 + 0x98) - *(float *)(puGpffff8af8 + 0x9e);
    fVar4 = (float)FUN_00112f70(*(float *)(puGpffff8af8 + 0x98) / 1024.0);
    fVar2 = *(float *)(puGpffff8af8 + 0x9c);
    fVar5 = *(float *)(puGpffff8af8 + 0x9a);
    fVar6 = (float)FUN_00112f70(*(undefined4 *)(puGpffff8af8 + 0xde));
    fVar7 = *(float *)(puGpffff8af8 + 0x48);
    fVar8 = (float)FUN_00112bf8(*(undefined4 *)(puGpffff8af8 + 0xde));
    FUN_00137ae0(fVar7 + fVar3 * fVar6,fVar5 + fVar2 * fVar4,
                 *(float *)(puGpffff8af8 + 0x4c) + fVar3 * fVar8,0x27);
  }
  else {
    FUN_001d1a50();
    FUN_00137930(0x68);
    FUN_00120d30(0,0,0,0,uRam0083675a);
    FUN_00139920(0x27);
    FUN_0014bd30(**(undefined1 **)(puGpffff8af8 + 0xbc));
    FUN_0013b4e0(0,0x27,**(undefined1 **)(puGpffff8af8 + 0xbc));
    FUN_00123750(0x32e);
    *puGpffff8af8 = 0xc;
  }
  return;
}

