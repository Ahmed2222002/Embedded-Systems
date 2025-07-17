# ATMega32 Smart Home System Project

## Overview
This project implements a smart home system on the ATMega32 microcontroller, featuring password-protected access, LCD display, keypad input, ADC-based temperature monitoring, and control of lights and an air conditioner. The system allows users to set an admin password, control room lighting, and adjust air conditioner settings based on temperature readings.

## Image
![ATMega32 Smart Home Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/smart_Home_Project/image.png)

## Project Structure
The project consists of the following files:
- **main.c**: Main application file that handles system initialization, password management, and user interface for controlling lights and air conditioner.
- **ADC_driver.c**: Implementation of ADC initialization and reading functions for temperature measurement (assumed, based on inclusion).
- **ADC_driver.h**: Header file for ADC driver (assumed, based on inclusion).
- **DIO_Module.c**: Implementation of DIO functions for controlling ATMega32 ports and pins (assumed, based on inclusion).
- **DIO_Module.h**: Header file for DIO module (assumed, based on inclusion).
- **EEPROM_driver.h**: Header file for EEPROM read/write functions (assumed, based on inclusion).
- **keypad.h**: Header file for keypad input functions (assumed, based on inclusion).
- **LCD.h**: Header file for LCD display functions (assumed, based on inclusion).
- **timer0_driver.h**: Header file for Timer0 configuration (assumed, based on inclusion).
- **macros.h**: Utility macros for bit manipulation (assumed, based on inclusion).

## Hardware Requirements
- ATMega32 microcontroller
- 16x2 LCD display connected to the microcontroller
- 4x4 keypad for user input
- Temperature sensor (e.g., LM35) connected to Port A, Pin 0 for ADC input
- LEDs or relays connected to Port C (pins 4–7) for light control
- Air conditioner control output connected to Port C, Pin 0
- Power supply and necessary connections for the ATMega32
- Crystal oscillator (8 MHz, as defined by `F_CPU 8000000UL`)

## Software Requirements
- AVR-GCC compiler
- AVR Libc library
- Programming tool (e.g., AVRISP mkII or USBasp) for uploading code to the ATMega32

## Setup and Configuration
1. **Connect Hardware**:
   - Connect the LCD display to the appropriate microcontroller pins (as defined in `LCD.h`).
   - Connect the 4x4 keypad to the microcontroller (as defined in `keypad.h`).
   - Connect a temperature sensor to Port A, Pin 0 for ADC input.
   - Connect LEDs or relays to Port C, pins 4–7, for controlling lights in four rooms.
   - Connect an air conditioner control output (e.g., relay) to Port C, Pin 0.
   - Ensure the ATMega32 is powered and connected to the programming tool.

2. **Compile and Upload**:
   - Compile the code using AVR-GCC.
   - Upload the compiled binary to the ATMega32 using a compatible programmer.

3. **System Configuration**:
   - **ADC**: Initialized on Port A, Pin 0 with a prescaler of 64 for temperature sensor readings.
   - **DIO**: Port A, Pin 0 is set as input for ADC; Port C, Pin 0 is set as output for air conditioner control; Port C, pins 4–7 are set as outputs for light control.
   - **Timer0**: Configured in CTC mode with a prescaler of 5 and OCR0 value of 78 for timing operations (e.g., system pause).
   - **EEPROM**: Used to store the admin password and a flag to check if the system is initialized for the first time.
   - **LCD and Keypad**: Initialized for user interface and input handling.

4. **Program Behavior**:
   - On first boot, the system prompts the user to set a 4-digit admin password, stored in EEPROM.
   - Users must enter the correct password (with up to 5 attempts) to access the main menu.
   - If 5 incorrect attempts are made, the system pauses for 20 seconds.
   - The main menu allows users to:
     - Control lights in four rooms (turn on/off via Port C, pins 4–7).
     - Set the air conditioner temperature, which is compared with the ADC-measured temperature to control the air conditioner output (Port C, Pin 0).
   - Temperature is read continuously via ADC and scaled by 0.25 for display.

## Usage
- **Password Setup**: On first boot, enter a 4-digit numeric password using the keypad. Use 'c' for backspace.
- **Password Check**: Enter the 4-digit password to access the main menu. After 5 failed attempts, the system pauses for 20 seconds.
- **Main Menu**: Select:
  - `1` to control lights (choose room 1–4, then turn on or off).
  - `2` to set the air conditioner temperature (enter a two-digit value).
- The system automatically turns the air conditioner on/off based on the comparison between the set temperature and the ADC-measured temperature.
- The LCD displays menus, prompts, and status messages.

## Code Example
```c
int main(void)
{
    LCD_Initialization();
    keypadInitialization();
    setBitDirection('A', 0, '0'); // Set PA0 as input for ADC
    ADC_initialization('0', '64'); // Initialize ADC on PA0 with prescaler 64
    setBitDirection('C', 0, '1'); // Set PC0 as output for air conditioner
    timer0_ctc_init(78, 5);       // Initialize Timer0 in CTC mode
    char is_frist_time, is_password_true, no_trails = 5, pause_time = 20;

    is_frist_time = EEPROM_read(flag);
    if (is_frist_time == 0xFF)
    {
        set_admian_password(); // Set initial password
    }
    while (1)
    {
        is_password_true = check_password();
        if (is_password_true == 1)
        {
            break;
        }
        else if (no_trails == 0)
        {
            pause_system(pause_time); // Pause for 20 seconds after 5 failed attempts
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
    while (1)
    {
        main_window(); // Display main menu and handle user input
    }
}
```

## Notes
- The system assumes a 4x4 keypad for input and a 16x2 LCD for output. Ensure these are correctly interfaced as per their respective drivers.
- The temperature is calculated as `0.25 * ADC_value`. Adjust the scaling factor in `main_window()` if the sensor requires a different calibration.
- The air conditioner control assumes a simple on/off mechanism. For real-world use, ensure proper relay or driver circuits are used.
- The `pause_system` function uses Timer0 to count seconds, triggered by the `TIMER0_COMP_vect` ISR.
- The `wrong_choice` constant is used to handle invalid keypad inputs in the light control menu.
- Ensure the ATMega32 is running at 8 MHz, as defined by `F_CPU`.


## License
This project is licensed under the MIT License.
