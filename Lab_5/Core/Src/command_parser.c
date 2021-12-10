/*
 * command_parser.c
 *
 *  Created on: Nov 25, 2021
 *      Author: MINH TRI
 */
#include "main.h"
#include "global.h"
#include "command_parser.h"
#include "timer.h"
#include <stdio.h>
#include <string.h>
#define MAX_BUFFER_SIZE 30
UART_HandleTypeDef huart2;
uint8_t temp = 0;
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
uint8_t buffer[MAX_BUFFER_SIZE];
//static uint8_t out2[30];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart){
	if(huart->Instance == USART2){
		 buffer[index_buffer++] = temp ;
		HAL_UART_Transmit (&huart2 ,&temp ,1,50) ;
		if(index_buffer >= MAX_BUFFER_SIZE) index_buffer = 0;
		buffer_flag = 1;
	    HAL_UART_Receive_IT(&huart2,&temp,1);
}
}
enum state_parser{WAIT_START, WAIT_END};
enum state_parser currentState = WAIT_START;
char command[30];
unsigned char command_index = 0;
unsigned char command_done = 0;

void command_parser_fsm(){
	switch(currentState){
	case WAIT_START:
		if(buffer[index_buffer-1] =='!' /*temp =='!'*/){
			//HAL_UART_Transmit(&huart2, out2, sprintf(out2, "\r\n Start parse \r\n"), 1000);
			currentState = WAIT_END;
			command_index = 0;
		}
		break;
	case WAIT_END:
		if(buffer[index_buffer-1]=='#' /*temp =='#'*/){
			//HAL_UART_Transmit(&huart2, out2, sprintf(out2, "\r\n End parse \r\n"), 1000);
			currentState = WAIT_START;
			command[command_index] = '\0';
			command_done = 1;
		}else{
			command[command_index++] = /*temp*/ buffer[index_buffer-1];
			if(command_index >= MAX_BUFFER_SIZE) command_index = 0;
		}
		break;
	}
}

char* getCommand(){
	return command;
}
unsigned char status(){
	return command_done;
}
void clearCommand(){
	command[0] = '\0';
}
