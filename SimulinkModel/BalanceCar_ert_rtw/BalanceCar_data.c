/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BalanceCar_data.c
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

/* Block parameters (default storage) */
P_BalanceCar_T BalanceCar_P = {
  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S40>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_j
   * Referenced by: '<S45>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S48>/Filter Coefficient'
   */
  100.0,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S40>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S45>/Integrator'
   */
  1.0,

  /* Computed Parameter: Speed_PWM_Y0
   * Referenced by: '<S5>/Speed_PWM'
   */
  0,

  /* Computed Parameter: Saturation_UpperSat
   * Referenced by: '<S5>/Saturation'
   */
  900,

  /* Computed Parameter: Saturation_LowerSat
   * Referenced by: '<S5>/Saturation'
   */
  -900,

  /* Computed Parameter: Direction_PWM_Y0
   * Referenced by: '<S3>/Direction_PWM'
   */
  0,

  /* Computed Parameter: UnitDelay_InitialCondition
   * Referenced by: '<Root>/Unit Delay'
   */
  0,

  /* Computed Parameter: UnitDelay1_InitialCondition
   * Referenced by: '<Root>/Unit Delay1'
   */
  0,

  /* Expression: true
   * Referenced by: '<S3>/AvoidObstacleEnable'
   */
  true,

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S5>/Constant'
   */
  2,

  /* Start of '<Root>/SetPWM' */
  {
    /* Computed Parameter: Saturation2_UpperSat
     * Referenced by: '<S4>/Saturation2'
     */
    990,

    /* Computed Parameter: Saturation2_LowerSat
     * Referenced by: '<S4>/Saturation2'
     */
    -990,

    /* Computed Parameter: Saturation3_UpperSat
     * Referenced by: '<S4>/Saturation3'
     */
    999,

    /* Computed Parameter: Saturation3_LowerSat
     * Referenced by: '<S4>/Saturation3'
     */
    -999,

    /* Start of '<S8>/abs' */
    {
      /* Computed Parameter: y_Y0
       * Referenced by: '<S9>/y'
       */
      0U
    }
    /* End of '<S8>/abs' */
  }
  ,

  /* End of '<Root>/SetPWM' */

  /* Start of '<Root>/BalanceControl' */
  {
    /* Computed Parameter: Balance_PWM_Y0
     * Referenced by: '<S2>/Balance_PWM'
     */
    0
  }
  /* End of '<Root>/BalanceControl' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
