/*
 * USART.h
 *
 *  Created on: Mar 20, 2024
 *      Author: omar
 */

#ifndef INC_USART_H_
#define INC_USART_H_

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "STM32F103C8.h"
#include "RCC.h"
#include "GPIO.h"
#include "ISR.h"


/******************************************************************************
*                       configration structure          	                  *
*******************************************************************************/
typedef struct
{
	uint8_t 	USART_Mode;				//specifies TX/TR Enable/Disable
										//This parameter must be set based on @ref UART_Mode_define

	uint32_t	BaudRate;				//This member configures the UART communication baud rate
										//This parameter must be set based on @ref UART_baudRate_define

	uint8_t		payload_length;			//This member specifies the number of data bits transmitted or received
										//This parameter must be set based on @ref UART_payload_length

	uint8_t		parity;					//This member specifies the parity mode
										//This parameter must be set based on @ref UART_parity_define

	uint8_t		stopbits;				//This member specifies the number of stop bits transmitted
										//This parameter must be set based on @ref UART_StopBits_define

	uint8_t		HWFlowCtl;				//This member specifies the hardware flow control mode is Enable/Disable
										//This parameter must be set based on @ref UART_HWFlowCtl_define

	uint8_t		IRQ_Enable;				//This member Enable or Disable UART IRQ TX/RX
										//This parameter must be set based on @ref UART_IRQ_Enable_define


	void(* P_IRQ_CallBack)(void) ;		//Set the C function which will be called once the IRQ happen

}UART_Config;




/******************************************************************************
*                       	  References Macros         	                  *
*******************************************************************************/
//@ref UART_Mode_define
#define UART_Mode_RX						0b10
#define UART_Mode_TX						0b01
#define UART_Mode_TX_RX						0b11

//@ref UART_baudRate_define

#define UART_BaudRate_2400					2400
#define UART_BaudRate_9600					9600
#define UART_BaudRate_19200					19200
#define UART_BaudRate_57600					57600
#define UART_BaudRate_115200				115200
#define UART_BaudRate_230400				230400
#define UART_BaudRate_460800				460800
#define UART_BaudRate_921600				921600
#define UART_BaudRate_2250000				2250000
#define UART_BaudRate_45000000				45000000

//@ref UART_payload_length
#define UART_payload_length_8B				0
#define UART_payload_length_9B 				1

//@ref UART_parity_define
#define UART_parity_NONE					0b00
#define UART_parity_EVEN					0b10
#define UART_parity_ODD						0b11

//@ref UART_StopBits_define
#define UART_StopBits_half					0b01
#define UART_StopBits_1						0b00
#define UART_StopBits_1_half				0b11
#define UART_StopBits_2						0b10

//@ref UART_HWFlowCtl_define
#define UART_HWFlowCtl_NONE					0b00
#define UART_HWFlowCtl_RTS					0b01
#define UART_HWFlowCtl_CTS					0b10
#define UART_HWFlowCtl_RTS_CTS				0b11

//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE				(uint32_t)(0)
#define UART_IRQ_Enable_TXE					(uint32_t)(1<<7)
#define UART_IRQ_Enable_TC					(uint32_t)(1<<6)
#define UART_IRQ_Enable_RXNEIE				(uint32_t)(1<<5)
#define UART_IRQ_Enable_PE					(uint32_t)(1<<8)


typedef enum
{
	enable ,
	disable
}USART_Polling_mechanism_t;

//BaudRate Calculation
//USARTDIV = fclk / (16 * BaudRate )
//USARTDIV_MUL100 =
//uint32 ((100 * fclk) / (16 * BaudRate) == (25 * fclk) / (4 * BaudRate ) )
//DIV_Mantissa_MUL100 = Integer part (USARTDIV)*100
//DIV_Mantissa = Integer part (USARTDIV)
//DIV_Fraction = ((USARTDIV_MUL100 - DIV_Mantissa_MUL100)* 16 )/100
#define  USARTDIV(_PCLK_ , _BAUD_ )				(uint32_t)(_PCLK_ / (16 * _BAUD_))
#define  USARTDIV_MUL100(_PCLK_ , _BAUD_ )		(uint32_t)((25 * _PCLK_ ) / (4 * _BAUD_))
#define  Mantissa_MUL100(_PCLK_ , _BAUD_ )		(uint32_t)(USARTDIV(_PCLK_ , _BAUD_ ) * 100)
#define  Mantissa(_PCLK_ , _BAUD_ )				(uint32_t)(USARTDIV(_PCLK_ , _BAUD_ ) )
#define  DIV_Fraction(_PCLK_ , _BAUD_ )			(uint32_t)(((USARTDIV_MUL100(_PCLK_ , _BAUD_ )- Mantissa_MUL100(_PCLK_ , _BAUD_ ))*16)/100)
#define  UART_BRR_Register(_PCLK_ , _BAUD_ )	 ((Mantissa(_PCLK_ , _BAUD_ )) << 4) | ((DIV_Fraction(_PCLK_ , _BAUD_ ))&0xF)

/******************************************************************************
*                                    APIs			                          *
*******************************************************************************/
void MCAL_UART_Init(USART_TypeDef* USARTx , UART_Config* UART_cnfg , uint32_t PCLK);
void MCAL_UART_DeInit(USART_TypeDef* USARTx);

void MCAL_UART_SendData(USART_TypeDef* USARTx , uint16_t* pTxBuffer , USART_Polling_mechanism_t PollingEn);
void MCAL_UART_ReceiveData(USART_TypeDef* USARTx , uint16_t* pRxBuffer , USART_Polling_mechanism_t PollingEn);

void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx);


#endif /* INC_USART_H_ */
