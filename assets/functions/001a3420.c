
undefined4 FUN_001a3420(byte param_1)

{
  bool bVar1;
  uint uVar2;
  long lVar3;
  int iVar4;
  
  FUN_00153ef0();
  bRam00267968 = param_1;
  FUN_00116978(0x85a340,0xffff,0x1a);
  bRam00267980 = *(byte *)((uint)bRam00267968 + (uint)bRam00267964 * 2 + 0x243fe0);
  for (iVar4 = 0; iVar4 < (int)(uint)bRam00267980; iVar4 = iVar4 + 1) {
    *(short *)(iVar4 * 2 + 0x85a340) =
         (short)iVar4 + *(short *)((uint)bRam00267968 * 2 + (uint)bRam00267964 * 4 + 0x243fc0);
    *(short *)(iVar4 * 2 + 0x85a360) =
         (short)iVar4 + *(short *)((uint)bRam00267968 * 2 + (uint)bRam00267964 * 4 + 0x243ff0);
    *(undefined *)(iVar4 + 0x85a380) =
         (&PTR_DAT_00244230)[(uint)bRam00267964 * 2 + (uint)bRam00267968][iVar4];
    *(undefined2 *)(iVar4 * 2 + 0x85a390) =
         *(undefined2 *)
          ((&PTR_DAT_00244190)[(uint)bRam00267964 * 2 + (uint)bRam00267968] + iVar4 * 2);
  }
  if (bRam00267968 == 0) {
    if (bRam00267964 == 5) {
      if (((bRam002678c8 & 1) == 1) || ((bRam002678c8 & 0x20) == 0x20)) {
        bRam00267980 = bRam00267980 - 1;
        sRam0085a340 = sRam0085a342;
        uRam0085a360 = uRam0085a362;
        bRam0085a380 = bRam0085a381;
        uRam0085a390 = uRam0085a392;
      }
      if (((bRam002678c8 & 2) == 2) || ((bRam002678c8 & 0x40) == 0x40)) {
        bRam00267980 = bRam00267980 - 1;
      }
      if (bRam00267980 == 0) {
        return 0;
      }
    }
    else if (bRam00267964 != 6) {
      if (bRam00267964 == 2) {
        bVar1 = (uRam00267848 & 0x10) == 0x10;
        if (bVar1) {
          bRam00267980 = bRam00267980 - 1;
          FUN_001167c0(0x85a340,0x85a342,(uint)bRam00267980 << 1);
          FUN_001167c0(0x85a360,0x85a362,(uint)bRam00267980 << 1);
          FUN_001167c0(0x85a380,0x85a381,bRam00267980);
          FUN_001167c0(0x85a390,0x85a392,(uint)bRam00267980 << 1);
        }
        uVar2 = (uint)bVar1;
        if ((uRam00267848 & 0x20) == 0x20) {
          bRam00267980 = bRam00267980 - 1;
          uVar2 = (uint)bVar1;
          FUN_001167c0((1 - uVar2) * 2 + 0x85a340,(2 - uVar2) * 2 + 0x85a340,(uint)bRam00267980 << 1
                      );
          FUN_001167c0((1 - uVar2) * 2 + 0x85a360,(2 - uVar2) * 2 + 0x85a360,(uint)bRam00267980 << 1
                      );
          FUN_001167c0(0x85a381 - uVar2,0x85a382 - uVar2,bRam00267980);
          FUN_001167c0((1 - uVar2) * 2 + 0x85a390,(2 - uVar2) * 2 + 0x85a390,(uint)bRam00267980 << 1
                      );
          uVar2 = uVar2 + 1;
        }
        if ((uRam00267848 & 1) == 1) {
          bRam00267980 = bRam00267980 - 1;
          FUN_001167c0((3 - uVar2) * 2 + 0x85a340,(4 - uVar2) * 2 + 0x85a340,(bRam00267980 - 1) * 2)
          ;
          FUN_001167c0((3 - uVar2) * 2 + 0x85a360,(4 - uVar2) * 2 + 0x85a360,(bRam00267980 - 1) * 2)
          ;
          FUN_001167c0(0x85a383 - uVar2,0x85a384 - uVar2,bRam00267980 - 1);
          FUN_001167c0((3 - uVar2) * 2 + 0x85a390,(4 - uVar2) * 2 + 0x85a390,(bRam00267980 - 1) * 2)
          ;
          uVar2 = uVar2 + 1;
        }
        lVar3 = FUN_00149660(0,0x87);
        if (((lVar3 == 0) || ((uRam00267848 & 0x4000) == 0x4000)) ||
           ((uRam00267848 & 0x8000) == 0x8000)) {
          bRam00267980 = bRam00267980 - 1;
          FUN_001167c0((4 - uVar2) * 2 + 0x85a340,(5 - uVar2) * 2 + 0x85a340,(bRam00267980 - 1) * 2)
          ;
          FUN_001167c0((4 - uVar2) * 2 + 0x85a360,(5 - uVar2) * 2 + 0x85a360,(bRam00267980 - 1) * 2)
          ;
          FUN_001167c0(0x85a384 - uVar2,0x85a385 - uVar2,bRam00267980 - 1);
          FUN_001167c0((4 - uVar2) * 2 + 0x85a390,(5 - uVar2) * 2 + 0x85a390,(bRam00267980 - 1) * 2)
          ;
        }
        lVar3 = FUN_00149660(0,0x80);
        if (((lVar3 == 0) || (lVar3 = FUN_00149660(0,0x82), lVar3 != 0)) ||
           (lVar3 = FUN_0016be80(0x4d), lVar3 != 0)) {
          bRam00267980 = bRam00267980 - 1;
        }
      }
      else if ((bRam00267964 == 1) &&
              ((((1 < bRam0085a2f7 || (lVar3 = FUN_00149940(0x25), lVar3 != 0)) ||
                ((lVar3 = FUN_00149940(0x23), lVar3 == 0 || (lVar3 = FUN_0016be80(0x4f), lVar3 != 0)
                 ))) || ((((bRam002677b8 & 8) == 8 &&
                          (((bRam002677b8 & 8) != 8 || (cRam002677ba != '\x04')))) &&
                         (((bRam002677b8 & 8) != 8 || (cRam002677b9 != -2)))))))) {
        bRam00267980 = bRam00267980 - 1;
      }
    }
  }
  sRam00267970 = sRam0085a340;
  sRam0026796c = sRam0085a340;
  bRam00267974 = 0;
  FUN_001a4540();
  FUN_001a4540(1);
  FUN_001a4540(2);
  FUN_001a4630();
  FUN_001a4630(1);
  FUN_001a4630(2);
  FUN_001a4af0(0,sRam00267970);
  if (1 < bRam00267980) {
    FUN_001a4af0(1,sRam00267970 + 1);
  }
  if (2 < bRam00267980) {
    FUN_001a4af0(2,sRam00267970 + 2);
  }
  FUN_0015cd00(0,0x434c0000,0x47c34e80,3);
  FUN_0015cd00(0,0x42a00000,0x47c34e80,4);
  if (3 < bRam00267980) {
    FUN_0015c550(4);
  }
  FUN_0015cd00(0xc3880000,0x43200000,0x47c34e80,5);
  FUN_0015c550(5);
  bRam00267978 = 0;
  FUN_00152ed0(0,0x1786000,0x1785000);
  if (bRam00267968 == 0) {
    lVar3 = FUN_0016bc20(bRam0085a380,1);
    if (lVar3 == 0) {
      if (bRam00267964 == 5) {
        if (((bRam002678c8 & 0x20) == 0x20) || ((bRam002678c8 & 0x40) == 0x40)) {
          FUN_00152f40(0,0x114,0x4220,5);
        }
        else if ((bRam0085a380 == 0xfe) && ((uRam00859fe0 & 1) != 1)) {
          FUN_00152f40(0,0x115,0x4220,5);
        }
        else {
          FUN_00152f40(0,*(undefined2 *)(((uint)bRam00267974 + (uint)bRam00267978) * 2 + 0x85a360),
                       0x4220,5);
        }
      }
      else {
        FUN_00152f40(0,*(undefined2 *)((uint)bRam00267968 * 2 + (uint)bRam00267964 * 4 + 0x244010),
                     0x4220,5);
      }
    }
    else {
      FUN_00152f40(0,*(undefined2 *)(((uint)bRam00267974 + (uint)bRam00267978) * 2 + 0x85a360),
                   0x4220,5);
    }
  }
  else if ((bRam00267964 == 6) && (bRam00267968 == 1)) {
    iVar4 = 0;
    while ((iVar4 < 5 &&
           (((((*(uint *)(iVar4 * 0x20 + 0x859f20) & 1) != 1 ||
              ((*(uint *)(iVar4 * 0x20 + 0x859f20) & 0x800) == 0x800)) ||
             ((*(uint *)(iVar4 * 0x20 + 0x859f20) & 0x1000) == 0x1000)) ||
            ((*(uint *)(iVar4 * 0x20 + 0x859f20) & 2) == 2))))) {
      iVar4 = iVar4 + 1;
    }
    if (iVar4 == 5) {
      iVar4 = 0;
      while ((iVar4 < 5 && ((*(uint *)(iVar4 * 0x20 + 0x859f20) & 1) != 1))) {
        iVar4 = iVar4 + 1;
      }
      if (iVar4 == 5) {
        FUN_00152f40(0,uRam0024402a,0x4220,5);
      }
      else {
        FUN_00152f40(0,0x117,0x4220,5);
      }
    }
  }
  else if (*(char *)(bRam0085a380 + 0x85a2a0) == '\0') {
    FUN_00152f40(0,*(undefined2 *)((uint)bRam00267968 * 2 + (uint)bRam00267964 * 4 + 0x244010),
                 0x4220,5);
  }
  else {
    FUN_00152f40(0,*(undefined2 *)(((uint)bRam00267974 + (uint)bRam00267978) * 2 + 0x85a360),0x4220,
                 5);
  }
  if (((bRam00267964 != 5) || (bRam00267968 != 0)) && ((bRam00267964 != 6 || (bRam00267968 != 1))))
  {
    uRam0026797c = 0;
    FUN_00159ce0(0,0x32e,0xd3e,0x1ad5000);
    FUN_0015a0e0(0xc3700000,0xc2400000,0x47c34000);
    if (((bRam00267964 == 3) || (bRam00267964 == 4)) && (bRam00267968 == 0)) {
      FUN_0015a6b0(0x3f800000,0,bRam0085a380,1);
      FUN_0015a0e0(0xc3600000,0xc2400000,0x47c34000);
    }
    else {
      if (((bRam00267964 == 2) && (bRam00267968 == 0)) && (bRam0085a380 != 0x25)) {
        FUN_0015a0e0(0xc3600000,0xc2600000,0x47c34000);
      }
      FUN_0015a290(0x3f800000,0,bRam0085a380,1);
    }
    FUN_0015aab0();
  }
  return 1;
}

