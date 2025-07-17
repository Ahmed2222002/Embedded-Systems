/*
 * smart_home.c
 *
 * Created: 2/19/2024 11:03:31 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "EEPROM_driver.h"
#include "keypad.h"
#include "LCD.h"
#include "timer0_driver.h"
#include "ADC_driver.h"
#include "DIO_Module.h"
#define flag 0x00
#define start_location 0x01
#define wrong_choice 0

void set_admian_password();
unsigned char check_password();
void pause_system(unsigned char pause_time);
void main_window();
void control_light();
void control_Air_conditioner();

volatile char counter = 0;
unsigned char air_conditioner_temperature = 0 ;
unsigned char temperature;
int main(void)
{
	LCD_Initialization();
    keypadInitialization();
	setBitDirection('A',0,'0');
	ADC_initialization('0','64');
	setBitDirection('C',0,'1');
	timer0_ctc_init(78,5);
	char is_frist_time , is_password_true , no_trails = 5 , pause_time = 20 ;
	
 
	is_frist_time = EEPROM_read(flag);
	if (is_frist_time == 0xFF)
	{
		set_admian_password();
	}
		
	while(1)
	{
		is_password_true = check_password();
		if (is_password_true == 1)
		{
			break;
		}
			
		/*pause the System */
		else if (no_trails == 0)
		{
			pause_system(pause_time);
			no_trails = 5;
		}
			
		else
		{
			clearScreen();
			LCD_printString("wrong password");
			no_trails -= 1;
			_delay_ms(1000);
		}
	}
		
	while(1)
	{
		main_window();
	}
    
}

void set_admian_password()
{
	char value,i;
	clearScreen();
	LCD_printString("set password");
	LCD_moveCursor(2,1);
	
	for(i=0 ; i<4 ; )
	{
		do
		{
			value = keypadRead();
			_delay_ms(200);
		} while (value == 'Z');
		
		/*this case handle if use want to make backspace*/
		if (value == 'c')
		{
			LCD_moveCursor(2,i);
			LCD_printCharacter(0x20);
			LCD_moveCursor(2,i);
			if (i > 0)
			{
				--i;
			}
			
		}
		/*this make sure that user inter numbers only*/
		else if (value >= 48 && value <= 57)
		{
			LCD_printCharacter(value);
			_delay_ms(10);
			LCD_moveCursor(2,i+1);
			LCD_printCharacter('*');
			EEPROM_write(start_location+i,value);
			++i;
		}
		
	}
	
	EEPROM_write(flag,0);
}

unsigned char check_password()
{
	clearScreen();
	LCD_printString("check password");
	LCD_moveCursor(2,1);
	char i ,value , flag1 = 1;
	for(i = 0 ; i < 4 ;)
	{
		do 
		{
			value = keypadRead();
			_delay_ms(200);
		} while (value == 'Z');
		
		/*this case handle if user want to make backspace*/
		if (value == 'c')
		{
			LCD_moveCursor(2,i);
			LCD_printCharacter(0x20);
			LCD_moveCursor(2,i);
			if (i > 0)
			{
				--i;
			}
			
		}
		
		/*this make sure that user inter numbers only*/
		else if (value >= 48 && value <= 57)
		{
			LCD_printCharacter(value);
			_delay_ms(30);
			LCD_moveCursor(2,i+1);
			LCD_printCharacter('*');
			
			/*I need Else block  because I give user option of make backspace 
			without else block if user inputer an wrong number then make backspace
			and correct the number the flag variable still equal 0
			and generate wrong password although password is correct
			*/
			if (value != EEPROM_read(start_location+i))
			{
				flag1 = 0;
			}
			else
			{
				flag1 = 1;
			}
			
			++i;
		}
		
	}
	
	return flag1;
}

void pause_system(unsigned char pause_time)
{
	clearScreen();
	LCD_sendCommand(0xC);
	LCD_printString("sys paused ");
	counter = 0;
	while(pause_time > 0)
	{
		if (counter>=100)
		{
			--pause_time;
			counter = 0;
		}
		
		LCD_printCharacter((pause_time/10) + 48);
		LCD_printCharacter((pause_time%10) + 48);
		LCD_printString("sec");
		LCD_moveCursor(1,12);
	}
	pause_time = 20;
	LCD_sendCommand(0x0E);
	
}

void main_window()
{
	unsigned char keypad_value;
	clearScreen();
	LCD_printString("1-light ");
	LCD_moveCursor(2,1);
	LCD_printString("2-Air_conditioner");
	do 
	{
		temperature = 0.25 * readADC();
		/*turn on air_conditioner*/
		if (air_conditioner_temperature < temperature && air_conditioner_temperature != 0)
		{
			setBit('C',0);
		}
		/*turn off air_conditioner*/
		else if (air_conditioner_temperature > temperature)
		{
			clearBit('C',0);
		}
		keypad_value = keypadRead();
		_delay_ms(150);
		
		
	} while (keypad_value == 'Z');
	
	
	
	if (keypad_value == '1')
	{
		control_light();
	}
	
	else if (keypad_value == '2' )
	{
		control_Air_conditioner();
	}
}

void control_light()
{
	unsigned char keypad_value , room_pin;
	setBitDirection('C',7,'1');
	setBitDirection('C',6,'1');
	setBitDirection('C',5,'1');
	setBitDirection('C',4,'1');
	clearScreen();
	while(1)
	{
		LCD_printString("1-Room1  2-Room2");
		LCD_moveCursor(2,1);
		LCD_printString("3-Room3  4-Room4");
		do 
		{
			keypad_value = keypadRead();
			_delay_ms(250);
		} while (keypad_value == 'Z');
	
		switch(keypad_value)
		{
			case '1':
				room_pin = 7;
				break;
			case '2':
				room_pin = 6;
				break;
			case '3':
				room_pin = 5;
				break;
			case '4':
				room_pin = 4;
				break;
			default:
				room_pin = wrong_choice ;
				break;
			
		}
		if (room_pin != wrong_choice)
		{
			break;
		}
		clearScreen();
		LCD_printString("wrong choice");
		_delay_ms(1000);
		clearScreen();
	}
	clearScreen();
	if (readBit('C',(unsigned char)room_pin) == 0)
	{
		LCD_printString("light is off");
		LCD_moveCursor(2,1);
	}
	else if (readBit('C',(unsigned char)room_pin)==1)
	{
		LCD_printString("Light is ON");
		LCD_moveCursor(2,1);
	}
	
	LCD_printString("1-ON   2-OFF");
	do
	{
		keypad_value = keypadRead();
		_delay_ms(250);
	} while (keypad_value == 'Z');
	
	if (keypad_value == '1')
	{
		setBit('C',(unsigned char)room_pin);
	}
	else if (keypad_value == '2')
	{
		clearBit('C',(unsigned char)room_pin);
	}
	
}

void control_Air_conditioner()
{
	unsigned char keypad_value , i = 100;
	air_conditioner_temperature = 0;
	clearScreen();
	LCD_printString("Temperature = --");
	LCD_moveCursor(1,15);
	
	while(i > 1)
	{
		i = i / 10;
		do
		{
			keypad_value = keypadRead();
			_delay_ms(250);
		} while (keypad_value == 'Z');
		
		LCD_printCharacter(keypad_value);
		
		air_conditioner_temperature += (keypad_value - 48) * i;
	}
	_delay_ms(500);
}

ISR(TIMER0_COMP_vect)
{
	++counter;
}