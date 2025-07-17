/*
 * TIMER.h
 *
 *  Created on: Jul 22, 2024
 *      Author: omar
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "RCC.h"
#include "GPIO.h"
#include "ISR.h"

















/******************************************************************************
*                                  APIs			                              *
*******************************************************************************/

//timer3 ch_1 --> A6  <> timer3 ch_2 --> A7 <> timer3 ch_3 --> B0 <> timer3 ch_4 --> B1
//Function to generate PWM
void MCAL_PWM_Init(PWM_Modes_t mode ,TIMER_channels_t channel , double duty_cycle , uint32_t freq,uint32_t TIM_PSC);

//delay Function
void delay(TIMx_TypeDef *TIMx, uint16_t time,uint8_t U,uint32_t clk);

//Function to calculate the time of any operation
uint32_t TIME_CALCULATION(uint32_t clk,uint8_t TIMER_ST);

//Input capture Functions

#endif /* INC_TIMER_H_ */
