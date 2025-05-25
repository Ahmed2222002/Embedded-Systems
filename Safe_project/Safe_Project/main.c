/*
 * Safe_project.c
 *
 * Created: 12/7/2023 12:41:56 PM
 * Author : Ahmed Hussien
 */ 
#define F_CPU 8000000UL
#include "EEPROM_driver.h"
#include "keypad.h"
#include "LCD.h"
#include "DIO_Module.h"
#include <util/delay.h>

#define STATUS 0x00
#define EEPROM_LOCATION1 0x01
#define EEPROM_LOCATION2 0x02
#define EEPROM_LOCATION3 0x03
#define EEPROM_LOCATION4 0x04
/*
this function set the password for first time and store the user input values in EEPROM
*/
void set_password();
/*
this function puse the Safe system for 20 sec when the user enter wrong password 5 times
*/
void puse();
/*
if user forget the password this function will be used to reset the password again
*/
char reset_passwor();

int main(void)
{
	
	LCD_Initialization();
	keypadInitialization();
	setBitDirection('A',0,'1');
	setBitDirection('A',1,'1');
	setBitDirection('A',2,'1');
	/*
	 password[4]: array contains the value entered by user and compare this values to the values stored in EEPROM
	 when flag is equals to 1 that means that Safe still locked
	*/
	char password[4] ,value, flag = 1 , no_trails = 5 , i;
	if (EEPROM_read(STATUS) == 0xff)
	{
		set_password();
	}
	 
    while (flag == 1) 
    {
		setBit('A',0);
		clearBit('A',1);
		clearBit('A',2);
		
		if (no_trails == 0)
		{
			puse();
			if (reset_passwor() == '1')
			{
				no_trails = 5;
				set_password();
			}
			else
			{
				clearScreen();
				_delay_ms(500);
			}
		}
		
		LCD_printString("check Pass:");
		
		for (i = 0 ; i<4 ; i++)
		{
			do
			{
				value = keypadRead();
			} while (value == 'Z');
			LCD_printCharacter(value);
			_delay_ms(700);
			LCD_moveCursor(1,12+i);
			LCD_printCharacter('*');
			LCD_moveCursor(1,13+i);
			
			password[i] = value;
		}
		
		clearScreen();
		
		if (password[0] == EEPROM_read(EEPROM_LOCATION1) && password[1] == EEPROM_read(EEPROM_LOCATION2)&& password[2] == EEPROM_read(EEPROM_LOCATION3) && password[3] == EEPROM_read(EEPROM_LOCATION4))
		{
			LCD_printString("password is true");
			LCD_moveCursor(2,1);
			LCD_printString("Safe is opened");
			setBit('A',2);
			clearBit('A',0);
			clearBit('A',1);
			flag = 0;
		}
		else
		{
			no_trails -=1;
			clearScreen();
			LCD_printString("wrong password");
			_delay_ms(2000);
			clearScreen();
		}
    }
}

void set_password()
{
	_delay_ms(500);
	char value = 'Z' , i;
	clearScreen();
	LCD_printString("set pass:");
	for (i = 0 ;i < 4 ;i++)
	{
		if (EEPROM_read(STATUS) == 0xff)
		{
			
			do
			{
				value = keypadRead();
			} while (value == 'Z');
			LCD_printCharacter(value);
			_delay_ms(700);
			LCD_moveCursor(1,10+i);
			LCD_printCharacter('*');
			LCD_moveCursor(1,11+i);
			EEPROM_write(EEPROM_LOCATION1+i,value);
		}
	}
	EEPROM_write(STATUS,0x00);
	clearScreen();
	
}

void puse()
{
	char counter = 20;
	setBit('a',1);
	clearBit('A',0);
	clearBit('A',2);
	clearScreen();
	LCD_printString("Safe is locked: ");
	LCD_moveCursor(2,1);
	LCD_printString("for ");
	while(counter)
	{
		LCD_moveCursor(2,5);
		LCD_printCharacter((counter/10)+48);
		LCD_printCharacter((counter%10)+48);
		LCD_printString(" sec");	
		counter -= 1;
		_delay_ms(1000);
	}
}

char reset_passwor()
{
	char value;
	clearScreen();
	LCD_printString("Reset Password?");
	LCD_moveCursor(2,1);
	LCD_printString("YES: 1    NO: 2");
	do
	{
		value = keypadRead();
	} while (value == 'Z');
	
	if (value == '1')
	{
		EEPROM_write(STATUS,0xff);
		return '1';
	}else{
		return '0';
	}
}