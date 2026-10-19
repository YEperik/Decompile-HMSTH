
void FUN_001cd0d0(undefined1 param_1)

{
  undefined1 uVar1;
  short sVar2;
  
  if (cRam00267840 == -1) {
    puRam002679e4 = (undefined2 *)0x1ad5000;
    FUN_001de930(0,2);
    FUN_001361f0(0x66,0xffa000,0xa17000);
    FUN_001361f0(0x65,0xffa000,0xa18000);
    FUN_00152ed0(0,0xa18000,0xa17000);
    *(undefined1 *)(puRam002679e4 + 2) = param_1;
    for (sVar2 = 0; sVar2 < 3; sVar2 = sVar2 + 1) {
      *(undefined1 *)((int)puRam002679e4 + sVar2 + 8) = 0xff;
    }
    uVar1 = FUN_001df930();
    *(undefined1 *)((int)puRam002679e4 + 5) = uVar1;
    uVar1 = FUN_001cd4b0();
    *(undefined1 *)((int)puRam002679e4 + 5) = uVar1;
    if (*(char *)((int)puRam002679e4 + 5) == -1) {
      FUN_00152f40(0,9,0x20,0);
      *(undefined1 *)(puRam002679e4 + 8) = 1;
      *puRam002679e4 = 6;
      puRam002679e4[1] = 0xc;
    }
    else {
      *(undefined1 *)((int)puRam002679e4 + 0x11) = 0;
      *puRam002679e4 = 6;
      puRam002679e4[1] = 2;
      FUN_00123950(1,(uint)*(byte *)(puRam002679e4 + 2) * 2 + 0x16);
      FUN_001cd3f0(0x41800000);
      *(undefined1 *)((int)puRam002679e4 + 7) = 0;
      *(undefined1 *)(puRam002679e4 + 3) = 0;
      *(undefined1 *)(puRam002679e4 + 8) = 0;
    }
    FUN_00139920();
    FUN_0015e770(0xb);
  }
  return;
}

