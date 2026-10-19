
void FUN_001c1a90(void)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  char acStack_10 [6];
  undefined1 uStack_a;
  undefined1 uStack_9;
  char acStack_4 [4];
  
  uVar3 = 0xffff;
  switch(cRam00859ffb) {
  case '\x01':
    uVar3 = 0x33;
    builtin_strncpy(acStack_4,"\b\x04\x04\x04",4);
    break;
  case '\x02':
    uVar3 = 0x47;
    builtin_strncpy(acStack_4,"\f\x06\x06\x06",4);
    break;
  case '\x03':
    uVar3 = 0x60;
    builtin_strncpy(acStack_4,"\x10\b\b\b",4);
    break;
  case '\x04':
    uVar3 = 0x7e;
    builtin_strncpy(acStack_4,"\x14\n\n\n",4);
    break;
  case '\x05':
    uVar3 = 0xa1;
    builtin_strncpy(acStack_4,"\x18\f\f\f",4);
    break;
  case '\x06':
    uVar3 = 0xc9;
    builtin_strncpy(acStack_4,"\x1c\x0e\x0e\x0e",4);
    break;
  case '\a':
    uVar3 = 0xff;
    builtin_strncpy(acStack_4," \x10\x10\x10",4);
  }
  if (uVar3 <= bRam00859ffa) {
    cRam00859ffb = cRam00859ffb + '\x01';
    acStack_10[0] = '\0';
    acStack_10[1] = uRam00859ffd;
    acStack_10[2] = 1;
    acStack_10[3] = uRam00859fff;
    acStack_10[4] = 2;
    acStack_10[5] = uRam0085a001;
    uStack_a = 3;
    uStack_9 = uRam0085a003;
    for (bVar2 = 0; bVar2 < 4; bVar2 = bVar2 + 1) {
      for (uVar3 = 0; uVar3 < 3; uVar3 = uVar3 + 1 & 0xff) {
        if ((byte)acStack_10[uVar3 * 2 + 1] < (byte)acStack_10[(uVar3 + 1) * 2 + 1]) {
          cVar1 = acStack_10[uVar3 * 2];
          acStack_10[uVar3 * 2] = acStack_10[(uVar3 + 1) * 2];
          acStack_10[(uVar3 + 1) * 2] = cVar1;
          cVar1 = acStack_10[uVar3 * 2 + 1];
          acStack_10[uVar3 * 2 + 1] = acStack_10[(uVar3 + 1) * 2 + 1];
          acStack_10[(uVar3 + 1) * 2 + 1] = cVar1;
        }
      }
    }
    for (uVar3 = 0; uVar3 < 4; uVar3 = uVar3 + 1 & 0xff) {
      cVar1 = acStack_10[uVar3 * 2];
      if (cVar1 == '\x03') {
        cRam0085a002 = cRam0085a002 + acStack_4[uVar3];
      }
      else if (cVar1 == '\x02') {
        cRam0085a000 = cRam0085a000 + acStack_4[uVar3];
      }
      else if (cVar1 == '\x01') {
        cRam00859ffe = cRam00859ffe + acStack_4[uVar3];
      }
      else if (cVar1 == '\0') {
        cRam00859ffc = cRam00859ffc + acStack_4[uVar3];
      }
    }
    uRam00859ffd = 0;
    uRam00859fff = 0;
    uRam0085a001 = 0;
    uRam0085a003 = 0;
  }
  return;
}

