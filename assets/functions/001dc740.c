
void FUN_001dc740(byte param_1,byte param_2)

{
  if (param_2 < (byte)((*(char *)(iRam002679ec + (uint)param_1 + 0xc) + '\x01') * '\x04')) {
    FUN_001df680();
  }
  else {
    FUN_001df6f0();
  }
  return;
}

