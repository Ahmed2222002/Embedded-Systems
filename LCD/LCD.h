/*
 * LCD.h
 *
 * Created: 11/1/2023 9:55:34 PM
 *  Author: hp
 */ 


#ifndef LCD_H_
#define LCD_H_

void LCD_Initialization();
void LCD_sendCommand(char cmd);
void send_pulse();
void LCD_printCharacter(char character);
void LCD_printString(char* ptr);
void LCD_moveCursor(char row , char column);
void clearScreen();

#endif /* LCD_H_ */