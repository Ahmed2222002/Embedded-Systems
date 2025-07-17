/*
 * timer2_driver.c
 *
 * Created: 2/3/2024 4:43:10 PM
 *  Author: hp
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"

void timer2_RTC_config()
{
	SET_BIT(ASSR,AS2);
	
	sei();
	
	SET_BIT(TIMSK,TOIE2);
	
	SET_BIT(TCCR2,CS20);
	
	SET_BIT(TCCR2,CS22);
}

void timer2_ctc_init(char OCR2_value,unsigned char prescaler , char external_clk_source)
{
	if (external_clk_source == 1)
	{
		SET_BIT(ASSR,AS2);
	}
	sei();
	
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE2);
	
	//load value in OCR
	OCR2 = OCR2_value;
	
	// select CTC mode
	SET_BIT(TCCR2,WGM21);
	
	//set clock select bits CS22 , CS21 , CS20 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
			SET_BIT(TCCR2,CS20);
			break;
		case 2: // clk / 8
			SET_BIT(TCCR2,CS21);
			break;
		case 3: // clk / 32
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS21);
			break;
		case 4: // clk / 64
			SET_BIT(TCCR2,CS22);
			break;
		case 5: // clk /128
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS22);
			break;
		case 6: // clk /256
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS22);
			break;
		case 7: // clk /1024
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS22);
			break;
	}
	
}

void timer2_wave_CTC_mode(char OCR2_value,unsigned char prescaler,char external_clk_source)
{
	if (external_clk_source == 1)
	{
		SET_BIT(ASSR,AS2);
	}
	
	//set OC2 pin as output pin
	SET_BIT(DDRD,7);
	
	sei();
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE2);
	
	//load value in OCR
	OCR2 = OCR2_value;
	
	// select CTC mode
	SET_BIT(TCCR2,WGM21);
	
	//set clock select bits CS22 , CS21 , CS20 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
			SET_BIT(TCCR2,CS20);
			break;
		case 2: // clk / 8
			SET_BIT(TCCR2,CS21);
			break;
		case 3: // clk / 32
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS21);
			break;
		case 4: // clk / 64
			SET_BIT(TCCR2,CS22);
			break;
		case 5: // clk /128
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS22);
			break;
		case 6: // clk /256
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS22);
			break;
		case 7: // clk /1024
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS22);
			break;
	}
	// toggle OC2 on compare match
	SET_BIT(TCCR2,COM20);
	
}

void timer2_fast_PWM (char OCR2_value,unsigned char prescaler , char external_clk_source)
{
	if (external_clk_source == 1)
	{
		SET_BIT(ASSR,AS2);
	}
	//set OC2 pin as output pin
	SET_BIT(DDRD,7);
	
	sei();
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE2);
	
	//load value in OCR
	OCR2 = OCR2_value;
	
	// select fast PWM  mode
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	
	//set clock select bits CS22 , CS21 , CS20 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
		SET_BIT(TCCR2,CS20);
		break;
		case 2: // clk / 8
		SET_BIT(TCCR2,CS21);
		break;
		case 3: // clk / 32
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		break;
		case 4: // clk / 64
		SET_BIT(TCCR2,CS22);
		break;
		case 5: // clk /128
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS22);
		break;
		case 6: // clk /256
		SET_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
		break;
		case 7: // clk /1024
		SET_BIT(TCCR2,CS20);
		SET_BIT(TCCR2,CS21);
		SET_BIT(TCCR2,CS22);
		break;
	}
	
	//SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
}



void timer2_phase_correct (char OCR2_value,unsigned char prescaler ,char external_clk_source )
{
	if (external_clk_source == 1)
	{
		SET_BIT(ASSR,AS2);
	}
	//set OC2 pin as output pin
	SET_BIT(DDRD,7);
	
	sei();
	//set interrupt enable bit for CTC mode
	SET_BIT(TIMSK,OCIE2);
	
	//load value in OCR
	OCR2 = OCR2_value;
	
	// select phase correct PWM  mode
	SET_BIT(TCCR2,WGM20);

	
	//set clock select bits CS22 , CS21 , CS20 (prescaler)
	switch(prescaler)
	{
		case 1: // clk (no prescaling)
			SET_BIT(TCCR2,CS20);
			break;
		case 2: // clk / 8
			SET_BIT(TCCR2,CS21);
			break;
		case 3: // clk / 32
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS21);
			break;
		case 4: // clk / 64
			SET_BIT(TCCR2,CS22);
			break;
		case 5: // clk /128
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS22);
			break;
		case 6: // clk /256
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS22);
			break;
		case 7: // clk /1024
			SET_BIT(TCCR2,CS20);
			SET_BIT(TCCR2,CS21);
			SET_BIT(TCCR2,CS22);
			break;
	}
	
	//SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
}