/*
 * TIMER.c
 *
 *  Created on: Jul 25, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "TIMER.h"













void delay(TIMx_TypeDef *TIMx, uint16_t time,uint8_t U,uint32_t clk)
{

	if(TIMx == TIM2)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_TIM2, RCC_Enable);
	}
	else if(TIMx == TIM3)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_TIM3, RCC_Enable);
	}
	else if(TIMx == TIM4)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_TIM3, RCC_Enable);
	}

	TIMx->CR1 &=~ (1 << 0 );

}
