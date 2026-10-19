
void FUN_001a9ff0(void)

{
  char cVar1;
  ushort uVar2;
  long lVar3;
  ushort uVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [12];
  undefined4 uStack_4;
  
  lVar3 = FUN_00167620();
  if ((lVar3 == 0) && (lVar3 = FUN_0021a800(bGpffff8844), lVar3 == 0)) {
    if (((bGpffff8844 == bGpffff89d4) || ((bGpffff89d4 == 0x1a || (bGpffff8844 == 0x1a)))) &&
       ((cGpffff89d0 == '\x01' || ((cGpffff89d0 == '\n' || (cGpffff89d0 == '\v')))))) {
      FUN_001856e0();
      FUN_0014f900(&uStack_30);
      FUN_00137ae0(uStack_30,uStack_2c,uStack_28);
      if (cGpffff89d0 == '\n') {
        FUN_00148e20(auStack_20,0x17a9280,0x3b,0x8d800,0xbc500);
        uRam0083d020 = uRam00834058;
      }
      else if (cGpffff89d0 == '\v') {
        FUN_00148e20(auStack_10,0x180b280,0x3b,0x8d800,0xbc500);
      }
      bGpffff8844 = bGpffff89d4;
      for (uVar6 = 1; (int)uVar6 < 0x10; uVar6 = uVar6 + 1) {
        if ((((bGpffff8844 == 0x19) || (bGpffff8844 == 0x1a)) || (bGpffff8844 == 0x1b)) ||
           (bGpffff8844 == 0x18)) {
          FUN_00214320(uVar6 & 0xff);
        }
      }
      FUN_00166d90(0x1e,1);
      FUN_0013a0b0(0,1);
      cGpffff89d0 = '\0';
      FUN_002199d0();
      FUN_0021a400();
      FUN_00179c80();
    }
    else if (cGpffff89d0 == '\x01') {
      FUN_0014e620();
      FUN_0014e740();
      FUN_0013f0c0(0,uRam00834120);
      for (uVar6 = 0; (int)uVar6 < 0x80; uVar6 = uVar6 + 1) {
        if (((uVar6 != 0) && ((uVar6 != 0x11 || ((uRam00834050 & 0x80) != 0x80)))) &&
           ((uVar6 != bGpffff884c || ((uRam00834050 & 0x400) != 0x400)))) {
          FUN_001376f0(uVar6 & 0xff);
        }
      }
      FUN_00208d00(uVar6);
      FUN_001ff950();
      cGpffff89d0 = '\x02';
    }
    else if (cGpffff89d0 == '\x02') {
      FUN_0014d170(bGpffff89d4);
      uStack_4 = FUN_00141880();
      FUN_0013a3e0(0,uStack_4,0,uStack_4);
      FUN_00139c00();
      FUN_0013a0b0(0,1);
      if ((uRam00834050 & 0x80) == 0x80) {
        uStack_4 = FUN_00141880(0x11);
        FUN_0013a3e0(0,uStack_4,0,uStack_4,0x11);
        FUN_00139c00(0x11);
        FUN_0013a0b0(0x11,1);
      }
      if (((uRam00834050 & 0x400) == 0x400) &&
         (((cGpffff8950 == 's' || (cGpffff8950 == 't')) || (cGpffff8950 == 'u')))) {
        FUN_00139c00(bGpffff884c);
        FUN_0013a0b0(bGpffff884c,1);
        if (cGpffff8950 == 's') {
          bRam0085a004 = bGpffff8844;
        }
        else if (cGpffff8950 == 't') {
          *(byte *)((bGpffff884c - 0x1b) * 0x20 + 0x859e69) = bGpffff8844;
        }
      }
      FUN_0014f900(&uStack_30);
      if ((uRam00834050 & 0x80) == 0x80) {
        FUN_00137ae0(uStack_30,uStack_2c,uStack_28,0x11);
      }
      else {
        FUN_00137ae0(uStack_30,uStack_2c,uStack_28);
      }
      FUN_0014e450();
      cGpffff89d0 = '\0';
      FUN_001c3f40();
      uGpffff8894 = 0;
      uGpffff8890 = 0;
      uGpffff888c = 0;
      uGpffff8898 = 0;
      uRam00859fe0 = uRam00859fe0 & 0xbfffffff;
      uRam00859fc0 = uRam00859fc0 & 0xbfffffff;
      FUN_0017c050();
      if (cGpffff8846 == '\x15') {
        uRam0083d020 = uRam00834058;
      }
      cVar1 = '\0';
      if (bGpffff8888 != bGpffff8844) {
        cVar1 = FUN_00170db0();
      }
      bGpffff8888 = 0xff;
      if (cVar1 == '\0') {
        FUN_00185ad0();
        if ((uRam00834050 & 0x80) == 0x80) {
          FUN_001506e0(0x11,cGpffff8846,1);
        }
        else {
          FUN_001506e0(0,cGpffff8846,1);
        }
        if (bGpffff8844 == 0xd) {
          for (iVar7 = 0; iVar7 < 5; iVar7 = iVar7 + 1) {
            if (((*(uint *)(iVar7 * 0x20 + 0x859f20) & 1) == 1) &&
               ((*(uint *)(iVar7 * 0x20 + 0x859f20) & 0x400000) == 0x400000)) {
              puVar5 = (uint *)(iVar7 * 0x20 + 0x859f20);
              *puVar5 = *puVar5 & 0xffbfffff;
              cGpffff89c4 = (char)iVar7 + '\b';
              sGpffff8860 = 0x14;
              break;
            }
          }
        }
        else if (bGpffff8844 == 0xe) {
          for (iVar7 = 0; iVar7 < 6; iVar7 = iVar7 + 1) {
            if (((*(uint *)(iVar7 * 0x20 + 0x859e60) & 1) == 1) &&
               ((*(uint *)(iVar7 * 0x20 + 0x859e60) & 0x2000) == 0x2000)) {
              puVar5 = (uint *)(iVar7 * 0x20 + 0x859e60);
              *puVar5 = *puVar5 & 0xffffdfff;
              cGpffff89c4 = (char)iVar7 + '\x0f';
              sGpffff8860 = 0x14;
              break;
            }
          }
        }
        if (sGpffff8860 != 0x14) {
          FUN_00166d90(0x1e,1);
          if (bGpffff8844 < 0xb) {
            FUN_00164680();
          }
          if (((bGpffff89dc & 8) != 8) || (bGpffff8844 != 7)) {
            FUN_00207cb0();
          }
          FUN_00179c80();
        }
        FUN_002199d0();
        FUN_00219a60(bGpffff8844);
        FUN_0021a400();
      }
      else {
        uGpffff885c = uGpffff885c & 0xfbff;
        if (bGpffff8844 == 4) {
          FUN_0014e740();
          FUN_0014d170(4);
          FUN_0014e450();
        }
        if ((sGpffff882c == 0xf) && ((sGpffff8830 == 0x24 || (sGpffff8830 == 0x27)))) {
          FUN_0017c050();
        }
        FUN_0015e770(0x1a);
      }
    }
    else {
      if ((((bGpffff89dc & 2) == 2) || (bGpffff8844 == 0xd)) || (bGpffff8844 == 0x1d)) {
        FUN_00126ea0(1);
      }
      uVar2 = uGpffff885c & 0xfbff;
      uVar4 = uGpffff885c & 0x200;
      uGpffff885c = uVar2;
      if (uVar4 == 0x200) {
        FUN_001369a0(0,0x43200000,0x44400000,0x3e4ccccd);
        sGpffff8860 = 3;
        if ((uRam00834050 & 0x80) == 0x80) {
          FUN_0013a620(0x11,1,1);
        }
        else {
          FUN_0013a620(0,1,1);
        }
        uGpffff885c = uGpffff885c & 0xfdff;
      }
      if ((uRam00834050 & 0x80) != 0x80) {
        FUN_0013a620(0,1,1);
      }
      FUN_00138ce0();
      FUN_0015e770(uGpffff89e0);
      if (((bGpffff89dc & 8) == 8) && (bGpffff8844 == 7)) {
        sGpffff8860 = 0x18;
      }
      else {
        FUN_001612e0();
      }
    }
  }
  return;
}

