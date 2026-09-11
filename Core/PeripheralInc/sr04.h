/*
 * @Author       : yzy
 * @Date         : 2021-05-31 17:03:27
 * @LastEditors  : yzy
 * @LastEditTime : 2021-05-31 19:02:54
 * @Description  : 
 * @FilePath     : \F103_Test\BSP_HARDWARE\hc-sr04.h
 */
#ifndef HCSR04_H_
#define HCSR04_H_

#include "main.h"

#define HCSR04_ECHO_TIMEOUT_MS	(30u)	/* no-echo timeout; must be < actual trigger period */
#define HCSR04_OPEN_DISTANCE_CM	(450.0f)/* out-of-range sentinel, means "clear road" */

typedef struct
{
	uint8_t  edge_state;
	uint16_t tim_overflow_counter;
	uint32_t prescaler;
	uint32_t period;
	uint32_t t1;	//	?????
	uint32_t t2;	//	?????
	uint32_t high_level_us;	//	???????
	float    distance;
	TIM_TypeDef* instance;
  uint32_t ic_tim_ch;
	HAL_TIM_ActiveChannel active_channel;
	TIM_HandleTypeDef* htim;/* saved by Hcsr04Init, used to re-arm capture polarity on timeout */
}Hcsr04InfoTypeDef;

extern Hcsr04InfoTypeDef Hcsr04Info;

/**
 * @description: ??????????????????
 * @param {TIM_HandleTypeDef} *htim
 * @param {uint32_t} Channel
 * @return {*}
 */
void Hcsr04Init(TIM_HandleTypeDef *htim, uint32_t Channel);

/**
 * @description: HC-SR04??
 * @param {*}
 * @return {*}
 */
void Hcsr04Start(void);

void Hcsr04TimeoutHandle(void);

/**
 * @description: ?????????????
 * @param {*}    main.c????void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
 * @return {*}
 */
void Hcsr04TimOverflowIsr(TIM_HandleTypeDef *htim);

/**
 * @description: ???????????->??
 * @param {*}    main.c????void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * @return {*}
 */
void Hcsr04TimIcIsr(TIM_HandleTypeDef* htim);

/**
 * @description: ???? 
 * @param {*}
 * @return {*}
 */
float Hcsr04Read(void);

#endif /* HCSR04_H_ */


