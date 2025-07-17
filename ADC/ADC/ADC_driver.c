/*
 * ADC_driver.c
 *
 * Created: 1/25/2024 6:09:52 AM
 *  Author: Ahmed Hussien
 */ 
#include "macros.h"
#define ADMUX *((volatile unsigned char*)(0x27)) 
#define ADCSRA *((volatile unsigned char*)(0x26))
#define ADCH *((volatile unsigned char*)(0x25))
#define ADCL *((volatile unsigned char*)(0x24))

#define lift_adjust 0

void ADC_initialization(char connected_pin_number ,char prscaler )
{
	//enable ADC
	SET_BIT(ADCSRA,7);
	
	// select the pin of portA that will be connected to ADC
	// default pin is PA0
	switch(connected_pin_number)
	{
		case '1'://ADMUX = 0000001
			SET_BIT(ADMUX,0);
			break;
		case '2'://ADMUX = 0000010
			SET_BIT(ADMUX,1);
			break;
	    case '3'://ADMUX = 0000011
			SET_BIT(ADMUX,0);
			SET_BIT(ADMUX,1);
			break;
		case '4'://ADMUX = 0000100
			SET_BIT(ADMUX,2);
			break;
		case 5://ADMUX = 0000101
			SET_BIT(ADMUX,0);
			SET_BIT(ADMUX,2);
			break;
		case '6'://ADMUX = 0000110
			SET_BIT(ADMUX,1);
			SET_BIT(ADMUX,2);
			break;
		case '7'://ADMUX = 0000111
			SET_BIT(ADMUX,0);
			SET_BIT(ADMUX,1);
			SET_BIT(ADMUX,2);
			break;
		default://ADMUX = 0000000
			ADMUX = 0;
			break;
	}
	//choose lift or right adjustment 
	#if (lift_adjust == 1)
		SET_BIT(ADMUX,5);
	#else
		CLEAR_BIT(ADMUX,5);
	#endif
	
	// select V_reference = AVCC
	SET_BIT(ADMUX,6);
	CLEAR_BIT(ADMUX,7);
	
	// select prescaler
	// default prescaler  = 2  
	
	switch(prscaler)
	{
		case '4':
			SET_BIT(ADCSRA,1);
			break;
		case '8':
			SET_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,1);
			break;
		case '16':
			SET_BIT(ADCSRA,2);
			break;
		case '32':
			SET_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,2);
			break;
		case '64':
			SET_BIT(ADCSRA,1);
			SET_BIT(ADCSRA,2);
			break;
		case '128':
			SET_BIT(ADCSRA,0);
			SET_BIT(ADCSRA,1);
			SET_BIT(ADCSRA,2);
			break;
		default:
			break;
			
			
	}
	
}

unsigned short readADC()
{
	unsigned short ADC_value;
	// start of conversion 
	SET_BIT(ADCSRA,6);
	
	// wait till conversion is done 
	while(READ_BIT(ADCSRA,6) == 1);
	
	// read ADC_value 
	# if (lift_adjust == 1)
		ADC_value = ADCH ;
	#else
		ADC_value = ADCL;
		ADC_value = ADC_value | (ADCH << 7);
	#endif
	
	return ADC_value;
	
}