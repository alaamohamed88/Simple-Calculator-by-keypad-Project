/*
 * KEYPAD.h
 *
 * Created: 12/07/2023 11:20:18 م
 *  Author: Alaa Mohamed
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO_Driver.h"

#define KEYPAD_PORT 'C'
#define ROW1_PIN 0
#define ROW2_PIN 1
#define ROW3_PIN 2
#define ROW4_PIN 3
#define COLUMN1_PIN 4
#define COLUMN2_PIN 5
#define COLUMN3_PIN 6
#define COLUMN4_PIN 7
#define NOT_PRESSED 0xff
void KEYPAD_Initialize();
char KEYPAD_ReadPress();

#endif /* KEYPAD_H_ */