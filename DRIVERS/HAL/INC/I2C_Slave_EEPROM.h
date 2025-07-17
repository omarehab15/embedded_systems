/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: May 3, 2024
 *      Author: omar
 */

#ifndef INC_I2C_SLAVE_EEPROM_H_
#define INC_I2C_SLAVE_EEPROM_H_
/******************************************************************************
*                               INCLUDES			                          *
*******************************************************************************/
#include "STM32F103C8.h"
#include "I2C.h"

/****************************************
* MACROs
*****************************************/
//E2PROM is an I2C SLAVE
//Idle Mode : device is in high-impedance state and waits for data.
//Master Transmitter Mode : the device transmits data to a slave receiver.
//Master Receiver Mode : the device receives data from a slave transmitter.

#define EEPROM_Slave_address	0x2A

/******************************************************************************
*                                  APIs 			                          *
*******************************************************************************/

void HAL_EEPROM_init(void);
unsigned char HAL_EEPROM_write_Nbytes(unsigned int Memory_address , unsigned char* bytes , uint8_t Data_Length);
unsigned char HAL_EEPROM_Read_bytes(unsigned int Memory_address ,uint8_t* dataOut ,uint8_t datalen);

#endif /* INC_I2C_SLAVE_EEPROM_H_ */
