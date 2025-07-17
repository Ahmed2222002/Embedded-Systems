/*
 * ADC2_driver.c
 *
 * Created: 1/31/2024 6:42:27 AM
 *  Author: hp
 */ 

#include <avr/io.h>
#include "macros.h"

void ADC_initialization()
{
	//Enable ADC
	SET_BIT(ADCSRA,ADEN);
	
	//select ADC channel
	SET_BIT(ADMUX,MUX4);
	
	//select reference voltage = 2.5v (internal volt)
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
	
	//select prescaler = 64 
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	
}

unsigned short ADC_read()
{
	unsigned short adc_value;
	
	SET_BIT(ADCSRA,ADSC);
	
	while(READ_BIT(ADCSRA,ADSC) == 1);
	adc_value = ADCL;
	
	adc_value = adc_value | (ADCH<<8);
	
	return adc_value;
}