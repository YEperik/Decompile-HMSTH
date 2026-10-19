
void FUN_001d1220(void)

{
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_10;
  float fStack_c;
  undefined4 uStack_8;
  
  puRam002679e8[1] = puRam002679e8[1] + 1;
  if ((('\x02' < *(char *)(puRam002679e8 + 0xbe)) && (*(char *)((int)puRam002679e8 + 0x189) == '\0')
      ) && (FUN_00124180(uRam00836758,&uStack_10), fStack_c <= *(float *)(puRam002679e8 + 0x32))) {
    FUN_00218ea0(0x25);
    FUN_001ff4f0(uStack_10,fStack_c,uStack_8,0xb,0,0);
    FUN_00137930(0x27);
    *(undefined1 *)((int)puRam002679e8 + 0x189) = 1;
  }
  if ((((uRam00836750 & 0x1000) != 0x1000) && ((uRam00836750 & 0x800) != 0x800)) ||
     (0x3c < (short)puRam002679e8[1])) {
    uStack_20 = FUN_00112f70(*(undefined4 *)(puRam002679e8 + 0x78));
    uStack_18 = FUN_00112bf8(*(undefined4 *)(puRam002679e8 + 0x78));
    uStack_1c = 0;
    FUN_00139920();
    FUN_00137cc0(0x41800000,0,&uStack_20);
    *puRam002679e8 = 0x14;
    FUN_001d2100();
  }
  return;
}

