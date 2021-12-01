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
#define led1_red_Pin GPIO_PIN_1
#define led1_red_GPIO_Port GPIOA
#define led1_yellow_Pin GPIO_PIN_2
#define led1_yellow_GPIO_Port GPIOA
#define led1_green_Pin GPIO_PIN_3
#define led1_green_GPIO_Port GPIOA
#define led2_red_Pin GPIO_PIN_5
#define led2_red_GPIO_Port GPIOA
#define led2_yellow_Pin GPIO_PIN_6
#define led2_yellow_GPIO_Port GPIOA
#define led2_green_Pin GPIO_PIN_7
#define led2_green_GPIO_Port GPIOA
#define led7_0_Pin GPIO_PIN_0
#define led7_0_GPIO_Port GPIOB
#define led7_1_Pin GPIO_PIN_1
#define led7_1_GPIO_Port GPIOB
#define led7_2_Pin GPIO_PIN_2
#define led7_2_GPIO_Port GPIOB
#define led7_2_2_Pin GPIO_PIN_10
#define led7_2_2_GPIO_Port GPIOB
#define led7_2_3_Pin GPIO_PIN_11
#define led7_2_3_GPIO_Port GPIOB
#define led7_2_4_Pin GPIO_PIN_12
#define led7_2_4_GPIO_Port GPIOB
#define led7_2_5_Pin GPIO_PIN_13
#define led7_2_5_GPIO_Port GPIOB
#define led7_2_6_Pin GPIO_PIN_14
#define led7_2_6_GPIO_Port GPIOB
#define led7_3_Pin GPIO_PIN_3
#define led7_3_GPIO_Port GPIOB
#define led7_4_Pin GPIO_PIN_4
#define led7_4_GPIO_Port GPIOB
#define led7_5_Pin GPIO_PIN_5
#define led7_5_GPIO_Port GPIOB
#define led7_6_Pin GPIO_PIN_6
#define led7_6_GPIO_Port GPIOB
#define led7_2_0_Pin GPIO_PIN_8
#define led7_2_0_GPIO_Port GPIOB
#define led7_2_1_Pin GPIO_PIN_9
#define led7_2_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
