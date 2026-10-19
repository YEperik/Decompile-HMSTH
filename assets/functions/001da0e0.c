
void FUN_001da0e0(void)

{
  undefined1 uVar1;
  
  uVar1 = FUN_001deee0();
  *(undefined1 *)(puRam002679ec + 3) = uVar1;
  *(byte *)(puRam002679ec + 7) = *(char *)(puRam002679ec + 7) + 1U & 0x7f;
  switch(*puRam002679ec) {
  case 1:
    FUN_001d9d70();
    break;
  case 2:
    FUN_001da090();
    break;
  case 3:
    FUN_001da2d0();
    break;
  case 4:
    FUN_001db270();
    break;
  case 5:
    FUN_001da410();
    break;
  case 6:
    FUN_001da5d0();
    break;
  case 7:
    FUN_001da7f0();
    break;
  case 8:
    FUN_001db200();
    break;
  case 9:
    FUN_001da200();
    break;
  case 10:
    FUN_001da240();
  }
  return;
}

