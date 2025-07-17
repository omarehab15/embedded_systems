/*
 * ISR.c
 *
 *  Created on: Feb 28, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "ISR.h"

/******************************************************************************
 *                           Generic Variables			                      *
 *******************************************************************************/
void(* GP_IRQ_Callback[15])(void);

/******************************************************************************
 *                           Generic Functions			                      *
 *******************************************************************************/
void EXTI_get_PIN(GPIO_TypeDef *GPIOx ,GPIO_PINs_t EXTI_PinNum)
{
	switch(EXTI_PinNum)
	{
	case PIN0 :
	{
		AFIO->CR1 &=~(0b1111 << 0);
		if(GPIOx == GPIOA) {AFIO->CR1 |=(0b0000 << 0);}
		else if(GPIOx == GPIOB) {AFIO->CR1 |=(0b0001 << 0);}
		else if(GPIOx == GPIOC) {AFIO->CR1 |=(0b0010 << 0);}
		else if(GPIOx == GPIOD) {AFIO->CR1 |=(0b0011 << 0);}
	}
	break;
	case PIN1 :
	{
		AFIO->CR1 &=~(0b1111 << 4);
		if(GPIOx == GPIOA) {AFIO->CR1 |=(0b0000 << 4);}
		else if(GPIOx == GPIOB) {AFIO->CR1 |=(0b0001 << 4);}
		else if(GPIOx == GPIOC) {AFIO->CR1 |=(0b0010 << 4);}
		else if(GPIOx == GPIOD) {AFIO->CR1 |=(0b0011 << 4);}
	}
	break;
	case PIN2 :
	{
		AFIO->CR1 &=~(0b1111 << 8);
		if(GPIOx == GPIOA) {AFIO->CR1 |=(0b0000 << 8);}
		else if(GPIOx == GPIOB) {AFIO->CR1 |=(0b0001 << 8);}
		else if(GPIOx == GPIOC) {AFIO->CR1 |=(0b0010 << 8);}
		else if(GPIOx == GPIOD) {AFIO->CR1 |=(0b0011 << 8);}
	}
	break;
	case PIN3 :
	{
		AFIO->CR1 &=~(0b1111 << 12);
		if(GPIOx == GPIOA) {AFIO->CR1 |=(0b0000 << 12);}
		else if(GPIOx == GPIOB) {AFIO->CR1 |=(0b0001 << 12);}
		else if(GPIOx == GPIOC) {AFIO->CR1 |=(0b0010 << 12);}
		else if(GPIOx == GPIOD) {AFIO->CR1 |=(0b0011 << 12);}
	}
	break;
	case PIN4 :
	{
		AFIO->CR2 &=~(0b1111 << 0);
		if(GPIOx == GPIOA) {AFIO->CR2 |=(0b0000 << 0);}
		else if(GPIOx == GPIOB) {AFIO->CR2 |=(0b0001 << 0);}
		else if(GPIOx == GPIOC) {AFIO->CR2 |=(0b0010 << 0);}
		else if(GPIOx == GPIOD) {AFIO->CR2 |=(0b0011 << 0);}
	}
	break;
	case PIN5 :
	{
		AFIO->CR2 &=~(0b1111 << 4);
		if(GPIOx == GPIOA) {AFIO->CR2 |=(0b0000 << 4);}
		else if(GPIOx == GPIOB) {AFIO->CR2 |=(0b0001 << 4);}
		else if(GPIOx == GPIOC) {AFIO->CR2 |=(0b0010 << 4);}
		else if(GPIOx == GPIOD) {AFIO->CR2 |=(0b0011 << 4);}
	}
	break;
	case PIN6 :
	{
		AFIO->CR2 &=~(0b1111 << 8);
		if(GPIOx == GPIOA) {AFIO->CR2 |=(0b0000 << 8);}
		else if(GPIOx == GPIOB) {AFIO->CR2 |=(0b0001 << 8);}
		else if(GPIOx == GPIOC) {AFIO->CR2 |=(0b0010 << 8);}
		else if(GPIOx == GPIOD) {AFIO->CR2 |=(0b0011 << 8);}
	}
	break;
	case PIN7 :
	{
		AFIO->CR2 &=~(0b1111 << 12);
		if(GPIOx == GPIOA) {AFIO->CR2 |=(0b0000 << 12);}
		else if(GPIOx == GPIOB) {AFIO->CR2 |=(0b0001 << 12);}
		else if(GPIOx == GPIOC) {AFIO->CR2 |=(0b0010 << 12);}
		else if(GPIOx == GPIOD) {AFIO->CR2 |=(0b0011 << 12);}
	}
	break;
	case PIN8 :
	{
		AFIO->CR3 &=~(0b1111 << 0);
		if(GPIOx == GPIOA) {AFIO->CR3 |=(0b0000 << 0);}
		else if(GPIOx == GPIOB) {AFIO->CR3 |=(0b0001 << 0);}
		else if(GPIOx == GPIOC) {AFIO->CR3 |=(0b0010 << 0);}
		else if(GPIOx == GPIOD) {AFIO->CR3 |=(0b0011 << 0);}
	}
	break;
	case PIN9 :
	{
		AFIO->CR3 &=~(0b1111 << 4);
		if(GPIOx == GPIOA) {AFIO->CR3 |=(0b0000 << 4);}
		else if(GPIOx == GPIOB) {AFIO->CR3 |=(0b0001 << 4);}
		else if(GPIOx == GPIOC) {AFIO->CR3 |=(0b0010 << 4);}
		else if(GPIOx == GPIOD) {AFIO->CR3 |=(0b0011 << 4);}
	}
	break;
	case PIN10 :
	{
		AFIO->CR3 &=~(0b1111 << 8);
		if(GPIOx == GPIOA) {AFIO->CR3 |=(0b0000 << 8);}
		else if(GPIOx == GPIOB) {AFIO->CR3 |=(0b0001 << 8);}
		else if(GPIOx == GPIOC) {AFIO->CR3 |=(0b0010 << 8);}
		else if(GPIOx == GPIOD) {AFIO->CR3 |=(0b0011 << 8);}
	}
	break;
	case PIN11 :
	{
		AFIO->CR3 &=~(0b1111 << 12);
		if(GPIOx == GPIOA) {AFIO->CR3 |=(0b0000 << 12);}
		else if(GPIOx == GPIOB) {AFIO->CR3 |=(0b0001 << 12);}
		else if(GPIOx == GPIOC) {AFIO->CR3 |=(0b0010 << 12);}
		else if(GPIOx == GPIOD) {AFIO->CR3 |=(0b0011 << 12);}
	}
	break;
	case PIN12 :
	{
		AFIO->CR4 &=~(0b1111 << 0);
		if(GPIOx == GPIOA) {AFIO->CR4 |=(0b0000 << 0);}
		else if(GPIOx == GPIOB) {AFIO->CR4 |=(0b0001 << 0);}
		else if(GPIOx == GPIOC) {AFIO->CR4 |=(0b0010 << 0);}
		else if(GPIOx == GPIOD) {AFIO->CR4 |=(0b0011 << 0);}
	}
	break;
	case PIN13 :
	{
		AFIO->CR4 &=~(0b1111 << 4);
		if(GPIOx == GPIOA) {AFIO->CR4 |=(0b0000 << 4);}
		else if(GPIOx == GPIOB) {AFIO->CR4 |=(0b0001 << 4);}
		else if(GPIOx == GPIOC) {AFIO->CR4 |=(0b0010 << 4);}
		else if(GPIOx == GPIOD) {AFIO->CR4 |=(0b0011 << 4);}
	}
	break;
	case PIN14 :
	{
		AFIO->CR4 &=~(0b1111 << 8);
		if(GPIOx == GPIOA) {AFIO->CR4 |=(0b0000 << 8);}
		else if(GPIOx == GPIOB) {AFIO->CR4 |=(0b0001 << 8);}
		else if(GPIOx == GPIOC) {AFIO->CR4 |=(0b0010 << 8);}
		else if(GPIOx == GPIOD) {AFIO->CR4 |=(0b0011 << 8);}
	}
	break;
	case PIN15 :
	{
		AFIO->CR4 &=~(0b1111 << 12);
		if(GPIOx == GPIOA) {AFIO->CR4 |=(0b0000 << 12);}
		else if(GPIOx == GPIOB) {AFIO->CR4 |=(0b0001 << 12);}
		else if(GPIOx == GPIOC) {AFIO->CR4 |=(0b0010 << 12);}
		else if(GPIOx == GPIOD) {AFIO->CR4 |=(0b0011 << 12);}
	}
	break;
	}
}

void NVIC_Enable(GPIO_PINs_t EXTI_PinNum)
{
	switch(EXTI_PinNum)
	{
	case PIN0: MCAL_NVIC_ENABLE(NVIC_EXTI0, NVIC_ENABLE);
	break;
	case PIN1: MCAL_NVIC_ENABLE(NVIC_EXTI1, NVIC_ENABLE);
	break;
	case PIN2: MCAL_NVIC_ENABLE(NVIC_EXTI2, NVIC_ENABLE);
	break;
	case PIN3: MCAL_NVIC_ENABLE(NVIC_EXTI3, NVIC_ENABLE);
	break;
	case PIN4: MCAL_NVIC_ENABLE(NVIC_EXTI4, NVIC_ENABLE);
	break;
	case PIN5 :
	case PIN6 :
	case PIN7 :
	case PIN8 :
	case PIN9 :MCAL_NVIC_ENABLE(NVIC_EXTI5_9, NVIC_ENABLE);
	break;
	case PIN10 :
	case PIN11 :
	case PIN12 :
	case PIN13 :
	case PIN14 :
	case PIN15 :MCAL_NVIC_ENABLE(NVIC_EXTI10_15, NVIC_ENABLE);
	break;
	}
}
/******************************************************************************
 *                           APIS IMPLEMENTATION			                      *
 *******************************************************************************/
void MCAL_NVIC_ENABLE(NVIC_Preph_t preph  , uint8_t state)
{
	switch(state)
	{
	case NVIC_ENABLE :
	{
		if(preph < 32)
		{
			NVIC->ISER0 |= (1 << preph);
		}
		else
		{
			NVIC->ISER1 |= (1 << (preph-32));
		}
	}
	break;
	default:
	{
		if(preph < 32)
		{
			NVIC->ICER0 |= (1 << preph);
		}
		else
		{
			NVIC->ICER1 |= (1 << (preph-32));
		}
	}
	break;
	}
}

void MCAL_EXTI_INIT(GPIO_TypeDef *GPIOx ,GPIO_PINs_t EXTI_PinNum , EXTI_Trigger_t trigger , void (*function_addres) (void))
{
	MCAL_GPIO_Init(GPIOx, EXTI_PinNum, Input_AF);
	EXTI_get_PIN(GPIOx, EXTI_PinNum);

	/***********trigger case***********/
	EXTI->RTSR &=~(1 << EXTI_PinNum);
	EXTI->FTSR &=~(1 << EXTI_PinNum);
	switch(trigger)
	{
	case EXTI_Trigger_Rising :
	{
		EXTI->RTSR |=(1 << EXTI_PinNum);
	}
	break;
	case EXTI_Trigger_Falling :
	{
		EXTI->FTSR |=(1 << EXTI_PinNum);
	}
	break;
	case EXTI_Trigger_Both :
	{
		EXTI->RTSR |=(1 << EXTI_PinNum);
		EXTI->FTSR |=(1 << EXTI_PinNum);
	}
	break;
	}

	/**********Update IRQ Handling callback ***************/
	GP_IRQ_Callback[EXTI_PinNum]= function_addres ;

	EXTI->IMR |= (1 << EXTI_PinNum);

	NVIC_Enable(EXTI_PinNum);

}

/**================================================================
 * @Fn              - MCAL_EXTI_GPIO_DEINIT
 * @brief           - Reset External interrupt registers and NVIC coresponding IRQ mask
 * @retval          - none
 *================================================================ */
void MCAL_EXTI_GPIO_DEINIT(void){
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR = 0xFFFFFFFF;


	MCAL_NVIC_ENABLE(NVIC_EXTI0, NVIC_DISABLE);
	MCAL_NVIC_ENABLE(NVIC_EXTI1, NVIC_DISABLE);
	MCAL_NVIC_ENABLE(NVIC_EXTI2, NVIC_DISABLE);
	MCAL_NVIC_ENABLE(NVIC_EXTI3, NVIC_DISABLE);
	MCAL_NVIC_ENABLE(NVIC_EXTI4, NVIC_DISABLE);
	MCAL_NVIC_ENABLE(NVIC_EXTI5_9, NVIC_DISABLE);
	MCAL_NVIC_ENABLE(NVIC_EXTI10_15, NVIC_DISABLE);

}

/******************************************************************************************************************/
void EXTI0_IRQHandler(void){
	// clear bit in pending register (EXTI_PR)
	EXTI->PR |= (1<<0);
	GP_IRQ_Callback[0]();
}

void EXTI1_IRQHandler(void){
	EXTI->PR |= (1<<1);
	GP_IRQ_Callback[1]();

}

void EXTI2_IRQHandler(void){
	EXTI->PR |= (1<<2);
	GP_IRQ_Callback[2]();
}

void EXTI3_IRQHandler(void){
	EXTI->PR |= (1<<3);
	GP_IRQ_Callback[3]();
}

void EXTI4_IRQHandler(void){
	EXTI->PR |= (1<<4);
	GP_IRQ_Callback[4]();
}

void EXTI9_5_IRQHandler(void){
	if(EXTI->PR & (1<<5)) {EXTI->PR |= (1<<5); GP_IRQ_Callback[5]();  }
	if(EXTI->PR & (1<<6)) {EXTI->PR |= (1<<6); GP_IRQ_Callback[6]();  }
	if(EXTI->PR & (1<<7)) {EXTI->PR |= (1<<7); GP_IRQ_Callback[7]();  }
	if(EXTI->PR & (1<<8)) {EXTI->PR |= (1<<8); GP_IRQ_Callback[8]();  }
	if(EXTI->PR & (1<<9)) {EXTI->PR |= (1<<9); GP_IRQ_Callback[9]();  }
}

void EXTI15_10_IRQHandler(void){
	if(EXTI->PR & (1<<10)) {EXTI->PR |= (1<<10); GP_IRQ_Callback[10]();  }
	if(EXTI->PR & (1<<11)) {EXTI->PR |= (1<<11); GP_IRQ_Callback[11]();  }
	if(EXTI->PR & (1<<12)) {EXTI->PR |= (1<<12); GP_IRQ_Callback[12]();  }
	if(EXTI->PR & (1<<13)) {EXTI->PR |= (1<<13); GP_IRQ_Callback[13]();  }
	if(EXTI->PR & (1<<14)) {EXTI->PR |= (1<<14); GP_IRQ_Callback[14]();  }
	if(EXTI->PR & (1<<15)) {EXTI->PR |= (1<<15); GP_IRQ_Callback[15]();  }

}
