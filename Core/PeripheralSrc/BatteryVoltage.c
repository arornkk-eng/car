/*
 * @Author       : Yuan Ge
 * @Date         : 2024-05-31
 * @LastEditors  : Yuan Ge
 * @LastEditTime : 2024-06-21 
 * @Description  : 
 * @FilePath     : 
 */
#include "BatteryVoltage.h"
#include "adc.h"
/*
    ??????,?????????
*/
unsigned short g_sADC_Value = 0;// ADC?????
uint8_t g_fVoltage  = 0;        // 0.1V/LSB
uint8_t GetBatVoltage(void)
{
    HAL_ADC_PollForConversion(&hadc1, 100);// ??????,???????????,??ms
    g_sADC_Value = HAL_ADC_GetValue(&hadc1);// ???ADC??
    g_fVoltage = (uint8_t)(g_sADC_Value * 0.04163);//
	return g_fVoltage;// 12V:120
	
}
