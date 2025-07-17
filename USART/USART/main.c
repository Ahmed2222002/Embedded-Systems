/*
 * USART.c
 *
 * Created: 2/7/2024 5:13:58 PM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include "uart_driver.h"
#include "LCD.h"
#include <util/delay.h>

int main(void)
{
    uart_initialize(9600);
	_delay_ms(10);
	LCD_Initialization();
	_delay_ms(350);
	unsigned char data_recieved;
	
   uart_send('A');
	_delay_ms(1000);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
	uart_send('H');
	_delay_ms(1000);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
	
	uart_send('M');
	_delay_ms(1000);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
	uart_send('E');
	_delay_ms(1000);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
	uart_send('D');
	_delay_ms(1000);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
	data_recieved = uart_receive();
	LCD_printCharacter(data_recieved);
	
}

