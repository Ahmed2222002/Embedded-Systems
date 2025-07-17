/*
 * LM35.c
 *
 * Created: 1/31/2024 6:41:29 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include "LCD.h"
#include "ADC2_driver.h"

int main(void)
{
	clearScreen();
    LCD_Initialization();
	ADC_initialization();
	LCD_printString("temp = ");
	unsigned short mille_volt;
	char temperature ;
    while (1) 
    {
		mille_volt = ADC_read() * 2.5;
		
		if (mille_volt < 1000)
		{
			temperature = (1000-mille_volt) / 10;
			LCD_moveCursor(1,8);
			LCD_printCharacter('-');
			if (temperature < 10)
			{
				LCD_printCharacter(temperature + 48 );
				LCD_printCharacter(0xdf);
				LCD_printCharacter('C');
				LCD_printCharacter(0x20);
			}
			else
			{
				LCD_printCharacter((temperature/10) + 48 );
				LCD_printCharacter((temperature%10) + 48 );
				LCD_printCharacter(0xdf);
				LCD_printCharacter('C');
				LCD_printCharacter(0x20);
			}
		}
		else if (mille_volt > 1000)
		{
			temperature = (mille_volt-1000) / 10;
			LCD_moveCursor(1,8);
			if (temperature < 10)
			{
				LCD_printCharacter(temperature + 48 );
				LCD_printCharacter(0xdf);
				LCD_printCharacter('C');
				LCD_printCharacter(0x20);
			}
			else
			{
				LCD_printCharacter((temperature/10) + 48 );
				LCD_printCharacter((temperature%10) + 48 );
				LCD_printCharacter(0xdf);
				LCD_printCharacter('C');
				LCD_printCharacter(0x20);
			}
		}
		else
		{
			LCD_moveCursor(1,8);
			LCD_printCharacter('0');
			LCD_printCharacter(0xdf);
			LCD_printCharacter('C');
			LCD_printCharacter(0x20);
		}
    }
}

