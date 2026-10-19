
void FUN_001bf620(char param_1)

{
  byte bVar1;
  
  if (param_1 == '\0') {
    bVar1 = cRam002679a0 + 1;
    cRam002679a0 = cRam002679a0 + '\x01';
    if (bVar1 < 4) {
      cRam0026782c = cRam0026782c + '\x02';
      cRam002679a0 = '\x04';
    }
  }
  else {
    bVar1 = cRam002679a4 + 1;
    cRam002679a4 = cRam002679a4 + '\x01';
    if (bVar1 < 4) {
      cRam00267828 = cRam00267828 + '\x02';
      cRam002679a4 = '\x04';
    }
  }
  uRam00859fe0 = uRam00859fe0 | 0x80000;
  uRam0085a004 = uRam00267734;
  uRam00267994 = 0;
  return;
}

