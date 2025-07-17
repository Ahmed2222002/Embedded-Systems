/*
 * LCD.c
 *
 * Created: 11/1/2023 9:54:36 PM
 * Author : hp
 */ 

#define  F_CPU 8000000UL 
#include "LCD.h"
#include <util/delay.h>

// go to LCD_Hardware_Interface.h
int main(void)
{
   /* LCD_Initialization();
	LCD_printString("Ahmed");
	_delay_ms(1000);
	LCD_printString("Hussien");
    LCD_moveCursor(2,1);
	LCD_printString("Embedded Systems");
	_delay_ms(1000);
	clearScreen();
	*/
   LCD_Initialization();
   
   LCD_printString("     HELLO     ");
   _delay_ms(1000);
   clearScreen();
   
   LCD_printString("This is the");
   LCD_moveCursor(2,1);
   LCD_printString("First LCD project");
   _delay_ms(3000);
   
   clearScreen();
   LCD_moveCursor(1,1);
   LCD_printString("Developed by ENG");
   LCD_moveCursor(2,1);
   LCD_printString(" Ahmed Hussien");
   _delay_ms(3000);
   
   clearScreen();
   LCD_moveCursor(1,1);
   LCD_printString(" Thank you for ");
   LCD_moveCursor(2,1);
   LCD_printString("    watching    ");
   _delay_ms(1000);
   clearScreen();
   
  /*while(1)
  {
	  LCD_sendCommand(0x1C);
	  _delay_ms(500);
  }*/
}

