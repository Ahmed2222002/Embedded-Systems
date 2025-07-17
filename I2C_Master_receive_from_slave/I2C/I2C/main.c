/*
Master code
 * I2C.c
 *
 * Created: 2/14/2024 6:33:35 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include "i2c_driver.h"
#include "LCD.h"
#include <util/delay.h>

int main(void)
{
	LCD_Initialization();
    I2C_master_init(50000);
	unsigned char slave_data;	
	while(1)
	{
		_delay_ms(500);
		I2C_start_condition();
		I2C_send_SLA_R(0b11100001);
		slave_data = I2C_master_Receive_data_with_NACK();
		LCD_printCharacter(slave_data);
		I2C_stop_condition();	
	}
	
	
	
}
