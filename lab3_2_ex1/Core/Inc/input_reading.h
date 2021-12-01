/*
 * input_reading.h
 *
 *  Created on: Oct 3, 2021
 *      Author: MINH TRI
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_
#include "global.h"
GPIO_PinState get_button_value(int index) ;
void button_reading(void) ;
 int is_button_pressed(int index);
 int is_button_pressed_1s(int index) ;
 GPIO_PinState readPin(int button);
#endif /* INC_INPUT_READING_H_ */
