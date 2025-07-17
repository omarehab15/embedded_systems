/*
 * SPI.c
 *
 *  Created on: Mar 26, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "SPI.h"

/******************************************************************************
 *                            Generic Variables			                      *
 *******************************************************************************/
SPI_Config_t* Global_SPI_Config[2] = {NULL,NULL};
SPI_Config_t  Global_SPI_Config1 ;
SPI_Config_t  Global_SPI_Config2 ;
/******************************************************************************
 *                            Generic Macros 			                      *
 *******************************************************************************/
#define SPI1_INDEX				0
#define SPI2_INDEX				1

#define SPI_SR_TXE				((uint8_t)(0x02))  // Transmit Buffer is empty

#define SPI_SR_RXNE				((uint8_t)(0x01))  // Receive Buffer is not empty

/******************************************************************************
 *                            Generic Macros 			                      *
 *******************************************************************************/
void SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_Master)
		{
			//NSS A4
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_Output_Disable :
			{
				MCAL_GPIO_Init(GPIOA, PIN4, Input_Flo_Mode);
			}
			break;
			case SPI_NSS_Hard_Master_Output_Enable:
			{
				MCAL_GPIO_Init(GPIOA, PIN4, Output_AF_PP_Mode_Speed10MHZ);
			}
			break;
			}
			//SCK A5
			MCAL_GPIO_Init(GPIOA, PIN5, Output_AF_PP_Mode_Speed10MHZ);
			//MISO A6
			MCAL_GPIO_Init(GPIOA, PIN6, Input_Flo_Mode);
			//MOSI A7
			MCAL_GPIO_Init(GPIOA, PIN7, Output_AF_PP_Mode_Speed10MHZ);
		}
		else
		{
			//NSS A4
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				MCAL_GPIO_Init(GPIOA, PIN4, Input_Flo_Mode);
			}
			//SCK A5
			MCAL_GPIO_Init(GPIOA, PIN5, Input_Flo_Mode);
			//MISO A6
			MCAL_GPIO_Init(GPIOA, PIN6, Output_AF_PP_Mode_Speed10MHZ);
			//MOSI A7
			MCAL_GPIO_Init(GPIOA, PIN7, Input_Flo_Mode);
		}
	}
	else if (SPIx == SPI2)
	{
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_Master)
		{
			//NSS B12
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_Output_Disable:
			{
				MCAL_GPIO_Init(GPIOB, PIN12, Input_Flo_Mode);
			}
			break;
			case SPI_NSS_Hard_Master_Output_Enable:
			{
				MCAL_GPIO_Init(GPIOB, PIN12, Output_AF_PP_Mode_Speed10MHZ);
			}
			break;
			}
			//SCK B13
			MCAL_GPIO_Init(GPIOB, PIN13, Output_AF_PP_Mode_Speed10MHZ);
			//MISO B14
			MCAL_GPIO_Init(GPIOB, PIN14, Input_Flo_Mode);
			//MOSI B15
			MCAL_GPIO_Init(GPIOB, PIN15, Output_AF_PP_Mode_Speed10MHZ);
		}
		else
		{
			//NSS B12
			if(Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				MCAL_GPIO_Init(GPIOB, PIN12, Input_Flo_Mode);
			}
			//SCK B13
			MCAL_GPIO_Init(GPIOB, PIN13, Input_Flo_Mode);
			//MISO B14
			MCAL_GPIO_Init(GPIOB, PIN14, Output_AF_PP_Mode_Speed10MHZ);
			//MOSI B15
			MCAL_GPIO_Init(GPIOB, PIN15, Input_Flo_Mode);
		}
	}
}
/******************************************************************************
 *                            APIS IMPLEMENTATION			                  *
 *******************************************************************************/
/**================================================================
 * @Fn			-MCAL_SPI_Init
 * @brief 		-Initializes the SPIs  according to the specified parameters in SPI_Config_t
 * @param[in] 	-SPIx: where x can be (1 , 2  depending on device used) to select the SPI peripheral
 * @param[in] 	-SPI_Config: pointer Structure to configure SPI features
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config_t *SPI_Config)
{
	//Safety for registers
	uint16_t temp_CR1 = 0 ;
	uint16_t temp_CR2 = 0 ;

	if(SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_Config;
		Global_SPI_Config[SPI1_INDEX] = SPI_Config ;
		MCAL_RCC_Peripherals_enable(APB2, RCC_SPI1, RCC_Enable);
	}
	else if (SPIx == SPI1)
	{
		Global_SPI_Config2 = *SPI_Config;
		Global_SPI_Config[SPI1_INDEX] = SPI_Config ;
		MCAL_RCC_Peripherals_enable(APB1, RCC_SPI2, RCC_Enable);
	}

	//SPI enable
	temp_CR1 =(1 << 6);

	//Master or Slave
	temp_CR1 |= SPI_Config->Device_Mode ;

	// SPI Communication Mode
	temp_CR1 |= SPI_Config->Communication_Mode ;

	//SPI Frame Format
	temp_CR1 |= SPI_Config->Frame_Format ;

	//SPI Data Size
	temp_CR1 |= SPI_Config->Data_Size ;

	//SPI Clock polarity
	temp_CR1 |= SPI_Config->CLK_Polarity ;

	//SPI Clock Phase
	temp_CR1 |= SPI_Config->CLK_Phase ;

	//=======================NSS=====================

	if(SPI_Config->NSS == SPI_NSS_Hard_Master_Output_Enable)
	{
		temp_CR2 |= SPI_Config->NSS ;
	}
	else if(SPI_Config->NSS == SPI_NSS_Hard_Master_Output_Disable)
	{
		temp_CR2 &= SPI_Config->NSS ;
	}
	else
	{
		temp_CR1 |= SPI_Config->NSS ;
	}
	//===============================================
	//SPI BaudRate Prescaler
	temp_CR1 |= SPI_Config->SPI_BAUDRATEPRESCALER ;

	// Interrupt
	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		//SPI IRQ ENable define
		temp_CR2 &= SPI_Config->IRQ_Enable ;
		if(SPIx  == SPI1 )
		{
			MCAL_NVIC_ENABLE(NVIC_SPI1, NVIC_ENABLE);
		}
		else if(SPIx  == SPI2 )
		{
			MCAL_NVIC_ENABLE(NVIC_SPI2, NVIC_ENABLE);
		}
	}

	SPIx->CR1 = temp_CR1 ;
	SPIx->CR2 = temp_CR2 ;
	SPI_GPIO_Set_Pins(SPIx);

}


/**================================================================
 * @Fn			-MCAL_SPI_DeInit
 * @brief 		-Reset SPI peripheral
 * @param[in] 	-SPIx: where x can be (1 , 2  depending on device used) to select the SPI peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx  == SPI1 )
	{
		MCAL_NVIC_ENABLE(NVIC_SPI1, NVIC_DISABLE);
		MCAL_RCC_Peripherals_enable(APB2, RCC_SPI1, RCC_Disable);
		MCAL_RCC_Peripherals_Reset(APB2, RCC_SPI1, RCC_Reset);
	}
	else if(SPIx  == SPI2 )
	{
		MCAL_NVIC_ENABLE(NVIC_SPI2, NVIC_DISABLE);
		MCAL_RCC_Peripherals_enable(APB1, RCC_SPI2, RCC_Disable);
		MCAL_RCC_Peripherals_Reset(APB1, RCC_SPI2, RCC_Reset);
	}
}

/**================================================================
 * @Fn			-MCAL_SPI_SendData
 * @brief 		-Send data using SPI
 * @param[in] 	-SPIx: where x can be (1 , 2  depending on device used) to select the SPI peripheral
 * @param[in] 	-pTxBuffer: buffer to carry the data
 * @param[in] 	-PollingEn: to enable or disable polling mechanism
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,SPI_PollingMechanism_t PollingEn )
{
	if (PollingEn == SPI_PollingEnable)
		while(!((SPIx)->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer ;
}

/**================================================================
 * @Fn			-MCAL_SPI_ReceiveData
 * @brief 		-Receive data using SPI
 * @param[in] 	-SPIx: where x can be (1 , 2  depending on device used) to select the SPI peripheral
 * @param[in] 	-pTxBuffer: buffer to carry the data
 * @param[in] 	-PollingEn: to enable or disable polling mechanism
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,SPI_PollingMechanism_t PollingEn )
{
	if (PollingEn == SPI_PollingEnable)
		while(!((SPIx)->SR & SPI_SR_RXNE));
	*pTxBuffer =SPIx->DR  ;
}
/**================================================================
 * @Fn			-MCAL_SPI_TX_RX
 * @brief 		-transmit and Receive data using SPI
 * @param[in] 	-SPIx: where x can be (1 , 2  depending on device used) to select the SPI peripheral
 * @param[in] 	-pTxBuffer: buffer to carry the data
 * @param[in] 	-PollingEn: to enable or disable polling mechanism
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,SPI_PollingMechanism_t PollingEn )
{
	if (PollingEn == SPI_PollingEnable)
		while(!((SPIx)->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer ;
	if (PollingEn == SPI_PollingEnable)
		while(!((SPIx)->SR & SPI_SR_RXNE));
	*pTxBuffer =SPIx->DR  ;
}
