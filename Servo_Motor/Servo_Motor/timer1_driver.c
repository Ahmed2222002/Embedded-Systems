/*
 * timer1_driver.c
 *
 * Created: 2/5/2024 9:14:25 AM
 *  Author: Ahmed Hussien
 */ 
#include "macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>
void timer1_SERVO_config(double degree)
{
	
	
	SET_BIT(DDRD,5);
	SET_BIT(TCCR1B,CS11);  /* no prescaling */
	
	OCR1A = (1.5 +(degree*0.005555555556)) * 1000;
	
	/* select  fast PWM mode and the to is ICR1*/
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	ICR1 = 19999;
	
	SET_BIT(TCCR1A,COM1A1);
}

