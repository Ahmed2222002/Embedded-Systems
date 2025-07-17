/*
 * uart_driver.c
 *
 * Created: 2/7/2024 5:14:26 PM
 *  Author: hp
 */
#define  F_CPU 8000000UL 
#include <avr/io.h>
#include "macros.h"
#include <util/delay.h>
void uart_initialize(unsigned long baud_rate)
{
	unsigned short ubrr;
	/*enable USART receiver & transmitter */
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	/*calculate baud rate */
	ubrr = (F_CPU/ (16 * baud_rate)) - 1 ;
	
	UBRRH = (ubrr >> 8 );
	UBRRL = ubrr;
}

void uart_send(unsigned char data)
{
	/* wait till UDR register is empty*/
	while(READ_BIT(UCSRA,UDRE) == 0);
	
	UDR = data ;
	
	/* clear flag bit*/
	SET_BIT(UCSRA,UDRE); 
}

unsigned char uart_receive()
{
	unsigned char data;
	/*wait till receive has completed */
	while(READ_BIT(UCSRA,RXC) == 0);
	
	data = UDR;
	
	/*clear flag bit */
	
	return data;
}

void uart_send_string( char *ptr)
{
	while(*ptr!=0)
	{
		uart_send(*ptr);
		ptr++;
		_delay_ms(100);
	}
}