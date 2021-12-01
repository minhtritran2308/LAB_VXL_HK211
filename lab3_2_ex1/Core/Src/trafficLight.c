/*
 * trafficLight.c
 *
 *  Created on: Oct 3, 2021
 *      Author: MINH TRI
 */
#include "input_processing.h"
#include "trafficLight.h"
#include "led_display.h"
#include "global.h"
#include "main.h"
#include "timer.h"

int currentCount1 = 5; //time for seg1
int currentCount2 = 3; //time for seg2
enum trafficLightState {RED1_GREEN2, RED1_AMBER2, GREEN1_RED2, AMBER1_RED2};
enum trafficLightState currentStateLight = RED1_GREEN2;
enum trafficLightState nextStateLight = RED1_GREEN2;
void red1Control(){

	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(amber1_GPIO_Port, amber1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, GPIO_PIN_SET);
}
void red2Control(){

	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(amber2_GPIO_Port, amber2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, GPIO_PIN_SET);
}
void amber1Control(){

	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(amber1_GPIO_Port, amber1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, GPIO_PIN_SET);
}
void amber2Control(){

	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(amber2_GPIO_Port, amber2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, GPIO_PIN_SET);
}
void green1Control(){

	HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(amber1_GPIO_Port, amber1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, GPIO_PIN_RESET);
}
void green2Control(){

	HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(amber2_GPIO_Port, amber2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, GPIO_PIN_RESET);
}

void trafficLightRun(int flagHalfSec, int flag1Sec){
	currentStateLight = nextStateLight;
	switch(currentStateLight){
		case RED1_GREEN2:
			red1Control();
			green2Control();
			if(flagHalfSec){
				update7SEG1(0,currentCount1);
				update7SEG2(0,currentCount2);
			}
			if(flag1Sec) {
				update7SEG1(1,currentCount1);
				update7SEG2(1,currentCount2);
				currentCount1--;
				currentCount2--;
			}
			if(currentCount1 == timeAmber){
				nextStateLight = RED1_AMBER2;
				currentCount2 = timeAmber;
			}

			break;
		case RED1_AMBER2:
			red1Control();
			amber2Control();
			if(flagHalfSec){
				update7SEG1(0,currentCount1);
				update7SEG2(0,currentCount2);
			}
			if(flag1Sec) {
				update7SEG1(1,currentCount1);
				update7SEG2(1,currentCount2);
				currentCount1--;
				currentCount2--;
			}
			if(currentCount1<=0){
				nextStateLight = GREEN1_RED2;
				currentCount1 = timeGreen;
				currentCount2 = timeRed;
			}

			break;
		case GREEN1_RED2:
			red2Control();
			green1Control();
			if(flagHalfSec){
				update7SEG1(0,currentCount1);
				update7SEG2(0,currentCount2);
			}
			if(flag1Sec) {
				update7SEG1(1,currentCount1);
				update7SEG2(1,currentCount2);
				currentCount1--;
				currentCount2--;
			}
			if(currentCount2== (timeAmber)){
				nextStateLight = AMBER1_RED2;
				currentCount1 = timeAmber;
			}
			break;
		case AMBER1_RED2:
			red2Control();
			amber1Control();
			if(flagHalfSec){
				update7SEG1(0,currentCount1);
				update7SEG2(0,currentCount2);
			}
			if(flag1Sec) {
				update7SEG1(1,currentCount1);
				update7SEG2(1,currentCount2);
				currentCount1--;
				currentCount2--;
			}
			if(currentCount1==0){
				nextStateLight = RED1_GREEN2;
				currentCount1 = timeRed;
				currentCount2 = timeGreen;
			}
			break;

	}

}


