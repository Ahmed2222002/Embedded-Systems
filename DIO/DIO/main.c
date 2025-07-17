/*
 * DIO.c
 *
 * Created: 10/8/2023 12:07:02 AM
 * Author : Ahmed Hussien
 */ 
#define F_CPU 8000000UL
#include "LED.h"
#include "BUTTON.h"
#include <util/delay.h>
#define ledDelay 50
int main(void)
{
   char port = 'A';
   char count = 1;
   signed char i = 0 ;
   leds8_Initilize('A','1');
   leds8_Initilize('B','1');
   leds8_Initilize('C','1');
   leds8_Initilize('D','1');
   while(1)
   {
	   switch (count)
	   {
		   case 1 ... 4:
		   
		   for ( i=0 ; i<8 ; i++ )
		   {
			   ledOn(port,i);
			   _delay_ms(ledDelay);
		   }
		   ++port;
		   ++count;
		   break;
		   
		   case 5 ... 8:
		   if (port == 'E') port = 'D';
		   for(i = 7; i>=0 ; i--)
		   {
			   ledOff(port,i);
			   _delay_ms(ledDelay);
		   }
		   --port;
		   ++count;
		   break;
		   
		   default:
			   count = 1;
			   port = 'A';
	   }  
   }
}

