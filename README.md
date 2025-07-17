# ATMega32 LM35 Temperature Sensor Project

## Overview
This project implements a temperature monitoring system using the LM35 temperature sensor interfaced with the ATMega32 microcontroller. The system reads analog voltage from the LM35 via the ADC, converts it to a temperature value, and displays it on a 16x2 LCD. The temperature is shown in degrees Celsius, with support for both positive and negative values.

## Image
![ATMega32 LM35 Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/LM35_Temperature_sensor/image1.png)
![ATMega32 LM35 Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/LM35_Temperature_sensor/image2.png)


## Project Structure
The project consists of the following files:
- **main.c**: Main application file that initializes the LCD and ADC, reads temperature data, and displays it on the LCD.
- **LCD.c**: Implementation of LCD control functions for initialization and displaying text (assumed, based on inclusion).
- **LCD.h**: Header file declaring LCD function prototypes (assumed, based on inclusion).
- **ADC2_driver.h**: Header file for ADC driver functions (assumed, based on inclusion).
- **DIO_Module.c**: Implementation of Digital Input/Output (DIO) functions for controlling ATMega32 ports and pins (assumed, based on LCD dependency).
- **DIO_Module.h**: Header file for DIO module (assumed, based on LCD dependency).
- **LCD_Hardware_Interface.h**: Configuration file for LCD pin connections (assumed, based on LCD dependency).
- **macros.h**: Utility macros for bit manipulation (assumed, based on LCD and ADC dependencies).

## Hardware Requirements
- ATMega32 microcontroller
- LM35 temperature sensor connected to the ADC input (typically Port A, Pin 0)
- 16x2 LCD display connected to the ATMega32 (as configured in `LCD_Hardware_Interface.h`)
- Power supply and necessary connections for the ATMega32
- Crystal oscillator (8 MHz, as defined by `F_CPU 8000000UL`)

## Software Requirements
- AVR-GCC compiler
- AVR Libc library
- Programming tool (e.g., AVRISP mkII or USBasp) for uploading code to the ATMega32

## Setup and Configuration
1. **Connect Hardware**:
   - Connect the LM35 temperature sensor to the ADC input pin (typically Port A, Pin 0). Ensure the LM35’s output pin is connected, with VCC and GND appropriately wired.
   - Connect the 16x2 LCD to the ATMega32 as defined in `LCD_Hardware_Interface.h` (default: Port A for data, Port B for RS and E pins).
   - Ensure the ATMega32 is powered and connected to the programming tool.

2. **Compile and Upload**:
   - Compile the code using AVR-GCC.
   - Upload the compiled binary to the ATMega32 using a compatible programmer.

3. **System Configuration**:
   - **LCD**: Initialized using `LCD_Initialization()` to set up the display in 4-bit or 8-bit mode (as configured in `LCD_Hardware_Interface.h`).
   - **ADC**: Initialized using `ADC_initialization()` to read analog voltage from the LM35 (assumed to be on Port A, Pin 0).
   - **Temperature Calculation**: The ADC value (10-bit) is converted to millivolts using `ADC_read() * 2.5`. The temperature is calculated as `(millivolts - 1000) / 10` for positive temperatures or `(1000 - millivolts) / 10` for negative temperatures, with 1000 mV corresponding to 0°C.

4. **Program Behavior**:
   - The LCD displays "temp = " on the first row.
   - The temperature is continuously updated on the LCD, starting at column 8 of the first row.
   - For temperatures below 0°C, a minus sign is displayed, followed by the temperature value.
   - For temperatures above 0°C, only the value is shown.
   - Single-digit temperatures (e.g., 5°C) are displayed with one digit, while double-digit temperatures (e.g., 25°C) use two digits, followed by the degree symbol (°C).
   - At exactly 0°C, "0°C" is displayed.

## Usage
- Initialize the system using `LCD_Initialization()` and `ADC_initialization()`.
- The program continuously reads the LM35 output via the ADC, converts it to a temperature value, and displays it on the LCD.
- The temperature is updated in real-time, with proper formatting for negative, zero, and positive values.
- Modify the ADC scaling factor (2.5 mV per ADC unit) or temperature calculation in `main.c` if using a different sensor or reference voltage.

## Code Example
```c
#include "LCD.h"
#include "ADC2_driver.h"

int main(void)
{
    clearScreen();
    LCD_Initialization(); // Initialize LCD
    ADC_initialization(); // Initialize ADC
    LCD_printString("temp = "); // Display static label
    unsigned short mille_volt;
    char temperature;
    while (1)
    {
        mille_volt = ADC_read() * 2.5; // Convert ADC value to millivolts
        if (mille_volt < 1000) // Negative temperature
        {
            temperature = (1000 - mille_volt) / 10;
            LCD_moveCursor(1, 8);
            LCD_printCharacter('-');
            if (temperature < 10)
                LCD_printCharacter(temperature + 48);
            else
            {
                LCD_printCharacter((temperature / 10) + 48);
                LCD_printCharacter((temperature % 10) + 48);
            }
            LCD_printCharacter(0xdf); // Degree symbol
            LCD_printCharacter('C');
            LCD_printCharacter(0x20); // Space
        }
        // Similar logic for positive and zero temperatures
    }
}
```

## Notes
- The LM35 outputs 10 mV per °C, with 0 V at 0°C. The ADC value is scaled by 2.5 mV (assuming a 2.56 V reference voltage or similar). Verify the reference voltage in `ADC2_driver.h` and adjust the scaling factor if necessary.
- The LCD is assumed to be configured as per `LCD_Hardware_Interface.h`. Ensure the pin connections match the hardware setup.
- The degree symbol is displayed using the LCD’s custom character code `0xdf`. Confirm compatibility with your LCD.
- The program handles temperatures from -99°C to 99°C. For wider ranges, modify the display logic in `main.c`.
- The ATMega32 is assumed to run at 8 MHz (`F_CPU 8000000UL`). Ensure the clock frequency is correctly configured.

## License
This project is licensed under the MIT License.
