
void FUN_001ca610(float param_1,float param_2,undefined4 param_3,float param_4,float param_5,
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
  float in_stack_00000008;
  float in_stack_00000010;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  
  if (0.0 < in_stack_00000008) {
    uStack_70 = in_stack_00000008;
  }
  else {
    uStack_70 = -in_stack_00000008;
  }
  if (0.0 < in_stack_00000010) {
    uStack_6c = in_stack_00000010;
  }
  else {
    uStack_6c = -in_stack_00000010;
  }
  lVar3 = 1;
  while (fVar5 = (float)FUN_001000c0(lVar3), fVar5 < uStack_70) {
    lVar3 = lVar3 << 1;
  }
  lVar4 = 1;
  while (fVar5 = (float)FUN_001000c0(lVar4), fVar5 < uStack_6c) {
    lVar4 = lVar4 << 1;
  }
  uStack_68 = param_5;
  if (param_5 < 0.0) {
    uStack_68 = -param_5;
  }
  uStack_64 = param_4;
  if (param_4 < 0.0) {
    uStack_64 = -param_4;
  }
  uVar1 = FUN_0011d018(uStack_64 * 2.0);
  uVar2 = FUN_0011d018(uStack_68 * 2.0);
  fVar5 = (float)FUN_001000c0(lVar3);
  fVar6 = (float)FUN_001000c0(lVar4);
  param_7 = param_7 / fVar6;
  fVar6 = (float)FUN_001000c0(lVar3);
  fVar7 = (float)FUN_001000c0(lVar4);
  FUN_0015ae30((param_8 + 1.0) / fVar5,param_7,param_6 / fVar6,(in_stack_00000000 + 1.0) / fVar7,
               param_9,uVar1,uVar2);
  FUN_0015bcd0(param_9,param_10,param_11,param_12);
  FUN_0015c040(param_1 + fRam002679dc,param_2 + fRam002679d8,param_3,param_9);
  return;
}

