/*
 * USART.c
 *
 *  Created on: Mar 20, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "USART.h"

/******************************************************************************
 *                           generic variables			                      *
 *******************************************************************************/
UART_Config* Global_UART_config[3] ={ NULL , NULL , NULL} ;
uint8_t USART_Index = 0 ;
/******************************************************************************
 *                           generic Function    		                      *
 *******************************************************************************/
void UART_GPIO_Set_Pins(USART_TypeDef* USARTx)
{
	if (USARTx == USART1)
	{
		//PA9   TX
		//PA10  RX
		//PA11  CTS
		//PA12  RTS
		MCAL_GPIO_Init(GPIOA, PIN9, Output_AF_PP_Mode_Speed10MHZ);
		MCAL_GPIO_Init(GPIOA, PIN10, Input_AF);

		if(Global_UART_config[0]->HWFlowCtl  == UART_HWFlowCtl_CTS || Global_UART_config[0]->HWFlowCtl  == UART_HWFlowCtl_RTS_CTS)
		{
			MCAL_GPIO_Init(GPIOA, PIN11, Input_Flo_Mode);
		}
		else if(Global_UART_config[0]->HWFlowCtl  == UART_HWFlowCtl_RTS || Global_UART_config[0]->HWFlowCtl  == UART_HWFlowCtl_RTS_CTS)
		{
			MCAL_GPIO_Init(GPIOA, PIN12, Output_AF_PP_Mode_Speed10MHZ);
		}


	}
	else if (USARTx == USART2)
	{
		//PA2   TX
		//PA3  RX
		//PA0  CTS
		//PA1  RTS
		MCAL_GPIO_Init(GPIOA, PIN2, Output_AF_PP_Mode_Speed10MHZ);
		MCAL_GPIO_Init(GPIOA, PIN3, Input_AF);

		if(Global_UART_config[1]->HWFlowCtl  == UART_HWFlowCtl_CTS || Global_UART_config[1]->HWFlowCtl  == UART_HWFlowCtl_RTS_CTS)
		{
			MCAL_GPIO_Init(GPIOA, PIN0, Input_Flo_Mode);
		}
		else if(Global_UART_config[1]->HWFlowCtl  == UART_HWFlowCtl_RTS || Global_UART_config[1]->HWFlowCtl  == UART_HWFlowCtl_RTS_CTS)
		{
			MCAL_GPIO_Init(GPIOA, PIN1, Output_AF_PP_Mode_Speed10MHZ);
		}
	}
	else if (USARTx == USART3)
	{
		//PB10  TX
		//PB11  RX
		//PB13  CTS
		//PB14  RTS
		MCAL_GPIO_Init(GPIOB, PIN10, Output_AF_PP_Mode_Speed10MHZ);
		MCAL_GPIO_Init(GPIOB, PIN11, Input_AF);
		if(Global_UART_config[2]->HWFlowCtl  == UART_HWFlowCtl_CTS || Global_UART_config[2]->HWFlowCtl  == UART_HWFlowCtl_RTS_CTS)
		{
			MCAL_GPIO_Init(GPIOB, PIN13, Input_Flo_Mode);
		}
		else if(Global_UART_config[2]->HWFlowCtl  == UART_HWFlowCtl_RTS || Global_UART_config[2]->HWFlowCtl  == UART_HWFlowCtl_RTS_CTS)
		{
			MCAL_GPIO_Init(GPIOB, PIN14, Output_AF_PP_Mode_Speed10MHZ);
		}
	}
}
/******************************************************************************
 *                           APIS IMPLEMENTATION			                      *
 *******************************************************************************/
/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param[in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */
void MCAL_UART_Init(USART_TypeDef* USARTx , UART_Config* UART_cnfg , uint32_t PCLK)
{

	//UART Clock Enable
	if(USARTx == USART1)
	{
		MCAL_RCC_Peripherals_enable(APB2, RCC_USART1, RCC_Enable);
		USART_Index = 0 ;
		Global_UART_config[USART_Index] = UART_cnfg ;
	}
	else if (USARTx == USART2)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_USART2, RCC_Enable);
		USART_Index = 1 ;
		Global_UART_config[USART_Index] = UART_cnfg ;
	}
	else if (USARTx == USART3)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_USART3, RCC_Enable);
		USART_Index = 2 ;
		Global_UART_config[USART_Index] = UART_cnfg ;
	}

	//Enable USART Module
	USARTx->CR1 |= (1 << 13);
	//Set USART Mode
	USARTx->CR1 &=~(0b11 << 2);
	USARTx->CR1 |=((UART_cnfg->USART_Mode) << 2);

	//Set pay load length
	USARTx->CR1 &=~(0b1 << 12);
	USARTx->CR1 |=((UART_cnfg->payload_length)<< 12);

	//SET USART Parity
	USARTx->CR1 &=~(0b11 << 9);
	USARTx->CR1 |=((UART_cnfg->parity) << 9);

	//Set the stop bits
	USARTx->CR2 &=~(0b11 << 12);
	USARTx->CR2 |=((UART_cnfg->stopbits) << 12);

	//Set HWFlowCtl
	USARTx->CR3 &=~(0b11 << 8);
	USARTx->CR3 |=((UART_cnfg->HWFlowCtl) << 8);

	//Set USART Baud Rate
	uint32_t Brr = UART_BRR_Register(PCLK , UART_cnfg->BaudRate);
	USARTx->BRR = Brr ;

	//Enable / Disable USART interrupt
	if(UART_cnfg->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_cnfg->IRQ_Enable;

		//Enable NVIC
		if(USARTx == USART1)
		{
			MCAL_NVIC_ENABLE(NVIC_USART1, NVIC_ENABLE);
		}
		else if(USARTx == USART2)
		{
			MCAL_NVIC_ENABLE(NVIC_USART2, NVIC_ENABLE);
		}
		else if(USARTx == USART3)
		{
			MCAL_NVIC_ENABLE(NVIC_USART3, NVIC_ENABLE);
		}
	}

	UART_GPIO_Set_Pins(USARTx);
}

/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param[in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */
void MCAL_UART_DeInit(USART_TypeDef* USARTx)
{
	if(USARTx == USART1)
	{
		MCAL_RCC_Peripherals_enable(APB2, RCC_USART1, RCC_Disable);
		MCAL_RCC_Peripherals_Reset(APB2, RCC_USART1, RCC_Reset);
	}
	else if(USARTx == USART2)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_USART2, RCC_Disable);
		MCAL_RCC_Peripherals_Reset(APB1, RCC_USART2, RCC_Reset);
	}
	else if (USARTx == USART2)
	{
		MCAL_RCC_Peripherals_enable(APB1, RCC_USART3, RCC_Disable);
		MCAL_RCC_Peripherals_Reset(APB1, RCC_USART3, RCC_Reset);
	}
}

/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param[in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */


/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param[in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */
void MCAL_UART_SendData(USART_TypeDef* USARTx , uint16_t* pTxBuffer , USART_Polling_mechanism_t PollingEn)
{
	if (PollingEn == enable)
	{
		while (! (USARTx->SR & 1<<7));
	}

	if(USARTx == USART1)
	{
		USART_Index = 0 ;
	}
	else if (USARTx == USART2)
	{
		USART_Index = 1 ;
	}
	else if (USARTx == USART3)
	{
		USART_Index = 2 ;
	}

	if(Global_UART_config[USART_Index]->payload_length == UART_payload_length_9B)
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0xFF);
	}
}

void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx)
{
	//wait until TC is set in the SR
	while(~(USARTx->SR) & 1 << 6);
}

void MCAL_UART_ReceiveData(USART_TypeDef* USARTx , uint16_t* pRxBuffer , USART_Polling_mechanism_t PollingEn)
{
	//wait until RXNE flag is set in the SR
	if(PollingEn ==enable)
	{
		while(! (USARTx->SR & 1 << 5));
	}
	if(USARTx == USART1)
	{
		USART_Index = 0 ;
	}
	else if (USARTx == USART2)
	{
		USART_Index = 1 ;
	}
	else if (USARTx == USART3)
	{
		USART_Index = 2 ;
	}

	//check the USART_Wordlength item for 9BIT or 8 BIT in the frame
	if(Global_UART_config[USART_Index]->payload_length == UART_payload_length_9B)
	{
		if(Global_UART_config[USART_Index]->parity == UART_parity_NONE)
		{
			*((uint16_t*)pRxBuffer) = USARTx->DR;
		}
		else
		{
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
	}
	else
	{
		if(Global_UART_config[USART_Index]->parity == UART_parity_NONE)
		{
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}
		else
		{
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}
}


void USART1_IRQHandler(void)
{
	Global_UART_config[0]->P_IRQ_CallBack() ;
}

void USART2_IRQHandler(void)
{
	Global_UART_config[1]->P_IRQ_CallBack() ;
}
void USART3_IRQHandler(void)
{
	Global_UART_config[2]->P_IRQ_CallBack() ;
}
