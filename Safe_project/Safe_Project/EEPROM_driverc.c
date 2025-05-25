/*
 * EEPROM_driverc.c
 *
 * Created: 12/7/2023 10:32:41 AM
 *  Author: hp
 */ 
#include "DIO_Module.h"
#include "macros.h"
#define EEARL *((volatile unsigned char*) (0x3E))
#define EEARH *((volatile unsigned char*) (0x3F))
#define EEAR  *((volatile unsigned char*) (0x3E))
#define EEDR  *((volatile unsigned char*) (0x3D))
#define EECR  *((volatile unsigned char*) (0x3C))

void EEPROM_write(unsigned short address,unsigned char data)
{
	EEAR  = address;
	//EEARL  = address;
	//EEARH  = (address>>8);
	EEDR  = data;
	//set EEMWE
	SET_BIT(EECR,2);
	//set EEWE
	SET_BIT(EECR,1);
	while(READ_BIT(EECR,1)==1);
}

unsigned char EEPROM_read(unsigned short address)
{
	EEAR  = address;
	//EEARL  = address;
	//EEARH  = (address>>8);
	
	// SET EERE
	SET_BIT(EECR,0);
	
	return EEDR;
}
