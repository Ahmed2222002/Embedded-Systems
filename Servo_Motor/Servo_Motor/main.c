/*
 * Timers.c
 *
 * Created: 2/3/2024 6:37:15 AM
 * Author : Ahmed Hussien
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "DIO_Module.h"
#include "macros.h"
#include "timer1_driver.h"
int main(void)
{
	while(1)
	{
		
		timer1_SERVO_config(23.5);
	}
}

