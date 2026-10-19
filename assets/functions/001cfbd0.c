
void FUN_001cfbd0(void)

{
  ulong uVar1;
  ulong uVar2;
  long lVar3;
  undefined4 uVar4;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_4;
  
  uVar1 = FUN_001df320();
  uVar2 = FUN_001df330();
  if ((uVar2 & 0xf0) != 0) {
    *(undefined1 *)(puGpffff8af8 + 0xd4) = 1;
  }
  lVar3 = FUN_0012e170(0,0x40);
  if (lVar3 == 0) {
    lVar3 = FUN_0012e170(0,0x20);
    if (lVar3 == 0) {
      if (*(char *)(puGpffff8af8 + 0xd4) != '\0') {
        if ((uVar1 & 0x10) == 0) {
          if (((uVar1 & 0x20) != 0) &&
             (*(float *)(puGpffff8af8 + 0x7c) = *(float *)(puGpffff8af8 + 0x7c) + 0.06,
             0.785 < *(float *)(puGpffff8af8 + 0x7c))) {
            *(undefined4 *)(puGpffff8af8 + 0x7c) = 0x3f48f5c3;
          }
        }
        else {
          *(float *)(puGpffff8af8 + 0x7c) = *(float *)(puGpffff8af8 + 0x7c) - 0.06;
          if (*(float *)(puGpffff8af8 + 0x7c) < -0.785) {
            *(undefined4 *)(puGpffff8af8 + 0x7c) = 0xbf48f5c3;
          }
        }
        uVar4 = FUN_001d1bc0(*(undefined4 *)(puGpffff8af8 + 0x7a),
                             *(undefined4 *)(puGpffff8af8 + 0x7c));
        *(undefined4 *)(puGpffff8af8 + 0x78) = uVar4;
      }
    }
    else {
      *puGpffff8af8 = 0x17;
    }
  }
  else {
    *puGpffff8af8 = 3;
    puGpffff8af8[0x89] = 0;
    FUN_001d8f20(*(undefined1 *)(puGpffff8af8 + 0x86),0x56);
    fStack_4 = (*(float *)(puGpffff8af8 + 0x78) * 180.0) / 3.14;
    FUN_00129020(-fStack_4,puGpffff8af8 + 0x58);
  }
  uStack_20 = FUN_00112f70(*(undefined4 *)(puGpffff8af8 + 0x78));
  uStack_18 = FUN_00112bf8(*(undefined4 *)(puGpffff8af8 + 0x78));
  uStack_1c = 0;
  FUN_00137b90(0,&uStack_20);
  FUN_001d1790();
  return;
}

