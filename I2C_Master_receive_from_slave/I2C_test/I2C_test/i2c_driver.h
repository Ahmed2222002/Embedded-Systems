/*
 * i2c_driver.h
 *
 * Created: 2/14/2024 6:34:45 AM
 *  Author: hp
 */ 


#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

void I2C_master_init(unsigned long scl);

void I2C_start_condition();

void I2C_repeated_start();

void I2C_send_SLA_W(unsigned char SLA_W);

void I2C_send_SLA_R(unsigned char SLA_R);

/*master write in slave*/
void I2C_master_send_data(unsigned char data);

void I2C_stop_condition();

void set_device_address(unsigned char address);

/*
use this function when you want to read data that has been transmitted by master to slave 
for example use this function when master transmit data to slave and you want to print data to LCD
*/
unsigned char read_slave_content();

unsigned char slave_transmite_content();

/*
	master want to read from slave 
	slave transmit it's content to master
	slave will use this function not master
*/
void slave_transmite_its_content();

/*
	master want to read from slave 
	slave transmit it's content to master
	master will use this function not slave
*/
unsigned char I2C_master_Receive_slave_content();


/*
	master want to read from slave 1 byte
	slave transmit it's content to master
	master not send but it send stop condition
	master will use this function not slave
*/

unsigned char I2C_master_Receive_data_with_NACK();

#endif /* I2C_DRIVER_H_ */