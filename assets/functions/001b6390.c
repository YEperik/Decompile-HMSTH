
void FUN_001b6390(char param_1)

{
  FUN_001b6240();
  if (cRam0085a003 != -1) {
    cRam0085a003 = cRam0085a003 + '\x01';
  }
  if ((uRam00859fe0 & 0x40) != 0x40) {
    if (param_1 != -1) {
      if ((((param_1 == '\x14') || (param_1 == '\x13')) || (param_1 == '\x12')) ||
         (((param_1 == '\t' || (param_1 == '\b')) || ((param_1 == '\a' || (param_1 == '\x06')))))) {
        if (bRam00859ffa < 0xfd) {
          bRam00859ffa = bRam00859ffa + 2;
        }
        else {
          bRam00859ffa = 0xff;
        }
      }
      else if (((param_1 != '@') && (param_1 != 'A')) &&
              ((param_1 != '9' && ((param_1 != 'H' && (param_1 != '?')))))) {
        if (bRam00859ffa < 0xfe) {
          bRam00859ffa = bRam00859ffa + 1;
        }
        else {
          bRam00859ffa = 0xff;
        }
      }
    }
    uRam00859fe0 = uRam00859fe0 | 0x60;
  }
  if ((((((uRam00859fe0 & 1) == 1) && ((uRam00859fe0 & 0x100) != 0x100)) &&
       ((uRam00859fe0 & 2) != 2)) &&
      (((uRam00859fe0 & 0x40000) != 0x40000 && (cRam00835056 != '\r')))) &&
     ((cRam00835056 != '\x0e' && (cRam00835056 != '\x0f')))) {
    if ((uRam00859fe0 & 0x20000000) == 0x20000000) {
      uRam00267788 = 2;
      FUN_001c9020();
    }
    else {
      FUN_0013e2a0(0x10);
      uRam00859fe0 = uRam00859fe0 & 0xffffbfff | 0x40000;
      FUN_001b9230(0xc499c000,0,0x451c4000);
    }
  }
  return;
}

