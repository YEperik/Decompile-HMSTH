
/* WARNING: Removing unreachable block (ram,0x001d2b58) */

void FUN_001d29b0(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  ulong uVar4;
  byte unaff_s0_lo;
  float fVar5;
  undefined1 auStack_10 [16];
  
  FUN_001d2d20(*(undefined4 *)(iGpffff8af8 + 0x1a0),auStack_10);
  cVar1 = '\0';
  while (cVar1 == '\0') {
    unaff_s0_lo = FUN_001d2fc0(auStack_10);
    cVar1 = FUN_001d3220(unaff_s0_lo);
  }
  *(byte *)(iGpffff8af8 + 0x17c) = unaff_s0_lo;
  *(uint *)(iGpffff8af8 + 0x178) = (uint)unaff_s0_lo * 0x14 + 0x244710;
  if (((unaff_s0_lo == 6) || (unaff_s0_lo == 7)) || (unaff_s0_lo == 8)) {
    *(char *)(iGpffff8af8 + 7) = *(char *)(iGpffff8af8 + 0x10c) + -1;
  }
  else {
    *(undefined1 *)(iGpffff8af8 + 7) = *(undefined1 *)(iGpffff8af8 + 0x10c);
  }
  FUN_001d1d60();
  uVar4 = FUN_00148df0(*(undefined2 *)(*(int *)(iGpffff8af8 + 0x178) + 4),
                       *(undefined2 *)(*(int *)(iGpffff8af8 + 0x178) + 6));
  if ((long)uVar4 < 0) {
    fVar5 = (float)(uVar4 & 0xffffffff);
  }
  else {
    fVar5 = (float)(int)uVar4;
  }
  *(float *)(iGpffff8af8 + 0x18c) = fVar5;
  *(float *)(iGpffff8af8 + 0x18c) =
       *(float *)(iGpffff8af8 + 0x18c) / 2.0 +
       (*(float *)(iGpffff8af8 + 0x18c) / 2.0) / (float)*(byte *)(iGpffff8af8 + 7);
  uVar2 = FUN_00148df0(*(undefined1 *)(*(int *)(iGpffff8af8 + 0x178) + 0xc),
                       *(undefined1 *)(*(int *)(iGpffff8af8 + 0x178) + 0xd));
  *(undefined1 *)(iGpffff8af8 + 0x17d) = uVar2;
  if (*(char *)(iGpffff8af8 + 0x17c) < '\x03') {
    *(undefined1 *)(iGpffff8af8 + 0x18a) = 0;
  }
  else if (*(char *)(iGpffff8af8 + 0x17c) == '\x06') {
    *(undefined1 *)(iGpffff8af8 + 0x18a) = 5;
  }
  else if (*(char *)(iGpffff8af8 + 0x17c) == '\a') {
    *(undefined1 *)(iGpffff8af8 + 0x18a) = 8;
  }
  else {
    uVar2 = FUN_00148df0(1,4);
    *(undefined1 *)(iGpffff8af8 + 0x18a) = uVar2;
  }
  uVar3 = FUN_00148df0(*(undefined2 *)(*(int *)(iGpffff8af8 + 0x178) + 8),
                       *(undefined2 *)(*(int *)(iGpffff8af8 + 0x178) + 10));
  FUN_001d33f0(uVar3,*(undefined2 *)(*(int *)(iGpffff8af8 + 0x178) + 10),iGpffff8af8 + 0x150);
  *(undefined1 *)(iGpffff8af8 + 0x17f) = 0;
  FUN_001d40e0();
  return;
}

