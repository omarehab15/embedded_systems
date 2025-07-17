/*
 * ISR.h
 *
 *  Created on: Feb 26, 2024
 *      Author: omar
 */

#ifndef INC_ISR_H_
#define INC_ISR_H_
/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include"STM32F103C8.h"
#include "GPIO.h"

/******************************************************************************
*                          ISR Configuration References	                      *
*******************************************************************************/
#define NVIC_DISABLE		0
#define NVIC_ENABLE			1

/*************************************************************************************/
typedef enum{
	EXTI0   =0,
	EXTI1   =1,
	EXTI2   =2,
	EXTI3   =3,
	EXTI4   =4,
	EXTI5   =5,
	EXTI6   =6,
	EXTI7   =7,
	EXTI8   =8,
	EXTI9   =9,
	EXTI10 =10,
	EXTI11 =11,
	EXTI12 =12,
	EXTI13 =13,
	EXTI14 =14,
	EXTI15 =15
}EXTI_Line_t;

typedef enum {
	EXTI_Trigger_Rising		=0,
	EXTI_Trigger_Falling	=1,
	EXTI_Trigger_Both		=2
}EXTI_Trigger_t;


typedef enum {
	//ISER0
	NVIC_EXTI0 		=	6 ,
	NVIC_EXTI1 		=	7 ,
	NVIC_EXTI2 		=	8 ,
	NVIC_EXTI3 		=	9 ,
	NVIC_EXTI4 		=	10,
	NVIC_DMA1_CH1   =   11,
	NVIC_DMA1_CH2   =   12,
	NVIC_DMA1_CH3   =   13,
	NVIC_DMA1_CH4   =   14,
	NVIC_DMA1_CH5   =   15,
	NVIC_DMA1_CH6   =   16,
	NVIC_DMA1_CH7   =   17,
	NVIC_ADC1_2     =   18,
	NVIC_CAN1_TX	=	19,
	NVIC_CAN1_RX0	=	20,
	NVIC_CAN1_RX1	=	21,
	NVIC_CAN1_SCE	=	22,
	NVIC_EXTI5_9 	=	23,
	NVIC_TIM1_BRK	=	24,
	NVIC_TIM1_UP	=	25,
	NVIC_TIM1_TRG_COM=	26,
	NVIC_TIM1_CC	=	27,
	NVIC_TIM2		=	28,
	NVIC_TIM3		=	29,
	NVIC_TIM4		=	30,
	NVIC_I2C1_EV	=	31,
	NVIC_I2C1_ER	=	32,
	//ISER1
	NVIC_I2C2_EV	=	33,
	NVIC_I2C2_ER	=	34,
	NVIC_SPI1		=	35,
	NVIC_SPI2		=	36,
	NVIC_USART1		=	37,
	NVIC_USART2		=	38,
	NVIC_USART3		=	39,
	NVIC_EXTI10_15	= 	40,

}NVIC_Preph_t;

/******************************************************************************
*                                  APIs			                              *
*******************************************************************************/
void MCAL_NVIC_ENABLE(NVIC_Preph_t preph  , uint8_t state);
void MCAL_EXTI_INIT(GPIO_TypeDef *GPIOx ,GPIO_PINs_t GPIO_PinNum , EXTI_Trigger_t trigger , void (*function_addres) (void));
void MCAL_EXTI_DEINIT(void);
#endif /* INC_ISR_H_ */
