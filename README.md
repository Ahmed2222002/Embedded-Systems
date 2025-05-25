# Safe Project

![Safe Project Screenshot](https://github.com/Ahmed2222002/Embedded-Systems/raw/Safe_Project/Screenshot.png)

## Overview
The Safe Project is an embedded system application designed for the ATmega32 microcontroller. It implements a password-protected safe system using a keypad for input, an LCD for display, and EEPROM for storing the password. The system allows users to set a 4-digit password, check it to unlock the safe, and reset the password if forgotten, with a lockout mechanism after multiple failed attempts.

## Features
- **Password Setting**: Users can set a 4-digit password, which is stored in the ATmega32's EEPROM.
- **Password Verification**: The system checks the entered password against the stored one to unlock the safe.
- **Lockout Mechanism**: After 5 failed attempts, the system locks for 20 seconds.
- **Password Reset**: Users can reset the password if forgotten by entering a specific key.
- **Visual Feedback**: An LCD displays prompts, password entry, and system status.
- **Indicator LEDs**: Connected to PORTA pins to indicate locked, unlocked, or error states.

## Hardware Components
- **ATmega32 Microcontroller**: The core processing unit.
- **4x4 Keypad**: Connected to PORTD for user input.
- **LCD Display**: Configured in 4-bit mode, connected to PORTA (high pins) for output display.
- **LEDs**: Connected to PORTA pins 0 (locked), 1 (error), and 2 (unlocked).
- **EEPROM**: Internal ATmega32 EEPROM for persistent password storage.

## Software Components
The project is written in C and consists of the following files:

- **main.c**: Main program logic for password handling, safe operation, and system flow.
- **EEPROM_driver.c**: Handles reading from and writing to the ATmega32 EEPROM.
- **keypad.c**: Manages keypad initialization and reading key presses.
- **LCD.c**: Controls the LCD for initialization, sending commands, and displaying characters/strings.
- **DIO_Module.c**: Provides digital I/O functions for port and pin manipulation.
- **macros.h**: Defines utility macros for bit manipulation.
- **LCD_Hardware_Interface.h**: Configures LCD pin connections and mode (4-bit or 8-bit).

## Functionality
1. **Initialization**:
   - On first boot, if the EEPROM status (address 0x00) is 0xFF, the user is prompted to set a 4-digit password.
   - The password is stored in EEPROM at addresses 0x01 to 0x04.

2. **Password Entry**:
   - Users enter a 4-digit password via the keypad.
   - Each key press is displayed briefly on the LCD, then masked with an asterisk (*) for security.
   - The entered password is compared with the stored one.

3. **Unlocking**:
   - If the password matches, the LCD displays "password is true" and "Safe is opened," and an LED on PORTA.2 is lit.
   - The system exits the main loop, indicating the safe is unlocked.

4. **Failed Attempts**:
   - If the password is incorrect, the number of remaining attempts decreases.
   - After 5 failed attempts, the system locks for 20 seconds, displaying a countdown on the LCD.

5. **Password Reset**:
   - During lockout, users can choose to reset the password by pressing '1' (yes) or '2' (no).
   - If '1' is pressed, the EEPROM status is set to 0xFF, prompting a new password setup.

## Setup Instructions
1. **Hardware Setup**:
   - Connect the 4x4 keypad to PORTD of the ATmega32 (first 4 pins as outputs, last 4 as inputs with pull-ups).
   - Connect the LCD in 4-bit mode to PORTA (pins 4-7), with Register Select (RS) on PORTB.1 and Enable (EN) on PORTB.0.
   - Connect LEDs to PORTA pins 0 (locked), 1 (error), and 2 (unlocked).
   - Ensure the ATmega32 is powered and clocked at 8 MHz (F_CPU defined as 8000000UL).

2. **Software Setup**:
   - Compile the project using an AVR-compatible compiler (e.g., AVR-GCC).
   - Upload the compiled code to the ATmega32 using a programmer (e.g., USBasp).
   - Ensure the following libraries are included:
     - `<util/delay.h>` for delays.
     - Custom headers: `DIO_Module.h`, `macros.h`, `LCD_Hardware_Interface.h`.

3. **Configuration**:
   - Verify the `LCD_Hardware_Interface.h` settings:
     - `LCD_CONNECTED_PORT` set to 'A'.
     - `LCD_PINS` set to 4 (4-bit mode).
     - `IS_CONNECTED_TO_HIGH_PINS` set to 1 (LCD connected to PORTA pins 4-7).
     - `REGESTER_SELECT_PORT` set to 'B', `REGESTER_SELECT_PIN` to 1.
     - `ENABEL_PORT` set to 'B', `ENABEL_PIN` to 0.
   - Adjust pin assignments in `LCD_Hardware_Interface.h` or `keypad.c` if using different ports.

4. **Operation**:
   - Power on the system.
   - If it's the first boot, set a 4-digit password using the keypad.
   - Enter the password to unlock the safe.
   - After 5 failed attempts, the system locks for 20 seconds, offering a reset option.

## Notes
- The keypad layout is software-defined in `keypad.c` as:
