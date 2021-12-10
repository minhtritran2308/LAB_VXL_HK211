/*
 * uart_com.c
 *
 *  Created on: Nov 21, 2021
 *      Author: MINH TRI
 */
#include "uart_com.h"
#include "main.h"
#include "global.h"
#include "timer.h"
#include "command_parser.h"
#include <stdio.h>
#include <string.h>
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;
enum communicateState{RTS_WAIT, RTS_OK, ADC_SEND};

enum communicateState commState = RTS_WAIT;
int ADC_value = 0;

char str[20];
static uint8_t out[30];

void uart_communication_fsm(){
	switch(commState){

	case RTS_WAIT:
		if(status() == 1){
			command_done = 0;
			HAL_UART_Transmit(&huart2, out, sprintf(out, "\r\nYour command is: %s \r\n", getCommand()), 1000);
			if(strcmp(getCommand(),"RTS") == 0){
				ADC_value = HAL_ADC_GetValue(&hadc1);
				commState = ADC_SEND;
				setTimer1(3000);
			}
		}
		break;
	case ADC_SEND:
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC = %d#\r\n", ADC_value),1000);
		commState = RTS_OK;

		break;
	case RTS_OK:
		if(status() == 1){
			command_done = 0;
			HAL_UART_Transmit(&huart2, out, sprintf(out, "\r\nYour command is: %s \r\n", getCommand()), 1000);
				if(strcmp(getCommand(),"OK") == 0){
					commState = RTS_WAIT;
					setTimer1(0);
				}
			clearCommand();
		}
		if(timer1_flag==1){
			commState = ADC_SEND;
			setTimer1(3000);
		}
		break;
	}
}
