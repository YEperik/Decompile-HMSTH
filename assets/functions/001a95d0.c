
void FUN_001a95d0(void)

{
  long lVar1;
  
  switch(uRam00267750) {
  case 0:
    FUN_0018d850();
    goto LAB_001a98b0;
  case 1:
    uRam00267750 = 0;
    goto LAB_001a98b0;
  case 2:
    lVar1 = FUN_00126990();
    if ((lVar1 == 0) && (lVar1 = FUN_001269c0(), lVar1 == 0)) {
      uRam00267750 = 0;
    }
    goto LAB_001a98b0;
  case 3:
    lVar1 = FUN_001268f0();
    if (lVar1 == 0) {
      FUN_00126750(0x3f800000);
      uRam00267750 = 0;
    }
    goto LAB_001a98b0;
  case 4:
    FUN_00190880();
    goto LAB_001a98b0;
  case 5:
    FUN_0019bda0();
    break;
  case 6:
    FUN_001dd330();
    break;
  case 7:
  case 0x1b:
    FUN_0019c970();
    break;
  case 8:
  case 0x1c:
    FUN_0019caa0();
    break;
  case 9:
    FUN_0019cbf0();
    break;
  case 10:
    FUN_0019cfd0();
    break;
  case 0xb:
    FUN_0019d120();
    break;
  case 0xc:
    FUN_001a1790();
    break;
  case 0xd:
    FUN_0019d6a0();
    break;
  case 0xe:
    FUN_001a64b0();
    break;
  case 0xf:
    FUN_0019d9d0();
    break;
  case 0x10:
    FUN_0019da40();
    break;
  case 0x11:
    FUN_0019dab0();
    break;
  case 0x12:
    FUN_0019db10();
    break;
  case 0x13:
    FUN_0019db70();
    goto LAB_001a98b0;
  case 0x14:
    FUN_0019e700();
    break;
  case 0x15:
    FUN_0019e8b0();
    break;
  case 0x16:
    FUN_0019ea20();
    break;
  case 0x17:
    FUN_0019f0e0();
    break;
  case 0x18:
    FUN_0019f240();
    break;
  case 0x19:
    FUN_0019f450();
    break;
  case 0x1a:
    FUN_0019f5b0();
    break;
  case 0x1d:
    FUN_0019f620();
    break;
  case 0x1e:
  case 0x1f:
    FUN_0019f750();
    break;
  case 0x20:
    FUN_0019f920();
    break;
  case 0x21:
    FUN_0019fbd0();
    break;
  case 0x22:
    FUN_0019fe80();
    break;
  case 0x23:
    FUN_001a06f0();
    break;
  case 0x24:
    FUN_001a0960();
    break;
  case 0x25:
    FUN_001a09d0();
    break;
  case 0x26:
    FUN_001a0cc0();
    break;
  case 0x27:
    FUN_001a0e10();
    break;
  case 0x28:
    FUN_001a0f20();
    break;
  case 0x29:
    FUN_001a1300();
    break;
  default:
    uRam00267750 = 0;
LAB_001a98b0:
    lVar1 = FUN_001536f0();
    if (((lVar1 == 0) && (lVar1 = FUN_0015ee20(), lVar1 == 0)) &&
       (lVar1 = FUN_00167620(), lVar1 == 0)) {
      FUN_00161a80();
    }
  }
  return;
}

