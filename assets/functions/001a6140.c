
void FUN_001a6140(char param_1)

{
  byte bVar1;
  uint uVar2;
  undefined1 uStack_20;
  char cStack_1f;
  char cStack_1e;
  undefined1 uStack_1d;
  undefined1 uStack_1c;
  undefined1 uStack_1b;
  undefined1 uStack_1a;
  undefined1 auStack_19 [17];
  char cStack_8;
  
  DAT_00266fa0 = DAT_00266fa0 + param_1;
  if (DAT_00266fa0 < '\x01') {
    DAT_00266fa0 = '\x01';
  }
  if ('c' < DAT_00266fa0) {
    DAT_00266fa0 = 'c';
  }
  bVar1 = *(byte *)((((uint)uRam00267970 + (uint)bRam00267978) - (uint)uRam0026796c) + 0x85a380);
  if (cRam00267968 == '\0') {
    if (99 < (int)((uint)*(byte *)(bVar1 + 0x85a2a0) + (int)DAT_00266fa0)) {
      DAT_00266fa0 = 'c' - *(char *)(bVar1 + 0x85a2a0);
    }
    for (; (iRam00267864 <
            (int)((int)DAT_00266fa0 *
                 (uint)*(ushort *)
                        ((((uint)uRam00267970 + (uint)bRam00267978) - (uint)uRam0026796c) * 2 +
                        0x85a390)) && ('\x01' < DAT_00266fa0)); DAT_00266fa0 = DAT_00266fa0 + -1) {
    }
  }
  else if ((long)(ulong)*(byte *)(bVar1 + 0x85a2a0) < (long)DAT_00266fa0) {
    DAT_00266fa0 = *(char *)(bVar1 + 0x85a2a0);
  }
  uStack_20 = 0xf9;
  cStack_1f = DAT_00266fa0 / '\n' + '\x11';
  cStack_1e = DAT_00266fa0 % '\n' + '\x11';
  uStack_1d = 0xff;
  uStack_1c = 0xff;
  uStack_1b = 0xff;
  uStack_1a = 0xff;
  auStack_19[0] = 0xff;
  cStack_8 = param_1;
  FUN_00154290((bRam00267978 & 0x7f) << 1,&uStack_20);
  uVar2 = FUN_001545a0(auStack_19 + 1,
                       (int)DAT_00266fa0 *
                       (uint)*(ushort *)
                              ((((uint)uRam00267970 + (uint)bRam00267978) - (uint)uRam0026796c) * 2
                              + 0x85a390));
  FUN_00116978(&uStack_20,0x10,8);
  FUN_001167c0(auStack_19 + -(uVar2 & 0xff),auStack_19 + 1,uVar2 & 0xff);
  auStack_19[0] = 0x21;
  FUN_00154290(bRam00267978 * '\x02' + '\x01',&uStack_20);
  return;
}

