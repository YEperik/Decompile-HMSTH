
bool FUN_001da8f0(void)

{
  char cVar1;
  long lVar2;
  long lVar3;
  
  lVar3 = 0;
  lVar2 = FUN_0012e170(0,4);
  if (lVar2 == 0) {
    lVar2 = FUN_0012e170(0,8);
    if (lVar2 == 0) {
      if ((*(byte *)(iGpffff8afc + 6) & 0x44) == 0) {
        if ((*(byte *)(iGpffff8afc + 6) & 0x88) == 0) {
          if ((*(byte *)(iGpffff8afc + 6) & 0x11) == 0) {
            if (((*(byte *)(iGpffff8afc + 6) & 0x22) != 0) && (*(char *)(iGpffff8afc + 8) < '\a')) {
              *(char *)(iGpffff8afc + 8) = *(char *)(iGpffff8afc + 8) + '\x01';
              FUN_00218ea0(2);
              if (*(char *)(iGpffff8afc + 8) == '\x04') {
                *(undefined1 *)(iGpffff8afc + 0x2a) = 1;
                FUN_001dcf30();
              }
            }
          }
          else if ('\0' < *(char *)(iGpffff8afc + 8)) {
            *(char *)(iGpffff8afc + 8) = *(char *)(iGpffff8afc + 8) + -1;
            FUN_00218ea0(2);
            if (*(char *)(iGpffff8afc + 8) == '\x03') {
              *(undefined1 *)(iGpffff8afc + 0x2a) = 0;
              FUN_001dcf30();
            }
          }
        }
        else {
          cVar1 = *(char *)(iGpffff8afc + 9) + '\x01';
          *(char *)(iGpffff8afc + 9) = cVar1;
          if (cVar1 < '\x03') {
            FUN_00218ea0(2);
          }
          else {
            *(undefined1 *)(iGpffff8afc + 9) = 2;
            if ((int)*(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc) << 2 <
                (int)(*(byte *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0x10) - 0xc)) {
              FUN_00218ea0(2);
              lVar3 = 1;
            }
          }
        }
      }
      else {
        cVar1 = *(char *)(iGpffff8afc + 9) + -1;
        *(char *)(iGpffff8afc + 9) = cVar1;
        if (cVar1 < '\0') {
          *(undefined1 *)(iGpffff8afc + 9) = 0;
          if ('\0' < *(char *)(iGpffff8afc + *(char *)(iGpffff8afc + 0x2a) + 0xc)) {
            FUN_00218ea0(2);
            lVar3 = -1;
          }
        }
        else {
          FUN_00218ea0(2);
        }
      }
    }
    else if (*(char *)(iGpffff8afc + 8) < '\x04') {
      FUN_00218ea0(2);
      *(char *)(iGpffff8afc + 8) = *(char *)(iGpffff8afc + 8) + '\x04';
      *(undefined1 *)(iGpffff8afc + 0x2a) = 1;
      FUN_001dcf30();
    }
  }
  else if ('\x03' < *(char *)(iGpffff8afc + 8)) {
    FUN_00218ea0(2);
    *(char *)(iGpffff8afc + 8) = *(char *)(iGpffff8afc + 8) + -4;
    *(undefined1 *)(iGpffff8afc + 0x2a) = 0;
    FUN_001dcf30();
  }
  if (lVar3 != 0) {
    FUN_001dae90(lVar3);
  }
  return lVar3 != 0;
}

