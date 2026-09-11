/*
 * @Author       : Yuan Ge
 * @Date         : 2024-05-31
 * @LastEditors  : Yuan Ge
 * @LastEditTime : 2024-06-21 
 * @Description  : 
 * @FilePath     : 
 */
#include "DHT11.h"
#include "delay.h"


void DHT11_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
 
	GPIO_InitStruct.Pin = TEMP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(TEMP_GPIO_Port, &GPIO_InitStruct);
}
 
void DHT11_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct = {0};
 
	GPIO_InitStruct.Pin  = TEMP_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(TEMP_GPIO_Port, &GPIO_InitStruct);
}
 
 
void DHT11_Start(void)
{
	DHT11_OUT();
	DHT11_LOW;
	HAL_Delay(20);
	DHT11_HIGH;
	delay_us(30);
}
 
 
uint8_t DHT11_Check(void)
{
	uint8_t retry = 0 ;
	DHT11_IN();
		
	while(DHT11_IO_IN && retry <100) 
	{
		retry++;
		delay_us(1);//1us
	}
	if(retry>=100) 
	{return  1;}
	 else retry =  0 ;
		
	while(!DHT11_IO_IN && retry<100)
	{
		retry++;
		delay_us(1);//1us
	}
		
	if(retry>=100)
	{return 1;}
	return 0 ;
}
 
 
uint8_t DHT11_Read_Bit(void)
{
	uint8_t retry = 0 ;
	while(DHT11_IO_IN && retry <100)
	{
		retry++;
		delay_us(1);
	}
		retry = 0 ;
	while(!DHT11_IO_IN && retry<100)
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);
	if(DHT11_IO_IN) return 1;
	else 
	return 0 ;
}
 
 
uint8_t DHT11_Read_Byte(void)
{
	uint8_t i , dat ;
	dat = 0 ;
	for(i=0; i<8; i++)
	{
		dat <<= 1;
		dat |= DHT11_Read_Bit();
	}
	return dat ; 
}
 
 
uint8_t DHT11_Read_Data(uint8_t* temp , uint8_t* humi)
{
	uint8_t buf[5];
	uint8_t i;
	DHT11_Start();
    if(DHT11_Check() == 0)
	{
		for(i=0; i<5; i++)
		{
			buf[i] = DHT11_Read_Byte();
		}
		if(buf[0]+buf[1]+buf[2]+buf[3] == buf[4])
		{
			*humi = buf[0];
			*temp = buf[2];
		}
	}else return 1;
	
   return 0 ;
}

