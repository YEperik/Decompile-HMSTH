
void FUN_001c5a00(undefined1 param_1,undefined1 param_2)

{
  ulong uVar1;
  undefined4 auStack_30 [2];
  undefined4 uStack_28;
  undefined2 uStack_16;
  undefined2 uStack_14;
  byte bStack_11;
  undefined1 uStack_10;
  undefined1 uStack_8;
  
  if ((((cGpffff8844 != '\x06') &&
       (((cGpffff8944 == '\0' || (cGpffff8944 == '\x04')) && (cRam0085a2f7 != '\x03')))) &&
      (((7 < bRam0085a2f5 && (bRam0085a2f5 < 0x13)) &&
       (uStack_10 = param_1, uStack_8 = param_2, uVar1 = FUN_00148df0(0,99), uVar1 < 0x19)))) &&
     (FUN_001c72b0(&bStack_11,&uStack_16,&uStack_14), bStack_11 != 0xff)) {
    FUN_001c5940(bStack_11,uStack_16,uStack_14,0xc4,0x177f000);
    FUN_0014fe50(uStack_10,uStack_8,auStack_30);
    FUN_00137ae0(auStack_30[0],0,uStack_28,bStack_11);
    FUN_001378a0(bStack_11);
    FUN_00139920(bStack_11);
    *(undefined1 *)((bStack_11 - 0x21) * 8 + 0x859930) = 1;
    *(undefined1 *)((bStack_11 - 0x21) * 8 + 0x859934) = 0;
    *(ushort *)((bStack_11 - 0x21) * 8 + 0x859932) = (ushort)bStack_11;
    *(undefined1 *)((bStack_11 - 0x21) * 8 + 0x859935) = 0;
  }
  return;
}

