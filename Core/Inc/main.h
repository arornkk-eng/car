/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MPU_INT_Pin GPIO_PIN_13
#define MPU_INT_GPIO_Port GPIOC
#define PC14_Pin GPIO_PIN_14
#define PC14_GPIO_Port GPIOC
#define PC15_Pin GPIO_PIN_15
#define PC15_GPIO_Port GPIOC
#define PC0_Pin GPIO_PIN_0
#define PC0_GPIO_Port GPIOC
#define PC1_Pin GPIO_PIN_1
#define PC1_GPIO_Port GPIOC
#define TEMP_Pin GPIO_PIN_2
#define TEMP_GPIO_Port GPIOC
#define VBUS_Pin GPIO_PIN_3
#define VBUS_GPIO_Port GPIOC
#define ENCODER1_A_Pin GPIO_PIN_0
#define ENCODER1_A_GPIO_Port GPIOA
#define ENCODER1_B_Pin GPIO_PIN_1
#define ENCODER1_B_GPIO_Port GPIOA
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define MOTOR2_OUT2_Pin GPIO_PIN_4
#define MOTOR2_OUT2_GPIO_Port GPIOA
#define MOTOR2_OUT1_Pin GPIO_PIN_5
#define MOTOR2_OUT1_GPIO_Port GPIOA
#define MOTOR1_PWM_Pin GPIO_PIN_6
#define MOTOR1_PWM_GPIO_Port GPIOA
#define MOTOR2_PWM_Pin GPIO_PIN_7
#define MOTOR2_PWM_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_4
#define KEY1_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_5
#define KEY2_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_1
#define BEEP_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_10
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_11
#define OLED_SDA_GPIO_Port GPIOB
#define S1_Pin GPIO_PIN_6
#define S1_GPIO_Port GPIOC
#define S2_Pin GPIO_PIN_7
#define S2_GPIO_Port GPIOC
#define S3_Pin GPIO_PIN_8
#define S3_GPIO_Port GPIOC
#define S4_Pin GPIO_PIN_9
#define S4_GPIO_Port GPIOC
#define ECHO_Pin GPIO_PIN_8
#define ECHO_GPIO_Port GPIOA
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define SPI2_CE_Pin GPIO_PIN_15
#define SPI2_CE_GPIO_Port GPIOA
#define USART3_TX_Pin GPIO_PIN_10
#define USART3_TX_GPIO_Port GPIOC
#define USART3_RX_Pin GPIO_PIN_11
#define USART3_RX_GPIO_Port GPIOC
#define PC12_Pin GPIO_PIN_12
#define PC12_GPIO_Port GPIOC
#define PD2_Pin GPIO_PIN_2
#define PD2_GPIO_Port GPIOD
#define TRIG_Pin GPIO_PIN_3
#define TRIG_GPIO_Port GPIOB
#define MOTOR1_OUT2_Pin GPIO_PIN_4
#define MOTOR1_OUT2_GPIO_Port GPIOB
#define MOTOR1_OUT1_Pin GPIO_PIN_5
#define MOTOR1_OUT1_GPIO_Port GPIOB
#define ENCODER2_A_Pin GPIO_PIN_6
#define ENCODER2_A_GPIO_Port GPIOB
#define ENCODER2_B_Pin GPIO_PIN_7
#define ENCODER2_B_GPIO_Port GPIOB
#define MPU_SCL_Pin GPIO_PIN_8
#define MPU_SCL_GPIO_Port GPIOB
#define MPU_SDA_Pin GPIO_PIN_9
#define MPU_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
