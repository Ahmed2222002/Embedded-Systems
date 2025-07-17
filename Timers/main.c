/*
 * Timers.c
 *
 * Created: 2/3/2024 6:37:15 AM
 * Author : Ahmed Hussien
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DIO_Module.h"
#include "macros.h"
#include "timer0_driver.h"
volatile char x = 0 ;
int main(void)
{
	setBitDirection('A',0,'1');
	
	timer0_ctc_init(78,5);
	while(1)
	{
		
		if (x>=100)
		{
			toggelBit('A',0);
			x = 0;
		}
	}
}

ISR(TIMER0_COMP_vect)
{
	++x;
}
