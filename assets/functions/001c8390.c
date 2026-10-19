
void FUN_001c8390(byte param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  byte bStack_8;
  
  if (*(char *)((uint)param_1 * 8 + 0x859935) == '\0') {
    bStack_8 = param_1;
    if ((bRam0085a2f5 == 0) || (5 < bRam0085a2f5)) {
      if ((*(uint *)((uint)*(ushort *)((uint)param_1 * 8 + 0x859932) * 0x100 + 0x834050) & 4) != 4)
      {
        uVar1 = FUN_0011d018(*(undefined4 *)
                              ((uint)*(ushort *)((uint)param_1 * 8 + 0x859932) * 0x100 + 0x8340e0));
        uVar2 = FUN_00148df0(0,uVar1);
        if ((long)uVar2 < 0) {
          fStack_20 = (float)(uVar2 & 0xffffffff);
        }
        else {
          fStack_20 = (float)(int)uVar2;
        }
        uVar1 = FUN_0011d018(*(undefined4 *)
                              ((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340e4))
        ;
        uVar2 = FUN_00148df0(0,uVar1);
        if ((long)uVar2 < 0) {
          fStack_1c = (float)(uVar2 & 0xffffffff);
        }
        else {
          fStack_1c = (float)(int)uVar2;
        }
        uVar1 = FUN_0011d018(*(undefined4 *)
                              ((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340e8))
        ;
        uVar2 = FUN_00148df0(0,uVar1);
        if ((long)uVar2 < 0) {
          fStack_18 = (float)(uVar2 & 0xffffffff);
        }
        else {
          fStack_18 = (float)(int)uVar2;
        }
        uVar2 = FUN_00148df0(0,99);
        if (uVar2 < 0x32) {
          fStack_20 = fStack_20 +
                      *(float *)((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340d0
                                );
        }
        else {
          fStack_20 = *(float *)((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340d0
                                ) - fStack_20;
        }
        uVar2 = FUN_00148df0(0,99);
        if (uVar2 < 0x32) {
          fStack_1c = fStack_1c +
                      *(float *)((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340d4
                                );
        }
        else {
          fStack_1c = *(float *)((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340d4
                                ) - fStack_1c;
        }
        uVar2 = FUN_00148df0(0,99);
        if (uVar2 < 0x32) {
          fStack_18 = fStack_18 +
                      *(float *)((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340d8
                                );
        }
        else {
          fStack_18 = *(float *)((uint)*(ushort *)((uint)bStack_8 * 8 + 0x859932) * 0x100 + 0x8340d8
                                ) - fStack_18;
        }
        FUN_00138310(fStack_20,fStack_1c,fStack_18,0x3f800000,
                     *(ushort *)((uint)bStack_8 * 8 + 0x859932) & 0xff);
        FUN_00128900(&fStack_20);
        FUN_00137cc0(0x41f00000,*(ushort *)((uint)bStack_8 * 8 + 0x859932) & 0xff,&fStack_20);
      }
    }
    else {
      FUN_001c7510(param_1);
    }
  }
  return;
}

