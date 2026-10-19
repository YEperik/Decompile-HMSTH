
void FUN_001c7780(byte param_1)

{
  char cVar1;
  long lVar2;
  
  cVar1 = *(char *)((uint)param_1 * 8 + 0x859935);
  if (cVar1 == '\x02') {
    lVar2 = FUN_0013a2c0(*(ushort *)((uint)param_1 * 8 + 0x859932) & 0xff);
    if (lVar2 == 0) {
      FUN_001c7510(param_1);
    }
  }
  else if (cVar1 == '\x01') {
    cVar1 = *(char *)((uint)param_1 * 8 + 0x859936);
    *(char *)((uint)param_1 * 8 + 0x859936) = cVar1 + -1;
    if (cVar1 == '\x01') {
      FUN_00139920(*(ushort *)((uint)param_1 * 8 + 0x859932) & 0xff,2);
      *(undefined1 *)((uint)param_1 * 8 + 0x859935) = 2;
    }
  }
  else if ((cVar1 == '\0') &&
          (lVar2 = FUN_0013a2c0(*(ushort *)((uint)param_1 * 8 + 0x859932) & 0xff), lVar2 == 0)) {
    FUN_00139920(*(ushort *)((uint)param_1 * 8 + 0x859932) & 0xff,1);
    *(undefined1 *)((uint)param_1 * 8 + 0x859936) = 0x3c;
    *(undefined1 *)((uint)param_1 * 8 + 0x859935) = 1;
  }
  return;
}

