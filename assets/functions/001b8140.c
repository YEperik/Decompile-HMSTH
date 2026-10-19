
void FUN_001b8140(short param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint *puVar4;
  short *psVar5;
  uint uVar6;
  
  if ((bRam002678cc & 4) == 4) {
    if (((uRam00859fe0 & 1) == 1) && (bRam0085a004 < 0xb)) {
      uRam00859fe0 = uRam00859fe0 & 0xffffefff;
      if (((cRam00267834 != '\0') && (cRam00267834 != '\x04')) &&
         (((bRam0085a004 != 0 && (bRam0085a004 != 1)) || ((bRam002678c8 & 2) != 2)))) {
        uVar2 = sRam00859fe8 + param_1;
        iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2) >>
                5;
        sRam00859fe8 = uVar2 + ((short)iVar3 * 0xf & 0x3fffU) * -4;
        uRam00859fe0 = uRam00859fe0 | 0x400;
        iVar3 = (uint)bRam00859ffa + iVar3 * -2;
        if (iVar3 < 0) {
          bRam00859ffa = 0;
        }
        else {
          bRam00859ffa = (byte)iVar3;
        }
      }
      if ((uRam00859fe0 & 2) != 2) {
        FUN_001b58b0();
      }
    }
    if (((uRam00859fc0 & 1) == 1) && (bRam00859fc9 < 0xb)) {
      if ((cRam00267834 == '\0') || (cRam00267834 == '\x04')) {
        if ((cRam00267834 == '\0') && ((uRam00859fc0 & 2) != 2)) {
          iVar3 = 0;
          if ((bRam0085a2f5 < 10) || (0xf < bRam0085a2f5)) {
            sVar1 = FUN_0015e790();
            if (sVar1 == 0x14) {
              if ((bRam00267880 < 10) || (0xf < bRam00267880)) {
                if (bRam00267880 < 10) {
                  iVar3 = 6;
                }
              }
              else {
                iVar3 = bRam00267880 - 10;
              }
            }
          }
          else {
            uVar2 = sRam00859fc6 + param_1;
            iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2
                         ) >> 5;
            sRam00859fc6 = uVar2 + ((short)iVar3 * 0xf & 0x3fffU) * -4;
          }
          if (6 < iVar3) {
            iVar3 = 6;
          }
          if ((int)((uint)bRam00859fc8 + iVar3) < 0x100) {
            bRam00859fc8 = (byte)((uint)bRam00859fc8 + iVar3);
          }
          else {
            bRam00859fc8 = 0xff;
          }
        }
      }
      else {
        uVar2 = sRam00859fc6 + param_1;
        iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2) >>
                5;
        sRam00859fc6 = uVar2 + ((short)iVar3 * 0xf & 0x3fffU) * -4;
        uRam00859fc0 = uRam00859fc0 | 0x400;
        iVar3 = (uint)bRam00859fc8 + iVar3 * -2;
        if (iVar3 < 0) {
          bRam00859fc8 = 0;
        }
        else {
          bRam00859fc8 = (byte)iVar3;
        }
      }
      if ((uRam00859fc0 & 2) != 2) {
        FUN_001b5740(0x859fc0);
      }
      uRam002679ac = uRam002679ac + param_1;
      if (4 < (int)((int)((ulong)((long)(int)(uint)uRam002679ac * -0x77777777) >> 0x20) +
                   (uint)uRam002679ac) >> 5) {
        uRam00859fc0 = uRam00859fc0 | 0x80000020;
      }
    }
    for (uVar6 = 0; uVar6 < 6; uVar6 = uVar6 + 1 & 0xff) {
      if (((*(uint *)(uVar6 * 0x20 + 0x859e60) & 1) == 1) &&
         (*(byte *)(uVar6 * 0x20 + 0x859e69) < 0xb)) {
        if ((cRam00267834 == '\0') || (cRam00267834 == '\x04')) {
          if ((cRam00267834 == '\0') && ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 2) != 2)) {
            iVar3 = 0;
            if ((bRam0085a2f5 < 10) || (0xf < bRam0085a2f5)) {
              sVar1 = FUN_0015e790();
              if (sVar1 == 0x14) {
                if ((bRam00267880 < 10) || (0xf < bRam00267880)) {
                  if (bRam00267880 < 10) {
                    iVar3 = 6;
                  }
                }
                else {
                  iVar3 = bRam00267880 - 10;
                }
              }
            }
            else {
              *(short *)(uVar6 * 0x20 + 0x859e66) = *(short *)(uVar6 * 0x20 + 0x859e66) + param_1;
              uVar2 = *(ushort *)(uVar6 * 0x20 + 0x859e66);
              iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) +
                           (uint)uVar2) >> 5;
              *(ushort *)(uVar6 * 0x20 + 0x859e66) =
                   *(short *)(uVar6 * 0x20 + 0x859e66) + ((short)iVar3 * 0xf & 0x3fffU) * -4;
            }
            if (6 < iVar3) {
              iVar3 = 6;
            }
            iVar3 = (uint)*(byte *)(uVar6 * 0x20 + 0x859e68) + iVar3 * 2;
            if (iVar3 < 0x100) {
              *(char *)(uVar6 * 0x20 + 0x859e68) = (char)iVar3;
            }
            else {
              *(undefined1 *)(uVar6 * 0x20 + 0x859e68) = 0xff;
            }
          }
        }
        else {
          *(short *)(uVar6 * 0x20 + 0x859e66) = *(short *)(uVar6 * 0x20 + 0x859e66) + param_1;
          uVar2 = *(ushort *)(uVar6 * 0x20 + 0x859e66);
          iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2)
                  >> 5;
          *(short *)(uVar6 * 0x20 + 0x859e66) =
               *(short *)(uVar6 * 0x20 + 0x859e66) + (short)iVar3 * -0x3c;
          puVar4 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar4 = *puVar4 | 0x400;
          iVar3 = (uint)*(byte *)(uVar6 * 0x20 + 0x859e68) - iVar3;
          if (iVar3 < 0) {
            *(undefined1 *)(uVar6 * 0x20 + 0x859e68) = 0;
          }
          else {
            *(char *)(uVar6 * 0x20 + 0x859e68) = (char)iVar3;
          }
        }
        if (((*(uint *)(uVar6 * 0x20 + 0x859e60) & 0x800) != 0x800) &&
           ((*(uint *)(uVar6 * 0x20 + 0x859e60) & 2) != 2)) {
          FUN_001b5740(uVar6 * 0x20 + 0x859e60);
        }
        psVar5 = (short *)(uVar6 * 2 + 0x85a3b0);
        *psVar5 = *psVar5 + param_1;
        uVar2 = *(ushort *)(uVar6 * 2 + 0x85a3b0);
        if (2 < (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2) >>
                5) {
          puVar4 = (uint *)(uVar6 * 0x20 + 0x859e60);
          *puVar4 = *puVar4 | 0x20;
        }
      }
    }
    for (uVar6 = 0; uVar6 < 5; uVar6 = uVar6 + 1 & 0xff) {
      if (((*(uint *)(uVar6 * 0x20 + 0x859f20) & 1) == 1) &&
         (*(byte *)(uVar6 * 0x20 + 0x859f29) < 0xb)) {
        if ((cRam00267834 == '\0') || (cRam00267834 == '\x04')) {
          if ((cRam00267834 == '\0') && ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 2) != 2)) {
            iVar3 = 0;
            if ((bRam0085a2f5 < 10) || (0xf < bRam0085a2f5)) {
              sVar1 = FUN_0015e790();
              if (sVar1 == 0x14) {
                if ((bRam00267880 < 10) || (0xf < bRam00267880)) {
                  if (bRam00267880 < 10) {
                    iVar3 = 6;
                  }
                }
                else {
                  iVar3 = bRam00267880 - 10;
                }
              }
            }
            else {
              *(short *)(uVar6 * 0x20 + 0x859f26) = *(short *)(uVar6 * 0x20 + 0x859f26) + param_1;
              uVar2 = *(ushort *)(uVar6 * 0x20 + 0x859f26);
              iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) +
                           (uint)uVar2) >> 5;
              *(ushort *)(uVar6 * 0x20 + 0x859f26) =
                   *(short *)(uVar6 * 0x20 + 0x859f26) + ((short)iVar3 * 0xf & 0x3fffU) * -4;
            }
            if (6 < iVar3) {
              iVar3 = 6;
            }
            iVar3 = iVar3 + (uint)*(byte *)(uVar6 * 0x20 + 0x859f28);
            if (iVar3 < 0x100) {
              *(char *)(uVar6 * 0x20 + 0x859f28) = (char)iVar3;
            }
            else {
              *(undefined1 *)(uVar6 * 0x20 + 0x859f28) = 0xff;
            }
          }
        }
        else {
          *(short *)(uVar6 * 0x20 + 0x859f26) = *(short *)(uVar6 * 0x20 + 0x859f26) + param_1;
          uVar2 = *(ushort *)(uVar6 * 0x20 + 0x859f26);
          iVar3 = (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2)
                  >> 5;
          *(ushort *)(uVar6 * 0x20 + 0x859f26) =
               *(short *)(uVar6 * 0x20 + 0x859f26) + ((short)iVar3 * 0xf & 0x3fffU) * -4;
          puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar4 = *puVar4 | 0x400;
          iVar3 = (uint)*(byte *)(uVar6 * 0x20 + 0x859f28) + iVar3 * -2;
          if (iVar3 < 0) {
            *(undefined1 *)(uVar6 * 0x20 + 0x859f28) = 0;
          }
          else {
            *(char *)(uVar6 * 0x20 + 0x859f28) = (char)iVar3;
          }
        }
        if (((((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x800) != 0x800) &&
             ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x1000) != 0x1000)) &&
            ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 0x2000) != 0x2000)) &&
           ((*(uint *)(uVar6 * 0x20 + 0x859f20) & 2) != 2)) {
          FUN_001b5740(uVar6 * 0x20 + 0x859f20);
        }
        psVar5 = (short *)(uVar6 * 2 + 0x85a3c0);
        *psVar5 = *psVar5 + param_1;
        uVar2 = *(ushort *)(uVar6 * 2 + 0x85a3c0);
        if (4 < (int)((int)((ulong)((long)(int)(uint)uVar2 * -0x77777777) >> 0x20) + (uint)uVar2) >>
                5) {
          puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar4 = *puVar4 | 0x20;
          puVar4 = (uint *)(uVar6 * 0x20 + 0x859f20);
          *puVar4 = *puVar4 | 0x80000000;
        }
      }
    }
  }
  return;
}

