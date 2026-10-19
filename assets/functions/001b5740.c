
void FUN_001b5740(uint *param_1)

{
  if (((*param_1 & 0x80) != 0x80) && ((*param_1 & 2) != 2)) {
    if (cRam00267834 != '\x04') {
      if (((cRam00267834 == '\x03') || (cRam00267834 == '\x02')) || (cRam00267834 == '\x01')) {
        if ((*param_1 & 4) == 4) {
          *param_1 = *param_1 & 0xfffffffb;
        }
        *param_1 = *param_1 | 8;
      }
      else if (cRam00267834 == '\0') {
        if ((*param_1 & 8) == 8) {
          *param_1 = *param_1 & 0xfffffff7;
        }
        else if ((*param_1 & 4) != 4) {
          *param_1 = *param_1 | 4;
        }
      }
    }
    *param_1 = *param_1 | 0x80;
  }
  return;
}

