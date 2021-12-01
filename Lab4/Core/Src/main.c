/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void do_blink1(){
	HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
}
void do_blink2(){
	HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);
}
void do_blink3(){
	HAL_GPIO_TogglePin(led3_GPIO_Port, led3_Pin);
}
void do_blink4(){
	HAL_GPIO_TogglePin(led4_GPIO_Port, led4_Pin);
}
void do_blink5(){
	HAL_GPIO_TogglePin(led5_GPIO_Port, led5_Pin);
}
typedef struct{
	 void (*pTask)(void);
	 uint32_t Delay;
	 uint8_t Period;
	 uint32_t RunMe;
	 //uint32_t Task_ID;
 }sTask;

 #define SCH_MAX_TASKS 5

sTask SCH_tasks_G[SCH_MAX_TASKS];

// unsigned char SCH_Delete_Task(unsigned char TASK_INDEX){
//  unsigned char Return_code ;
//  if( SCH_tasks_G[TASK_INDEX].pTask == 0) {
//	  Return_code = 1;
//  } else {
//	  Return_code = 0;
//  }
//	  SCH_tasks_G[TASK_INDEX].pTask = 0x0000 ;
//	  SCH_tasks_G[TASK_INDEX].Delay = 0 ;
//	  SCH_tasks_G[TASK_INDEX].Period = 0 ;
//	  SCH_tasks_G[TASK_INDEX].RunMe = 0 ;
//	  return Return_code ;
// }
void SCH_Delete_Task(unsigned char TASK_INDEX){

	  for(unsigned int i = TASK_INDEX+1; i<SCH_MAX_TASKS; i++){
		  //shift left
		  	SCH_tasks_G[i-1].pTask = SCH_tasks_G[i].pTask;
			SCH_tasks_G[i-1].Delay = SCH_tasks_G[i].Delay ;
			SCH_tasks_G[i-1].Period = SCH_tasks_G[i].Period ;
			SCH_tasks_G[i-1].RunMe = SCH_tasks_G[i].RunMe ;


	  }
	  SCH_tasks_G[SCH_MAX_TASKS-1].pTask = 0x0000 ;
	  SCH_tasks_G[SCH_MAX_TASKS-1].Delay = 0 ;
	  SCH_tasks_G[SCH_MAX_TASKS-1].Period = 0 ;
	  SCH_tasks_G[SCH_MAX_TASKS-1].RunMe = 0 ;
 }
void SCH_Delete_Task1(unsigned char TASK_INDEX){

	  SCH_tasks_G[TASK_INDEX].pTask = 0x0000 ;
	  SCH_tasks_G[TASK_INDEX].Delay = 0 ;
	  SCH_tasks_G[TASK_INDEX].Period = 0 ;
	  SCH_tasks_G[TASK_INDEX].RunMe = 0 ;

 }
void SCH_Init(){
	unsigned char i;
	for(i = 0; i<SCH_MAX_TASKS; i++){
		SCH_Delete_Task1(i);
	}
}
 void SCH_Update(void){
	 	unsigned char index = 0;;
	 	 if(SCH_tasks_G[index].pTask){
			  if(SCH_tasks_G[index].Delay <= 0){
				  SCH_tasks_G [index].RunMe += 1;
			  }else{
				  SCH_tasks_G[index].Delay -= 1;
			  }
		  }
}
void SCH_Add_Task(void(*pFunction )(), unsigned int DELAY, unsigned int PERIOD){
	unsigned int pos = 0;
	unsigned int pos2 = 0;

	for(pos = 0; pos<SCH_MAX_TASKS; pos++){
		if(SCH_tasks_G[pos].pTask ==0){
			break;
		}
	}
	if(pos==SCH_MAX_TASKS) return;

	if(SCH_tasks_G[0].pTask==0){ //queue ban dau rong
		SCH_tasks_G[0].pTask = pFunction;
		SCH_tasks_G[0].Delay = DELAY;
		SCH_tasks_G[0].Period = PERIOD;
		SCH_tasks_G[0].RunMe = 0;
	}else{
		unsigned int valDelay = DELAY;
			for(int i = 0; i<=pos; i++){
				if(SCH_tasks_G[i].Delay <= valDelay && SCH_tasks_G[i].pTask){ // cu nho hon bang moi
					valDelay -= SCH_tasks_G[i].Delay ;
				}else{
					pos2 = i;
					if (SCH_tasks_G[i].pTask)
						SCH_tasks_G[i].Delay -= valDelay;
					break;
				}
			}
			for(int j = pos; j>pos2; j--){
				SCH_tasks_G[j].pTask = SCH_tasks_G[j-1].pTask;
				SCH_tasks_G[j].Delay = SCH_tasks_G[j-1].Delay;
				SCH_tasks_G[j].Period = SCH_tasks_G[j-1].Period;
				SCH_tasks_G[j].RunMe = SCH_tasks_G[j-1].RunMe;
			}
			SCH_tasks_G[pos2].pTask = pFunction;
			SCH_tasks_G[pos2].Delay = valDelay;
			SCH_tasks_G[pos2].Period = PERIOD;
			SCH_tasks_G[pos2].RunMe = 0;
	}
}

 void SCH_Dispatch_Tasks(void){
	 unsigned char index = 0;
	 sTask tempTask;
	 for(index = 0; index<SCH_MAX_TASKS; index++){
		 if ( SCH_tasks_G[index].RunMe > 0) {
			  (*SCH_tasks_G[index].pTask)(); // Run the task
			  SCH_tasks_G[index].RunMe -= 1; // Reset / reduce RunMe f l a g
			  //luu lai task hien tai vao tempTask
//			  tempTask.Delay = SCH_tasks_G[index].Period;
			  tempTask.Period = SCH_tasks_G[index].Period;
//			  tempTask.RunMe = SCH_tasks_G[index].RunMe;
			  tempTask.pTask = SCH_tasks_G[index].pTask;
			  //-----------------------------------//
			  SCH_Delete_Task(index) ;
			  if(tempTask.Period > 0){
				  // neu Task ko phai One Shot add vao lai array
				  //unsigned int tmpDelay = tempTask.Period;
				  SCH_Add_Task(tempTask.pTask, tempTask.Period, tempTask.Period);
			  }


		  }
	}
 }



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  SCH_Init();
  SCH_Add_Task(do_blink1,5,50);
  SCH_Add_Task(do_blink2,10,100);
  SCH_Add_Task(do_blink3,15,150);
  SCH_Add_Task(do_blink4,20,200);
  SCH_Add_Task(do_blink5,25,250);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  SCH_Dispatch_Tasks();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led_Pin|led2_Pin|led3_Pin|led4_Pin
                          |led5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : led_Pin led2_Pin led3_Pin led4_Pin
                           led5_Pin */
  GPIO_InitStruct.Pin = led_Pin|led2_Pin|led3_Pin|led4_Pin
                          |led5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim ){
	SCH_Update();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
