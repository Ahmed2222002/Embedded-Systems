/*
 * ADC.c
 *
 * Created: 1/25/2024 6:09:16 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include "ADC_driver.h"
#include "DIO_Module.h"


int main(void)
{
	
	
   setBitDirection('A',0,'0');
   ADC_initialization('0','64');
   setBortDirection('D','1');
    while (1) 
    {
		unsigned short adc_val = readADC();
		writePort('D',adc_val);
    }
}

