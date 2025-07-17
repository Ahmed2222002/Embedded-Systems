# ATMega32 LCD Module Test Project

## Overview
This project implements an LCD driver for the ATMega32 microcontroller, enabling control of a 16x2 LCD display in either 4-bit or 8-bit mode. The driver supports initialization, sending commands, displaying characters and strings, moving the cursor, and clearing the screen. The hardware interface is configurable, allowing users to specify the ports and pins used for the LCD connection.

## Project Structure
The project consists of the following files:
- **LCD.c**: Implementation of LCD initialization, command sending, and display functions.
- **LCD.h**: Header file declaring LCD function prototypes.
- **LCD_Hardware_Interface.h**: Configuration file for defining LCD pin connections and operating mode (4-bit or 8-bit).
- **DIO_Module.c**: Implementation of Digital Input/Output (DIO) functions for controlling ATMega32 ports and pins (assumed, based on inclusion).
- **DIO_Module.h**: Header file for DIO module (assumed, based on inclusion).
- **macros.h**: Utility macros for bit manipulation (assumed, based on inclusion).

## Hardware Requirements
- ATMega32 microcontroller
- 16x2 LCD display
- Connections to the ATMega32 as defined in `LCD_Hardware_Interface.h`:
  - Default: LCD data pins (D4–D7 or D0–D7) to Port A, Register Select (RS) to Port B, Pin 1, and Enable (E) to Port B, Pin 0.
  - Pull-up resistors (if needed) for control pins (RS and E).
- Power supply and necessary connections for the ATMega32
- Crystal oscillator (8 MHz, as defined by `F_CPU 8000000UL`)

## Software Requirements
- AVR-GCC compiler
- AVR Libc library
- Programming tool (e.g., AVRISP mkII or USBasp) for uploading code to the ATMega32

## Setup and Configuration
1. **Connect Hardware**:
   - Connect the LCD to the ATMega32 as specified in `LCD_Hardware_Interface.h`:
     - `LCD_CONNECTED_PORT`: Port for LCD data pins (default: Port A).
     - `LCD_PINS`: Set to 4 for 4-bit mode or 8 for 8-bit mode (default: 4).
     - `IS_CONNECTED_TO_HIGH_PINS`: For 4-bit mode, set to 0 for low pins (0–3) or 1 for high pins (4–7) of the port (default: 1).
     - `REGESTER_SELECT_PORT` and `REGESTER_SELECT_PIN`: Port and pin for RS (default: Port B, Pin 1).
     - `ENABEL_PORT` and `ENABEL_PIN`: Port and pin for Enable (default: Port B, Pin 0).
   - Ensure the ATMega32 is powered and connected to the programming tool.

2. **Compile and Upload**:
   - Compile the code using AVR-GCC.
   - Upload the compiled binary to the ATMega32 using a compatible programmer.

3. **LCD Configuration**:
   - The driver supports both 4-bit and 8-bit modes, configurable via `LCD_PINS` in `LCD_Hardware_Interface.h`.
   - In 4-bit mode, the LCD can be connected to either the low (pins 0–3) or high (pins 4–7) nibble of the specified port.
   - The driver initializes the LCD with:
     - 8-bit or 4-bit mode command.
     - Cursor on, display on (`CURSOR_ON_DISPLAN_ON`).
     - Clear screen.
     - Entry mode (left-to-right text).
   - Timing delays are included to ensure reliable LCD operation.

4. **Program Behavior**:
   - `LCD_Initialization()`: Configures the LCD and sets up the specified pins as outputs.
   - `LCD_sendCommand()`: Sends commands (e.g., clear screen, move cursor) to the LCD.
   - `LCD_printCharacter()`: Displays a single character.
   - `LCD_printString()`: Displays a null-terminated string.
   - `LCD_moveCursor()`: Moves the cursor to a specified row (1 or 2) and column (1–16).
   - `clearScreen()`: Clears the display and resets the cursor.

## Usage
- Initialize the LCD using `LCD_Initialization()` to set up the display.
- Use `LCD_printString()` to display text, `LCD_printCharacter()` for single characters, or `LCD_sendCommand()` for custom commands.
- Move the cursor with `LCD_moveCursor(row, column)` to position text on the 16x2 display.
- Clear the screen with `clearScreen()` when needed.
- Modify `LCD_Hardware_Interface.h` to change the LCD pin connections or mode.

## Code Example
```c
#include "LCD.h"

int main(void)
{
    LCD_Initialization(); // Initialize LCD
    while (1)
    {
        clearScreen(); // Clear the screen
        LCD_printString("Hello, ATMega32!"); // Display a string
        LCD_moveCursor(2, 1); // Move cursor to second row, first column
        LCD_printString("LCD Test"); // Display another string
        _delay_ms(2000); // Wait 2 seconds
    }
}
```

## Notes
- The LCD driver assumes a 16x2 LCD display. For other display sizes, adjust commands in `LCD.c` as needed.
- The `LCD_Hardware_Interface.h` file provides a flexible interface for pin configuration. Ensure the settings match the physical connections.
- In 4-bit mode, the driver sends data in two nibbles (high nibble first, then low nibble). Ensure the correct nibble is selected via `IS_CONNECTED_TO_HIGH_PINS`.
- The driver includes delays (`_delay_ms()`) to meet LCD timing requirements. Adjust these if using a different clock frequency.
- The ATMega32 is assumed to run at 8 MHz (`F_CPU 8000000UL`). Ensure the clock frequency is correctly configured.
- If `IS_CONNECTED_TO_HIGH_PINS` is not set correctly for 4-bit mode, a warning is generated during compilation.

## License
This project is licensed under the MIT License.
