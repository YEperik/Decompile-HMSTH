
bool FUN_001c3390(char param_1,byte param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  bool bVar5;
  uint uVar6;
  undefined2 uStack_14;
  undefined1 uStack_12;
  char cStack_10;
  byte bStack_8;
  
  cStack_10 = param_1;
  bStack_8 = param_2;
  puVar4 = (undefined1 *)0x0;
  uStack_14 = DAT_00267020;
  uStack_12 = DAT_00267022;
  uVar6 = 0;
  bVar5 = true;
  if (((param_1 == '\x12') || (param_2 != 0)) || ((bRam00267898 & 0x80) == 0x80)) {
    if (((param_1 == '\x12') || (param_2 != 1)) || ((bRam00267898 & 0x40) == 0x40)) {
      uVar2 = (uint)*(byte *)((int)&uStack_14 + (uint)param_2);
    }
    else {
      uVar2 = 4;
      bRam00267898 = bRam00267898 | 0x40;
    }
  }
  else {
    uVar2 = 5;
    bRam00267898 = bRam00267898 | 0x80;
  }
  uVar3 = 1 << (param_2 & 0x1f);
  bVar1 = (byte)uVar3;
  if (param_1 == 's') {
    bVar5 = (uVar3 & 0xff) != ((uint)bRam0026789d & uVar3 & 0xff);
    if (!bVar5) {
      uVar2 = 0;
    }
    bRam0026789d = bRam0026789d | bVar1;
    uVar6 = bRam00267824 + uVar2;
    puVar4 = (undefined1 *)0x267824;
  }
  else if (param_1 == 'r') {
    bVar5 = (uVar3 & 0xff) != ((uint)bRam0026789c & uVar3 & 0xff);
    if (!bVar5) {
      uVar2 = 0;
    }
    bRam0026789c = bRam0026789c | bVar1;
    uVar6 = bRam00267823 + uVar2;
    puVar4 = (undefined1 *)0x267823;
  }
  else if (param_1 == 'q') {
    bVar5 = (uVar3 & 0xff) != ((uint)bRam0026789b & uVar3 & 0xff);
    if (!bVar5) {
      uVar2 = 0;
    }
    bRam0026789b = bRam0026789b | bVar1;
    uVar6 = bRam00267822 + uVar2;
    puVar4 = (undefined1 *)0x267822;
  }
  else if (param_1 == 'p') {
    bVar5 = (uVar3 & 0xff) != ((uint)bRam0026789a & uVar3 & 0xff);
    if (!bVar5) {
      uVar2 = 0;
    }
    bRam0026789a = bRam0026789a | bVar1;
    uVar6 = bRam00267821 + uVar2;
    puVar4 = (undefined1 *)0x267821;
  }
  else if (param_1 == 'o') {
    bVar5 = (uVar3 & 0xff) != ((uint)bRam00267899 & uVar3 & 0xff);
    if (!bVar5) {
      uVar2 = 0;
    }
    bRam00267899 = bRam00267899 | bVar1;
    uVar6 = bRam00267820 + uVar2;
    puVar4 = (undefined1 *)0x267820;
  }
  else if (param_1 == '\x12') {
    bVar5 = (uVar3 & 0xff) != ((uint)bRam00267898 & uVar3 & 0xff);
    if (!bVar5) {
      uVar2 = 0;
    }
    bRam00267898 = bRam00267898 | bVar1;
    uVar6 = bRam00267818 + uVar2;
    puVar4 = (undefined1 *)0x267818;
  }
  if (uVar6 < 0xff) {
    *puVar4 = (char)uVar6;
  }
  else {
    *puVar4 = 0xff;
  }
  return bVar5;
}

