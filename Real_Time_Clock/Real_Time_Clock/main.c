/*
 * Timers.c
 *
 * Created: 2/3/2024 6:37:15 AM
 * Author : Ahmed Hussien
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer2_driver.h"
#include "keypad.h"
#include "sevenSegment.h"
#include "DIO_Module.h"
#include "LCD.h"

volatile  char seconds = 0 ;

char minutes = 0;

char houres = 1;

int main(void)
{
	char keypad_value;
    setBitDirection('A',0,'1');
    setBitDirection('A',1,'1');
	setBitDirection('A',2,'1');
	setBitDirection('A',3,'1');
	setBitDirection('A',4,'1');
	setBitDirection('A',5,'1');
    sevenSegmentInitialize('D');
	timer2_RTC_config();
	LCD_Initialization();
	LCD_printString("press ON button");
	LCD_moveCursor(2,1);
	LCD_printString("to modify time");
	 keypadInitialization();
	 char temp = 0;
    while(1)
    {
		keypad_value = keypadRead();
		
		// if user need to modfiy time
		if (keypad_value == 'c')
		{
			setBit('A',0);
			setBit('A',1);
			setBit('A',2);
			setBit('A',3);
			setBit('A',4);
			setBit('A',5);
			
			clearScreen();
			_delay_ms(200);
			LCD_printString("houres = --");
			LCD_moveCursor(1,10);
			do
			{
				keypad_value = keypadRead();
				
			}while(keypad_value == 'Z');
			LCD_printCharacter(keypad_value);
			_delay_ms(250);
			temp = (keypad_value - 48) * 10 ;
			
			do
			{
				keypad_value = keypadRead();
			}while(keypad_value == 'Z');
			LCD_printCharacter(keypad_value);
			_delay_ms(250);
			houres = (keypad_value-48) + temp ;
			
			clearScreen();
			_delay_ms(200);
			LCD_printString("minutes = --");
			LCD_moveCursor(1,11);
			do
			{
				keypad_value = keypadRead();
			}while(keypad_value == 'Z');
			LCD_printCharacter(keypad_value);
			_delay_ms(250);
			temp = (keypad_value - 48) * 10 ;
			
			do
			{
				keypad_value = keypadRead();
			}while(keypad_value == 'Z');
			LCD_printCharacter(keypad_value);
			_delay_ms(250);
			minutes = (keypad_value-48) + temp ; 
			
			seconds = 0;
			clearScreen();
			LCD_printString("press ON button");
			LCD_moveCursor(2,1);
			LCD_printString("to modify time");
			
		}
		clearBit('A',0);
		setBit('A',1);
		setBit('A',2);
		setBit('A',3);
		setBit('A',4);
		setBit('A',5);
        sevenSegmentWrite('D',seconds % 10);
		_delay_ms(5);
		
		clearBit('A',1);
		setBit('A',0);
		setBit('A',2);
		setBit('A',3);
		setBit('A',4);
		setBit('A',5);
        sevenSegmentWrite('D',seconds / 10);
		_delay_ms(5);
		
		if (minutes < 60 && seconds == 60)
		{
			minutes++;
			seconds = 0;
		}
		setBit('A',0);
		setBit('A',1);
		clearBit('A',2);
		setBit('A',3);
		setBit('A',4);
		setBit('A',5);
		sevenSegmentWrite('D',minutes % 10);
		_delay_ms(5);
		
		setBit('A',1);
		setBit('A',0);
		setBit('A',2);
		clearBit('A',3);
		setBit('A',4);
		setBit('A',5);
		sevenSegmentWrite('D',minutes / 10);
		_delay_ms(5);
		if (houres < 24 && minutes == 60)
		{
			houres++;
			minutes = 0;
		}
		
		setBit('A',1);
		setBit('A',0);
		setBit('A',2);
		setBit('A',3);
		clearBit('A',4);
		setBit('A',5);
		sevenSegmentWrite('D',houres%10);
		_delay_ms(5);
		
		setBit('A',1);
		setBit('A',0);
		setBit('A',2);
		setBit('A',3);
		setBit('A',4);
		clearBit('A',5);
		sevenSegmentWrite('D',houres/10);
		_delay_ms(5);
		if (houres == 24)
		{
			houres = 1 ; 
		}
			
    }
    return 0;
}

ISR(TIMER2_OVF_vect)
{
	seconds++;
}

