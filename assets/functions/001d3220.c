
undefined4 FUN_001d3220(byte param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if ((((&DAT_00244711)[(uint)param_1 * 0x14] == '\x01') && (cRam00267844 != '[')) &&
     (cRam00267844 != '\\')) {
    uVar1 = 0;
  }
  else if (((&DAT_00244711)[(uint)param_1 * 0x14] == '\x02') && (cRam00267844 != '\\')) {
    uVar1 = 0;
  }
  else {
    if (param_1 == 8) {
      if ((bRam0026785c & 4) == 4) {
        return 0;
      }
    }
    else if (param_1 == 7) {
      if ((bRam0026785c & 2) == 2) {
        return 0;
      }
      lVar2 = FUN_00148df0(0,0x10);
      if (lVar2 != 0) {
        return 0;
      }
    }
    else if (param_1 == 6) {
      if ((bRam0026785c & 1) == 1) {
        return 0;
      }
    }
    else {
      if (param_1 != 2) {
        return 1;
      }
      if ((bRam00267860 & 2) == 2) {
        return 0;
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

