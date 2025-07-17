/*
 * ADC_driver.h
 *
 * Created: 1/25/2024 6:10:22 AM
 *  Author: hp
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

void ADC_initialization(char connected_pin_number, char prscaler );
unsigned short readADC();




#endif /* ADC_DRIVER_H_ */