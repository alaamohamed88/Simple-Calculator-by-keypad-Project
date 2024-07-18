/*
 * KEYPAD.c
 *
 * Created: 12/07/2023 11:20:35 م
 *  Author: Alaa Mohamed
 */ 

#include "KEYPAD.h"

void KEYPAD_Initialize()
{
	DIO_setPinDirection(KEYPAD_PORT,ROW1_PIN,OUTPUT);
	DIO_setPinDirection(KEYPAD_PORT,ROW2_PIN,OUTPUT);
	DIO_setPinDirection(KEYPAD_PORT,ROW3_PIN,OUTPUT);
	DIO_setPinDirection(KEYPAD_PORT,ROW4_PIN,OUTPUT);
	DIO_setPinDirection(KEYPAD_PORT,COLUMN1_PIN,INPUT);
	DIO_setPinDirection(KEYPAD_PORT,COLUMN2_PIN,INPUT);
	DIO_setPinDirection(KEYPAD_PORT,COLUMN3_PIN,INPUT);
	DIO_setPinDirection(KEYPAD_PORT,COLUMN4_PIN,INPUT);
	DIO_setInternalPullup(KEYPAD_PORT,COLUMN1_PIN,1);
	DIO_setInternalPullup(KEYPAD_PORT,COLUMN2_PIN,1);
	DIO_setInternalPullup(KEYPAD_PORT,COLUMN3_PIN,1);
	DIO_setInternalPullup(KEYPAD_PORT,COLUMN4_PIN,1);
}

char KEYPAD_ReadPress()
{
	char KEYPAD_arr[4][4] = {{'7','8','9','/'},{'4','5','6','x'},{'1','2','3','-'},{'A','0','=','+'}};
	char row, column;
	char return_value = NOT_PRESSED;
	for (row = 0;row < 4;row++)
	{
		DIO_writePin(KEYPAD_PORT,ROW1_PIN,1);
		DIO_writePin(KEYPAD_PORT,ROW2_PIN,1);
		DIO_writePin(KEYPAD_PORT,ROW3_PIN,1);
		DIO_writePin(KEYPAD_PORT,ROW4_PIN,1);
		DIO_writePin(KEYPAD_PORT,row,0);
		for (column = 0;column < 4;column++)
		{
			if (DIO_readPin(KEYPAD_PORT,column+4) == 0)
			{
				return_value = KEYPAD_arr[row][column];
				break;
			}
		}
		if(return_value != NOT_PRESSED)
		{
			break;
		}
	}
	return return_value;
}