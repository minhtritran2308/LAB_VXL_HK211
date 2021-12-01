/*
 * global.h
 *
 *  Created on: Oct 4, 2021
 *      Author: MINH TRI
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

extern int timeRed ;
extern int timeAmber ;
extern int timeGreen;
/*Temp value for traffic light used for increase or decrease*/
extern int bufferRed;
extern int bufferAmber;
extern int bufferGreen;
/*Flag for used for control led and autoIncrease*/
extern int flagAuto;
extern int flagHalfSec;
extern int flag1Sec;
/*Counter*/
extern int timer0_counter;
extern int timer1_counter;
extern int timer2_counter;
#endif /* INC_GLOBAL_H_ */
