/*
 * Timers.c
 *
 * Created: 2/3/2024 6:37:15 AM
 * Author : Ahmed Hussien
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "DIO_Module.h"
#include "macros.h"
int main(void)
{
	unsigned short a,b,high, distance ;
	LCD_Initialization();
	setBitDirection('D',7,'1');
	setBitDirection('B',5,'1');
	while(1)
	{
		setBit('D',7);
		_delay_us(50);
		clearBit('D',7);
		
		TCCR1A = 0;
		TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag)  */

		TCCR1B = 0xc1;  	/* Rising edge, no prescaler , noise canceler*/
		while ((TIFR&(1<<ICF1)) == 0);
		a = ICR1;  		/* Take value of capture register */
		TIFR |= (1<<ICF1);  	/* Clear ICF flag */
	
		TCCR1B = 0x81;  	/* Falling edge, no prescaler ,noise canceler*/
		while ((TIFR&(1<<ICF1)) == 0);
		b = ICR1;  		/* Take value of capture register */
		TIFR |= (1<<ICF1);  	/* Clear ICF flag */
	
		TIFR = (1<<ICF1);  	/* Clear ICF flag */

		TCCR1B = 0;
		
		if (a < b)
		{
			high=b-a;
			
			distance = ((high*34600)/(F_CPU*2)) ;
			
			if (distance < 80)
			{
				clearScreen();
				
				LCD_printString("distance = ");
				LCD_printCharacter((distance/10) + 48 );
				LCD_printCharacter((distance%10) + 48 );
				LCD_printString("CM");
			}
			else
			{
				clearScreen();
				LCD_printString("no object ");
			}
			
		}
		 	toggelBit('B',5);
		 	_delay_ms(1000);	
	}
   
}

