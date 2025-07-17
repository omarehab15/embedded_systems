/*
 * SPI.h
 *
 *  Created on: Mar 26, 2024
 *      Author: omar
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_
/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include"STM32F103C8.h"
#include "RCC.h"
#include "GPIO.h"
#include "ISR.h"

/******************************************************************************
*                                 Macros Configuration References			  *
*******************************************************************************/
//@ref SPI_Device_Mode  //CR1 >> Bit 2
#define SPI_Device_Mode_Slave					(uint32_t)(0)
#define SPI_Device_Mode_Master					(uint32_t)(1 << 2)

//@ref SPI_Communication_Mode  CR1
#define SPI_DIRECTION_2LINES					(uint32_t)(0)
#define SPI_DIRECTION_2LINES_RXONLY				(uint32_t)(1<<10)
#define SPI_DIRECTION_1LINES_TXONLY	 			(uint32_t)(1<<15 | 1<<14)
#define SPI_DIRECTION_1LINES_RXONLY	 			(uint32_t)(1<<15)

//@ref SPI_Frame_Format		CR1
#define SPI_Frame_Format_MSB					(uint32_t)(0)
#define SPI_Frame_Format_LSB					(uint32_t)(1<<7)

//@ref SPI_Data_Size		CR1
#define SPI_DATA_Size_8B						(uint32_t)(0)
#define SPI_DATA_Size_16B						(uint32_t)(1<<11)

//@ref SPI_Clock_Polarity	CR1
#define SPI_CLK_Polarity_LOW					(uint32_t)(1<<1)
#define SPI_CLK_Polarity_GIGH					(uint32_t)(1<<1)

//@ref SPI_Clock_Phase
#define SPI_CLK_Phase_1st_EDGE_Capture			(uint32_t)(1<<1)
#define SPI_CLK_Phase_2nd_EDGE_Capture			(uint32_t)(1<<1)

//@ref SPI_NSS SPI Slave Select Management
//-----------------NSS--------------------
//Hardware
#define SPI_NSS_Hard_Slave						(uint32_t)(0) //CR
#define SPI_NSS_Hard_Master_Output_Enable		(uint32_t)(1<<2) //CR2
#define SPI_NSS_Hard_Master_Output_Disable		~((uint32_t)(1<<2)) //CR2

//NSS is Driven by SW (Master or Slave)
#define SPI_NSS_SW_Reset						(uint32_t)(1<<9)//CR1
#define SPI_NSS_SW_Set							(uint32_t)(1<<9 | 1<<8)//CR1

//@ref SPI_BaudRatePrescaler //CR1
#define SPI_BaudRatePrescaler_2					(uint32_t)(0)
#define SPI_BaudRatePrescaler_4					(uint32_t)(0b001U << 3)
#define SPI_BaudRatePrescaler_8					(uint32_t)(0b010U << 3)
#define SPI_BaudRatePrescaler_16				(uint32_t)(0b011U << 3)
#define SPI_BaudRatePrescaler_32				(uint32_t)(0b100U << 3)
#define SPI_BaudRatePrescaler_64				(uint32_t)(0b101U << 3)
#define SPI_BaudRatePrescaler_128				(uint32_t)(0b110U << 3)
#define SPI_BaudRatePrescaler_256				(uint32_t)(0b111U << 3)

//@ref SPI_IRQ_Enable_Define
#define SPI_IRQ_Enable_NONE						(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE					(uint32_t)(1<<7)//CR2
#define SPI_IRQ_Enable_RXNEIE					(uint32_t)(1<<5)//CR2
#define SPI_IRQ_Enable_ERRIE					(uint32_t)(1<<6)//CR2

//==============================================
//			User type definitions (structures)
//==============================================
struct S_IRQ_SRC
{
	uint8_t TXE:1 ;
	uint8_t RXNE:1 ;
	uint8_t ERRI:1 ;
	uint8_t Reserved:5 ;
};

typedef enum
{
	SPI_PollingEnable ,
	SPI_PollingDisable
}SPI_PollingMechanism_t;


typedef struct
{
	uint16_t        Device_Mode ;           				//specifies the SPI operation mode @ref SPI_Device_Mode
	uint16_t        Communication_Mode ;    				//specifies the SPI bidirectional mode state @ref SPI_Communication_Mode
	uint16_t        Frame_Format ;          				//specifies LSB or MSB @ref SPI_Frame_Format
	uint16_t        Data_Size ;             				//specifies Size of TX/RX Data 8/16 Bits @ref SPI_Data_Size
	uint16_t        CLK_Polarity ;          				//specifies Clock Polarity (Low_Level when Idle or High_Level when idle )
															//this Parameter set based on @ref SPI_Clock_Polarity
	uint16_t        CLK_Phase ;             				//specifies Clock Phase (Sampling at 1st or 2nd edge)according to CLKPolarity
															//this Parameter set based on @ref SPI_Clock_Phase
	uint32_t        NSS;                    				//specifies whether the NSS signal managed by
															//Hardware (NSS Pin) or (Software SSI bit enable)
															//this Parameter set based on @ref SPI_NSS
	uint16_t        SPI_BAUDRATEPRESCALER ; 				//Specifies the baud rate prescaler value which will be
															//used to configure the transmit and receive SCK Clock.
															//This Parameter can be a value of @ref SPI_BaudRatePrescaler
															//@note The Communication Clock derived form the master clock.
															//The slave clock dose not need to be set.*/
															//Take care you have to Configure RCC to enter the correct clock to APB1 >> SPI2
															//or APB2 >> SPI1 .*/
	uint16_t        IRQ_Enable ;            				//Specifies Interrupt Enable or Disable
															//This parameter must be set based on @ref SPI_IRQ_Enable_Define
	void (* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src );		// Set C Function() which will be called once the IRQ Happen .
}SPI_Config_t;

/******************************************************************************
*                               	APIs			                          *
*******************************************************************************/
void MCAL_SPI_Init(SPI_TypeDef *SPIx,SPI_Config_t *SPI_Config);
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx);

void MCAL_SPI_SendData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,SPI_PollingMechanism_t PollingEn );

void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,SPI_PollingMechanism_t PollingEn );

void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx,uint16_t *pTxBuffer ,SPI_PollingMechanism_t PollingEn );


#endif /* INC_SPI_H_ */
