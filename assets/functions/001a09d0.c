
void FUN_001a09d0(void)

{
  char cVar1;
  undefined8 uVar2;
  long lVar3;
  
  cVar1 = FUN_0013a2c0();
  switch(uGpffff8a5c) {
  case 0:
    FUN_00139920(0,6);
    uGpffff8a5c = 1;
    break;
  case 1:
    if (cVar1 == '\0') {
      uVar2 = FUN_001854b0(cGpffff895c);
      FUN_0016cc90(uVar2,0x20);
      if (cGpffff895c == 'm') {
        uGpffff8a5c = 3;
      }
      else {
        uGpffff8a5c = 2;
      }
    }
    else {
      lVar3 = FUN_00123d10(uRam00834058);
      if (lVar3 != 0) {
        FUN_0014bd30(cGpffff895c);
        FUN_0013b4e0(0,0x27,cGpffff895c);
        FUN_0013cae0();
        if (cGpffff895c == 'n') {
          FUN_0013fae0(0,0x38,2,0,0,0);
        }
      }
    }
    break;
  case 2:
    lVar3 = FUN_001536f0();
    if (lVar3 == 0) {
      if (cGpffff895c == 'n') {
        FUN_00139920(0,0x12);
        FUN_0013d410();
        uGpffff8a5c = 5;
      }
      else {
        uGpffff8a5c = 0xff;
      }
    }
    break;
  case 3:
    lVar3 = FUN_001536f0();
    if (lVar3 == 0) {
      FUN_0013ea60();
      FUN_00139920(0,0xe);
      uGpffff8a5c = 4;
    }
    break;
  case 4:
    if (cVar1 == '\0') {
      FUN_0013e710();
      uGpffff8a5c = 0xff;
    }
    else {
      lVar3 = FUN_00123d10(uRam00834058);
      if (lVar3 != 0) {
        if ((cGpffff8844 == '\0') || (cGpffff8844 == '\x01')) {
          FUN_00178b90(1);
        }
        else {
          FUN_00178b90(4);
        }
        FUN_0013c060();
        FUN_0014c0c0();
      }
    }
    break;
  case 5:
    if (cVar1 == '\0') {
      FUN_0016bff0(cGpffff895c,1);
      uGpffff8a5c = 0xff;
    }
    break;
  default:
    FUN_00138ce0();
    uGpffff8a5c = 0;
    cGpffff895c = -1;
    uGpffff8860 = 0;
  }
  return;
}

