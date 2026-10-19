
void FUN_001c7510(byte param_1)

{
  switch(*(undefined2 *)((uint)param_1 * 8 + 0x859932)) {
  case 0x21:
    bRam002679c0 = bRam002679c0 & 0xfe;
    break;
  case 0x22:
    bRam002679c0 = bRam002679c0 & 0xfd;
    break;
  case 0x23:
    bRam002679c0 = bRam002679c0 & 0xfb;
    break;
  case 0x24:
    bRam002679c0 = bRam002679c0 & 0xf7;
    break;
  case 0x25:
    bRam002679c0 = bRam002679c0 & 0xef;
    break;
  case 0x26:
    bRam002679c0 = bRam002679c0 & 0xdf;
  }
  FUN_001376f0(*(ushort *)((uint)param_1 * 8 + 0x859932) & 0xff);
  *(undefined1 *)((uint)param_1 * 8 + 0x859930) = 0;
  *(undefined1 *)((uint)param_1 * 8 + 0x859936) = 0;
  *(undefined1 *)((uint)param_1 * 8 + 0x859935) = 0;
  *(undefined2 *)((uint)param_1 * 8 + 0x859932) = 0xff;
  return;
}

