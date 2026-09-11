/*
 * @Author       : Yuan Ge
 * @Date         : 2024-05-31
 * @LastEditors  : Yuan Ge
 * @LastEditTime : 2024-06-21 
 * @Description  : 
 * @FilePath     : 
 */
#include "sr04.h"
#include "delay.h"
Hcsr04InfoTypeDef Hcsr04Info;

static volatile uint8_t s_echo_pending = 0;	/* 1: 本轮触发尚未得到结果 */
static uint32_t s_echo_start_ms = 0;			/* 触发时刻(ms) */

/**
 * @description: ??????????????????
 * @param {TIM_HandleTypeDef} *htim
 * @param {uint32_t} Channel
 * @return {*}
 */
void Hcsr04Init(TIM_HandleTypeDef *htim, uint32_t Channel)
{
  /*--------[ Configure The HCSR04 IC Timer Channel ] */
  // MX_TIM2_Init();  // cubemx???
  Hcsr04Info.prescaler = htim->Init.Prescaler; //  72-1
  Hcsr04Info.period = htim->Init.Period;       //  65535
	Hcsr04Info.ic_tim_ch = Channel;
  Hcsr04Info.instance = htim->Instance;
  Hcsr04Info.htim = htim;
  if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_1)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_1;             //  TIM_CHANNEL_1
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_2)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_2;             //  TIM_CHANNEL_2
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_3)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_3;             //  TIM_CHANNEL_3
  }
  else if(Hcsr04Info.ic_tim_ch == TIM_CHANNEL_4)
  {
    Hcsr04Info.active_channel = HAL_TIM_ACTIVE_CHANNEL_4;             //  TIM_CHANNEL_4
  }
  /*--------[ Start The ICU Channel ]-------*/
  HAL_TIM_Base_Start_IT(htim);
  HAL_TIM_IC_Start_IT(htim, Channel);//????
}

/**
 * @description: HC-SR04??
 * @param {*}
 * @return {*}
 */
void Hcsr04Start(void)
{
  if(s_echo_pending) return;	/* 上一轮还未完成, 不重复触发(否则超时窗口会被反复清零) */
  HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
  delay_us(20);  //  10us??
  HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
  s_echo_pending = 1;
  s_echo_start_ms = HAL_GetTick();
}

/**
 * @description: ?????????????
 * @param {*}    main.c????void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
 * @return {*}
 */
void Hcsr04TimOverflowIsr(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == Hcsr04Info.instance) //  
  {
    Hcsr04Info.tim_overflow_counter++;
  }
}

/**
 * @description: ???????????->??
 * @param {*}    main.c????void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
 * @return {*}
 */
void Hcsr04TimIcIsr(TIM_HandleTypeDef* htim)
{
  if((htim->Instance == Hcsr04Info.instance) && (htim->Channel == Hcsr04Info.active_channel))
  {
    if(Hcsr04Info.edge_state == 0)      //  ?????
    {
      // ?????????T1,???????????
      Hcsr04Info.t1 = HAL_TIM_ReadCapturedValue(htim, Hcsr04Info.ic_tim_ch);
      __HAL_TIM_SET_CAPTUREPOLARITY(htim, Hcsr04Info.ic_tim_ch, TIM_INPUTCHANNELPOLARITY_FALLING);
      Hcsr04Info.tim_overflow_counter = 0;  //  ??????????
      Hcsr04Info.edge_state = 1;        //  ????????????
    }
    else if(Hcsr04Info.edge_state == 1) //  ?????
    {
      // ???????T2,????????
      Hcsr04Info.t2 = HAL_TIM_ReadCapturedValue(htim, Hcsr04Info.ic_tim_ch);
      Hcsr04Info.t2 += Hcsr04Info.tim_overflow_counter * Hcsr04Info.period; //  ???????????
      Hcsr04Info.high_level_us = Hcsr04Info.t2 - Hcsr04Info.t1; //  ??????? = ?????? - ??????
      // ????
      Hcsr04Info.distance = (Hcsr04Info.high_level_us / 1000000.0) * 340.0 / 2.0 * 100.0;
      s_echo_pending = 0;	/* 本轮测量完成 */
      // ?????????
      Hcsr04Info.edge_state = 0;  //  ??????,??
      __HAL_TIM_SET_CAPTUREPOLARITY(htim, Hcsr04Info.ic_tim_ch, TIM_INPUTCHANNELPOLARITY_RISING);
    }
  }
}

/**
 * @description: ???? 
 * @param {*}
 * @return {*}
 */
float Hcsr04Read(void)
{
  // ??????
  if(Hcsr04Info.distance >= 450)
  {
    Hcsr04Info.distance = 450;
  }
  return Hcsr04Info.distance;
}

/**
 * @description: 无回波超时判定(在任务上下文调用)
 * 正前方超出量程时 ECHO 不产生脉冲, 捕获中断永不触发, distance 会永久
 * 冻结在上一次有效值。此函数在超时后把 distance 置为超量程哨兵值, 并
 * 重新武装捕获极性, 修复"下降沿不来导致永久失步"的卡死形态。
 */
void Hcsr04TimeoutHandle(void)
{
  uint32_t primask;

  if(!s_echo_pending) return;
  if((uint32_t)(HAL_GetTick() - s_echo_start_ms) < HCSR04_ECHO_TIMEOUT_MS) return;

  primask = __get_PRIMASK();
  __disable_irq();
  if(s_echo_pending)	/* 临界区内二次确认: ISR 可能刚完成一次有效测量 */
  {
    Hcsr04Info.distance = HCSR04_OPEN_DISTANCE_CM;	/* 畅通哨兵 */
    Hcsr04Info.edge_state = 0;
    Hcsr04Info.tim_overflow_counter = 0;
    __HAL_TIM_SET_CAPTUREPOLARITY(Hcsr04Info.htim, Hcsr04Info.ic_tim_ch, TIM_INPUTCHANNELPOLARITY_RISING);
    s_echo_pending = 0;
  }
  __set_PRIMASK(primask);
}
#if 1
/* USER CODE BEGIN 4 */
/**
 * @description: ?????????
 * @param {TIM_HandleTypeDef} *htim
 * @return {*}
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  Hcsr04TimIcIsr(htim);
}

/**
 * @description: ???????
 * @param {*}
 * @return {*}
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		Hcsr04TimOverflowIsr(htim);
}
/* USER CODE END 4 */

#endif
