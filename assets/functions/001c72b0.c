
void FUN_001c72b0(undefined1 *param_1,undefined2 *param_2,undefined2 *param_3)

{
  *param_1 = 0xff;
  if ((bRam002679c0 & 1) == 1) {
    if ((bRam002679c0 & 2) == 2) {
      if ((bRam002679c0 & 4) == 4) {
        if ((bRam002679c0 & 8) == 8) {
          if ((bRam002679c0 & 0x10) == 0x10) {
            if ((bRam002679c0 & 0x20) != 0x20) {
              *param_1 = 0x26;
              *param_2 = 0x102;
              *param_3 = 0x72c;
              bRam002679c0 = bRam002679c0 | 0x20;
            }
          }
          else {
            *param_1 = 0x25;
            *param_2 = 0xfe;
            *param_3 = 0x714;
            bRam002679c0 = bRam002679c0 | 0x10;
          }
        }
        else {
          *param_1 = 0x24;
          *param_2 = 0xfa;
          *param_3 = 0x6fc;
          bRam002679c0 = bRam002679c0 | 8;
        }
      }
      else {
        *param_1 = 0x23;
        *param_2 = 0xf6;
        *param_3 = 0x6e4;
        bRam002679c0 = bRam002679c0 | 4;
      }
    }
    else {
      *param_1 = 0x22;
      *param_2 = 0xf2;
      *param_3 = 0x6cc;
      bRam002679c0 = bRam002679c0 | 2;
    }
  }
  else {
    *param_1 = 0x21;
    *param_2 = 0xee;
    *param_3 = 0x6b4;
    bRam002679c0 = bRam002679c0 | 1;
  }
  return;
}

