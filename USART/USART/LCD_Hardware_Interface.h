/*
 * LCD_Hardware_Interface.h
 *
 * Created: 11/9/2023 7:28:37 AM
 *  Author: Ahmed Hussien
 
 * This file simulate the idea of GUI in software application and allow you to define which ATMEGA32 pins 
   you want to connect LCD on
   
 * How it work 
 
    1-Use LCD_CONNECTED_PORT macro to select which port of ATMEGA32 you will connect LCD on
   
    2-Use macro LCD_PINS to define how many pins you need to connect LCD
	  --> 4 means that LCD work in 4-bit mode
	  --> 8 means that LCD work in 8-bit mode
	  --> otherwise will generate warning or the LCD not work
	 
	3-IF you want to work with 4-bit mode then you need to  use IS_CONNECTED_TO_HIGH_PINS macro
	   to define which pins you will connect LCD
	   0 mean that you will connect (D4,D5,D6,D7) of LCD to first 4-pins of selected port in the MC
	   1 mean that you will connect (D4,D5,D6,D7) of LCD to last 4-pins of selected port in the MC
 
	   note: If you want to work with 8-bit mode then any value of IS_CONNECTED_TO_HIGH_PINS macro not effected
   
    4-Use REGESTER_SELECT_PORT macro to define which port of MC you will connect register select pin of LCD
	
	5-Use REGESTER_SELECT_PIN macro to define which PIN of MC you will connect register select pin of LCD
	
	6-Use ENABEL_PORT macro to define which port of MC you will connect ENABEl PIN of LCD
	
	7-Use ENABEL_PIN macro to define which PIN of MC you will connect ENABEl PIN of LCD
	
	note: the default is 
	LCD connected to last 4-pins of port A 
	register select pin connect to port B pin 1
	enable pin connect to port B 0s
 */ 


#ifndef LCD_HARDWARE_INTERFACE_H_
#define LCD_HARDWARE_INTERFACE_H_


#define LCD_CONNECTED_PORT 'A'
#define LCD_PINS 4
#define IS_CONNECTED_TO_HIGH_PINS 1
#define REGESTER_SELECT_PORT 'B'
#define REGESTER_SELECT_PIN 1
#define ENABEL_PORT 'B'
#define ENABEL_PIN 0

#endif /* LCD_HARDWARE_INTERFACE_H_ */