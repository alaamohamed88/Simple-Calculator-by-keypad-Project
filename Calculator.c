/*
 * Calculator.c
 *
 * Created: 29/07/2023 08:07:52 م
 *  Author: Alaa Mohamed
 */ 


/*A simple calculator for simple calculations with two-digit numbers maximum*/

#define  F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "KEYPAD.h"

int main(void)
{
	label:	LCD_Initialize();
	KEYPAD_Initialize();
	unsigned char operands[6]={NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED,NOT_PRESSED} ;
	unsigned char first_operand=0,second_operand=0;
	unsigned short result ;
	unsigned char counter = 0;
	unsigned char i,operations_counter = 0; // counters for for loop
	while(1)
	{
		/* first character to be printed on LCD */
		/* first character must be a number only */
		do
		{
			operands[counter]=KEYPAD_ReadPress();				

		} while(operands[counter] == NOT_PRESSED);
		
		if(operands[counter]=='A'||operands[counter]=='='||operands[counter]=='+'||operands[counter]=='-'||operands[counter]=='x'||operands[counter]=='/')
		{
			LCD_SendCommand(CLEAR_SCREEN);
			LCD_SendCommand(RETURN_HOME);
			goto label ;
		}
		else
		{
				LCD_SendCharacter(operands[counter]);
		}
		counter++;
		_delay_ms(300);
		
		/* second character to be printed on LCD */
		/* second character can be a number or an operation */
		
		do
		{
			operands[counter]=KEYPAD_ReadPress();
			
		}while(operands[counter] == NOT_PRESSED);
		
		if(operands[counter]=='A'||operands[counter]=='=')
		{
			LCD_SendCommand(CLEAR_SCREEN);
			LCD_SendCommand(RETURN_HOME);
			goto label ;
		}
		else
		{
			LCD_SendCharacter(operands[counter]);
		}
		counter++;
		_delay_ms(300);
		
		/* Third character to be printed on LCD */
		/* Third character may be a number or an operation */
		
		do
		{
			operands[counter]=KEYPAD_ReadPress();
			
		}while(operands[counter] == NOT_PRESSED);
		
		for (i=1;i<3;i++)
		{
			if(operands[i] == '+' || operands[i] == '-' || operands[i] == '/' || operands[i] == 'x')
			{
				operations_counter++;
			}
			if (operations_counter==2)
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Syntax Error");
				_delay_ms(2000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				goto label ;
			}
		}
		operations_counter = 0;
		if(operands[counter] == 'A' ||operands[counter] == '=')
		{
			LCD_SendCommand(CLEAR_SCREEN);
			LCD_SendCommand(RETURN_HOME);
			goto label ;
		}
		else
		{
			LCD_SendCharacter(operands[counter]);
		}
		counter++;
		_delay_ms(300);
		
		/* fourth character to be printed on LCD */
		/* fourth character can be a number or equal sign */
		
		do
		{
			operands[counter]=KEYPAD_ReadPress();
			
		}while(operands[counter] == NOT_PRESSED);
		
		for (i=1;i<4;i++)
		{
			if(operands[i] == '+' || operands[i] == '-' || operands[i] == '/' || operands[i] == 'x')
			{
				operations_counter++;
			}
			if (operations_counter==2)
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Syntax Error");
				_delay_ms(2000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				goto label ;
			}
		}
		operations_counter = 0;
		//if the operation is on one-digit numbers (for example 3+3):
		if(operands[counter] == '=')
		{
			// checking if third character is an operation sign to display syntax error message
			if ((operands[counter-1] == '+') || (operands[counter-1] == '-') || (operands[counter-1] == '/') || (operands[counter-1] == 'x'))
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Syntax Error");
				_delay_ms(2000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				goto label ;
			}
			else 
			{
				//checking if second character is a number as this mode is for operating on one digit numbers only
				if (operands[counter-2] == '+' || operands[counter-2] == '-' || operands[counter-2] == '/' || operands[counter-2] == 'x')
				{
					LCD_SendCharacter(operands[counter]);
					first_operand = (operands[counter-3]-48);
					second_operand = (operands[counter-1]-48);
					switch(operands[counter-2])
					{
						case '+':
						{
							result = first_operand + second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case '-':
						{
							result = first_operand - second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case 'x':
						{
							result = first_operand * second_operand;
							if(result >= 100 && result < 1000)
							{
								LCD_SendCharacter((result/100)+48);
								LCD_SendCharacter(((result/10)%10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result < 10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case '/':
						{
							result = (float)first_operand / second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						default:
						break;
					}
					counter++;
					_delay_ms(300);
					do
					{
						operands[counter]=KEYPAD_ReadPress();
						
					}while(operands[counter] == NOT_PRESSED);
					if (operands[counter] != NOT_PRESSED)
					{
						operands[counter]= NOT_PRESSED;
						counter--;
						LCD_SendCommand(CLEAR_SCREEN);
						LCD_SendCommand(RETURN_HOME);
						goto label ;
					}
				}
				else
				{
					LCD_SendCommand(CLEAR_SCREEN);
					LCD_SendCommand(RETURN_HOME);
					goto label ;
				}
			}				
		}
		//if the operation is on two-digit number and one-digit number (for example 33+3 or 3+33):
		else if((operands[counter]!='A')&&(operands[counter]!='+')&&(operands[counter]!='-')&&(operands[counter]!='x')&&(operands[counter]!='/')&&(operands[counter]!='='))
		{
			LCD_SendCharacter(operands[counter]);
		}
		else
		{
			LCD_SendCommand(CLEAR_SCREEN);
			LCD_SendCommand(RETURN_HOME);
			goto label ;
		}
		counter++;
		_delay_ms(300);
		
		/* fifth character to be printed on LCD */
		/* fifth character can be a number or equal sign */
		
		do
		{
			operands[counter]=KEYPAD_ReadPress();
			
		}while(operands[counter] == NOT_PRESSED);
		
		for (i=1;i<5;i++)
		{
			if(operands[i] == '+' || operands[i] == '-' || operands[i] == '/' || operands[i] == 'x')
			{
				operations_counter++;
			}
			if (operations_counter==2)
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Syntax Error");
				_delay_ms(2000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				goto label ;
			}
		}
		operations_counter = 0;
		//if the operation is on two-digit number and one-digit number (for example 3+33 or 33+3):
		if(operands[counter] == '=')
		{
			// checking if fourth character is an operation sign to display syntax error message
			if ((operands[counter-1] == '+') || (operands[counter-1] == '-') || (operands[counter-1] == '/') || (operands[counter-1] == 'x'))
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Syntax Error");
				_delay_ms(2000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				goto label ;
			}
			else
			{
				//checking if operation sign is the third character so first operand is two-digit number and second operand is one-digit number
				if (operands[counter-2] == '+' || operands[counter-2] == '-' || operands[counter-2] == '/' || operands[counter-2] == 'x')
				{
					LCD_SendCharacter(operands[counter]);
					first_operand = (operands[counter-3]-48)+((operands[counter-4]-48)*10);
					second_operand = (operands[counter-1]-48);
					switch(operands[counter-2])
					{
						case '+':
						{
							result = first_operand + second_operand;
							if(result >= 100 && result < 1000)
							{
								LCD_SendCharacter((result/100)+48);
								LCD_SendCharacter(((result/10)%10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case '-':
						{
							result = first_operand - second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case 'x':
						{
							result = first_operand * second_operand;
							if(result >= 100 && result < 1000)
							{
								LCD_SendCharacter((result/100)+48);
								LCD_SendCharacter(((result/10)%10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result < 10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case '/':
						{
							result = first_operand / second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						default:
						break;
					}
					counter++;
					_delay_ms(300);
					do
					{
						operands[counter]=KEYPAD_ReadPress();
						
					}while(operands[counter] == NOT_PRESSED);
					if (operands[counter] != NOT_PRESSED)
					{
						operands[counter]= NOT_PRESSED;
						counter--;
						LCD_SendCommand(CLEAR_SCREEN);
						LCD_SendCommand(RETURN_HOME);
						goto label ;
					}
				}
				//checking if operation sign is the second character so first operand is one-digit number and second operand is two-digit number
				else if (operands[counter-3] == '+' || operands[counter-3] == '-' || operands[counter-3] == '/' || operands[counter-3] == 'x')
				{
					LCD_SendCharacter(operands[counter]);
					first_operand = (operands[counter-4]-48);
					second_operand = (operands[counter-1]-48)+((operands[counter-2]-48)*10);
					switch(operands[counter-3])
					{
						case '+':
						{
							result = first_operand + second_operand;
							if(result >= 100 && result < 1000)
							{
								LCD_SendCharacter((result/100)+48);
								LCD_SendCharacter(((result/10)%10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case '-':
						{
							result = first_operand - second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case 'x':
						{
							result = first_operand * second_operand;
							if(result >= 100 && result < 1000)
							{
								LCD_SendCharacter((result/100)+48);
								LCD_SendCharacter(((result/10)%10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result < 10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						case '/':
						{
							result = first_operand / second_operand;
							if (result >= 10 && result < 100)
							{
								LCD_SendCharacter((result/10)+48);
								LCD_SendCharacter((result%10)+48);
							}
							else if(result<10)
							{
								LCD_SendCharacter(result+48);
							}
							break;
						}
						default:
						break;
					}
					counter++;
					_delay_ms(300);
					do
					{
						operands[counter]=KEYPAD_ReadPress();
						
					}while(operands[counter] == NOT_PRESSED);
					if (operands[counter] != NOT_PRESSED)
					{
						operands[counter]= NOT_PRESSED;
						counter--;
						LCD_SendCommand(CLEAR_SCREEN);
						LCD_SendCommand(RETURN_HOME);
						goto label ;
					}
				}
				else
				{
					LCD_SendCommand(CLEAR_SCREEN);
					LCD_SendCommand(RETURN_HOME);
					goto label ;
				}
			}
		}
		//if the operation is on two two-digit numbers (for example 33+33):
		else if((operands[counter]!='A')&&(operands[counter]!='+')&&(operands[counter]!='-')&&(operands[counter]!='x')&&(operands[counter]!='/')&&(operands[counter]!='='))
		{
			LCD_SendCharacter(operands[counter]);
		}
		else
		{
			LCD_SendCommand(CLEAR_SCREEN);
			LCD_SendCommand(RETURN_HOME);
			goto label ;
		}
		counter++;
		_delay_ms(300);
		
		/* sixth character to be printed on LCD */
		/* sixth character must be an equal sign */
		
		do
		{
			operands[counter]=KEYPAD_ReadPress();
			
		}while(operands[counter] == NOT_PRESSED);
		
		for (i=1;i<6;i++)
		{
			if(operands[i] == '+' || operands[i] == '-' || operands[i] == '/' || operands[i] == 'x')
			{
				operations_counter++;
			}
			if (operations_counter==2)
			{
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				LCD_SendString("Syntax Error");
				_delay_ms(2000);
				LCD_SendCommand(CLEAR_SCREEN);
				LCD_SendCommand(RETURN_HOME);
				goto label ;
			}
		}
		if(operands[counter]=='=')
		{
			LCD_SendCharacter(operands[counter]);
			first_operand = (operands[counter-4]-48) + ((operands[counter-5]-48)*10);
			second_operand = (operands[counter-1]-48) + ((operands[counter-2]-48)*10);
			switch(operands[counter-3])
			{
				case '+':
				{
					result = first_operand + second_operand;
					if(result >= 100 && result < 1000)
					{
						LCD_SendCharacter((result/100)+48);
						LCD_SendCharacter(((result/10)%10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if (result >= 10 && result < 100)
					{
						LCD_SendCharacter((result/10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if(result<10)
					{
						LCD_SendCharacter(result+48);
					}
					break;
				}
				case '-':
				{
					result = first_operand - second_operand;
					if(result >= 100 && result < 1000)
					{
						LCD_SendCharacter((result/100)+48);
						LCD_SendCharacter(((result/10)%10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if (result >= 10 && result < 100)
					{
						LCD_SendCharacter((result/10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if(result<10)
					{
						LCD_SendCharacter(result+48);
					}
					break;
				}
				case 'x':
				{
					result = first_operand * second_operand;
					if(result >= 1000 && result < 10000)
					{
						LCD_SendCharacter((result/1000)+48);
						LCD_SendCharacter(((result/100)%10)+48);
						LCD_SendCharacter(((result/10)%10)+48);
						LCD_SendCharacter((result%10)+48);
						
					}
					else if(result >= 100 && result < 1000)
					{
						LCD_SendCharacter((result/100)+48);
						LCD_SendCharacter(((result/10)%10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if (result >= 10 && result < 100)
					{
						LCD_SendCharacter((result/10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if(result < 10)
					{
						LCD_SendCharacter(result+48);
					}
					break;
				}
				case '/':
				{
					result = first_operand / second_operand;
					if(result >= 100 && result < 1000)
					{
						LCD_SendCharacter((result/100)+48);
						LCD_SendCharacter(((result/10)%10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if (result >= 10 && result < 100)
					{
						LCD_SendCharacter((result/10)+48);
						LCD_SendCharacter((result%10)+48);
					}
					else if(result<10)
					{
						LCD_SendCharacter(result+48);
					}
					break;
				}
				default:
				break;
			}
		}
		else
		{
			LCD_SendCommand(CLEAR_SCREEN);
			LCD_SendCommand(RETURN_HOME);
			goto label ;
		}
		_delay_ms(300);
	}			
}	