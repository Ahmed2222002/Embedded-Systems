# ATMega32 Keypad Module Test Project

## Overview
This project implements a keypad driver for the ATMega32 microcontroller, enabling interaction with a 4x4 keypad connected to Port D. The driver initializes the keypad and provides a function to read key presses, mapping them to a predefined character array. This module is designed for use in applications requiring user input, such as password entry or menu navigation.

## Image
![ATMega32 Keypad Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/keypad_Driver/image.png)


## Project Structure
The project consists of the following files:
- **keypad.c**: Implementation of keypad initialization and reading functions.
- **keypad.h**: Header file declaring keypad function prototypes.
- **DIO_Module.c**: Implementation of Digital Input/Output (DIO) functions for controlling ATMega32 ports and pins (assumed, based on inclusion).
- **DIO_Module.h**: Header file for DIO module (assumed, based on inclusion).
- **macros.h**: Utility macros for bit manipulation (assumed, based on inclusion).

## Hardware Requirements
- ATMega32 microcontroller
- 4x4 keypad connected to Port D (pins 0–7)
- Pull-up resistors (internal pull-ups are enabled in the code)
- Power supply and necessary connections for the ATMega32
- Crystal oscillator (8 MHz, as assumed by the ATMega32 configuration)

## Software Requirements
- AVR-GCC compiler
- AVR Libc library
- Programming tool (e.g., AVRISP mkII or USBasp) for uploading code to the ATMega32

## Setup and Configuration
1. **Connect Hardware**:
   - Connect a 4x4 keypad to Port D of the ATMega32:
     - Rows connected to pins PD0–PD3 (output pins).
     - Columns connected to pins PD4–PD7 (input pins with internal pull-ups).
   - Ensure the ATMega32 is powered and connected to the programming tool.

2. **Compile and Upload**:
   - Compile the code using AVR-GCC.
   - Upload the compiled binary to the ATMega32 using a compatible programmer.

3. **Keypad Configuration**:
   - The keypad is connected to Port D (`connected_port` defined as 'D').
   - Pins PD0–PD3 are configured as outputs for driving rows.
   - Pins PD4–PD7 are configured as inputs with internal pull-up resistors enabled.
   - The keypad layout is mapped to a 4x4 character array in software, as shown below:
     ```
     Software Layout:
     {'7', '8', '9', '/'}
     {'4', '5', '6', '*'}
     {'1', '2', '3', '-'}
     {'c', '0', '=', '+'}
     ```

4. **Program Behavior**:
   - The `keypadInitialization()` function sets up Port D pins for keypad operation.
   - The `keypadRead()` function scans the keypad by activating each row (setting it low) and checking column inputs for a key press.
   - When a key is pressed, the corresponding character from the software layout is returned. If no key is pressed, 'Z' is returned.

## Usage
- Initialize the keypad using `keypadInitialization()` to configure Port D pins.
- Use `keypadRead()` to detect key presses. The function returns a character corresponding to the pressed key or 'Z' if no key is pressed.
- Integrate the keypad driver into applications requiring user input, such as password entry or menu selection.
- The keypad layout can be modified by updating the `arr` array in `keypadRead()` to match the physical keypad's labeling.

## Code Example
```c
#include "keypad.h"

int main(void)
{
    keypadInitialization(); // Initialize keypad on Port D
    while (1)
    {
        unsigned char key = keypadRead(); // Read key press
        if (key != 'Z')
        {
            // Process the key (e.g., display on LCD or use in application logic)
            // Example: LCD_printCharacter(key); (assuming LCD.h is included)
        }
    }
}
```

## Notes
- The keypad driver assumes a 4x4 keypad with the specified software layout. If the physical keypad has a different layout, update the `arr` array in `keypad.c`.
- Internal pull-up resistors are enabled for input pins (PD4–PD7). External pull-up resistors are not required unless the internal ones are insufficient.
- The `keypadRead()` function includes a software layout that differs from the commented hardware layout. Ensure the software layout matches the physical keypad for correct operation.
- The driver does not include debouncing logic. For robust applications, consider adding a small delay or debouncing mechanism to handle key bounce.
- The ATMega32 is assumed to run at 8 MHz, as typical for such projects. Ensure the clock frequency is correctly configured.


## License
This project is licensed under the MIT License.
