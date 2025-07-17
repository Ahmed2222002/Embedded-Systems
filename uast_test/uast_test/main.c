/*
 * uast_test.c
 *
 * Created: 2/8/2024 9:03:27 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include "LCD.h"
#include "uart_driver.h"
#include "DIO_Module.h"
#include <util/delay.h>
int main(void)
{
	uart_initialize(9600);
	_delay_ms(10);
	LCD_Initialization();
    _delay_ms(350);
	unsigned char data_received;
    
	data_received = uart_receive();
	LCD_printCharacter(data_received);
	
	uart_send('H');
	_delay_ms(1000);
		
	data_received = uart_receive();
	LCD_printCharacter(data_received);
		
	uart_send('U');
	_delay_ms(1000);
	
	data_received = uart_receive();
	LCD_printCharacter(data_received);
	
	uart_send('S');
	_delay_ms(1000);
	
	data_received = uart_receive();
	LCD_printCharacter(data_received);
	
	uart_send('S');
	_delay_ms(1000);
	
	data_received = uart_receive();
	LCD_printCharacter(data_received);
	
	uart_send('I');
	_delay_ms(1000);
	
	uart_send('E');
	_delay_ms(1000);
	
	uart_send('N');
	_delay_ms(1000);
}

