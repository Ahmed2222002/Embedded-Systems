/*
 * EEPROM_driver.h
 *
 * Created: 12/7/2023 10:33:01 AM
 *  Author: hp
 */ 


#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

void EEPROM_write(unsigned short address,char data);

char EEPROM_read(unsigned short address);


#endif /* EEPROM_DRIVER_H_ */