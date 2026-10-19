
void FUN_001cf970(void)

{
  FUN_001deee0();
  FUN_001d7130();
  FUN_001d7e60();
  *(char *)(puGpffff8af8 + 0xdc) = *(char *)(puGpffff8af8 + 0xdc) + '\x01';
  *(byte *)(puGpffff8af8 + 0xdc) = *(byte *)(puGpffff8af8 + 0xdc) & 0x7f;
  switch(*puGpffff8af8) {
  case 1:
    FUN_001cfb70();
    break;
  case 2:
    FUN_001cfbd0();
    break;
  case 3:
    FUN_001cfe40();
    break;
  case 4:
    FUN_001cff60();
    break;
  case 5:
    FUN_001cffb0();
    break;
  case 6:
    FUN_001d0210();
    break;
  case 7:
    FUN_001d02d0();
    break;
  case 8:
    FUN_001d03a0();
    break;
  case 9:
    FUN_001d0490();
    break;
  case 10:
    FUN_001d0580();
    break;
  case 0xb:
    FUN_001d0910();
    break;
  case 0xc:
    FUN_001d0af0();
    break;
  case 0xd:
    FUN_001d0d00();
    break;
  case 0xe:
    FUN_001d06f0();
    break;
  case 0xf:
    FUN_001d13f0();
    break;
  case 0x10:
    FUN_001d1000();
    break;
  case 0x11:
    FUN_001d1040();
    break;
  case 0x12:
    FUN_001d1090();
    break;
  case 0x13:
    FUN_001d1220();
    break;
  case 0x14:
    FUN_001d13b0();
    break;
  case 0x15:
    FUN_001d0ed0();
    break;
  case 0x16:
    FUN_001d11d0();
    break;
  case 0x17:
    FUN_001d1430();
  }
  FUN_00161a80();
  FUN_001d99b0();
  return;
}

