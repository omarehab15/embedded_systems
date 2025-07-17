/*
 * GPIO.c
 *
 *  Created on: Feb 9, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "GPIO.h"

/******************************************************************************
 *                           APIS IMPLEMENTATION			                      *
 *******************************************************************************/
uint8_t Get_Position(GPIO_PINs_t PinNumber)
{
	switch(PinNumber)
	{
	case PIN0 :
	{
		return 0 ;
	}
	break;
	case PIN1 :
	{
		return 4 ;
	}
	break;
	case PIN2 :
	{
		return 8 ;
	}
	break;
	case PIN3 :
	{
		return 12 ;
	}
	break;
	case PIN4 :
	{
		return 16 ;
	}
	break;
	case PIN5 :
	{
		return 20 ;
	}
	break;
	case PIN6 :
	{
		return 24 ;
	}
	break;
	case PIN7 :
	{
		return 28 ;
	}
	break;
	case PIN8 :
	{
		return 0 ;
	}
	break;
	case PIN9 :
	{
		return 4 ;
	}
	break;
	case PIN10 :
	{
		return 8 ;
	}
	break;
	case PIN11 :
	{
		return 12 ;
	}
	break;
	case PIN12 :
	{
		return 16 ;
	}
	break;
	case PIN13 :
	{
		return 20 ;
	}
	break;
	case PIN14 :
	{
		return 24 ;
	}
	break;
	case PIN15 :
	{
		return 28 ;
	}
	break;
	}
	return 0 ;
}


/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes the GPIOx PINy according to the specified parameters in the PinConfig
 * @param[in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
 * 				 But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx ,GPIO_PINs_t GPIO_PinNum  , GPIO_MODEs_t GPIO_PinMODE  )
{
	if(GPIO_PinNum<PIN8){
		GPIOx->CRL &=~(0xf<<(Get_Position(GPIO_PinNum)));

		if((GPIO_PinMODE==Input_PD_Mode)||(GPIO_PinMODE==Input_PU_Mode)){
			if(GPIO_PinMODE == Input_PU_Mode){
				GPIOx->CRL |=(0b1000<<(Get_Position(GPIO_PinNum)));
				GPIOx->ODR |= (1<<GPIO_PinNum);
			}
			else{
				GPIOx->CRL |=(0b1000<<(Get_Position(GPIO_PinNum)));
				GPIOx->ODR &=~(1<<GPIO_PinNum);
			}

		}
		else GPIOx->CRL |=(GPIO_PinMODE<<(Get_Position(GPIO_PinNum)));

	}
	else if(GPIO_PinNum>7){
		//GPIOx->GPIOx_CRH
		GPIOx->CRH &=~(0xf<<(Get_Position(GPIO_PinNum)));

		if((GPIO_PinMODE==Input_PD_Mode)||(GPIO_PinMODE==Input_PU_Mode)){
			if(GPIO_PinMODE == Input_PU_Mode){
				GPIOx->CRH |=(0b1000<<(Get_Position(GPIO_PinNum)));
				GPIOx->ODR |= (1<<GPIO_PinNum);
			}
			else{
				GPIOx->CRH |=(0b1000<<(Get_Position(GPIO_PinNum)));
				GPIOx->ODR &=~(1<<GPIO_PinNum);
			}

		}
		else GPIOx->CRH |=(GPIO_PinMODE<<(Get_Position(GPIO_PinNum)));

	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-reset all the GPIO registers
 * @param[in] 	-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[out] 	-none
 * @retval		-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx )
{
	GPIOx->CRL  = 0x44444444;
	GPIOx->CRH  = 0x44444444;
	GPIOx->ODR  = 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->BRR  = 0x00000000;
	GPIOx->LCKR = 0x00000000;
}
/**================================================================
 * @Fn				-MCAL_GPIO_ReadPin
 * @brief 			-Read Specific PIN
 * @param [in] 		-GPIOx: where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in] 		-PinNumber: Set Pin Number according @ref GPIO_PINS_define
 * @retval 			-the input pin value (two values based on @ref GPIO_PIN_state )
 * @Note			-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx , GPIO_PINs_t PinNumber)
{
	return (GPIOx->IDR>>PinNumber)&1;
}
/**================================================================
 * @Fn					-MCAL_GPIO_ReadPort
 * @brief 				-read the input port VALUE
 * @param [in] 			-GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
 * @retval 				-the input port VALUE
 * Note					-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	return GPIOx->IDR;
}

/**================================================================
 * @Fn					-MCAL_GPIO_WritePIN
 * @brief 				-write on output PIN
 * @param [in] 			-GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
 * @retval 				-none
 * Note					-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx , GPIO_PINs_t PinNumber,uint8_t value)
{
	if(value!=0){
		GPIOx->ODR |=(1<<PinNumber);
	}
	else GPIOx->ODR &=~(1<<PinNumber);
}

/**================================================================
 * @Fn					-MCAL_GPIO_WritePort
 * @brief 				-write on output port
 * @param [in] 			-GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
 * @retval 				-none
 * Note					-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx ,uint16_t value)
{
	GPIOx->ODR = (uint16_t)value;
}
/**================================================================
 * @Fn					-MCAL_GPIO_TogglePin
 * @brief 				-Toggles the specified GPIO pin
 * @param [in] 			-GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
 * @param [in] 			-PinNumber: specifies the port bit to read. Set by @ref GPIO_PINS_define
 * @retval 				-none
 * Note					-none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx , GPIO_PINs_t PinNumber)
{
	GPIOx->ODR ^=(1<<PinNumber);
}

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx ,GPIO_PINs_t PinNumber)
{
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked

	//Set LCKK[16]
	volatile uint32_t tmp = 1<<16 ;
	//Set the LCKy
	tmp |= PinNumber ;

	//	Write 1
	GPIOx->LCKR = tmp ;
	//	Write 0
	GPIOx->LCKR = PinNumber ;
	//	Write 1
	GPIOx->LCKR = tmp ;

	//	Read 0
	tmp = GPIOx->LCKR  ;
	//	Read 1 (this read is optional but confirms that the lock is active)
	if ( (uint32_t) (GPIOx->LCKR  & 1<<16 ))
	{
		return GPIO_LOCK_Success ;
	}else
	{
		return GPIO_LOCK_ERROR ;

	}
	return 0 ;
}


