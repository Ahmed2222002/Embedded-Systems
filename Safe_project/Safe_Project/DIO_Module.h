/*
 * DIO_Module.h
 *
 * Created: 10/8/2023 12:08:07 AM
 *  Author: Ahmed Hussien
 */ 


#ifndef DIO_MODULE_H_
#define DIO_MODULE_H_

/*
Function Name : setBitDirection
Function Return : Void
Function Arguments : char portName , int pinNumber , char direction
Function Description : Set the direction of the given pin in the given port (direction 0 = input : 1 = output)
*/
void setBitDirection(char port , int bitNumber , char direction);

/*
Function Name : setBortDirection
Function Return : Void
Function Arguments : char portName ,  char direction
Function Description : Set the direction of the given port in the MC (direction 0 = input : 1 = output)
*/
void setBortDirection(char port , char direction);

/*
Function Name : setBit
Function Return : Void
Function Arguments : char portName , int pinNumber
Function Description : Set logic high (5V) in given pin in given port
*/
void setBit(char port , int bitNumber);

/*
Function Name : writePort
Function Return : Void
Function Arguments : char portName , char value
Function Description : write certain value on certain port
*/
void writePort(char port , char value);

/*
Function Name : writeHigh_4pins
Function Return : Void
Function Arguments : char portName , char value
Function Description : write the first 4 bits in certain value on the fist 4 pins of any port
*/
void writeLow_4pins(char port, char value);

/*
Function Name : writeHigh_4pins
Function Return : Void
Function Arguments : char portName , char value
Function Description : write the first 4 bits in certain value-->(not the last 4 bits becarfull) on the last 4 pins of any port
*/
void writeHigh_4pins(unsigned char port,unsigned char value);

/*
Function Name : clearBit
Function Return : Void
Function Arguments : char portName , int pinNumber
Function Description : Set logic low (0V) in given pin in given port
*/
void clearBit(char port , int bitNumber);

/*
Function Name : clearPort
Function Return : Void
Function Arguments : char portName
Function Description : Set logic low (0V) in given port in MC
*/
void clearPort(char port);

/*
Function Name : toggelBit
Function Return : Void
Function Arguments : char portName , int pinNumber
Function Description : make volt change between(0V to 5V)  in given pin in given port
*/
void toggelBit(char port , int bitNumber);


/*
Function Name : toggelPort
Function Return : Void
Function Arguments : char portName
Function Description : make volt change between(0V to 5V)  in given port in MC
*/
void toggelPort(char port);

/*
Function Name : readBit
Function Return : char
Function Arguments : char portName , int pinNumber
Function Description : read the value of the volt on given pin in given port
*/
char readBit(char port , int bitNumber);

/*
Function Name : readPort
Function Return : char
Function Arguments : char portName
Function Description : read the value of the volt on given pin in given port
*/
unsigned char readPort (char port);

/*
Function Name : pullUpConnect
Function Return : Void
Function Arguments : char portName , int pinNumber , char enable
Function Description : Connect or Disconnect the internal pull up
*/
void pullUpConnect(char port , int bitNumber , char enable);

#endif /* DIO_MODULE_H_ */