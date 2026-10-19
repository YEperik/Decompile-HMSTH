
void FUN_001ca2c0(float param_1,float param_2,undefined4 param_3,float param_4,float param_5,
                 float param_6,float param_7,float param_8,undefined2 param_9,undefined2 param_10,
                 undefined2 param_11,undefined2 param_12)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float in_stack_00000000;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  
  fStack_70 = param_8;
  if (param_8 <= 0.0) {
    fStack_70 = -param_8;
  }
  if (0.0 < in_stack_00000000) {
    fStack_6c = in_stack_00000000;
  }
  else {
    fStack_6c = -in_stack_00000000;
  }
  lVar3 = 1;
  while (fVar5 = (float)FUN_001000c0(lVar3), fVar5 < fStack_70) {
    lVar3 = lVar3 << 1;
  }
  lVar4 = 1;
  while (fVar5 = (float)FUN_001000c0(lVar4), fVar5 < fStack_6c) {
    lVar4 = lVar4 << 1;
  }
  param_6 = param_6 + 1.0;
  param_7 = param_7 + 1.0;
  fStack_68 = param_7;
  if (param_7 - param_5 < 0.0) {
    fStack_68 = -param_7;
  }
  fStack_68 = fStack_68 - param_5;
  fStack_64 = param_6;
  if (param_6 - param_4 < 0.0) {
    fStack_64 = -param_6;
  }
  fStack_64 = fStack_64 - param_4;
  uVar1 = FUN_0011d018(fStack_64 * 2.0);
  uVar2 = FUN_0011d018(fStack_68 * 2.0);
  fVar5 = (float)FUN_001000c0(lVar3);
  fVar6 = (float)FUN_001000c0(lVar4);
  param_5 = param_5 / fVar6;
  fVar6 = (float)FUN_001000c0(lVar3);
  fVar7 = (float)FUN_001000c0(lVar4);
  FUN_0015ae30(param_6 / fVar5,param_5,param_4 / fVar6,param_7 / fVar7,param_9,uVar1,uVar2);
  FUN_0015bcd0(param_9,param_10,param_11,param_12);
  FUN_0015c040(param_1 + fRam002679dc,param_2 + fRam002679d8,param_3,param_9);
  return;
}

