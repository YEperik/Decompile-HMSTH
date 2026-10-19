
void FUN_001b20c0(void)

{
  long lVar1;
  
  lVar1 = FUN_0021a800(uRam00267734);
  if (lVar1 == 0) {
    if (cRam00267988 == '\0') {
      FUN_00219830(1);
      FUN_00219830(2);
      FUN_00219830(3);
    }
    FUN_002199f0();
    FUN_0021b280();
    FUN_001fad00(uRam0026771c,uRam00267720,0x17);
    cRam00267988 = '\x01';
    uRam00267778 = uRam00267734;
  }
  return;
}

