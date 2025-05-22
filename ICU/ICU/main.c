/*
 * Timers.c
 *
 * Created: 2/3/2024 6:37:15 AM
 * Author : Ahmed Hussien
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include "LCD.h"
#include "macros.h"
int main(void)
{
	unsigned short a,b,c,high,period,duty_cycle,frequency;
	LCD_Initialization();
	TCCR1A = 0;
	TIFR = (1<<ICF1);  	/* Clear ICF (Input Capture flag)  */

	TCCR1B = 0xc1;  	/* Rising edge, no prescaler , noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	a = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	
	TCCR1B = 0x81;  	/* Falling edge, no prescaler ,noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	b = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */
	
	TCCR1B = 0xc1;  	/* Rising edge, no prescaler ,noise canceler*/
	while ((TIFR&(1<<ICF1)) == 0);
	c = ICR1;  		/* Take value of capture register */
	TIFR = (1<<ICF1);  	/* Clear ICF flag */

	TCCR1B = 0;  		/* Stop the timer */
		if (a < b &&  b<c)
		{
			high=b-a;
			period  = (c - a) ;
			duty_cycle =  ((float)high / period) * 100 ;
			
			frequency = F_CPU / period;
			LCD_printString("duty:");
			LCD_printCharacter((duty_cycle/10)+48);
			LCD_printCharacter((duty_cycle%10)+48);
			LCD_printCharacter('%');
			LCD_moveCursor(2,1);
			LCD_printString("freq:");
			LCD_printCharacter((frequency/1000)+48);
			LCD_printCharacter(((frequency/100)%10)+48);
			LCD_printCharacter(((frequency/10)%10)+48);
			LCD_printCharacter((frequency%10)+48);
			LCD_printString("HZ");
		}
		else
		{
			clearScreen();
			LCD_printString("out of range");
		}
		TCCR1B = 0;  
    return 0;
}

