
undefined4 FUN_001a2500(void)

{
  long lVar1;
  char cVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined1 uStack_8;
  char cStack_7;
  
  FUN_00124180(*(undefined2 *)((uint)bRam0026773c * 0x100 + 0x834058),&uStack_20);
  FUN_0013fae0(0,0x21,2,0,0,0);
  if ((cRam00267734 == '\0') || (cRam00267734 == '\x01')) {
    cVar2 = *(char *)((bRam0026773c - 0x28) * 5 + 0x859c11);
  }
  else {
    if ((cRam00267734 == '\n') && (lVar1 = FUN_00184e70(bRam0026773c), lVar1 != 0)) {
      return 0;
    }
    if (bRam0026773c < 0x3c) {
      cVar2 = *(char *)((uint)*(byte *)(bRam0026773c + 0x859a28) * 5 + 0x859a91);
    }
    else {
      FUN_00182af0(bRam0026773c - 0x3c,&uStack_8);
      cVar2 = cStack_7;
    }
  }
  switch(cVar2) {
  case '\0':
    FUN_001ff4f0(uStack_20,uStack_1c,uStack_18,3,0,uRam00834058);
    uRam00834054 = 0;
    FUN_0014bd30();
    FUN_00180920(0x859c10,bRam0026773c - 0x28,bRam0026773c - 0x28,0xff,0xff);
    break;
  case '\x01':
    uRam00834054 = 1;
    FUN_0014bd30(1);
    FUN_00180ad0(0x859c10,bRam0026773c - 0x28,bRam0026773c - 0x28);
    break;
  case '\x02':
    uRam00834054 = 2;
    FUN_0014bd30(2);
    FUN_00180ad0(0x859c10,bRam0026773c - 0x28,bRam0026773c - 0x28);
    break;
  case '\x03':
    uRam00834054 = 3;
    FUN_0014bd30(3);
    FUN_00180ad0(0x859c10,bRam0026773c - 0x28,bRam0026773c - 0x28);
    break;
  case '\x04':
    uRam00834054 = 0x40;
    FUN_0014bd30(0x40);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\x05':
    uRam00834054 = 0x41;
    FUN_0014bd30(0x41);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\x06':
    uRam00834054 = 10;
    FUN_0014bd30(10);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\a':
    uRam00834054 = 0xc;
    FUN_0014bd30(0xc);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\b':
    uRam00834054 = 0xb;
    FUN_0014bd30(0xb);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\t':
    uRam00834054 = 0xe;
    FUN_0014bd30(0xe);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\n':
    uRam00834054 = 0xf;
    FUN_0014bd30(0xf);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\v':
    uRam00834054 = 0x3f;
    FUN_0014bd30(0x3f);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\f':
    uRam00834054 = 0xd;
    FUN_0014bd30(0xd);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\r':
    uRam00834054 = 0x10;
    FUN_0014bd30(0x10);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
    break;
  case '\x0e':
    uRam00834054 = 0x11;
    FUN_0014bd30(0x11);
    FUN_0017ecc0(bRam0026773c - 0x28,*(undefined1 *)(bRam0026773c + 0x859a28));
  }
  bRam0026773c = 0x27;
  FUN_0013b4e0(0,0x27,uRam00834054 & 0xff);
  if (((cVar2 != '\x01') && (cVar2 != '\x02')) && (cVar2 != '\x03')) {
    FUN_0013cae0();
  }
  return 1;
}

