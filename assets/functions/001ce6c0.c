
byte FUN_001ce6c0(byte param_1,byte *param_2)

{
  byte *pbVar1;
  
  pbVar1 = (&PTR_DAT_00244670)[param_1];
  while( true ) {
    if ((*pbVar1 == 0xff) || (*param_2 < *pbVar1)) {
      return 0xff;
    }
    if (((*pbVar1 == *param_2) && (pbVar1[1] == param_2[1])) && (pbVar1[2] == param_2[2])) break;
    pbVar1 = pbVar1 + 4;
  }
  return pbVar1[3];
}

