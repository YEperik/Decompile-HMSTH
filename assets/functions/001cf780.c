
void FUN_001cf780(void)

{
  FUN_00153ef0();
  FUN_001361f0(0x66,0xffa000,0xa17000);
  FUN_001361f0(0x65,0xffa000,0xa18000);
  FUN_00152ed0(0,0xa18000,0xa17000);
  puRam002679e8 = (undefined2 *)0x1ad5000;
  uRam01ad5108 = uRam0083d070;
  uRam01ad5110 = uRam002678d0;
  FUN_00124180(uRam00834058,0x1ad5050);
  FUN_00124180(100,puRam002679e8 + 0x30);
  *(undefined4 *)(puRam002679e8 + 0x30) = 0x44000000;
  *(undefined4 *)(puRam002679e8 + 0x34) = 0x45800000;
  *(float *)(puRam002679e8 + 0x32) = *(float *)(puRam002679e8 + 0x32) - 140.0;
  *(undefined4 *)(puRam002679e8 + 0x20) = 0xbf559cf1;
  *(undefined4 *)(puRam002679e8 + 0x22) = 0x3eb83600;
  *(undefined4 *)(puRam002679e8 + 0x24) = 0xbf59c50d;
  *(undefined1 *)(puRam002679e8 + 0xd5) = 0;
  *(undefined1 *)((int)puRam002679e8 + 0x1a9) = 0;
  puRam002679e8[1] = 0;
  FUN_001d9810(0,4);
  *(undefined1 *)(puRam002679e8 + 0xd4) = 0;
  FUN_0013ea60();
  FUN_0013f0c0();
  FUN_001e0010();
  uRam00267888 = uRam00267888 | 0x20;
  FUN_001d1640();
  FUN_001d1880(0x42700000);
  FUN_001d8730();
  FUN_001d1c00();
  FUN_0015e770(10);
  FUN_00161310();
  *puRam002679e8 = 1;
  return;
}

