/*
 * Keypad.c
 *
 *  Created on: Mar 12, 2024
 *      Author: omar
 */

/******************************************************************************
 *                         	  Includes			       		                  *
 *******************************************************************************/
#include "Keypad.h"

/******************************************************************************
 *                           Generic Functions			                      *
 *******************************************************************************/
void delay(int x)
{
	uint32_t i, j;
	for (i = 0; i < x; i++)
		for (j = 0; j < 255; j++);

}

/******************************************************************************
 *                           Generic variables			                      *
 *******************************************************************************/
int Key_padRow[] = { R0, R1, R2, R3 }; //rows of the keypad
int Key_padCol[] = { C0, C1, C2, C3 }; //columns


/******************************************************************************
 *                           APIS IMPLEMENTATION			                      *
 *******************************************************************************/
void HAL_Keypad_init(void)
{
	MCAL_GPIO_Init(Keypad_port, R0, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, R1, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, R2, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, R3, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, C0, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, C1, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, C2, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(Keypad_port, C3, Output_PP_Mode_Speed10MHZ);
}

/***********************************************************************************/

char HAL_Keypad_getkey(void)
{
	int  i , j ;
	for(i = 0 ; i < 4 ; i++)
	{
		MCAL_GPIO_WritePin(Keypad_port, Key_padCol[0], PIN_SET);
		MCAL_GPIO_WritePin(Keypad_port, Key_padCol[1], PIN_SET);
		MCAL_GPIO_WritePin(Keypad_port, Key_padCol[2], PIN_SET);
		MCAL_GPIO_WritePin(Keypad_port, Key_padCol[3], PIN_SET);
		MCAL_GPIO_WritePin(Keypad_port, Key_padCol[i], PIN_SET);
		for(j = 0 ; j < 4 ; j++)
		{
			if(MCAL_GPIO_ReadPin(Keypad_port, Key_padRow[j])==0)
			{
				while(MCAL_GPIO_ReadPin(Keypad_port, Key_padRow[j])==0);
				switch(i)
				{
				case (0):
				{
				if(j==0){return '7';}
				else if(j==1){return '4';}
				else if(j==2){return '1';}
				else if(j==3){return '?';}
				}
				break;
				case (1):
				{
				if(j==0){return '8';}
				else if(j==1){return '5';}
				else if(j==2){return '2';}
				else if(j==3){return '0';}
				}
				break;
				case (2):
				{
				if(j==0){return '9';}
				else if(j==1){return '6';}
				else if(j==2){return '3';}
				else if(j==3){return '=';}
				}
				break;
				case (3):
				{
				if(j==0){return '/';}
				else if(j==1){return '*';}
				else if(j==2){return '-';}
				else if(j==3){return '+';}
				}
				break;
				}
			}
		}
	}
	return 'A';
}

