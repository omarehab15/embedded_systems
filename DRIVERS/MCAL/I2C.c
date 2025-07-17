/*
 * I2C.c
 *
 *  Created on: Apr 30, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "I2C.h"

/******************************************************************************
 *                           Generic variables			                      *
 *******************************************************************************/
I2C_InitTypeDef Global_I2C_Config[2] = {NULL,NULL};

/******************************************************************************
 *                            Generic Macros 			                      *
 *******************************************************************************/
#define I2C1_Index			0
#define I2C2_Index			1

/******************************************************************************
 *                           APIS IMPLEMENTATION			                      *
 *******************************************************************************/

/**=================================================================
 * @Fn -                    -MCAL_I2C_Init
 * @brief -                 -Initialize the I2Cx  according specified parameters in I2C_config
 * @param [in] -            -I2Cx : where x can be (1,2 depending on device used)
 * @param [in] -            -I2C_config pointer to a I2C_Config_t structure that contains
 * @retval -                -None
 * note -                   -None
 */
/**================================================================= */
void MCAL_I2C_Init(I2C_TypeDef *I2Cx , I2C_InitTypeDef *I2C_config , uint32_t pclk)
{
	uint16_t tempreg = 0 ;
	uint32_t freq , Result = 0 ;

	//Enable RCC Clock
	if( I2Cx == I2C1 )
	{
		Global_I2C_Config[I2C1_Index]=*I2C_config;
		MCAL_RCC_Peripherals_enable(APB1, RCC_I2C1, RCC_Enable);
	}
	else
	{
		Global_I2C_Config[I2C2_Index]=*I2C_config;
		MCAL_RCC_Peripherals_enable(APB1, RCC_I2C2, RCC_Enable);
	}

	if(I2C_config->I2C_Mode == I2C_Mode_I2C)
	{
		/**************************** INIT Timing *********************************/
		//I2C_CR2.FREQ[5:0]: peripheral clock frequancy
		/*Get the I2Cx->CR2 val*/
		tempreg = I2Cx->CR2;
		//Clear frequancy FREQ[5:0] bits
		tempreg &=~(I2C_CR2_FREQ); //Clear the first 6bits in CR2 register(FREQ[5:0]

		/*Set Frequancy bits depending on pclk value */
		/*FREQ[5:0]: Peripheral clock frequency
		The FREQ bits must be configured with the APB clock frequency value (I2C peripheral
		connected to APB). The FREQ field is used by the peripheral to generate data setup and
		hold times compliant with the I2C specifications. The minimum allowed frequency is 2 MHz,
		the maximum frequency is limited by the maximum APB frequency and cannot exceed
		50 MHz (peripheral intrinsic maximum limit).
		0b000000: Not allowed
		0b000001: Not allowed
		0b000010: 2 MHz*/
		freq = (uint16_t) (pclk / 1000000);

		tempreg |=freq;
		//Write to I2C_CR2
		I2Cx->CR2 = tempreg;

		/*Configure the clock control registers*/
		//Disable I2C peripheral
		I2Cx->CR1 &=~(I2C_CR1_PE);

		tempreg = 0;

		//Set Mode (Stansard mode / Fast mode)
		if(I2C_config->I2C_ClockSpeed == I2C_SCLK_SM_50K ||I2C_config->I2C_ClockSpeed == I2C_SCLK_SM_100K )
		{
			//Stansard Mode
			//Standard Mode speed calculation
			/*Tclk/2 = CCR * Tpclk
			 * CCR = Tclk /(Tpclk * 2)
			 * CCR = Fpclk /(I2C_ClockFrequancy * 2)
			 */
			Result = (uint16_t)(pclk /(I2C_config->I2C_ClockSpeed *2 ));
			tempreg |=Result;
			//Write to I2C_CCR
			I2Cx->CCR = tempreg;

			/*For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
				If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and Tpclk = 125 ns
				therefore the TRISE[5:0] bits must be programmed with 09h.
				(1000 ns / 125 ns = 8 + 1)*/

			I2Cx->TRISE = freq +1;

		}
		else if (I2C_SCLK_FM_200K || I2C_SCLK_FM_400K )
		{
			//Fast Mode ---Not Supported
		}

		/*Get the I2Cx CR1 val*/
		tempreg = I2Cx->CR1;
		tempreg |=(uint16_t)(I2C_config->I2C_ACK_Control)|(I2C_config->StretchMode)|(I2C_config->General_Call_Address_Detection |I2C_config->I2C_Mode);
		//Write to I2C_CR1
		I2Cx->CR1 = tempreg;
		/**************************** I2CX OAR1 & OAR2 Configuration *********************************/
		tempreg=0;
		if(I2C_config->I2C_Slave_Address.Enable_Daul_ADD == 1)
		{
			tempreg |=(I2C_OAR2_ENDUAL); //Enable Dual Address
			/*Set Secondary Address*/
			tempreg |=(I2C_config->I2C_Slave_Address.Secondary_slave_address<<1);//bits 7:1 of address in dual addressing mode
			//Write to
			I2Cx->OAR2 = tempreg;
		}
		tempreg = 0;
		tempreg |=(I2C_config->I2C_Slave_Address.Primary_slave_address<<1);
		tempreg |=(I2C_config->I2C_Slave_Address.I2C_Addressing_slave_mode);
		//Write to I2C_OAR1
		I2Cx->OAR1 = tempreg;
	}//I2C_SMBUS_Mode
	else
	{
		//SMBUS Not Supported
	}

	//Interrupt mode in slave mode
	if(I2C_config->P_Slave_Event_CallBack !=NULL)
	{
		//Slave Mode
		//Bit 10 ITBUFEN: Buffer interrupt enable
		I2Cx->CR1 |=I2C_CR2_ITBUFEN;
		//Bit 8 ITERREN: Error interrupt enable
		I2Cx->CR1 |=I2C_CR2_ITERREN;
		//Bit 9 ITEVTEN: Event interrupt enable
		I2Cx->CR1 |=I2C_CR2_ITEVTEN;

		//Enable interrupt in NVIC
		if( I2Cx == I2C1 )
		{
			MCAL_NVIC_ENABLE(NVIC_I2C1_EV, NVIC_ENABLE);
			MCAL_NVIC_ENABLE(NVIC_I2C1_ER, NVIC_ENABLE);
		}
		else if(I2Cx == I2C2)
		{
			MCAL_NVIC_ENABLE(NVIC_I2C2_EV, NVIC_ENABLE);
			MCAL_NVIC_ENABLE(NVIC_I2C2_ER, NVIC_ENABLE);
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}

	/*Enable I2C Peripheral Bit 0 PE: Peripheral enable*/
	I2Cx->CR1 |=I2C_CR1_PE;

}

/**=================================================================
 * @Fn -                    -MCAL_I2C_DeInit
 * @brief -                 -DeInit the I2Cx
 * @param [in] -            -I2Cx : where x can be (1,2 depending on device used)
 * @retval -                -None
 * note -                   -None
 */
/**================================================================= */
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx)
{

	if( I2Cx == I2C1 )
	{
		MCAL_RCC_Peripherals_Reset(APB1, RCC_I2C1, RCC_Reset);
		MCAL_NVIC_ENABLE(NVIC_I2C1_EV, NVIC_DISABLE);
		MCAL_NVIC_ENABLE(NVIC_I2C1_ER, NVIC_DISABLE);
	}
	else if(I2Cx == I2C2)
	{
		MCAL_RCC_Peripherals_Reset(APB1, RCC_I2C2, RCC_Reset);
		MCAL_NVIC_ENABLE(NVIC_I2C2_EV, NVIC_DISABLE);
		MCAL_NVIC_ENABLE(NVIC_I2C2_ER, NVIC_DISABLE);
	}

}

/**=================================================================
 * @Fn -                    -MCAL_I2C_Set_GPIO_Pins
 * @brief -                 -Set_GPIO_Pins according recommended in I2C
 * @param [in] -            -I2Cx : where x can be (1,2 depending on device used)
 * @retval -                -None
 * note -                   -None
 */
/**================================================================= */
void MCAL_I2C_Set_GPIO_Pins(I2C_TypeDef *I2Cx)
{

	if( I2Cx == I2C1 )
	{

		//I2C1_SCL-->PB6
		MCAL_GPIO_Init(GPIOB, PIN6, Output_AF_OD_Mode_Speed10MHZ);

		//I2C1_SDA-->PB7
		MCAL_GPIO_Init(GPIOB, PIN7, Output_AF_OD_Mode_Speed10MHZ);

	}
	else if(I2Cx == I2C2)
	{
		//I2C_SCL2-->PB10
		MCAL_GPIO_Init(GPIOB, PIN10, Output_AF_OD_Mode_Speed10MHZ);

		//I2C2_SDA-->PB11
		MCAL_GPIO_Init(GPIOB, PIN11, Output_AF_OD_Mode_Speed10MHZ);

	}

}

void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx ,uint16_t DevAddr , uint8_t* DataOut , uint32_t DataLen , Stop_Condition Stop,Repeated_Start Start)
{
	int i=0;
	//To do
	//Support timeout (configure timer working for specic duaration rise interrupt
	//in ISR rise flag=1 and any code exist in while (check flag || Any polling condion)
	//1. Set the start bit in the I2C_CR1 register to generate a Sart Condition
	I2C_Generate_Start(I2Cx , ENABLE, Start);

	//2. Wait for Ev5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(! I2C_Get_Flag_Status(I2Cx , EV5));

	//3. Send address
	I2C_Send_Address(I2Cx , DevAddr , I2C_Direction_Transmitter);

	//4.Wait for Ev6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(! I2C_Get_Flag_Status(I2Cx , EV6));

	//5. /*TRA , BUSY , TXE , MSL , TXE flage*/
	while(! I2C_Get_Flag_Status(I2Cx , MASTER_BYTE_TRANSMITTING));

	//6. Send Data
	for(i=0;i<DataLen;i++)
	{
		//6.EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
		while(!I2C_Get_Flag_Status(I2Cx, EV8_1));
		I2Cx->DR = DataOut[i];
		//Wait EV8
		//EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
		while(! I2C_Get_Flag_Status(I2Cx , EV8));
	}


	if(Stop == with_stop)
	{
		//7. Send stop condition
		I2C_Generate_STOP(I2Cx , ENABLE);
	}
	else
	{
		I2C_Generate_STOP(I2Cx, DISABLE);
	}
}

void I2C_Generate_Start(I2C_TypeDef *I2Cx , FunctionalState NewState ,Repeated_Start state )
{

	if ( state != repeated_start)
	{
		//Check if the bus is idle
		while(I2C_Get_Flag_Status(I2Cx , I2C_BUS_BUSY));//While Bus is Busy Stuck
	}
	//if == reapeated i not need check the bus because i hold the bus
	/*Bit 8 START: Start generation
	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	In Master Mode:
	0: No Start generation
	1: Repeated start generation
	In Slave mode:
	0: No Start generation
	1: Start generation when the bus is free*/
	if(NewState != DISABLE)
	{
		I2Cx->CR1 |=(I2C_CR1_START); //Enable stat generation
	}
	else
	{
		I2Cx->CR1 &=~(I2C_CR1_START);//Disable start generation
	}

}

//supported only 7bit mode
void I2C_Send_Address(I2C_TypeDef *I2Cx , uint16_t Address ,I2C_Direction Direction )
{
	Address = (Address<<1); //7 Bit

	if(Direction != I2C_Direction_Transmitter)
	{
		//Set the address bin0 for read
		Address |=(1<<0);
	}
	else
	{
		//Reset the address bin0 for write
		Address &=~(1<<0);
	}

	/*Send the address */
	I2Cx->DR = Address;
}

void I2C_Generate_STOP(I2C_TypeDef *I2Cx  , FunctionalState NewState)
{

	if(NewState != DISABLE)
	{
		/*Generate STOP condition*/
		/*Bit 9 STOP: Stop generation
		The bit is set and cleared by software, cleared by hardware when a Stop condition is
		detected, set by hardware when a timeout error is detected.
		In Master Mode:
		0: No Stop generation.
		1: Stop generation after the current byte transfer or after the current Start condition is sent*/
		I2Cx->CR1 |=I2C_CR1_STOP;
	}
	else
	{
		/*disable stop condition generate*/
		I2Cx->CR1 &=~I2C_CR1_STOP;
	}
}

FlagStatus I2C_Get_Flag_Status(I2C_TypeDef *I2Cx , Status Flag)
{
	//volatile uint32_t DumyRead;
	FlagStatus BitStatus = RESET;
	uint32_t flag1=0 , flag2=0;
	uint32_t LastEvent=0;


	switch (Flag)
	{
	case I2C_BUS_BUSY:
		/*Bit 1 BUSY: Bus busy
				0: No communication on the bus
				1: Communication ongoing on the bus
				– Set by hardware on detection of SDA or SCL low
				– cleared by hardware on detection of a Stop condition.
				It indicates a communication in progress on the bus. This information is still updated when
				the interface is disabled (PE=0).*/

		if(I2Cx->SR2 & I2C_SR2_BUSY)
		{
			BitStatus = SET;
		}
		else
		{
			BitStatus = RESET;
		}
		break ;

	case EV5:
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		/*Bit 0 SB: Start bit (Master mode)
			0: No Start condition
			1: Start condition generated.
			– Set when a Start condition generated.
			– Cleared by software by reading the SR1 register followed by writing the DR register, or by
			hardware when PE=0*/
		if( (I2Cx->SR1) & (I2C_SR1_SB) )
		{
			BitStatus = SET;
		}
		else
		{
			BitStatus = RESET;
		}
		break;


	case EV6:

		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
		/*Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
				This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
				when PE=0.
				Address matched (Slave)
				0: Address mismatched or not received.
				1: Received address matched.*/
		if( I2Cx->SR1 & I2C_SR1_ADDR)
		{
			BitStatus = SET;
		}
		else
		{
			BitStatus = RESET;
		}
		/*//ADDR=1, cleared by reading SR1 register followed by reading SR2
		DumyRead = I2Cx->I2C_SR2;*/
		break;



	case MASTER_BYTE_TRANSMITTING:

		/*Read I2Cx status registers*/
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2<<16;

		/* Get LastEvent value from I2C status register*/
		LastEvent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
		/*Check whether the last event contains the I2C_EVENT */
		if( (LastEvent & Flag) == Flag )
		{
			/*last event is equal ti I2C_EVENT*/
			BitStatus = SET;
		}
		else
		{
			/*last event is not equal ti I2C_EVENT*/
			BitStatus = RESET;
		}
		break;


	case EV8_1://EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	case EV8: //EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register

		/*Bit 7 TxE: Data register empty (transmitters)
			0: Data register not empty
			1: Data register empty
			– Set when DR is empty in transmission. TxE is not set during address phase.
			– Cleared by software writing to the DR register or by hardware after a start or a stop condition
			or when PE=0.*/
		if(I2Cx->SR1 & I2C_SR1_TXE)
		{
			//Data register empty
			BitStatus = SET;
		}
		else
		{
			//Data register not empty
			BitStatus = RESET;
		}
		break;

	case EV7:

		/*Bit 6 RxNE: Data register not empty (receivers)
		0: Data register empty
		1: Data register not empty*/
		if(I2Cx->SR1 & I2C_SR1_RXNE)
		{
			BitStatus = SET;
		}
		else
		{
			BitStatus = RESET;
		}

	case EV8_2 :
		break ;

	}
	return BitStatus;
}

void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx  , FunctionalState NewState)
{
	/*Bit 10 ACK: Acknowledge enable
	This bit is set and cleared by software and cleared by hardware when PE=0.
	0: No acknowledge returned
	1: Acknowledge returned after a byte is received (matched address or data)*/

	if(NewState == ENABLE)
	{
		I2Cx->CR1 |=(I2C_CR1_ACK);
	}
	else
	{
		I2Cx->CR1 &=~(I2C_CR1_ACK);
	}

}

void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx ,uint16_t DevAddr , uint8_t* DataOut , uint32_t DataLen , Stop_Condition Stop,Repeated_Start Start)
{
	int i=0;
	uint8_t indix = I2Cx == I2C1 ? I2C1_Index : I2C2_Index;

	I2C_Generate_Start(I2Cx , ENABLE, Start);

	//2. Wait for Ev5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(! I2C_Get_Flag_Status(I2Cx , EV5));

	//3. Send address
	I2C_Send_Address(I2Cx , DevAddr , I2C_Direction_Receiver);

	//4.Wait for Ev6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(! I2C_Get_Flag_Status(I2Cx , EV6));

	I2C_AcknowledgeConfig(I2Cx , ENABLE);



	if(DataLen)
	{
		//5.read data until len become zero
		for(i=DataLen ; i>1 ; i--)
		{
			//wait until RXNE BECOMES 1
			while(! I2C_Get_Flag_Status(I2Cx , EV7));
			//read data from data register
			*DataOut = I2Cx->DR;
			//increment the buffer address
			DataOut++;
		}
		//6.send not Ack
		I2C_AcknowledgeConfig(I2Cx , DISABLE); //To not receive
	}


	if(Stop == with_stop)
	{
		//7. Send stop condition
		I2C_Generate_STOP(I2Cx, ENABLE);
	}

	//re-enable ack
	if(Global_I2C_Config[indix].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx , ENABLE);
	}

}

//Slave interrupt mechanism
void MCAL_I2C_Slave_Send_Data(I2C_TypeDef *I2Cx , uint8_t Data)
{
	I2Cx->DR = Data;
}


uint8_t MCAL_I2C_Slave_Receive_Data(I2C_TypeDef *I2Cx)
{
	uint8_t result;
	result =(uint8_t)(I2Cx->DR);
	return result;
}


void I2C1_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}


void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}
