/*
 * uart_driver.h
 *
 * Created: 2/7/2024 5:14:42 PM
 *  Author: hp
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

void uart_initialize(unsigned long baud_rate);

void uart_send(unsigned char data);

unsigned char uart_receive();

void uart_send_string( char *ptr);

#endif /* UART_DRIVER_H_ */