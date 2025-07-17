/*
 * Keypad.h
 *
 *  Created on: Feb 24, 2024
 *      Author: omar
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "STM32F103C8.h"
#include "GPIO.h"
/******************************************************************************
*                        Macros Configuration References	                  *
*******************************************************************************/
#define R0				PIN3
#define R1				PIN4
#define R2				PIN5
#define R3				PIN6
#define C0				PIN7
#define C1				PIN8
#define C2				PIN9
#define C3				PIN10

#define Keypad_port		GPIOB
/******************************************************************************
*                        			  APIs	  				                  *
*******************************************************************************/
void HAL_Keypad_init(void);
char HAL_Keypad_getkey(void);
#endif /* INC_KEYPAD_H_ */
