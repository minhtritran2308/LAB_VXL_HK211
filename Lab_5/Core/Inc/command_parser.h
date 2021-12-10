/*
 * command_parser.h
 *
 *  Created on: Nov 21, 2021
 *      Author: MINH TRI
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_
void command_parser_fsm();
char* getCommand();
void clearcommand();
unsigned char status();
#endif /* INC_COMMAND_PARSER_H_ */
