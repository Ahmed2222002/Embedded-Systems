
/*
 * timer0_driver.c
 *
 * Created: 2/3/2024 6:38:46 AM
 *  Author: hp
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"
void timer0_ctc_init(char OCR0_value,unsigned char prescaler)
{
	sei();
	//set interrupt enable bit for CTC mode 
	SET_BIT(TIMSK,OCIE0);
	
	//load value in OCR
	OCR0 = OCR0_value;
	
	// select CTC mode 
	SET_BIT(TCCR0,WGM01);
	
	//set clock select bits CS02 , CS01 , CS00 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
			SET_BIT(TCCR0,CS00);
			break;
		case 2: // clk / 8
			SET_BIT(TCCR0,CS01);
			break;
		case 3: // clk / 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			break;
		case 4: // clk / 256
			SET_BIT(TCCR0,CS02);
			break;
		case 5: // clk /1024
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS02);
			break;
		case 6: //external clock source on T0 pin clock on falling edge
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
		case 7: //external clock source on T0 pin clock on rising edge
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
	}
	
}

void timer0_wave_CTC_mode(char OCR0_value,unsigned char prescaler)
{
	//set OC0 pin as output pin
	SET_BIT(DDRB,3);
	
	sei();
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE0);
	
	//load value in OCR
	OCR0 = OCR0_value;
	
	// select CTC mode
	SET_BIT(TCCR0,WGM01);
	
	//set clock select bits CS02 , CS01 , CS00 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
			SET_BIT(TCCR0,CS00);
			break;
		case 2: // clk / 8
			SET_BIT(TCCR0,CS01);
			break;
		case 3: // clk / 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			break;
		case 4: // clk / 256
			SET_BIT(TCCR0,CS02);
			break;
		case 5: // clk /1024
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS02);
			break;
		case 6: //external clock source on T0 pin clock on falling edge
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
		case 7: //external clock source on T0 pin clock on rising edge
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
	}
	// toggle OC0 on compare match
	SET_BIT(TCCR0,COM00);
	
}

void timer0_fast_PWM (char OCR0_value,unsigned char prescaler)
{
	//set OC0 pin as output pin
	SET_BIT(DDRB,3);
	
	sei();
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE0);
	
	//load value in OCR
	OCR0 = OCR0_value;
	
	// select fast PWM  mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	
	//set clock select bits CS02 , CS01 , CS00 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
			SET_BIT(TCCR0,CS00);
			break;
		case 2: // clk / 8
			SET_BIT(TCCR0,CS01);
			break;
		case 3: // clk / 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
		break;
			case 4: // clk / 256
			SET_BIT(TCCR0,CS02);
			break;
		case 5: // clk /1024
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS02);
			break;
		case 6: //external clock source on T0 pin clock on falling edge
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
		case 7: //external clock source on T0 pin clock on rising edge
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
			break;
	}
	
	//SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}



void timer0_phase_correct (char OCR0_value,unsigned char prescaler)
{
	//set OC0 pin as output pin
	SET_BIT(DDRB,3);
	
	sei();
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE0);
	
	//load value in OCR
	OCR0 = OCR0_value;
	
	// select phase correct PWM  mode
	SET_BIT(TCCR0,WGM00);

	
	//set clock select bits CS02 , CS01 , CS00 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
		SET_BIT(TCCR0,CS00);
		break;
		case 2: // clk / 8
		SET_BIT(TCCR0,CS01);
		break;
		case 3: // clk / 64
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		break;
		case 4: // clk / 256
		SET_BIT(TCCR0,CS02);
		break;
		case 5: // clk /1024
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS02);
		break;
		case 6: //external clock source on T0 pin clock on falling edge
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
		case 7: //external clock source on T0 pin clock on rising edge
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
		break;
	}
	
	//SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
}