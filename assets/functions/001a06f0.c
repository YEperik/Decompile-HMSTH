
void FUN_001a06f0(void)

{
  char cVar1;
  byte bVar2;
  long lVar3;
  
  lVar3 = FUN_001536f0();
  if ((lVar3 == 0) && (lVar3 = FUN_00167620(), lVar3 == 0)) {
    if (cRam00267948 == '\0') {
      FUN_00167330(0x1e);
      cRam00267948 = '\x01';
    }
    else {
      uRam00267888 = uRam00267888 | 0x4000;
      if ((uRam00834050 & 0x80) == 0x80) {
        FUN_00141f50(0x11);
        FUN_001b24b0();
        FUN_001376f0(0x11);
      }
      cVar1 = cRam0026773c;
      if ((uRam00834050 & 0x400) == 0x400) {
        if (uRam00834054 == 0x73) {
          FUN_0013c060();
          FUN_001b2160();
          FUN_001376f0(0x10);
        }
        else if ((uRam00834054 == 0x74) || (uRam00834054 == 0x75)) {
          FUN_001b21f0(cRam0026773c + -0x1b);
          FUN_0013c060();
          FUN_001376f0(cVar1);
        }
        else {
          FUN_0016bff0(uRam00834054 & 0xff,1);
          FUN_0013c060();
          FUN_001376f0(0x27);
        }
      }
      FUN_0013f0c0(0,0,0,0);
      FUN_0013e710();
      for (bVar2 = 1; bVar2 < 0x80; bVar2 = bVar2 + 1) {
        FUN_001376f0(bVar2);
      }
      FUN_0014e740();
      FUN_0014d170(3);
      FUN_0014e450();
      uRam0026771c = 0x11;
      uRam00267720 = 0x18;
      FUN_00149860(0x4b);
      FUN_0021a780();
      FUN_0015e770(0x1a);
      uRam00267750 = 0;
      cRam00267948 = '\0';
    }
  }
  return;
}

