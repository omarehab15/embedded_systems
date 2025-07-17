/*
 * LCD.c
 *
 *  Created on: May 8, 2024
 *      Author: omar
 */

/******************************************************************************
 *                               INCLUDES			                          *
 *******************************************************************************/
#include "LCD.h"

/******************************************************************************
 *                           Global function			                          *
 *******************************************************************************/
void my_wait_ms (int x)
{
	x = x*4.5;
	for(int i = 0 ; i < x ; i++)
	{
		for(int j = 0 ; j < 255 ; j++);
	}
}

/******************************************************************************
 *                       	    APIS IMPLEMENTATION			                  *
 *******************************************************************************/
void HAL_LCD_clear_screen(){
	HAL_LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

void HAL_LCD_lcd_kick(){
	MCAL_GPIO_WritePin(LCD_PORT, EN_SWITCH, PIN_SET);
	my_wait_ms(50);
	MCAL_GPIO_WritePin(LCD_PORT, EN_SWITCH, PIN_RESET);
}

void HAL_LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			HAL_LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			HAL_LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void HAL_LCD_INIT(){
	my_wait_ms(20);

	MCAL_GPIO_Init(LCD_PORT, RS_SWITCH, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, RW_SWITCH, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, EN_SWITCH, Input_Flo_Mode);



	my_wait_ms(15);
	MCAL_GPIO_Init(LCD_PORT, PIN0, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN1, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN2, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN3, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN4, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN5, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN6, Output_PP_Mode_Speed10MHZ);
	MCAL_GPIO_Init(LCD_PORT, PIN7, Output_PP_Mode_Speed10MHZ);
	HAL_LCD_clear_screen();

	HAL_LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	HAL_LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	HAL_LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	HAL_LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void HAL_LCD_check_lcd_isbusy(){

	MCAL_GPIO_Init(LCD_PORT, PIN0, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN1, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN2, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN3, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN4, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN5, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN6, Input_Flo_Mode);
	MCAL_GPIO_Init(LCD_PORT, PIN7, Input_Flo_Mode);

	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH, PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH, PIN_SET);

	HAL_LCD_lcd_kick();
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH, PIN_RESET);

}


void HAL_LCD_WRITE_COMMAND(unsigned char command)
{
	HAL_LCD_check_lcd_isbusy();
	MCAL_GPIO_WritePort(LCD_PORT, command);
	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH, PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH, PIN_RESET);

	my_wait_ms(1);
	HAL_LCD_lcd_kick();

}

void HAL_LCD_WRITE_CHAR(unsigned char character)
{
	HAL_LCD_check_lcd_isbusy();
	MCAL_GPIO_WritePort(LCD_PORT, character);
	MCAL_GPIO_WritePin(LCD_PORT, RW_SWITCH, PIN_RESET);
	MCAL_GPIO_WritePin(LCD_PORT, RS_SWITCH, PIN_SET);
	my_wait_ms(1);
	HAL_LCD_lcd_kick();

}

void HAL_LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		HAL_LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			HAL_LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			//LCD_clear_screen();
			HAL_LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
}
