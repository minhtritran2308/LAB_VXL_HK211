/*
 * input_processing.c
 *
 *  Created on: Oct 3, 2021
 *      Author: MINH TRI
 */
#include "main.h"
#include "input_reading.h"
#include "input_processing.h"
#include "trafficLight.h"
#include "global.h"
#include "timer.h"
enum state {MODE1, MODE2, MODE3, MODE4,INCREASE_RED, SET_RED, DECREASE_RED, INCREASE_AMBER, DECREASE_AMBER,
	SET_AMBER,INCREASE_GREEN, DECREASE_GREEN,SET_GREEN} ;
enum state currentState = MODE1 ;
enum state nextState = MODE1;
int bufferRed = 5;
int bufferAmber = 2 ;
int bufferGreen = 3;
int timeRed = 5;
int timeAmber = 2;
int timeGreen = 3;

void isTimeLogic(){
	if(timeRed>timeGreen && timeGreen>timeAmber && (timeGreen == (timeRed - timeAmber))){
		HAL_GPIO_WritePin(WARNING_GPIO_Port, WARNING_Pin, GPIO_PIN_SET);
		return;
	}else{
		if(timeRed>=5){
			timeAmber = 2;
			timeGreen = timeRed - timeAmber;
		}else{
			 timeRed = 5;
			 timeAmber = 2;
			 timeGreen = 3;
		}
		HAL_GPIO_WritePin(WARNING_GPIO_Port, WARNING_Pin, GPIO_PIN_RESET);
	}

}
// Have a total of 13 states
 void fsm_for_input_processing () {
	 currentState = nextState;
	switch (currentState){
		case MODE1:

			//-------------------/
			isTimeLogic();
			trafficLightRun(flagHalfSec, flag1Sec);

			//-------------------/
			if(is_button_pressed(0)){
				nextState = MODE2;
				bufferRed = timeRed;
				update7SEG1(1,2);
			}

			break;
		case MODE2://modify time of RED

			if(flagHalfSec){
				HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
				HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
			}

			if(is_button_pressed(1)){
				nextState = INCREASE_RED;
				bufferRed++;
				if(bufferRed>99) bufferRed = 1; // time of traffic light: 1-99
			}else if(is_button_pressed(3)){
				nextState = DECREASE_RED;
				bufferRed--;
				if(bufferRed<1) bufferRed = 99; // time of traffic light: 1-99
			}

			if(is_button_pressed(2)){
				nextState = SET_RED;
				timeRed = bufferRed;
			}

			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferRed);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferRed);
			}

			if(is_button_pressed(0)){
				nextState = MODE3;
				bufferAmber = timeAmber;
				update7SEG1(1,3);
			}

			break;
		case INCREASE_RED :
			if(flagHalfSec){
				HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
				HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
			}
			 if(!is_button_pressed(1)){
				 nextState = MODE2 ;
			 }
			 if(is_button_pressed_1s(1)){
				 if(flagAuto == 1){
					 bufferRed++;
					 if(bufferRed>99) bufferRed = 1;
					 if(is_button_pressed(2)){
						nextState = SET_RED;
						timeRed = bufferRed;

					}
				 }
			 }
			 else if(is_button_pressed(1)){
					 bufferRed++;
					 if(bufferRed>99) bufferRed = 1;

			 }


			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferRed);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferRed);
			}

			if(is_button_pressed(2)){
				nextState = SET_RED;
				timeRed = bufferRed;
			}

			 if(is_button_pressed(0)){
					nextState = MODE3;
					bufferAmber = timeAmber;
					update7SEG1(1,3);
				}
			 break ;
		 case DECREASE_RED :
			 if(flagHalfSec){
				HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
				HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
			}
			 if( !is_button_pressed(3)){
				 nextState = MODE2 ;
			 }
			 if(is_button_pressed_1s(3)){
				 if(flagAuto == 1){
					 bufferRed--;
					 if(bufferRed<1) bufferRed = 99;
					 if(is_button_pressed(2)){
						nextState = SET_RED;
						timeRed = bufferRed;

					}
				 }
			 }
			 else if(is_button_pressed(3)){
					 bufferRed--;
					 if(bufferRed<1) bufferRed = 99;

			 }
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferRed);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferRed);
			}
			if(is_button_pressed(2)){
				nextState = SET_RED;
				timeRed = bufferRed;
			}
			 if(is_button_pressed(0)){
					nextState = MODE3;
					bufferAmber = timeAmber;
					update7SEG1(1,3);
				}
			 break ;
		 case SET_RED:

			 if(flagHalfSec){
				HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
				HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
			}
			 if(!is_button_pressed(2)){
				 nextState = MODE2;
			 }
			 if(is_button_pressed(1)){
				 nextState = INCREASE_RED;
			 }

			 if(is_button_pressed(3)){
				 nextState = DECREASE_RED;
			 }
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferRed);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferRed);
			}

			 if(is_button_pressed(0)){
					nextState = MODE3;
					bufferAmber = timeAmber;
					update7SEG1(1,3);
				}
			 break;

			 //-----modify time of AMBER-------//
		 case MODE3:
			if(flagHalfSec){
				HAL_GPIO_TogglePin(amber1_GPIO_Port, amber1_Pin);
				HAL_GPIO_TogglePin(amber2_GPIO_Port, amber2_Pin);
			}

			if(is_button_pressed(1)){
				nextState = INCREASE_AMBER;
				bufferAmber++;
				if(bufferAmber>99) bufferAmber = 1; // time of traffic light: 1-99

			}else if(is_button_pressed(3)){
				nextState = DECREASE_AMBER;
				bufferAmber--;
				if(bufferAmber<1) bufferAmber = 99; // time of traffic light: 1-99

			}
			if(is_button_pressed(2)){
				nextState = SET_AMBER;
				timeAmber = bufferAmber;
			}
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferAmber);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferAmber);
			}

			if(is_button_pressed(0)){
				nextState = MODE4;
				bufferGreen = timeGreen;
				update7SEG1(1,4);
			}
			break;
		case INCREASE_AMBER :
			if(flagHalfSec){
				HAL_GPIO_TogglePin(amber1_GPIO_Port, amber1_Pin);
				HAL_GPIO_TogglePin(amber2_GPIO_Port, amber2_Pin);
			}
			 if( !is_button_pressed(1)){
				 nextState = MODE3 ;
			 }

			 if(is_button_pressed_1s(1)){
				 if(flagAuto == 1){
					 bufferAmber++;
					 if(bufferAmber>99) bufferAmber = 1;
					 if(is_button_pressed(2)){
						nextState = SET_AMBER;
						timeAmber = bufferAmber;

					}
				 }
			 }
			 else if(is_button_pressed(1)){
				 bufferAmber++;
					 if(bufferAmber>99) bufferAmber = 1;

			 }
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferAmber);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferAmber);
			}

			if(is_button_pressed(2)){
				nextState = SET_AMBER;
				timeAmber = bufferAmber;
			}
			 if(is_button_pressed(0)){
					nextState = MODE4;
					update7SEG1(1,4);
				}
			 break ;
		 case DECREASE_AMBER :
				if(flagHalfSec){
					HAL_GPIO_TogglePin(amber1_GPIO_Port, amber1_Pin);
					HAL_GPIO_TogglePin(amber2_GPIO_Port, amber2_Pin);
				}
			 if(!is_button_pressed(3)){
				 nextState = MODE3 ;
			 }
			 if(is_button_pressed_1s(3)){
				 if(flagAuto == 1){
					 bufferAmber--;
					 if(bufferAmber<1) bufferAmber = 99;
					 if(is_button_pressed(3)){
						nextState = SET_AMBER;
						timeAmber = bufferAmber;

					}
				 }
			 }
			 else if(is_button_pressed(1)){
				 bufferAmber--;
					 if(bufferAmber<1) bufferAmber = 99;

			 }

			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferAmber);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferAmber);
			}
			if(is_button_pressed(2)){
				nextState = SET_AMBER;
				timeAmber = bufferAmber;
			}
			 if(is_button_pressed(0)){
					nextState = MODE4;
					bufferGreen = timeGreen;
					update7SEG1(1,4);
				}
			 break ;
		 case SET_AMBER:

				if(flagHalfSec){
					HAL_GPIO_TogglePin(amber1_GPIO_Port, amber1_Pin);
					HAL_GPIO_TogglePin(amber2_GPIO_Port, amber2_Pin);
				}
			 if(is_button_pressed(1)){
				 nextState = INCREASE_AMBER;
			 }

			 if(is_button_pressed(3)){
				 nextState = DECREASE_AMBER;
			 }

			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferAmber);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferAmber);
			}

			if(is_button_pressed(0)){
				nextState = MODE4;
				bufferGreen = timeGreen;
				update7SEG1(1,4);
			}
			 break;

			 //-----modify time of GREEN-------//
		 case MODE4:
			if(flagHalfSec){
				HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
				HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
			}

			if(is_button_pressed(1)){
				nextState = INCREASE_GREEN;
				bufferGreen++;
				if(bufferGreen>99) bufferGreen = 1; // time of traffic light: 1-99
				if(is_button_pressed(2)){
					nextState = SET_GREEN;
					timeGreen = bufferGreen;
				}
			}
			if(is_button_pressed(3)){
				nextState = DECREASE_GREEN;
				bufferGreen--;
				if(bufferGreen<1) bufferGreen = 99; // time of traffic light: 1-99
				if(is_button_pressed(2)){
					nextState = SET_GREEN;
				}
			}
			if(is_button_pressed(2)){
				nextState = SET_GREEN;
				timeGreen = bufferGreen;
			}
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferGreen);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferGreen);
			}

			if(is_button_pressed(0)){
				nextState = MODE1;
			}
			break;
		case INCREASE_GREEN :
			if(flagHalfSec){
				HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
				HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
			}
			 if( !is_button_pressed(1)){
				 nextState = MODE4 ;

			 }
			 if(is_button_pressed_1s(1)){
				 if(flagAuto == 1){
					 bufferGreen++;
					 if(bufferGreen>99) bufferGreen = 1;
					 if(is_button_pressed(2)){
						nextState = SET_GREEN;
						timeGreen = bufferGreen;

					}
				 }
			 }
			 else if(is_button_pressed(1)){
				 bufferGreen++;
					 if(bufferGreen>99) bufferGreen = 1;

			 }
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferGreen);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferGreen);
			}

			if(is_button_pressed(2)){
				nextState = SET_GREEN;
				timeGreen = bufferGreen;
			}
			 if(is_button_pressed(0)){
					nextState = MODE1;

				}
			 break ;
		 case DECREASE_GREEN :
				if(flagHalfSec){
					HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
					HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
				}
			 if( !is_button_pressed(3)){
				 nextState = MODE4 ;
			 }
				 if(is_button_pressed_1s(3)){
					 if(flagAuto == 1){
						 bufferGreen--;
						 if(bufferGreen<1) bufferGreen = 99;
						 if(is_button_pressed(2)){
							nextState = SET_GREEN;
							timeGreen = bufferGreen;

						}
					 }
				 }
				 else if(is_button_pressed(3)){
					 bufferGreen--;
						 if(bufferGreen<1) bufferGreen = 99;

				 }
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferGreen);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferGreen);
			}
			if(is_button_pressed(2)){
				nextState = SET_GREEN;
				timeGreen = bufferGreen;
			}
			 if(is_button_pressed(0)){
					nextState = MODE1;
				}
			 break ;
		 case SET_GREEN:

				if(flagHalfSec){
					HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
					HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
				}
			 if(is_button_pressed(1)){
				 nextState = INCREASE_GREEN;
			 }

			 if(is_button_pressed(3)){
				 nextState = DECREASE_AMBER;
			 }
			 //--- display time value ---/
			 if(flagHalfSec){
				update7SEG2(0,bufferGreen);
			}
			if(flag1Sec) {
				update7SEG2(1,bufferGreen);
			}

			 if(is_button_pressed(0)){
				nextState = MODE1;

			}
			 break;

	 }
 }

