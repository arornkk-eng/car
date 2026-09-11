/*
 * @Author       : Yuan Ge
 * @Date         : 2024-05-31
 * @LastEditors  : Yuan Ge
 * @LastEditTime : 2024-06-21 
 * @Description  : 
 * @FilePath     : 
 */
#include "delay.h"
#include "stm32f1xx_hal.h"

//#define OLD_DELAY

static uint32_t g_fac_us = 0;            /* us ????? */
/**
* @brief    ???????
* @param    ?
* @retval   ?
*/
#ifdef OLD_DELAY
void delay_init(void)
{
	fac_us = HAL_RCC_GetHCLKFreq() / 1000000;   //72MHz/1000000 = 72
}
#else
/**
* @brief ???????
* @param sysclk: ??????, ? CPU ??(rcc_c_ck),72MHz
* @retval ?
*/
void delay_init(void)
{
	g_fac_us = HAL_RCC_GetHCLKFreq() / 1000000;
}
#endif
/**
* @brief    us????
* @note     ?????????us??
* @param    nus:????us?
* @note     nus????:0 ~ (2^32 / fac_us)(fac_us????????)
* @retval   ?
*/
#ifdef OLD_DELAY
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt = 0;
	uint32_t reload = SysTick->LOAD;    /*LOAD??*/
	ticks = nus * fac_us;             /*??????*/

	told = SysTick->VAL;                /*?????????*/
	while(1)
	{
		tnow = SysTick->VAL;
		if(tnow != told)
		{
			if(tnow < told)
			{
				tcnt += told - tnow; /*????SYSTICK?????????*/ 
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if(tcnt >= ticks)
			{
				break;            /*????/????????,???*/
			}
		}
	}
}

#else
/**
* @brief ?? nus
* @note ?????? OS, ?????????? us ??
* @param nus: ???? us ?
* @note nus ????: 0 ~ (2^32 / fac_us)(fac_us ????????, ??????)
* @retval ?
*/
void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told, tnow, tcnt = 0;
	uint32_t reload = SysTick->LOAD; /* LOAD ?? */
	ticks = nus * g_fac_us; /* ?????? */
	told = SysTick->VAL; /* ????????? */
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if(tnow < told)
			{
				tcnt += told - tnow;
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if (tcnt >= ticks)
			{
				break; /* ????/????????,??? */
			}
		}
	}
}
#endif
/**
* @brief    ms????
* @param    nms:????ms?
* @note     nms????:0 ~ (2^32 / fac_us / 1000)(fac_us????????)
* @retval   ?
*/
//对72M条件下,nms<=1864 
void delay_ms(uint16_t nms)
{	 		  	  
    delay_us(nms*1000);
} 









































