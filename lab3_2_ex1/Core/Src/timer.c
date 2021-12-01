/*
 * timer.c
 *
 *  Created on: Oct 14, 2021
 *      Author: MINH TRI
 */
#include "main.h"
#include "global.h"
#include "timer.h"
int flagHalfSec = 0;
int flag1Sec = 0;
int flagAuto = 0;
int timer0_counter = 0;
int timer1_counter = 0;
int timer2_counter = 0;
const int TIMER_CYCLE = 10;
void setTimer0(int duration){
	 timer0_counter = duration / TIMER_CYCLE ;
	 flag1Sec = 0;
}
void setTimer1(int duration){
	 timer1_counter = duration/ TIMER_CYCLE ;
	 flagHalfSec = 0;
}
void setTimer2(int duration){
	timer2_counter = duration/TIMER_CYCLE;
	flagAuto = 0;
}
void timer_run() {
	 if( timer0_counter > 0) {
		 timer0_counter--;
		 if( timer0_counter == 0) flag1Sec = 1;
	 }

	 if( timer1_counter > 0) {
		 timer1_counter--;
		 if( timer1_counter == 0) flagHalfSec = 1;
	 }
	 if(timer2_counter>0){
		 timer2_counter--;
		 if(timer2_counter == 0) flagAuto = 1;
	 }

 }
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef* htim ) {
		button_reading();
		timer_run();
}

