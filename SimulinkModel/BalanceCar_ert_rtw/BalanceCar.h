/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: BalanceCar.h
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

#ifndef RTW_HEADER_BalanceCar_h_
#define RTW_HEADER_BalanceCar_h_
#ifndef BalanceCar_COMMON_INCLUDES_
#define BalanceCar_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* BalanceCar_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Exported data define */

/* Definition for custom storage class: Define */
#define BALANCE_KD                     0.08F                     /* Referenced by: '<S2>/BALANCE_KD' */
#define BALANCE_KP                     40.0F                     /* Referenced by: '<S2>/BALANCE_KP' */
#define DIRECTION_KD                   0.01F                      /* Referenced by: '<S3>/Constant' */
#define DIRECTION_KP                   10.0F                     /* Referenced by: '<S3>/Constant1' */
#define HIGH                           1U                        /* Referenced by: '<S4>/MotorPinOutput' */
#define LOW                            0U                        /* Referenced by: '<S4>/MotorPinOutput' */
#define NUM0                           0U                        /* Referenced by:
                                                                  * '<S4>/MotorPinOutput'
                                                                  * '<S5>/Debounce'
                                                                  * '<S5>/Debounce1'
                                                                  */
#define OFF                            1U                        /* Referenced by:
                                                                  * '<S5>/Debounce'
                                                                  * '<S5>/Debounce1'
                                                                  */
#define ON                             0U                        /* Referenced by:
                                                                  * '<S5>/Chart'
                                                                  * '<S5>/Debounce'
                                                                  * '<S5>/Debounce1'
                                                                  */
#define SPEED_KD                       0.0F                      /* Referenced by: '<S39>/Derivative Gain' */
#define SPEED_KI                       0.01F                     /* Referenced by: '<S42>/Integral Gain' */
#define SPEED_KP                       18.0F                     /* Referenced by: '<S50>/Proportional Gain' */

/* Forward declaration for rtModel */
typedef struct tag_RTM_BalanceCar_T RT_MODEL_BalanceCar_T;

/* Block states (default storage) for system '<S5>/Debounce' */
typedef struct {
  real_T durationOperatorLastReferenceTi;/* '<S5>/Debounce' */
  real_T chartDisableTime;             /* '<S5>/Debounce' */
  real_T durationOperatorLastReference_e;/* '<S5>/Debounce' */
  uint32_T presentTicks;               /* '<S5>/Debounce' */
  uint32_T elapsedTicks;               /* '<S5>/Debounce' */
  uint32_T previousTicks;              /* '<S5>/Debounce' */
  uint8_T is_active_c4_BalanceCar;     /* '<S5>/Debounce' */
  uint8_T is_Debounce;                 /* '<S5>/Debounce' */
  uint8_T KeyState;                    /* '<S5>/Debounce' */
  boolean_T KeyOnFlag;                 /* '<S5>/Debounce' */
  boolean_T condWasTrueAtLastTimeStep_1;/* '<S5>/Debounce' */
  boolean_T condWasTrueAtLastTimeStep_1_a;/* '<S5>/Debounce' */
} DW_Debounce_BalanceCar_T;

/* Block states (default storage) for system '<Root>/SetPWM' */
typedef struct {
  uint8_T is_active_c8_BalanceCar;     /* '<S4>/MotorPinOutput' */
} DW_SetPWM_BalanceCar_T;

/* Block signals (default storage) */
typedef struct {
  real_T DirectionTargetPWM;           /* '<S3>/ReverseLazer' */
  uint8_T y;                           /* '<S3>/Truth Table' */
  uint8_T KeyOutput;                   /* '<S5>/Debounce1' */
  uint8_T KeyOutput_e;                 /* '<S5>/Debounce' */
} B_BalanceCar_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Filter_DSTATE;                /* '<S40>/Filter' */
  real_T Integrator_DSTATE;            /* '<S45>/Integrator' */
  real_T Filter_PREV_U;                /* '<S40>/Filter' */
  uint32_T previousTicks;              /* '<S3>/ReverseLazer' */
  uint32_T SpeedControl_PREV_T;        /* '<Root>/SpeedControl' */
  int16_T UnitDelay_DSTATE;            /* '<Root>/Unit Delay' */
  int16_T UnitDelay1_DSTATE;           /* '<Root>/Unit Delay1' */
  uint8_T task_5ms_count;              /* '<Root>/BalanceCarTask' */
  uint8_T task_10ms_count;             /* '<Root>/BalanceCarTask' */
  uint8_T task_20ms_count;             /* '<Root>/BalanceCarTask' */
  uint8_T task_50ms_count;             /* '<Root>/BalanceCarTask' */
  uint8_T is_active_c1_BalanceCar;     /* '<S3>/ReverseLazer' */
  uint8_T is_c1_BalanceCar;            /* '<S3>/ReverseLazer' */
  uint8_T is_TurnDirection1;           /* '<S3>/ReverseLazer' */
  uint8_T is_StopTurn;                 /* '<S3>/ReverseLazer' */
  uint8_T temporalCounter_i1;          /* '<S3>/ReverseLazer' */
  uint8_T Filter_SYSTEM_ENABLE;        /* '<S40>/Filter' */
  uint8_T is_active_c6_BalanceCar;     /* '<S5>/Chart' */
  boolean_T SpeedControl_RESET_ELAPS_T;/* '<Root>/SpeedControl' */
  DW_SetPWM_BalanceCar_T SetPWM;       /* '<Root>/SetPWM' */
  DW_Debounce_BalanceCar_T sf_Debounce1;/* '<S5>/Debounce1' */
  DW_Debounce_BalanceCar_T sf_Debounce;/* '<S5>/Debounce' */
} DW_BalanceCar_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Accel_Z;                      /* '<Root>/Accel_Z' */
  real_T Temperature;                  /* '<Root>/Temperature' */
  real_T Humidity;                     /* '<Root>/Humidity' */
} ExtU_BalanceCar_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Output6;                      /* '<Root>/Output6' */
  real_T Output7;                      /* '<Root>/Output7' */
} ExtY_BalanceCar_T;

/* Parameters for system: '<Root>/BalanceControl' */
struct P_BalanceControl_BalanceCar_T_ {
  int16_T Balance_PWM_Y0;              /* Computed Parameter: Balance_PWM_Y0
                                        * Referenced by: '<S2>/Balance_PWM'
                                        */
};

/* Parameters for system: '<Root>/BalanceControl' */
typedef struct P_BalanceControl_BalanceCar_T_ P_BalanceControl_BalanceCar_T;

/* Parameters for system: '<S8>/abs' */
struct P_abs_BalanceCar_T_ {
  uint16_T y_Y0;                       /* Computed Parameter: y_Y0
                                        * Referenced by: '<S9>/y'
                                        */
};

/* Parameters for system: '<S8>/abs' */
typedef struct P_abs_BalanceCar_T_ P_abs_BalanceCar_T;

/* Parameters for system: '<Root>/SetPWM' */
struct P_SetPWM_BalanceCar_T_ {
  int16_T Saturation2_UpperSat;      /* Computed Parameter: Saturation2_UpperSat
                                      * Referenced by: '<S4>/Saturation2'
                                      */
  int16_T Saturation2_LowerSat;      /* Computed Parameter: Saturation2_LowerSat
                                      * Referenced by: '<S4>/Saturation2'
                                      */
  int16_T Saturation3_UpperSat;      /* Computed Parameter: Saturation3_UpperSat
                                      * Referenced by: '<S4>/Saturation3'
                                      */
  int16_T Saturation3_LowerSat;      /* Computed Parameter: Saturation3_LowerSat
                                      * Referenced by: '<S4>/Saturation3'
                                      */
  P_abs_BalanceCar_T abs_g;            /* '<S8>/abs' */
};

/* Parameters for system: '<Root>/SetPWM' */
typedef struct P_SetPWM_BalanceCar_T_ P_SetPWM_BalanceCar_T;

/* Parameters (default storage) */
struct P_BalanceCar_T_ {
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S40>/Filter'
                               */
  real_T PIDController_InitialConditio_j;
                              /* Mask Parameter: PIDController_InitialConditio_j
                               * Referenced by: '<S45>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S48>/Filter Coefficient'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S40>/Filter'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S45>/Integrator'
                                        */
  int16_T Speed_PWM_Y0;                /* Computed Parameter: Speed_PWM_Y0
                                        * Referenced by: '<S5>/Speed_PWM'
                                        */
  int16_T Saturation_UpperSat;        /* Computed Parameter: Saturation_UpperSat
                                       * Referenced by: '<S5>/Saturation'
                                       */
  int16_T Saturation_LowerSat;        /* Computed Parameter: Saturation_LowerSat
                                       * Referenced by: '<S5>/Saturation'
                                       */
  int16_T Direction_PWM_Y0;            /* Computed Parameter: Direction_PWM_Y0
                                        * Referenced by: '<S3>/Direction_PWM'
                                        */
  int16_T UnitDelay_InitialCondition;
                               /* Computed Parameter: UnitDelay_InitialCondition
                                * Referenced by: '<Root>/Unit Delay'
                                */
  int16_T UnitDelay1_InitialCondition;
                              /* Computed Parameter: UnitDelay1_InitialCondition
                               * Referenced by: '<Root>/Unit Delay1'
                               */
  boolean_T AvoidObstacleEnable_Value; /* Expression: true
                                        * Referenced by: '<S3>/AvoidObstacleEnable'
                                        */
  int8_T Constant_Value;               /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S5>/Constant'
                                        */
  P_SetPWM_BalanceCar_T SetPWM;        /* '<Root>/SetPWM' */
  P_BalanceControl_BalanceCar_T BalanceControl;/* '<Root>/BalanceControl' */
};

/* Parameters (default storage) */
typedef struct P_BalanceCar_T_ P_BalanceCar_T;

/* Real-time Model Data Structure */
struct tag_RTM_BalanceCar_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

/* Block parameters (default storage) */
extern P_BalanceCar_T BalanceCar_P;

/* Block signals (default storage) */
extern B_BalanceCar_T BalanceCar_B;

/* Block states (default storage) */
extern DW_BalanceCar_T BalanceCar_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_BalanceCar_T BalanceCar_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_BalanceCar_T BalanceCar_Y;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern real32_T Angle;                 /* '<Root>/Input3' */
extern int16_T Gyro_Angle;             /* '<Root>/Input5' */
extern uint8_T Key1;                   /* '<Root>/Input' */
extern uint8_T Key2;                   /* '<Root>/Input1' */
extern int16_T Motor1Speed;            /* '<Root>/Input2' */
extern int16_T Motor2Speed;            /* '<Root>/Input4' */
extern int16_T Gyro_Turn;              /* '<Root>/Input6' */
extern real32_T Model_Distance;        /* '<Root>/Input7' */
extern real32_T BalanceCarOffset;      /* '<Root>/Input8' */
extern uint16_T Motor1PWM;             /* '<S4>/MotorPinOutput' */
extern uint16_T Motor2PWM;             /* '<S4>/MotorPinOutput' */
extern int16_T Direction_PWM;          /* '<S3>/Add' */
extern int16_T Balance_PWM;            /* '<S2>/Add' */
extern int16_T Speed_PWM;              /* '<S5>/Saturation' */
extern int16_T BalanceCarTargetSpeed;  /* '<S5>/Chart' */
extern uint8_T Motor1_A;               /* '<S4>/MotorPinOutput' */
extern uint8_T Motor1_B;               /* '<S4>/MotorPinOutput' */
extern uint8_T Motor2_A;               /* '<S4>/MotorPinOutput' */
extern uint8_T Motor2_B;               /* '<S4>/MotorPinOutput' */

/* Model entry point functions */
extern void BalanceCar_initialize(void);
extern void BalanceCar_step(void);

/* Real-time Model object */
extern RT_MODEL_BalanceCar_T *const BalanceCar_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<S5>/Scope2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'BalanceCar'
 * '<S1>'   : 'BalanceCar/BalanceCarTask'
 * '<S2>'   : 'BalanceCar/BalanceControl'
 * '<S3>'   : 'BalanceCar/DirectionControl'
 * '<S4>'   : 'BalanceCar/SetPWM'
 * '<S5>'   : 'BalanceCar/SpeedControl'
 * '<S6>'   : 'BalanceCar/DirectionControl/ReverseLazer'
 * '<S7>'   : 'BalanceCar/DirectionControl/Truth Table'
 * '<S8>'   : 'BalanceCar/SetPWM/MotorPinOutput'
 * '<S9>'   : 'BalanceCar/SetPWM/MotorPinOutput/abs'
 * '<S10>'  : 'BalanceCar/SpeedControl/Chart'
 * '<S11>'  : 'BalanceCar/SpeedControl/Debounce'
 * '<S12>'  : 'BalanceCar/SpeedControl/Debounce1'
 * '<S13>'  : 'BalanceCar/SpeedControl/PID Controller'
 * '<S14>'  : 'BalanceCar/SpeedControl/PID Controller/Anti-windup'
 * '<S15>'  : 'BalanceCar/SpeedControl/PID Controller/D Gain'
 * '<S16>'  : 'BalanceCar/SpeedControl/PID Controller/Filter'
 * '<S17>'  : 'BalanceCar/SpeedControl/PID Controller/Filter ICs'
 * '<S18>'  : 'BalanceCar/SpeedControl/PID Controller/I Gain'
 * '<S19>'  : 'BalanceCar/SpeedControl/PID Controller/Ideal P Gain'
 * '<S20>'  : 'BalanceCar/SpeedControl/PID Controller/Ideal P Gain Fdbk'
 * '<S21>'  : 'BalanceCar/SpeedControl/PID Controller/Integrator'
 * '<S22>'  : 'BalanceCar/SpeedControl/PID Controller/Integrator ICs'
 * '<S23>'  : 'BalanceCar/SpeedControl/PID Controller/N Copy'
 * '<S24>'  : 'BalanceCar/SpeedControl/PID Controller/N Gain'
 * '<S25>'  : 'BalanceCar/SpeedControl/PID Controller/P Copy'
 * '<S26>'  : 'BalanceCar/SpeedControl/PID Controller/Parallel P Gain'
 * '<S27>'  : 'BalanceCar/SpeedControl/PID Controller/Reset Signal'
 * '<S28>'  : 'BalanceCar/SpeedControl/PID Controller/Saturation'
 * '<S29>'  : 'BalanceCar/SpeedControl/PID Controller/Saturation Fdbk'
 * '<S30>'  : 'BalanceCar/SpeedControl/PID Controller/Sum'
 * '<S31>'  : 'BalanceCar/SpeedControl/PID Controller/Sum Fdbk'
 * '<S32>'  : 'BalanceCar/SpeedControl/PID Controller/Tracking Mode'
 * '<S33>'  : 'BalanceCar/SpeedControl/PID Controller/Tracking Mode Sum'
 * '<S34>'  : 'BalanceCar/SpeedControl/PID Controller/Tsamp - Integral'
 * '<S35>'  : 'BalanceCar/SpeedControl/PID Controller/Tsamp - Ngain'
 * '<S36>'  : 'BalanceCar/SpeedControl/PID Controller/postSat Signal'
 * '<S37>'  : 'BalanceCar/SpeedControl/PID Controller/preSat Signal'
 * '<S38>'  : 'BalanceCar/SpeedControl/PID Controller/Anti-windup/Passthrough'
 * '<S39>'  : 'BalanceCar/SpeedControl/PID Controller/D Gain/Internal Parameters'
 * '<S40>'  : 'BalanceCar/SpeedControl/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S41>'  : 'BalanceCar/SpeedControl/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S42>'  : 'BalanceCar/SpeedControl/PID Controller/I Gain/Internal Parameters'
 * '<S43>'  : 'BalanceCar/SpeedControl/PID Controller/Ideal P Gain/Passthrough'
 * '<S44>'  : 'BalanceCar/SpeedControl/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S45>'  : 'BalanceCar/SpeedControl/PID Controller/Integrator/Discrete'
 * '<S46>'  : 'BalanceCar/SpeedControl/PID Controller/Integrator ICs/Internal IC'
 * '<S47>'  : 'BalanceCar/SpeedControl/PID Controller/N Copy/Disabled'
 * '<S48>'  : 'BalanceCar/SpeedControl/PID Controller/N Gain/Internal Parameters'
 * '<S49>'  : 'BalanceCar/SpeedControl/PID Controller/P Copy/Disabled'
 * '<S50>'  : 'BalanceCar/SpeedControl/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S51>'  : 'BalanceCar/SpeedControl/PID Controller/Reset Signal/Disabled'
 * '<S52>'  : 'BalanceCar/SpeedControl/PID Controller/Saturation/Passthrough'
 * '<S53>'  : 'BalanceCar/SpeedControl/PID Controller/Saturation Fdbk/Disabled'
 * '<S54>'  : 'BalanceCar/SpeedControl/PID Controller/Sum/Sum_PID'
 * '<S55>'  : 'BalanceCar/SpeedControl/PID Controller/Sum Fdbk/Disabled'
 * '<S56>'  : 'BalanceCar/SpeedControl/PID Controller/Tracking Mode/Disabled'
 * '<S57>'  : 'BalanceCar/SpeedControl/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S58>'  : 'BalanceCar/SpeedControl/PID Controller/Tsamp - Integral/Passthrough'
 * '<S59>'  : 'BalanceCar/SpeedControl/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S60>'  : 'BalanceCar/SpeedControl/PID Controller/postSat Signal/Forward_Path'
 * '<S61>'  : 'BalanceCar/SpeedControl/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_BalanceCar_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
