/*
 * LCD.c
 *
 * Created: 11/1/2023 9:55:20 PM
 *  Author: Ahmed Hussien
 */
#define F_CPU 8000000UL
#include "DIO_Module.h"
#include <util/delay.h>
#include "LCD_Hardware_Interface.h"
#define LCD_8BIT_MODE 0x38
#define LCD_4BIT_MODE 0x28
#define CURSOR_ON_DISPLAN_ON 0x0E
#define CLEAR_SCREEN 0x01
#define ENTRY_MODE 0x06
void send_pulse()
{
	setBit(ENABEL_PORT,ENABEL_PIN);
	_delay_ms(2);
	clearBit(ENABEL_PORT,ENABEL_PIN);
	_delay_ms(2);
}
void LCD_sendCommand(unsigned char cmd)
{
	#if (LCD_PINS == 8)//8-bit mode
	writePort(LCD_CONNECTED_PORT,cmd);
	clearBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);//set logic low to register select pin
	send_pulse();
	#elif (LCD_PINS == 4)//4-bit mode
		#if (IS_CONNECTED_TO_HIGH_PINS == 0)
			writeLow_4pins(LCD_CONNECTED_PORT,cmd>>4);
			clearBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
			_delay_ms(1);
			writeLow_4pins(LCD_CONNECTED_PORT,cmd);
			clearBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
		#elif (IS_CONNECTED_TO_HIGH_PINS == 1)
			writeHigh_4pins(LCD_CONNECTED_PORT,cmd>>4);
			clearBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
			_delay_ms(1);
			writeHigh_4pins(LCD_CONNECTED_PORT,cmd);
			clearBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
		#endif
	#endif 
	_delay_ms(1);
}

void LCD_Initialization()
{
	#if (LCD_PINS == 8)
		_delay_ms(200);
		setBortDirection(LCD_CONNECTED_PORT,'1');
		setBitDirection(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN,'1');
		setBitDirection(ENABEL_PORT,ENABEL_PIN,'1');
		LCD_sendCommand(LCD_8BIT_MODE);//EIGHT_BITS MODE
		_delay_ms(1);
		LCD_sendCommand(CURSOR_ON_DISPLAN_ON);//CURSOR_ON_DISPLAN_ON
		_delay_ms(1);
		LCD_sendCommand(0x01);//CLEAR_SCREEN
		_delay_ms(10);
		LCD_sendCommand(ENTRY_MODE);//ENTRY_MODE
		
	#elif (LCD_PINS == 4)
		_delay_ms(200);
		#if (IS_CONNECTED_TO_HIGH_PINS == 0)
			setBitDirection(LCD_CONNECTED_PORT,0,'1');
			setBitDirection(LCD_CONNECTED_PORT,1,'1');
			setBitDirection(LCD_CONNECTED_PORT,2,'1');
			setBitDirection(LCD_CONNECTED_PORT,3,'1');
		#elif (IS_CONNECTED_TO_HIGH_PINS == 1)
			setBitDirection(LCD_CONNECTED_PORT,4,'1');
			setBitDirection(LCD_CONNECTED_PORT,5,'1');
			setBitDirection(LCD_CONNECTED_PORT,6,'1');
			setBitDirection(LCD_CONNECTED_PORT,7,'1');
		#else
			#warning "You must set IS_CONNECTED_TO_HIGH_PINS 0 to connect lcd to first 4-bit of any port or 1 to connect lcd to last 4-bit of any port"
		#endif
		
		setBitDirection(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN,'1');
		setBitDirection(ENABEL_PORT,ENABEL_PIN,'1');
		
		LCD_sendCommand(0x02); //return home
		_delay_ms(10);
		LCD_sendCommand(LCD_4BIT_MODE);//FOUR_BITS MODE
		_delay_ms(1);
		LCD_sendCommand(CURSOR_ON_DISPLAN_ON);//CURSOR_ON_DISPLAN_ON
		_delay_ms(1);
		LCD_sendCommand(0x01);//CLEAR_SCREEN
		_delay_ms(10);
		LCD_sendCommand(ENTRY_MODE);//ENTRY_MODE
	#endif
}

void LCD_printCharacter(char character)
{
	#if (LCD_PINS == 8)
		writePort(LCD_CONNECTED_PORT,character);
		setBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
		send_pulse();
		
	#elif (LCD_PINS == 4)
		#if (IS_CONNECTED_TO_HIGH_PINS == 0)
			writeLow_4pins(LCD_CONNECTED_PORT,character>>4);
			setBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
			writeLow_4pins(LCD_CONNECTED_PORT,character);
			setBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
		#elif (IS_CONNECTED_TO_HIGH_PINS == 1)
			writeHigh_4pins(LCD_CONNECTED_PORT,character>>4);
			setBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
			writeHigh_4pins(LCD_CONNECTED_PORT,character);
			setBit(REGESTER_SELECT_PORT,REGESTER_SELECT_PIN);
			send_pulse();
		#endif

	#endif
	_delay_ms(1);
}

void LCD_printString(char* ptr)
{
	while(*ptr != 0)
	{
		LCD_printCharacter(*ptr);
		++ptr;
	}
}
void LCD_moveCursor(char row , char column)
{
	char address;
	if (row == 1)
	{
		address = 0x80 + column -1;
	}
	else
	{
		address = 0xC0 + column -1;
	}
	LCD_sendCommand(address);
}
void clearScreen()
{
	LCD_sendCommand(0x01);
	_delay_ms(10);
}