
float FUN_001d87a0(float param_1)

{
  float fVar1;
  
  if (param_1 < 420.0) {
    fVar1 = 32.0;
  }
  else if (1936.0 < param_1) {
    fVar1 = 90.0;
  }
  else {
    fVar1 = ((param_1 - 420.0) / 1516.0) * 58.0 + 32.0;
  }
  return fVar1;
}

