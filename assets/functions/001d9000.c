
/* WARNING: Removing unreachable block (ram,0x001d9050) */
/* WARNING: Removing unreachable block (ram,0x001d9058) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_001d9000(void)

{
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_20 = (undefined4)_DAT_002448c0;
  uStack_1c = (undefined4)((ulong)_DAT_002448c0 >> 0x20);
  uStack_18 = DAT_002448c8;
  uStack_14 = DAT_002448cc;
  if ((*(char *)(iGpffff8af8 + 0x1b9) == '\x01') && ((*(byte *)(iGpffff8af8 + 0x1b8) & 0xf) == 0)) {
    *(undefined1 *)(iGpffff8af8 + 0x1b9) = 3;
  }
  if ((*(char *)(iGpffff8af8 + 0x1b9) == '\x02') || (*(char *)(iGpffff8af8 + 0x1b9) == '\x03')) {
    uStack_10 = *(undefined4 *)(iGpffff8af8 + 0x90);
    uStack_8 = *(undefined4 *)(iGpffff8af8 + 0x98);
    uStack_4 = *(undefined4 *)(iGpffff8af8 + 0x9c);
    uStack_c = 0;
    FUN_001d9130(&uStack_30,&uStack_20,iGpffff8af8 + 0x60,iGpffff8af8 + 0x90,&uStack_10);
    FUN_001ff4f0(uStack_30,uStack_2c,uStack_28,0xc);
  }
  return;
}

