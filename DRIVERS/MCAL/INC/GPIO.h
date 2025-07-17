/*
 * GPIO.h
 *
 *  Created on: Jan 29, 2024
 *      Author: omar
 */

#ifndef GPIO_H_
#define GPIO_H_

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "STM32F103C8.h"
#include "RCC.h"


/******************************************************************************
 *                        Macros Configuration References	                  *
 *******************************************************************************/

//@ref GPIO_PIN_state
#define PIN_SET					1
#define PIN_RESET				0

//@ref GPIO_LOCK_RETURN
#define GPIO_LOCK_Success		1
#define GPIO_LOCK_ERROR			0

/******************************************************************************
 *                        ENUMs Configuration References	                  *
 *******************************************************************************/

// @ref GPIO_PINS_define
typedef enum {

	PIN0=0,
	PIN1=1,
	PIN2=2,
	PIN3=3,
	PIN4=4,
	PIN5=5,
	PIN6=6,
	PIN7=7,
	PIN8=8,
	PIN9=9,
	PIN10=10,
	PIN11=11,
	PIN12=12,
	PIN13=13,
	PIN14=14,
	PIN15=15,
}GPIO_PINs_t;

//@ref GPIO_MODE_define
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3:  pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function  INPUT


typedef enum {
	//input modes
	Input_Analog_Mode				= 0b0000 ,
	Input_Flo_Mode					= 0b0100 ,
	Input_PU_Mode					= 0b11000,
	Input_PD_Mode					= 0b01000,
	Input_AF						= 0b0100,
	//output push-pull mode
	Output_PP_Mode_Speed10MHZ		= 0b0001 ,
	Output_PP_Mode_Speed2MHZ		= 0b0010 ,
	Output_PP_Mode_Speed50MHZ		= 0b0011 ,
	//output open-drain mode
	Output_OD_Mode_Speed10MHZ		= 0b0101 ,
	Output_OD_Mode_Speed2MHZ		= 0b0110 ,
	Output_OD_Mode_Speed50MHZ		= 0b0111 ,
	//Output Alternative function Push-Pull mode
	Output_AF_PP_Mode_Speed10MHZ	= 0b1001 ,
	Output_AF_PP_Mode_Speed2MHZ		= 0b1010 ,
	Output_AF_PP_Mode_Speed50MHZ	= 0b1011 ,
	//Output Alternative function Open-Drain
	Output_AF_OD_Mode_Speed10MHZ	= 0b1101 ,
	Output_AF_OD_Mode_Speed2MHZ		= 0b1110 ,
	Output_AF_OD_Mode_Speed50MHZ	= 0b1111 ,
}GPIO_MODEs_t;

//@ref GPIO_SPEED_define
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz
//#define GPIO_Input 			0b00
//#define GPIO_10MHZ 			0b01
//#define GPIO_2MHZ  			0b10
//#define GPIO_50MHZ 			0b11

/******************************************************************************
*                                    APIs			                          *
*******************************************************************************/
// functions to initialize GPIO
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx ,GPIO_PINs_t GPIO_PinNum  , GPIO_MODEs_t GPIO_PinMODE  );
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx );


//functions for Input mode
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx , GPIO_PINs_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);


//functions for Output mode
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx , GPIO_PINs_t PinNumber,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx ,uint16_t value);
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx , GPIO_PINs_t PinNumber);


//function for lock GPIO Pins
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx ,GPIO_PINs_t PinNumber);

/******************************************************************************
 *                                Another Functions			                  *
 *******************************************************************************/
uint8_t Get_Position(GPIO_PINs_t PinNumber);

#endif /* GPIO_H_ */
