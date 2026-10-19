
void FUN_001b58b0(void)

{
  if (((uRam00859fe0 & 0x80) != 0x80) && ((uRam00859fe0 & 2) != 2)) {
    if (cGpffff8944 != '\x04') {
      if (((cGpffff8944 == '\x03') || (cGpffff8944 == '\x02')) || (cGpffff8944 == '\x01')) {
        if ((uRam00859fe0 & 4) == 4) {
          uRam00859fe0 = uRam00859fe0 & 0xfffffffb;
        }
        uRam00859fe0 = uRam00859fe0 | 8;
      }
      else if (cGpffff8944 == '\0') {
        if ((uRam00859fe0 & 8) == 8) {
          uRam00859fe0 = uRam00859fe0 & 0xfffffff7;
        }
        else if ((uRam00859fe0 & 4) != 4) {
          uRam00859fe0 = uRam00859fe0 | 4;
        }
      }
    }
    uRam00859fe0 = uRam00859fe0 | 0x80;
  }
  return;
}

