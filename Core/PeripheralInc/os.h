#ifndef __OS_H
#define __OS_H

#include "stm32f1xx_hal.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "usart.h"
#include <string.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define USE_NEW_OS									(1u)/*1: Using new os,0: Using old os */									

#define TX_DATA_LEN									(18u)
#define RX_DATA_LEN									(6u)

#define BLUETOOTH_TX_DATA_LEN					(10u)
#define BLUETOOTH_RX_DATA_LEN				(5u)


typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

extern uint8_t Txbuffer[TX_DATA_LEN];
extern uint8_t Rxbuffer[RX_DATA_LEN];

extern uint8_t BluetoothTxbuffer[BLUETOOTH_TX_DATA_LEN];/* Transmit data buffer */
extern uint8_t BluetoothRxbuffer[BLUETOOTH_RX_DATA_LEN];/* Transmit data buffer */

extern float Distance;

#if USE_NEW_OS
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define MAX_TASKS 10

extern volatile uint32_t systemTime;
/* USER CODE END Private defines */
void OS_Scheduler(void);
void OS_Init(void);
void OS_Update(void);

#else
extern void Os_Init(void);
extern void Os_Period(void);
extern void Os_Task(void);
extern void ShowInformation(void);
enum os_period
{
	OS_0MS = 0u,
	OS_1MS = 1u,
	OS_5MS = 5u,
	OS_10MS = 10u,
	OS_50MS = 50u,
	OS_100MS = 100u,
	OS_500MS = 500u,
	OS_1000MS = 1000u
};
enum Os_Period_5ms
{
	OS_5MS_a = 1u,
	OS_5MS_b = 2u,
	OS_5MS_c = 3u,
	OS_5MS_d = 4u,
	OS_5MS_e = 5u
};
#endif
#endif
