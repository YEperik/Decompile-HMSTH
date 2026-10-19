
void FUN_001d7130(void)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char cVar5;
  char cVar6;
  
  cVar1 = FUN_0012e260();
  cVar2 = FUN_0012e2a0();
  if (cVar1 < '\0') {
    cVar5 = -1;
  }
  else {
    cVar5 = '\x01';
  }
  if (cVar2 < '\0') {
    cVar6 = -1;
  }
  else {
    cVar6 = '\x01';
  }
  *(undefined1 *)(iRam002679e8 + 5) = 0;
  if (cVar1 < -0x31) {
    *(byte *)(iRam002679e8 + 5) = *(byte *)(iRam002679e8 + 5) | 0x10;
  }
  if ('1' < cVar1) {
    *(byte *)(iRam002679e8 + 5) = *(byte *)(iRam002679e8 + 5) | 0x20;
  }
  if (cVar2 < -0x31) {
    *(byte *)(iRam002679e8 + 5) = *(byte *)(iRam002679e8 + 5) | 0x40;
  }
  if ('1' < cVar1) {
    *(byte *)(iRam002679e8 + 5) = *(byte *)(iRam002679e8 + 5) | 0x80;
  }
  *(byte *)(iRam002679e8 + 6) =
       *(byte *)(iRam002679e8 + 5) & (*(byte *)(iRam002679e8 + 5) ^ *(byte *)(iRam002679e8 + 4));
  *(undefined1 *)(iRam002679e8 + 4) = *(undefined1 *)(iRam002679e8 + 5);
  if ((ushort)((short)cVar1 * (short)cVar5) < 0x33) {
    cVar5 = '\0';
    uVar3 = 0;
  }
  else {
    uVar3 = (uint)(ushort)((short)cVar1 * (short)cVar5 - 0x32);
  }
  if ((ushort)((short)cVar2 * (short)cVar6) < 0x33) {
    cVar6 = '\0';
    uVar4 = 0;
  }
  else {
    uVar4 = (uint)(ushort)((short)cVar2 * (short)cVar6 - 0x32);
  }
  *(undefined1 *)(iRam002679e8 + 0x10) = *(undefined1 *)(iRam002679e8 + 0x12);
  *(undefined1 *)(iRam002679e8 + 0x11) = *(undefined1 *)(iRam002679e8 + 0x13);
  *(char *)(iRam002679e8 + 0x12) = (char)((int)(uVar3 * 0x7f000) / 0x4d >> 0xc) * cVar5;
  *(char *)(iRam002679e8 + 0x13) = (char)((int)(uVar4 * 0x7f000) / 0x4d >> 0xc) * cVar6;
  *(char *)(iRam002679e8 + 0x16) = cVar5;
  *(char *)(iRam002679e8 + 0x17) = cVar6;
  return;
}

