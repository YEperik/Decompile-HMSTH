
void FUN_001dac90(void)

{
  if ((*(byte *)(iGpffff8afc + 6) & 0x44) == 0) {
    if ((*(byte *)(iGpffff8afc + 6) & 0x88) == 0) {
      if ((*(byte *)(iGpffff8afc + 6) & 0x11) == 0) {
        if (((*(byte *)(iGpffff8afc + 6) & 0x22) != 0) && ('\0' < *(char *)(iGpffff8afc + 0x29))) {
          FUN_00218ea0(2);
          *(char *)(iGpffff8afc + 0x29) = *(char *)(iGpffff8afc + 0x29) + -10;
        }
      }
      else if ((long)*(char *)(iGpffff8afc + 0x29) < (long)(ulong)*(byte *)(iGpffff8afc + 0x28)) {
        FUN_00218ea0(2);
        *(char *)(iGpffff8afc + 0x29) = *(char *)(iGpffff8afc + 0x29) + '\n';
      }
    }
    else if ('\0' < *(char *)(iGpffff8afc + 0x29)) {
      FUN_00218ea0(2);
      *(char *)(iGpffff8afc + 0x29) = *(char *)(iGpffff8afc + 0x29) + -1;
    }
  }
  else if ((long)*(char *)(iGpffff8afc + 0x29) < (long)(ulong)*(byte *)(iGpffff8afc + 0x28)) {
    FUN_00218ea0(2);
    *(char *)(iGpffff8afc + 0x29) = *(char *)(iGpffff8afc + 0x29) + '\x01';
  }
  if ((long)(ulong)*(byte *)(iGpffff8afc + 0x28) < (long)*(char *)(iGpffff8afc + 0x29)) {
    *(undefined1 *)(iGpffff8afc + 0x29) = *(undefined1 *)(iGpffff8afc + 0x28);
  }
  else if (*(char *)(iGpffff8afc + 0x29) < '\0') {
    *(undefined1 *)(iGpffff8afc + 0x29) = 0;
  }
  FUN_001dbb00(1,*(undefined1 *)(iGpffff8afc + 0x29));
  return;
}

