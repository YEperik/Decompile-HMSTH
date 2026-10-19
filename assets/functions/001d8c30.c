
undefined4 FUN_001d8c30(void)

{
  undefined4 uVar1;
  long lVar2;
  
  if ((*(short *)(iGpffff8af8 + 0x10e) < 0x61) && (*(char *)(iGpffff8af8 + 0x10d) != '\x02')) {
    lVar2 = FUN_00148df0(0,(int)(((3 - (uint)*(byte *)(iGpffff8af8 + 7)) * 0x20 & 0xffff) +
                                (((0x60 - *(short *)(iGpffff8af8 + 0x10e)) * 2) / 3 & 0xffffU)) >> 5
                        );
    if (lVar2 == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

