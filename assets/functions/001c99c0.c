
void FUN_001c99c0(void)

{
  uGpffff8aa4 = 0;
  uRam00859fe0 = uRam00859fe0 & 0xec3cffff | 0x4000;
  if ((bRam00859ffa < 0x1f) || (0x50 < bRam00859ffa)) {
    if ((bRam00859ffa < 0x51) || (0x8c < bRam00859ffa)) {
      if ((bRam00859ffa < 0x8d) || (200 < bRam00859ffa)) {
        if (200 < bRam00859ffa) {
          uRam00859ff0 = 0x47070000;
        }
      }
      else {
        uRam00859ff0 = 0x46870000;
      }
    }
    else {
      uRam00859ff0 = 0x46070000;
    }
  }
  else {
    uRam00859ff0 = 0x45870000;
  }
  if (cRam00859ffd != -1) {
    cRam00859ffd = cRam00859ffd + '\x01';
  }
  return;
}

