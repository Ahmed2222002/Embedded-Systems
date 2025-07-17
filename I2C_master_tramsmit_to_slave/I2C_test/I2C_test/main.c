/*
 * I2C_test.c
 *
 * Created: 2/15/2024 11:24:49 AM
 * Author : hp
 */ 

#define F_CPU 8000000UL
#include "i2c_driver.h"
#include "LCD.h"

int main(void)
{
	
    set_device_address(0b11100000);
	LCD_Initialization();
	unsigned char master_data;
    while (1) 
    {
	  master_data =	read_slave_content();
	  LCD_printCharacter(master_data);
    }
}

