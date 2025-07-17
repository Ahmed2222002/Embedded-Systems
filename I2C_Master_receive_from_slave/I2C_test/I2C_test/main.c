/*
 * I2C_test.c
 *slave code
 * Created: 2/15/2024 11:24:49 AM
 * Author : hp
 */ 

#define F_CPU 8000000UL
#include "i2c_driver.h"
#include "LCD.h"

int main(void)
{
	
    set_device_address(0b11100000);
	
    while (1) 
    {
	  slave_transmite_its_content();
    }
}
