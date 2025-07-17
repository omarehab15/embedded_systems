/*
 * I2C.h
 *
 *  Created on: Apr 24, 2024
 *      Author: omar
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "STM32F103C8.h"
#include "RCC.h"
#include "GPIO.h"
#include "ISR.h"

/******************************************************************************
*                            Reference Structure 		                      *
*******************************************************************************/
struct S_I2C_Slave_Device_Address
{
	uint16_t			Enable_Daul_ADD ; //1-Enable  0-Disable
	uint16_t			Primary_slave_address ;
	uint16_t			Secondary_slave_address ;
	uint32_t			I2C_Addressing_slave_mode ; // @I2C_Addressing_slave

};

typedef enum
{
	I2C_EV_STOP  ,
	I2C_ERROR_AF ,
	I2C_EV_ADDR_Matched ,
	I2C_EV_DATA_REQ ,//the APP layer should send the data (I2C_Slave_SendData) in this state
	I2C_EV_DATA_RCV  //the APP layer should read the data (I2C_Slave_ReceiveData) in this state
}Slave_State;

typedef struct
{
	uint32_t								I2C_ClockSpeed; /* specifies the clock frequency
	                       	   	   	   	   	   	   	   	    this parameter must be set to  @I2C_SCLK */

	uint32_t								StretchMode;/* this parameter must be set to  @I2C_StretchMode */

	uint32_t								I2C_Mode;/* this parameter must be set to  @Mode */

	struct S_I2C_Slave_Device_Address		I2C_Slave_Address ;

	uint32_t								I2C_ACK_Control ; /* this parameter must be set to  @I2C_Ack */

	uint32_t								General_Call_Address_Detection ;

	void(* P_Slave_Event_CallBack)(Slave_State state) ;

}I2C_InitTypeDef;

/******************************************************************************
*                            Reference MACROs   		                      *
*******************************************************************************/
//@I2C_SCLK_
// -STrandard Speed (up to 100 KHZ )
// -Fast Speed (up to 400 KHZ )
//* to configure Clock before enable the peripheral
//----I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//* Configure the clock control registers
//		thigh = CCR * TPCLK1
//		SM or FM
//* Configure the rise time register
//------------------------

#define I2C_SCLK_SM_50K									50000U
#define I2C_SCLK_SM_100K								10000U
#define I2C_SCLK_FM_200K								20000U//Fast Mode Not Supported yet
#define I2C_SCLK_FM_400K								40000U

//------------------------------------------------------------------------------

//@I2C_StretchMode_
//I2C_CR1
//Bit7 NOSTRETCH:Clock stretching disable (Slave mode)
//0: Clock stretching enable
//1: Clock stretching disable

#define I2C_StretchMode_Enable							0X00000000U
#define I2C_StretchMode_Disable							I2C_CR1_NOSTRETCH

//------------------------------------------------------------------------------

//@I2C_Mode_
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode

#define I2C_Mode_I2C									0
#define I2C_Mode_SMBus									I2C_CR1_SMBUS

//------------------------------------------------------------------------------

//@I2C_Addressing_slave_
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)

#define I2C_Addressing_slave_mode_7Bit					0
#define I2C_Addressing_slave_mode_10Bit					(uint16_t)(1<<15)

//------------------------------------------------------------------------------

//@I2C_ACK_
//I2C_CR1
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)

#define I2C_ACK_Enable							(I2C_CR1_ACK)
#define I2C_ACK_Disable							0

//------------------------------------------------------------------------------

//@I2C_ENGC_
//I2C_CR1
//ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.

#define I2C_ENGC_Enable							(I2C_CR1_ENGC)
#define I2C_ENGC_Disable						0

//------------------------------------------------------------------------------

typedef enum
{
	with_stop ,
	without_stop
}Stop_Condition;

typedef enum
{
	Start ,
	repeated_start
}Repeated_Start;

typedef enum
{
	DISABLE = 0 ,
	ENABLE = 1
}FunctionalState;

typedef enum
{
	RESET = 0 ,
	SET = 1
}FlagStatus;

typedef enum
{
	I2C_Direction_Transmitter  ,  // Write
	I2C_Direction_Receiver		 // Read
}I2C_Direction;

typedef enum
{
	I2C_BUS_BUSY=0,
	EV5	,				//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6 ,				//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7 ,   			//EV5: RxNE = 1 Cleared by Reading DR Register
	EV8 , 				//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1,				//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8_2,  			//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	MASTER_BYTE_TRANSMITTING =((uint32_t) 0x00070080), /*TRA , BUSY , TXE , MSL , TXE flage*/
}Status;

/******************************************************************************
*                               	APIs			                          *
*******************************************************************************/
void MCAL_I2C_Init(I2C_TypeDef *I2Cx , I2C_InitTypeDef *I2C_config , uint32_t pclk);
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx);
void MCAL_I2C_Set_GPIO_Pins(I2C_TypeDef *I2Cx);

void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx ,uint16_t DevAddr , uint8_t* DataOut , uint32_t DataLen , Stop_Condition Stop,Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx ,uint16_t DevAddr , uint8_t* DataOut , uint32_t DataLen , Stop_Condition Stop,Repeated_Start Start);

void I2C_Generate_Start(I2C_TypeDef *I2Cx , FunctionalState NewState ,Repeated_Start state );
void I2C_Send_Address(I2C_TypeDef *I2Cx , uint16_t Address ,I2C_Direction Direction );
void I2C_Generate_STOP(I2C_TypeDef *I2Cx  , FunctionalState NewState);
FlagStatus I2C_Get_Flag_Status(I2C_TypeDef *I2Cx , Status Flag);
void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx  , FunctionalState NewState);


#endif /* INC_I2C_H_ */
