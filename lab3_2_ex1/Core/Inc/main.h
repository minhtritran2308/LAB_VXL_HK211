/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "input_reading.h"
#include "input_processing.h"
#include "led_display.h"
#include "timer.h"
#include "trafficLight.h"
#include "global.h"
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
#define red1_Pin GPIO_PIN_0
#define red1_GPIO_Port GPIOA
#define amber1_Pin GPIO_PIN_1
#define amber1_GPIO_Port GPIOA
#define green1_Pin GPIO_PIN_2
#define green1_GPIO_Port GPIOA
#define red2_Pin GPIO_PIN_3
#define red2_GPIO_Port GPIOA
#define amber2_Pin GPIO_PIN_4
#define amber2_GPIO_Port GPIOA
#define green2_Pin GPIO_PIN_5
#define green2_GPIO_Port GPIOA
#define button1_Pin GPIO_PIN_6
#define button1_GPIO_Port GPIOA
#define button2_Pin GPIO_PIN_7
#define button2_GPIO_Port GPIOA
#define SEG1_0_Pin GPIO_PIN_2
#define SEG1_0_GPIO_Port GPIOB
#define SEG2_1_Pin GPIO_PIN_10
#define SEG2_1_GPIO_Port GPIOB
#define SEG2_2_Pin GPIO_PIN_11
#define SEG2_2_GPIO_Port GPIOB
#define SEG2_3_Pin GPIO_PIN_12
#define SEG2_3_GPIO_Port GPIOB
#define SEG2_4_Pin GPIO_PIN_13
#define SEG2_4_GPIO_Port GPIOB
#define SEG2_5_Pin GPIO_PIN_14
#define SEG2_5_GPIO_Port GPIOB
#define SEG2_6_Pin GPIO_PIN_15
#define SEG2_6_GPIO_Port GPIOB
#define button3_Pin GPIO_PIN_8
#define button3_GPIO_Port GPIOA
#define button4_Pin GPIO_PIN_9
#define button4_GPIO_Port GPIOA
#define EN0_Pin GPIO_PIN_10
#define EN0_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_11
#define EN1_GPIO_Port GPIOA
#define EN2_Pin GPIO_PIN_12
#define EN2_GPIO_Port GPIOA
#define EN3_Pin GPIO_PIN_13
#define EN3_GPIO_Port GPIOA
#define WARNING_Pin GPIO_PIN_15
#define WARNING_GPIO_Port GPIOA
#define SEG1_1_Pin GPIO_PIN_3
#define SEG1_1_GPIO_Port GPIOB
#define SEG1_2_Pin GPIO_PIN_4
#define SEG1_2_GPIO_Port GPIOB
#define SEG1_3_Pin GPIO_PIN_5
#define SEG1_3_GPIO_Port GPIOB
#define SEG1_4_Pin GPIO_PIN_6
#define SEG1_4_GPIO_Port GPIOB
#define SEG1_5_Pin GPIO_PIN_7
#define SEG1_5_GPIO_Port GPIOB
#define SEG1_6_Pin GPIO_PIN_8
#define SEG1_6_GPIO_Port GPIOB
#define SEG2_0_Pin GPIO_PIN_9
#define SEG2_0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
