/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BalanceCar.c
 *
 * Code generated for Simulink model 'BalanceCar'.
 *
 * Model version                  : 1.56
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Mon Jun  2 11:08:17 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Custom Processor->Custom Processor
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "BalanceCar.h"
#include "rtwtypes.h"
#include <math.h>

/* Named constants for Chart: '<S5>/Debounce' */
#define BalanceCar_IN_Key1Off          ((uint8_T)1U)
#define BalanceCar_IN_KeyOn            ((uint8_T)2U)

/* Named constants for Chart: '<S3>/ReverseLazer' */
#define BalanceCar_IN_Default1         ((uint8_T)1U)
#define BalanceCar_IN_End1             ((uint8_T)1U)
#define BalanceCar_IN_Enter1           ((uint8_T)2U)
#define BalanceCar_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define BalanceCar_IN_StopTurn         ((uint8_T)2U)
#define BalanceCar_IN_TurnDirection1   ((uint8_T)3U)

/* Exported block signals */
real32_T Angle;                        /* '<Root>/Input3' */
int16_T Gyro_Angle;                    /* '<Root>/Input5' */
uint8_T Key1;                          /* '<Root>/Input' */
uint8_T Key2;                          /* '<Root>/Input1' */
int16_T Motor1Speed;                   /* '<Root>/Input2' */
int16_T Motor2Speed;                   /* '<Root>/Input4' */
int16_T Gyro_Turn;                     /* '<Root>/Input6' */
real32_T Model_Distance;               /* '<Root>/Input7' */
real32_T BalanceCarOffset;             /* '<Root>/Input8' */
uint16_T Motor1PWM;                    /* '<S4>/MotorPinOutput' */
uint16_T Motor2PWM;                    /* '<S4>/MotorPinOutput' */
int16_T Direction_PWM;                 /* '<S3>/Add' */
int16_T Balance_PWM;                   /* '<S2>/Add' */
int16_T Speed_PWM;                     /* '<S5>/Saturation' */
int16_T BalanceCarTargetSpeed;         /* '<S5>/Chart' */
uint8_T Motor1_A;                      /* '<S4>/MotorPinOutput' */
uint8_T Motor1_B;                      /* '<S4>/MotorPinOutput' */
uint8_T Motor2_A;                      /* '<S4>/MotorPinOutput' */
uint8_T Motor2_B;                      /* '<S4>/MotorPinOutput' */

/* Block signals (default storage) */
B_BalanceCar_T BalanceCar_B;

/* Block states (default storage) */
DW_BalanceCar_T BalanceCar_DW;

/* External inputs (root inport signals with default storage) */
ExtU_BalanceCar_T BalanceCar_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_BalanceCar_T BalanceCar_Y;

/* Real-time model */
static RT_MODEL_BalanceCar_T BalanceCar_M_;
RT_MODEL_BalanceCar_T *const BalanceCar_M = &BalanceCar_M_;
static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);
static void BalanceCar_Debounce_Init(uint8_T *rty_KeyOutput,
  DW_Debounce_BalanceCar_T *localDW);
static void BalanceCar_Debounce_Enable(RT_MODEL_BalanceCar_T * const
  BalanceCar_M, DW_Debounce_BalanceCar_T *localDW);
static void BalanceCar_Debounce(RT_MODEL_BalanceCar_T * const BalanceCar_M,
  uint8_T rtu_KeyInput, uint8_T *rty_KeyOutput, DW_Debounce_BalanceCar_T
  *localDW);
static void BalanceCar_BalanceControl_Init(int16_T *rty_Balance_PWM,
  P_BalanceControl_BalanceCar_T *localP);
static void BalanceCar_BalanceControl(real32_T rtu_Input, int16_T rtu_Input2,
  real32_T rtu_Input8, int16_T *rty_Balance_PWM);
static void BalanceCar_abs_Init(uint16_T *rty_y, P_abs_BalanceCar_T *localP);
static void BalanceCar_abs(int16_T rtu_x, uint16_T *rty_y);
static void BalanceCar_SetPWM_Init(uint16_T *rty_Motor1PWM1, uint16_T
  *rty_Motor2PWM1, P_SetPWM_BalanceCar_T *localP);
static void BalanceCar_SetPWM(real32_T rtu_Angle, int16_T rtu_Motor1PWMTemp,
  int16_T rtu_Motor2PWMTemp, uint16_T *rty_Motor1PWM1, uint16_T *rty_Motor2PWM1,
  uint8_T *rty_Motor1_A1, uint8_T *rty_Motor1_B1, uint8_T *rty_Motor2_A1,
  uint8_T *rty_Motor2_B1, DW_SetPWM_BalanceCar_T *localDW, P_SetPWM_BalanceCar_T
  *localP);
static void SpeedControl_Init(void);
static void SpeedControl_Enable(void);
static void SpeedControl(void);
static void BalanceCar_TruthTable(void);
static void DirectionControl_Init(void);
static void DirectionControl_Enable(void);
static void DirectionControl(void);

/* Forward declaration for local functions */
static void BalanceCar_KeyCounter(uint8_T *rty_KeyOutput,
  DW_Debounce_BalanceCar_T *localDW);

/* Forward declaration for local functions */
static void BalanceCar_Motor1Backward(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h);
static void BalanceCar_Motor1Forward(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h);
static void BalanceCar_SetDirection(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h,
  uint8_T *Motor2_A_n, uint8_T *Motor2_B_p, const int16_T *Saturation2, const
  int16_T *Saturation3);
static void BalanceCar_MotorStop(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h,
  uint8_T *Motor2_A_n, uint8_T *Motor2_B_p, uint16_T *rty_Motor1PWM1, uint16_T
  *rty_Motor2PWM1);
static void BalanceCar_FallDownDetect(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h,
  uint8_T *Motor2_A_n, uint8_T *Motor2_B_p, real32_T rtu_Angle, uint16_T
  *rty_Motor1PWM1, uint16_T *rty_Motor2PWM1);

/* Forward declaration for local functions */
static void BalanceCar_SpeedUp(void);
static void BalanceCar_SpeedDown(void);

/* Forward declaration for local functions */
static void BalanceCar_Task_5ms(const int16_T *UnitDelay, const int16_T
  *UnitDelay1);
static void BalanceCar_Task_10ms(void);
static void BalanceCar_Task_20ms(void);
static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

/* Function for Chart: '<S5>/Debounce' */
static void BalanceCar_KeyCounter(uint8_T *rty_KeyOutput,
  DW_Debounce_BalanceCar_T *localDW)
{
  if (localDW->KeyOnFlag && (localDW->KeyState == ((uint8_T)OFF))) {
    localDW->KeyOnFlag = false;
    *rty_KeyOutput = ((uint8_T)ON);
  } else {
    *rty_KeyOutput = ((uint8_T)OFF);
  }
}

/*
 * System initialize for atomic system:
 *    '<S5>/Debounce'
 *    '<S5>/Debounce1'
 */
static void BalanceCar_Debounce_Init(uint8_T *rty_KeyOutput,
  DW_Debounce_BalanceCar_T *localDW)
{
  localDW->KeyState = 1U;
  *rty_KeyOutput = 0U;
}

/*
 * Enable for atomic system:
 *    '<S5>/Debounce'
 *    '<S5>/Debounce1'
 */
static void BalanceCar_Debounce_Enable(RT_MODEL_BalanceCar_T * const
  BalanceCar_M, DW_Debounce_BalanceCar_T *localDW)
{
  real_T durationOperatorLastReferenceTi;
  durationOperatorLastReferenceTi = ((BalanceCar_M->Timing.clockTick0) * 0.001)
    - localDW->chartDisableTime;
  localDW->durationOperatorLastReferenceTi += durationOperatorLastReferenceTi;
  localDW->durationOperatorLastReference_e += durationOperatorLastReferenceTi;
}

/*
 * Output and update for atomic system:
 *    '<S5>/Debounce'
 *    '<S5>/Debounce1'
 */
static void BalanceCar_Debounce(RT_MODEL_BalanceCar_T * const BalanceCar_M,
  uint8_T rtu_KeyInput, uint8_T *rty_KeyOutput, DW_Debounce_BalanceCar_T
  *localDW)
{
  boolean_T condIsTrue;
  condIsTrue = (rtu_KeyInput <= ((uint8_T)NUM0));
  if ((!condIsTrue) || (!localDW->condWasTrueAtLastTimeStep_1)) {
    localDW->durationOperatorLastReferenceTi = ((BalanceCar_M->Timing.clockTick0)
      * 0.001);
  }

  localDW->condWasTrueAtLastTimeStep_1 = condIsTrue;
  condIsTrue = (rtu_KeyInput > ((uint8_T)NUM0));
  if ((!condIsTrue) || (!localDW->condWasTrueAtLastTimeStep_1_a)) {
    localDW->durationOperatorLastReference_e = ((BalanceCar_M->Timing.clockTick0)
      * 0.001);
  }

  localDW->condWasTrueAtLastTimeStep_1_a = condIsTrue;

  /* Chart: '<S5>/Debounce' */
  if (localDW->is_active_c4_BalanceCar == 0U) {
    localDW->is_active_c4_BalanceCar = 1U;
    localDW->durationOperatorLastReferenceTi = ((BalanceCar_M->Timing.clockTick0)
      * 0.001);
    localDW->is_Debounce = BalanceCar_IN_Key1Off;
    localDW->condWasTrueAtLastTimeStep_1 = (rtu_KeyInput <= ((uint8_T)NUM0));
  } else {
    if (localDW->is_Debounce == BalanceCar_IN_Key1Off) {
      condIsTrue = (rtu_KeyInput <= ((uint8_T)NUM0));
      if ((!condIsTrue) || (!localDW->condWasTrueAtLastTimeStep_1)) {
        localDW->durationOperatorLastReferenceTi =
          ((BalanceCar_M->Timing.clockTick0) * 0.001);
      }

      localDW->condWasTrueAtLastTimeStep_1 = condIsTrue;
      if (((BalanceCar_M->Timing.clockTick0) * 0.001) -
          localDW->durationOperatorLastReferenceTi >= 0.01) {
        localDW->durationOperatorLastReference_e =
          ((BalanceCar_M->Timing.clockTick0) * 0.001);
        localDW->is_Debounce = BalanceCar_IN_KeyOn;
        localDW->condWasTrueAtLastTimeStep_1_a = (rtu_KeyInput > ((uint8_T)NUM0));
      } else {
        localDW->KeyState = ((uint8_T)OFF);
      }
    } else {
      /* case IN_KeyOn: */
      condIsTrue = (rtu_KeyInput > ((uint8_T)NUM0));
      if ((!condIsTrue) || (!localDW->condWasTrueAtLastTimeStep_1_a)) {
        localDW->durationOperatorLastReference_e =
          ((BalanceCar_M->Timing.clockTick0) * 0.001);
      }

      localDW->condWasTrueAtLastTimeStep_1_a = condIsTrue;
      if (((BalanceCar_M->Timing.clockTick0) * 0.001) -
          localDW->durationOperatorLastReference_e >= 0.01) {
        localDW->durationOperatorLastReferenceTi =
          ((BalanceCar_M->Timing.clockTick0) * 0.001);
        localDW->is_Debounce = BalanceCar_IN_Key1Off;
        localDW->condWasTrueAtLastTimeStep_1 = (rtu_KeyInput <= ((uint8_T)NUM0));
      } else {
        localDW->KeyState = ((uint8_T)ON);
        localDW->KeyOnFlag = true;
      }
    }

    BalanceCar_KeyCounter(rty_KeyOutput, localDW);
  }

  /* End of Chart: '<S5>/Debounce' */
}

/* Function for Chart: '<S5>/Chart' */
static void BalanceCar_SpeedUp(void)
{
  if (BalanceCar_B.KeyOutput_e == ((uint8_T)ON)) {
    int32_T tmp;
    tmp = BalanceCarTargetSpeed + 20;
    if (BalanceCarTargetSpeed + 20 > 32767) {
      tmp = 32767;
    }

    BalanceCarTargetSpeed = (int16_T)tmp;
  }
}

/* Function for Chart: '<S5>/Chart' */
static void BalanceCar_SpeedDown(void)
{
  if (BalanceCar_B.KeyOutput == ((uint8_T)ON)) {
    int32_T tmp;
    tmp = BalanceCarTargetSpeed - 20;
    if (BalanceCarTargetSpeed - 20 < -32768) {
      tmp = -32768;
    }

    BalanceCarTargetSpeed = (int16_T)tmp;
  }
}

/* System initialize for function-call system: '<Root>/SpeedControl' */
static void SpeedControl_Init(void)
{
  /* InitializeConditions for DiscreteIntegrator: '<S40>/Filter' */
  BalanceCar_DW.Filter_DSTATE = BalanceCar_P.PIDController_InitialConditionF;

  /* InitializeConditions for DiscreteIntegrator: '<S45>/Integrator' */
  BalanceCar_DW.Integrator_DSTATE = BalanceCar_P.PIDController_InitialConditio_j;

  /* SystemInitialize for Chart: '<S5>/Debounce' */
  BalanceCar_Debounce_Init(&BalanceCar_B.KeyOutput_e, &BalanceCar_DW.sf_Debounce);

  /* SystemInitialize for Chart: '<S5>/Debounce1' */
  BalanceCar_Debounce_Init(&BalanceCar_B.KeyOutput, &BalanceCar_DW.sf_Debounce1);

  /* SystemInitialize for Saturate: '<S5>/Saturation' incorporates:
   *  Outport: '<S5>/Speed_PWM'
   */
  Speed_PWM = BalanceCar_P.Speed_PWM_Y0;
}

/* Enable for function-call system: '<Root>/SpeedControl' */
static void SpeedControl_Enable(void)
{
  BalanceCar_DW.SpeedControl_RESET_ELAPS_T = true;

  /* Enable for Chart: '<S5>/Debounce' */
  BalanceCar_Debounce_Enable(BalanceCar_M, &BalanceCar_DW.sf_Debounce);

  /* Enable for Chart: '<S5>/Debounce1' */
  BalanceCar_Debounce_Enable(BalanceCar_M, &BalanceCar_DW.sf_Debounce1);

  /* Enable for DiscreteIntegrator: '<S40>/Filter' */
  BalanceCar_DW.Filter_SYSTEM_ENABLE = 1U;
}

/* Output and update for function-call system: '<Root>/SpeedControl' */
static void SpeedControl(void)
{
  real_T Filter;
  real_T rtb_FilterCoefficient;
  uint32_T SpeedControl_ELAPS_T;
  int16_T rtb_Sum;
  if (BalanceCar_DW.SpeedControl_RESET_ELAPS_T) {
    SpeedControl_ELAPS_T = 0U;
  } else {
    SpeedControl_ELAPS_T = BalanceCar_M->Timing.clockTick0 -
      BalanceCar_DW.SpeedControl_PREV_T;
  }

  BalanceCar_DW.SpeedControl_PREV_T = BalanceCar_M->Timing.clockTick0;
  BalanceCar_DW.SpeedControl_RESET_ELAPS_T = false;

  /* Chart: '<S5>/Debounce' incorporates:
   *  Inport: '<Root>/Input'
   */
  BalanceCar_Debounce(BalanceCar_M, Key1, &BalanceCar_B.KeyOutput_e,
                      &BalanceCar_DW.sf_Debounce);

  /* Chart: '<S5>/Debounce1' incorporates:
   *  Inport: '<Root>/Input1'
   */
  BalanceCar_Debounce(BalanceCar_M, Key2, &BalanceCar_B.KeyOutput,
                      &BalanceCar_DW.sf_Debounce1);

  /* Chart: '<S5>/Chart' */
  if (BalanceCar_DW.is_active_c6_BalanceCar == 0U) {
    BalanceCar_DW.is_active_c6_BalanceCar = 1U;
    BalanceCarTargetSpeed = 0;
  } else {
    BalanceCar_SpeedUp();
    BalanceCar_SpeedDown();
  }

  /* End of Chart: '<S5>/Chart' */

  /* Sum: '<S5>/Sum1' incorporates:
   *  Constant: '<S5>/Constant'
   *  Inport: '<Root>/Input2'
   *  Inport: '<Root>/Input4'
   *  Product: '<S5>/Divide'
   *  Sum: '<S5>/Add'
   */
  rtb_Sum = (int16_T)(BalanceCarTargetSpeed - (int16_T)div_nde_s32_floor
                      ((int16_T)(Motor1Speed + Motor2Speed),
                       BalanceCar_P.Constant_Value));

  /* DiscreteIntegrator: '<S40>/Filter' */
  if (BalanceCar_DW.Filter_SYSTEM_ENABLE != 0) {
    /* DiscreteIntegrator: '<S40>/Filter' */
    Filter = BalanceCar_DW.Filter_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S40>/Filter' */
    Filter = BalanceCar_P.Filter_gainval * (real_T)SpeedControl_ELAPS_T
      * BalanceCar_DW.Filter_PREV_U + BalanceCar_DW.Filter_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S40>/Filter' */

  /* Gain: '<S48>/Filter Coefficient' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Gain: '<S39>/Derivative Gain'
   *  Sum: '<S40>/SumD'
   */
  rtb_FilterCoefficient = (SPEED_KD * (real_T)rtb_Sum - Filter) *
    BalanceCar_P.PIDController_N;

  /* Sum: '<S54>/Sum' incorporates:
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  DiscreteIntegrator: '<S45>/Integrator'
   *  Gain: '<S50>/Proportional Gain'
   */
  rtb_Sum = (int16_T)floor((SPEED_KP * (real_T)rtb_Sum +
    BalanceCar_DW.Integrator_DSTATE) + rtb_FilterCoefficient);

  /* Saturate: '<S5>/Saturation' */
  if (rtb_Sum > BalanceCar_P.Saturation_UpperSat) {
    /* Saturate: '<S5>/Saturation' */
    Speed_PWM = BalanceCar_P.Saturation_UpperSat;
  } else if (rtb_Sum < BalanceCar_P.Saturation_LowerSat) {
    /* Saturate: '<S5>/Saturation' */
    Speed_PWM = BalanceCar_P.Saturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Saturation' */
    Speed_PWM = rtb_Sum;
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* Update for DiscreteIntegrator: '<S40>/Filter' */
  BalanceCar_DW.Filter_SYSTEM_ENABLE = 0U;
  BalanceCar_DW.Filter_DSTATE = Filter;
  BalanceCar_DW.Filter_PREV_U = rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S45>/Integrator' incorporates:
   *  Constant: '<S5>/Constant'
   *  DataTypeConversion: '<S5>/Data Type Conversion'
   *  Gain: '<S42>/Integral Gain'
   *  Inport: '<Root>/Input2'
   *  Inport: '<Root>/Input4'
   *  Product: '<S5>/Divide'
   *  Sum: '<S5>/Add'
   *  Sum: '<S5>/Sum1'
   */
  BalanceCar_DW.Integrator_DSTATE += (real_T)(int16_T)(BalanceCarTargetSpeed -
    (int16_T)div_nde_s32_floor((int16_T)(Motor1Speed + Motor2Speed),
    BalanceCar_P.Constant_Value)) * SPEED_KI * BalanceCar_P.Integrator_gainval;
}

/* System initialize for function-call system: '<Root>/BalanceControl' */
static void BalanceCar_BalanceControl_Init(int16_T *rty_Balance_PWM,
  P_BalanceControl_BalanceCar_T *localP)
{
  /* SystemInitialize for Outport: '<S2>/Balance_PWM' */
  *rty_Balance_PWM = localP->Balance_PWM_Y0;
}

/* Output and update for function-call system: '<Root>/BalanceControl' */
static void BalanceCar_BalanceControl(real32_T rtu_Input, int16_T rtu_Input2,
  real32_T rtu_Input8, int16_T *rty_Balance_PWM)
{
  /* Sum: '<S2>/Add' incorporates:
   *  Constant: '<S2>/BALANCE_KD'
   *  Constant: '<S2>/BALANCE_KP'
   *  Product: '<S2>/Divide'
   *  Product: '<S2>/Divide1'
   *  Sum: '<S2>/Sum'
   */
  *rty_Balance_PWM = (int16_T)floorf((rtu_Input - rtu_Input8) * BALANCE_KP +
    (real32_T)rtu_Input2 * BALANCE_KD);
}

/* Output and update for atomic system: '<S3>/Truth Table' */
static void BalanceCar_TruthTable(void)
{
  /* Inport: '<Root>/Input7' */
  /*  Example condition 1 */
  /*  Example condition 2 */
  /*  Example condition 3 */
  if ((Model_Distance <= 10.0F) && (Model_Distance >= 0.0F)) {
    /*  Action 1:Dangerous */
    BalanceCar_B.y = 1U;
  } else if ((Model_Distance <= 30.0F) && (Model_Distance > 10.0F)) {
    /*  Action 2: Carefull */
    BalanceCar_B.y = 2U;
  } else if ((Model_Distance > 30.0F) && (Model_Distance < 50.0F)) {
    /*  Action 3:Warning */
    BalanceCar_B.y = 3U;
  } else {
    /*  Default */
    /*  Action 4:Noramal */
    BalanceCar_B.y = 0U;
  }

  /* End of Inport: '<Root>/Input7' */
}

/* System initialize for function-call system: '<Root>/DirectionControl' */
static void DirectionControl_Init(void)
{
  /* SystemInitialize for Sum: '<S3>/Add' incorporates:
   *  Outport: '<S3>/Direction_PWM'
   */
  Direction_PWM = BalanceCar_P.Direction_PWM_Y0;
}

/* Enable for function-call system: '<Root>/DirectionControl' */
static void DirectionControl_Enable(void)
{
  /* Enable for Chart: '<S3>/ReverseLazer' */
  BalanceCar_DW.previousTicks = BalanceCar_M->Timing.clockTick0;
}

/* Output and update for function-call system: '<Root>/DirectionControl' */
static void DirectionControl(void)
{
  uint32_T elapsedTicks;

  /* Truth Table: '<S3>/Truth Table' */
  BalanceCar_TruthTable();

  /* Chart: '<S3>/ReverseLazer' incorporates:
   *  Constant: '<S3>/AvoidObstacleEnable'
   */
  elapsedTicks = BalanceCar_M->Timing.clockTick0 - BalanceCar_DW.previousTicks;
  BalanceCar_DW.previousTicks = BalanceCar_M->Timing.clockTick0;
  if (BalanceCar_DW.temporalCounter_i1 + elapsedTicks <= 15U) {
    BalanceCar_DW.temporalCounter_i1 = (uint8_T)
      (BalanceCar_DW.temporalCounter_i1 + elapsedTicks);
  } else {
    BalanceCar_DW.temporalCounter_i1 = 15U;
  }

  if (BalanceCar_DW.is_active_c1_BalanceCar == 0U) {
    BalanceCar_DW.is_active_c1_BalanceCar = 1U;
    BalanceCar_DW.is_c1_BalanceCar = BalanceCar_IN_Default1;
    BalanceCar_B.DirectionTargetPWM = 0.0;
  } else {
    switch (BalanceCar_DW.is_c1_BalanceCar) {
     case BalanceCar_IN_Default1:
      if (BalanceCar_P.AvoidObstacleEnable_Value && (BalanceCar_B.y == 1) &&
          (BalanceCar_B.y == 2) && (BalanceCar_B.y == 3)) {
        BalanceCar_DW.is_c1_BalanceCar = BalanceCar_IN_TurnDirection1;
        BalanceCar_B.DirectionTargetPWM = 0.0;
        BalanceCar_DW.is_TurnDirection1 = BalanceCar_IN_Enter1;
      }
      break;

     case BalanceCar_IN_StopTurn:
      if ((BalanceCar_B.DirectionTargetPWM == 0.0) || (BalanceCar_B.y == 0)) {
        BalanceCar_DW.is_StopTurn = BalanceCar_IN_NO_ACTIVE_CHILD;
        BalanceCar_DW.is_c1_BalanceCar = BalanceCar_IN_Default1;
        BalanceCar_B.DirectionTargetPWM = 0.0;
      } else {
        switch (BalanceCar_DW.is_StopTurn) {
         case BalanceCar_IN_End1:
          break;

         default:
          /* case IN_Enter1: */
          if (BalanceCar_B.DirectionTargetPWM == 0.0) {
            BalanceCar_DW.is_StopTurn = BalanceCar_IN_End1;
          } else {
            BalanceCar_B.DirectionTargetPWM -= 10.0;
          }
          break;
        }
      }
      break;

     default:
      /* case IN_TurnDirection1: */
      if (BalanceCar_DW.is_TurnDirection1 == BalanceCar_IN_End1) {
        if (BalanceCar_DW.temporalCounter_i1 >= 10U) {
          BalanceCar_DW.is_TurnDirection1 = BalanceCar_IN_NO_ACTIVE_CHILD;
          BalanceCar_DW.is_c1_BalanceCar = BalanceCar_IN_StopTurn;
          BalanceCar_DW.is_StopTurn = BalanceCar_IN_Enter1;
        }

        /* case IN_Enter1: */
      } else if ((BalanceCar_B.y == 0) || (BalanceCar_B.DirectionTargetPWM >
                  100.0)) {
        BalanceCar_DW.is_TurnDirection1 = BalanceCar_IN_End1;
        BalanceCar_DW.temporalCounter_i1 = 0U;
      } else {
        BalanceCar_B.DirectionTargetPWM += 5.0;
      }
      break;
    }
  }

  /* End of Chart: '<S3>/ReverseLazer' */

  /* Sum: '<S3>/Add' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S3>/Constant1'
   *  Inport: '<Root>/Input6'
   *  Product: '<S3>/Divide'
   *  Product: '<S3>/Divide1'
   */
  Direction_PWM = (int16_T)floor((real32_T)Gyro_Turn * DIRECTION_KD +
    BalanceCar_B.DirectionTargetPWM * DIRECTION_KP);
}

/* System initialize for function-call system: '<S8>/abs' */
static void BalanceCar_abs_Init(uint16_T *rty_y, P_abs_BalanceCar_T *localP)
{
  /* SystemInitialize for Outport: '<S9>/y' */
  *rty_y = localP->y_Y0;
}

/* Output and update for function-call system: '<S8>/abs' */
static void BalanceCar_abs(int16_T rtu_x, uint16_T *rty_y)
{
  /* Abs: '<S9>/Abs' */
  if (rtu_x < 0) {
    *rty_y = (uint16_T)-rtu_x;
  } else {
    *rty_y = (uint16_T)rtu_x;
  }

  /* End of Abs: '<S9>/Abs' */
}

/* Function for Chart: '<S4>/MotorPinOutput' */
static void BalanceCar_Motor1Backward(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h)
{
  *Motor1_A_a = ((uint8_T)HIGH);
  *Motor1_B_h = ((uint8_T)LOW);
}

/* Function for Chart: '<S4>/MotorPinOutput' */
static void BalanceCar_Motor1Forward(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h)
{
  *Motor1_A_a = ((uint8_T)LOW);
  *Motor1_B_h = ((uint8_T)HIGH);
}

/* Function for Chart: '<S4>/MotorPinOutput' */
static void BalanceCar_SetDirection(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h,
  uint8_T *Motor2_A_n, uint8_T *Motor2_B_p, const int16_T *Saturation2, const
  int16_T *Saturation3)
{
  if (*Saturation2 > ((uint8_T)NUM0)) {
    BalanceCar_Motor1Forward(Motor1_A_a, Motor1_B_h);
  } else {
    BalanceCar_Motor1Backward(Motor1_A_a, Motor1_B_h);
  }

  if (*Saturation3 > ((uint8_T)NUM0)) {
    BalanceCar_Motor1Forward(Motor2_A_n, Motor2_B_p);
  } else {
    BalanceCar_Motor1Backward(Motor2_A_n, Motor2_B_p);
  }
}

/* Function for Chart: '<S4>/MotorPinOutput' */
static void BalanceCar_MotorStop(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h,
  uint8_T *Motor2_A_n, uint8_T *Motor2_B_p, uint16_T *rty_Motor1PWM1, uint16_T
  *rty_Motor2PWM1)
{
  *Motor1_A_a = ((uint8_T)LOW);
  *Motor1_B_h = ((uint8_T)LOW);
  *Motor2_A_n = ((uint8_T)LOW);
  *Motor2_B_p = ((uint8_T)LOW);
  *rty_Motor1PWM1 = ((uint8_T)NUM0);
  *rty_Motor2PWM1 = ((uint8_T)NUM0);
}

/* Function for Chart: '<S4>/MotorPinOutput' */
static void BalanceCar_FallDownDetect(uint8_T *Motor1_A_a, uint8_T *Motor1_B_h,
  uint8_T *Motor2_A_n, uint8_T *Motor2_B_p, real32_T rtu_Angle, uint16_T
  *rty_Motor1PWM1, uint16_T *rty_Motor2PWM1)
{
  /* Chart: '<S4>/MotorPinOutput' */
  if ((rtu_Angle > 55.0F) || (rtu_Angle < -50.0F)) {
    BalanceCar_MotorStop(Motor1_A_a, Motor1_B_h, Motor2_A_n, Motor2_B_p,
                         rty_Motor1PWM1, rty_Motor2PWM1);
  }

  /* End of Chart: '<S4>/MotorPinOutput' */
}

/* System initialize for function-call system: '<Root>/SetPWM' */
static void BalanceCar_SetPWM_Init(uint16_T *rty_Motor1PWM1, uint16_T
  *rty_Motor2PWM1, P_SetPWM_BalanceCar_T *localP)
{
  uint16_T Abs;
  *rty_Motor1PWM1 = 0U;
  *rty_Motor2PWM1 = 0U;

  /* SystemInitialize for Chart: '<S4>/MotorPinOutput' incorporates:
   *  SubSystem: '<S8>/abs'
   */
  BalanceCar_abs_Init(&Abs, &localP->abs_g);
}

/* Output and update for function-call system: '<Root>/SetPWM' */
static void BalanceCar_SetPWM(real32_T rtu_Angle, int16_T rtu_Motor1PWMTemp,
  int16_T rtu_Motor2PWMTemp, uint16_T *rty_Motor1PWM1, uint16_T *rty_Motor2PWM1,
  uint8_T *rty_Motor1_A1, uint8_T *rty_Motor1_B1, uint8_T *rty_Motor2_A1,
  uint8_T *rty_Motor2_B1, DW_SetPWM_BalanceCar_T *localDW, P_SetPWM_BalanceCar_T
  *localP)
{
  int16_T Saturation2;
  int16_T Saturation3;
  uint16_T Abs;

  /* Saturate: '<S4>/Saturation2' */
  if (rtu_Motor1PWMTemp > localP->Saturation2_UpperSat) {
    /* Saturate: '<S4>/Saturation2' */
    Saturation2 = localP->Saturation2_UpperSat;
  } else if (rtu_Motor1PWMTemp < localP->Saturation2_LowerSat) {
    /* Saturate: '<S4>/Saturation2' */
    Saturation2 = localP->Saturation2_LowerSat;
  } else {
    /* Saturate: '<S4>/Saturation2' */
    Saturation2 = rtu_Motor1PWMTemp;
  }

  /* End of Saturate: '<S4>/Saturation2' */

  /* Saturate: '<S4>/Saturation3' */
  if (rtu_Motor2PWMTemp > localP->Saturation3_UpperSat) {
    /* Saturate: '<S4>/Saturation3' */
    Saturation3 = localP->Saturation3_UpperSat;
  } else if (rtu_Motor2PWMTemp < localP->Saturation3_LowerSat) {
    /* Saturate: '<S4>/Saturation3' */
    Saturation3 = localP->Saturation3_LowerSat;
  } else {
    /* Saturate: '<S4>/Saturation3' */
    Saturation3 = rtu_Motor2PWMTemp;
  }

  /* End of Saturate: '<S4>/Saturation3' */

  /* Chart: '<S4>/MotorPinOutput' */
  if (localDW->is_active_c8_BalanceCar == 0U) {
    localDW->is_active_c8_BalanceCar = 1U;

    /* SignalConversion generated from: '<S8>/ SFunction ' */
    *rty_Motor1_A1 = ((uint8_T)LOW);

    /* SignalConversion generated from: '<S8>/ SFunction ' */
    *rty_Motor1_B1 = ((uint8_T)LOW);

    /* SignalConversion generated from: '<S8>/ SFunction ' */
    *rty_Motor2_A1 = ((uint8_T)LOW);

    /* SignalConversion generated from: '<S8>/ SFunction ' */
    *rty_Motor2_B1 = ((uint8_T)LOW);
  } else {
    /* Outputs for Function Call SubSystem: '<S8>/abs' */
    BalanceCar_abs(Saturation2, &Abs);

    /* End of Outputs for SubSystem: '<S8>/abs' */
    *rty_Motor1PWM1 = Abs;

    /* Outputs for Function Call SubSystem: '<S8>/abs' */
    BalanceCar_abs(Saturation3, &Abs);

    /* End of Outputs for SubSystem: '<S8>/abs' */
    *rty_Motor2PWM1 = Abs;

    /* SignalConversion generated from: '<S8>/ SFunction ' */
    BalanceCar_SetDirection(rty_Motor1_A1, rty_Motor1_B1, rty_Motor2_A1,
      rty_Motor2_B1, &Saturation2, &Saturation3);
    BalanceCar_FallDownDetect(rty_Motor1_A1, rty_Motor1_B1, rty_Motor2_A1,
      rty_Motor2_B1, rtu_Angle, rty_Motor1PWM1, rty_Motor2PWM1);
  }

  /* End of Chart: '<S4>/MotorPinOutput' */
}

/* Function for Chart: '<Root>/BalanceCarTask' */
static void BalanceCar_Task_5ms(const int16_T *UnitDelay, const int16_T
  *UnitDelay1)
{
  if (BalanceCar_DW.task_5ms_count == 1) {
    /* Outputs for Function Call SubSystem: '<Root>/BalanceControl' */
    /* Inport: '<Root>/Input3' incorporates:
     *  Inport: '<Root>/Input5'
     *  Inport: '<Root>/Input8'
     */
    BalanceCar_BalanceControl(Angle, Gyro_Angle, BalanceCarOffset, &Balance_PWM);

    /* End of Outputs for SubSystem: '<Root>/BalanceControl' */
  }

  if (BalanceCar_DW.task_5ms_count == 2) {
    /* Outputs for Function Call SubSystem: '<Root>/SetPWM' */
    /* Inport: '<Root>/Input3' */
    BalanceCar_SetPWM(Angle, *UnitDelay, *UnitDelay1, &Motor1PWM, &Motor2PWM,
                      &Motor1_A, &Motor1_B, &Motor2_A, &Motor2_B,
                      &BalanceCar_DW.SetPWM, &BalanceCar_P.SetPWM);

    /* End of Outputs for SubSystem: '<Root>/SetPWM' */
  }
}

/* Function for Chart: '<Root>/BalanceCarTask' */
static void BalanceCar_Task_10ms(void)
{
  if (BalanceCar_DW.task_10ms_count == 2) {
    /* Outputs for Function Call SubSystem: '<Root>/SpeedControl' */
    SpeedControl();

    /* End of Outputs for SubSystem: '<Root>/SpeedControl' */
  }
}

/* Function for Chart: '<Root>/BalanceCarTask' */
static void BalanceCar_Task_20ms(void)
{
  if (BalanceCar_DW.task_20ms_count == 3) {
    /* Outputs for Function Call SubSystem: '<Root>/DirectionControl' */
    DirectionControl();

    /* End of Outputs for SubSystem: '<Root>/DirectionControl' */
  }
}

/* Model step function */
void BalanceCar_step(void)
{
  int32_T UnitDelay_DSTATE_tmp;

  /* Chart: '<Root>/BalanceCarTask' incorporates:
   *  UnitDelay: '<Root>/Unit Delay'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  UnitDelay_DSTATE_tmp = (int32_T)(BalanceCar_DW.task_5ms_count + 1U);
  if (BalanceCar_DW.task_5ms_count + 1U > 255U) {
    UnitDelay_DSTATE_tmp = 255;
  }

  BalanceCar_DW.task_5ms_count = (uint8_T)UnitDelay_DSTATE_tmp;
  if ((uint8_T)((uint32_T)BalanceCar_DW.task_5ms_count -
                BalanceCar_DW.task_5ms_count / 5 * 5) == 0) {
    BalanceCar_DW.task_5ms_count = 0U;
  }

  UnitDelay_DSTATE_tmp = (int32_T)(BalanceCar_DW.task_10ms_count + 1U);
  if (BalanceCar_DW.task_10ms_count + 1U > 255U) {
    UnitDelay_DSTATE_tmp = 255;
  }

  BalanceCar_DW.task_10ms_count = (uint8_T)UnitDelay_DSTATE_tmp;
  if ((uint8_T)((uint32_T)BalanceCar_DW.task_10ms_count -
                BalanceCar_DW.task_10ms_count / 10 * 10) == 0) {
    BalanceCar_DW.task_10ms_count = 0U;
  }

  UnitDelay_DSTATE_tmp = (int32_T)(BalanceCar_DW.task_20ms_count + 1U);
  if (BalanceCar_DW.task_20ms_count + 1U > 255U) {
    UnitDelay_DSTATE_tmp = 255;
  }

  BalanceCar_DW.task_20ms_count = (uint8_T)UnitDelay_DSTATE_tmp;
  if ((uint8_T)((uint32_T)BalanceCar_DW.task_20ms_count -
                BalanceCar_DW.task_20ms_count / 20 * 20) == 0) {
    BalanceCar_DW.task_20ms_count = 1U;
  }

  UnitDelay_DSTATE_tmp = (int32_T)(BalanceCar_DW.task_50ms_count + 1U);
  if (BalanceCar_DW.task_50ms_count + 1U > 255U) {
    UnitDelay_DSTATE_tmp = 255;
  }

  BalanceCar_DW.task_50ms_count = (uint8_T)UnitDelay_DSTATE_tmp;
  if ((uint8_T)((uint32_T)BalanceCar_DW.task_50ms_count -
                BalanceCar_DW.task_50ms_count / 50 * 50) == 0) {
    BalanceCar_DW.task_50ms_count = 0U;
  }

  BalanceCar_Task_5ms(&BalanceCar_DW.UnitDelay_DSTATE,
                      &BalanceCar_DW.UnitDelay1_DSTATE);
  BalanceCar_Task_10ms();
  BalanceCar_Task_20ms();

  /* End of Chart: '<Root>/BalanceCarTask' */

  /* Sum: '<Root>/CacluateMotor1PWM' incorporates:
   *  Sum: '<Root>/CacluateMotor2PWM'
   */
  UnitDelay_DSTATE_tmp = (int16_T)(Balance_PWM + Speed_PWM);

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  Sum: '<Root>/CacluateMotor1PWM'
   */
  BalanceCar_DW.UnitDelay_DSTATE = (int16_T)(UnitDelay_DSTATE_tmp +
    Direction_PWM);

  /* Update for UnitDelay: '<Root>/Unit Delay1' incorporates:
   *  Sum: '<Root>/CacluateMotor2PWM'
   */
  BalanceCar_DW.UnitDelay1_DSTATE = (int16_T)(UnitDelay_DSTATE_tmp -
    Direction_PWM);

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  BalanceCar_M->Timing.clockTick0++;
}

/* Model initialize function */
void BalanceCar_initialize(void)
{
  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  BalanceCar_DW.UnitDelay_DSTATE = BalanceCar_P.UnitDelay_InitialCondition;

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay1' */
  BalanceCar_DW.UnitDelay1_DSTATE = BalanceCar_P.UnitDelay1_InitialCondition;

  /* SystemInitialize for Chart: '<Root>/BalanceCarTask' incorporates:
   *  SubSystem: '<Root>/SpeedControl'
   */
  SpeedControl_Init();

  /* SystemInitialize for Chart: '<Root>/BalanceCarTask' incorporates:
   *  SubSystem: '<Root>/BalanceControl'
   */
  BalanceCar_BalanceControl_Init(&Balance_PWM, &BalanceCar_P.BalanceControl);

  /* SystemInitialize for Chart: '<Root>/BalanceCarTask' incorporates:
   *  SubSystem: '<Root>/DirectionControl'
   */
  DirectionControl_Init();

  /* SystemInitialize for Chart: '<Root>/BalanceCarTask' incorporates:
   *  SubSystem: '<Root>/SetPWM'
   */
  BalanceCar_SetPWM_Init(&Motor1PWM, &Motor2PWM, &BalanceCar_P.SetPWM);

  /* Enable for Chart: '<Root>/BalanceCarTask' incorporates:
   *  SubSystem: '<Root>/SpeedControl'
   */
  SpeedControl_Enable();

  /* Enable for Chart: '<Root>/BalanceCarTask' incorporates:
   *  SubSystem: '<Root>/DirectionControl'
   */
  DirectionControl_Enable();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
