#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f1xx_hal.h"
#include "main.h"

#define DHT11_HIGH     HAL_GPIO_WritePin(TEMP_GPIO_Port, TEMP_Pin,	GPIO_PIN_SET)
#define DHT11_LOW      HAL_GPIO_WritePin(TEMP_GPIO_Port, TEMP_Pin, GPIO_PIN_RESET)
 
#define DHT11_IO_IN      HAL_GPIO_ReadPin(TEMP_GPIO_Port, TEMP_Pin)


void DHT11_OUT(void);
void DHT11_IN(void);
void DHT11_Start(void);
uint8_t DHT11_Check(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Read_Byte(void);
extern uint8_t DHT11_Read_Data(uint8_t* temp , uint8_t* humi);
#endif
