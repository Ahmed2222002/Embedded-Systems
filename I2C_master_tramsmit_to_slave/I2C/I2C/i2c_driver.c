/*
 * i2c_driver.c
 *
 * Created: 2/14/2024 6:34:09 AM
 *  Author: hp
 */ 
#define F_CPU 8000000UL
#define prescaler 1
#include <avr/io.h>
#include <util/delay.h>
#include "macros.h"
#include "DIO_Module.h"
#include "LCD.h"
void I2C_master_init(unsigned long scl)
{
	/*set SCL CLK*/
	TWBR = ((F_CPU / scl) - 16) / (2 * prescaler);
	TWSR=0;
	
}

void I2C_start_condition()
{

	/*clear TWINT flag and write logic 1 in  TWSTA (TWI SART CONDITION)*/
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	
	/*wait till TWINT has been equal  logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	// start condition has been transmitted
	while((TWSR & 0xF8) != 0x08);
}

void I2C_repeated_start()
{

	/*clear TWINT flag and write logic 1 in  TWSTA (TWI SART CONDITION)*/
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	
	/*wait till TWINT has been equal  logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	// repeated start has been transmitted
	while((TWSR & 0xF8) != 0x10);
}

void I2C_send_SLA_W(unsigned char SLA_W)
{
	TWDR = SLA_W;
	
	/*clear TWINT flag */
	SET_BIT(TWCR,TWINT);

	/*wait till SLA_R_W has been sent*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*SLA+W has been transmitted and Acknowledgment received*/
	while((TWSR & 0xF8) != 0x18);

}

void I2C_send_SLA_R(unsigned char SLA_R)
{
	TWDR = SLA_R;
	
	/*clear TWINT flag */
	SET_BIT(TWCR,TWINT);

	/*wait till SLA_R_W has been sent*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*SLA+R has been transmitted and Acknowledgment received*/
	while((TWSR & 0xF8) != 0x40);

}

void I2C_master_send_data(unsigned char data)
{
	TWDR = data;
	
	/*clear TWINT flag */
    SET_BIT(TWCR,TWINT);
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*Data byte has been transmitted and Acknowledgment received*/
	while((TWSR & 0xF8) != 0x28);
}


void I2C_stop_condition()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void set_device_address(unsigned char address)
{
	TWAR = address;
}

unsigned char read_slave_content()
{
	/*clear TWINT , Enable I2C , Enable Acknowledgment*/
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*own SLA+W has been received Acknowledgment has been returned */
	while((TWSR & 0xF8) != 0x60);
	
	/*clear TWINT again */
	 SET_BIT(TWCR,TWINT);
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*previously addressed with own SLA+W data has been received and Acknowledgment has been returned*/
	while((TWSR & 0xF8) != 0x80);
	
	return TWDR;
}
void slave_transmite_its_content()
{
	/*clear TWINT , Enable I2C */
	TWCR = (1<<TWINT) | (1<<TWEN) |(1<<TWEA);
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*own SLA+R has been received Acknowledgment has been returned */
	while((TWSR & 0xF8) != 0xA8);
	
	/*
	load any value to slave data register to test the function
	TWDR = '1';
	*/
	
	
	/*clear TWINT again */
	SET_BIT(TWCR,TWINT);
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*last data byte in TWDR has been transmitted , Not ACK has been received*/
	while((TWSR & 0xF8) != 0xC0);
}

unsigned char I2C_master_Receive_slave_content()
{
	/*clear TWINT , Enable I2C */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*how to print received data before master sending an Acknowledgment because when master is sending  ACK it override the content of TWDR */
	
	/*Data byte has been received and Acknowledgment has been returned*/
	while((TWSR & 0xF8) != 0x50);

	return TWDR;
}

unsigned char I2C_master_Receive_data_with_NACK()
{
	/*clear TWINT , Enable I2C */
	TWCR = (1<<TWINT) | (1<<TWEN) ;
	
	/*wait till TWINT has been equal logic high*/
	while(READ_BIT(TWCR,TWINT) == 0);
	
	/*Data byte has been received and Not Acknowledgment has been returned*/
	while((TWSR & 0xF8) != 0x58);
	
	return TWDR;
}
