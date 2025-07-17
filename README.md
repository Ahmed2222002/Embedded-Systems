# ATMega32 DIO Module Test Project

## Overview
This project demonstrates the implementation and testing of the Digital Input/Output (DIO) module on the ATMega32 microcontroller. The code provides a driver for controlling the DIO ports and pins, along with LED control functions to create a sequential lighting pattern across multiple ports. The program sequentially turns on and off LEDs connected to Ports A, B, C, and D, creating a visual effect.

## Image
![ATMega32 DIO LED Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/DIO_Driver/image.png)


## Project Structure
The project consists of the following files:
- **main.c**: Main application file that initializes the DIO module and controls LEDs on Ports A, B, C, and D in a sequential pattern.
- **DIO_Module.c**: Implementation of DIO functions for configuring and controlling ATMega32 ports and pins.
- **DIO_Module.h**: Header file for the DIO module, declaring function prototypes.
- **macros.h**: Utility macros for bit manipulation operations (assumed to be included, though not provided).


## Code Example
```c
int main(void)
{
    char port = 'A';
    char count = 1;
    signed char i = 0;
    leds8_Initilize('A', '1'); // Initialize Port A as output
    leds8_Initilize('B', '1'); // Initialize Port B as output
    leds8_Initilize('C', '1'); // Initialize Port C as output
    leds8_Initilize('D', '1'); // Initialize Port D as output
    while(1)
    {
        switch (count)
        {
            case 1 ... 4:
                for (i = 0; i < 8; i++)
                {
                    ledOn(port, i); // Turn on LED on current port, pin i
                    _delay_ms(ledDelay);
                }
                ++port;
                ++count;
                break;
            case 5 ... 8:
                if (port == 'E') port = 'D';
                for(i = 7; i >= 0; i--)
                {
                    ledOff(port, i); // Turn off LED on current port, pin i
                    _delay_ms(ledDelay);
                }
                --port;
                ++count;
                break;
            default:
                count = 1;
                port = 'A';
        }
    }
}
```
