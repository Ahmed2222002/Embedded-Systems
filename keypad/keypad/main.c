/*
 * keypad.c
 *
 * Created: 11/30/2023 6:29:35 PM
 * Author : Ahmed Hussien
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "keypad.h"
int main(void)
{
    /* Replace with your application code */
	LCD_Initialization();
	keypadInitialization();
	char x ;
    while (1) 
    {
		x = keypadRead();
		if (x == 'c')
		{
			clearScreen();
		}
		if (x != 'Z' && x != 'c')
		{
			LCD_printCharacter(x);
		}
		_delay_ms(200);
    }
}

