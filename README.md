# AVR Digital Clock with Keypad and LCD

## Description
This project implements a digital clock using an **AVR microcontroller**, a **4x4 keypad**, an **LCD display**, and a **seven-segment display**. The user can set the time using the keypad, and the clock keeps track of time using **Timer2**. The project is written in C for **AVR microcontrollers**.


![screen shot](https://github.com/Ahmed2222002/Embedded-Systems/blob/Real_time_clock_project/image.png?raw=true)

## Features
- **Real-time clock functionality** using Timer2.
- **LCD display** for user interaction.
- **Seven-segment display** to show time.
- **Keypad input** to modify the clock settings.
- **Digital I/O control** using custom `DIO_Module` functions.

## Project Files
| File                 | Description |
|----------------------|-------------|
| `main.c`            | Contains the main logic for the digital clock, keypad input handling, and seven-segment display updates. |
| `DIO_Module.c`      | Handles digital input/output operations, including setting pin directions and writing to ports. |
| `keypad.c`          | Implements keypad scanning and key detection. |
| `LCD.c`             | Manages LCD display commands, including printing characters and clearing the screen. |
| `sevenSegment.c`    | Controls a seven-segment display for visualizing time. |
| `timer2_driver.c`   | Configures and manages **Timer2** for real-time clock functionality. |

## Hardware Components
- **Microcontroller** (AVR, e.g., ATmega32)
- **4x4 Keypad** for user input
- **16x2 LCD Display**
- **Common Cathode/Anode Seven-Segment Display**
- **External Clock (for Timer2, optional)**
- **Push buttons & Resistors**
- **Power Supply (5V)**

## How It Works
1. The system initializes the **LCD**, **seven-segment display**, **keypad**, and **timer**.
2. The **keypad** allows the user to modify hours and minutes.
3. The **seven-segment display** continuously updates to show real-time seconds, minutes, and hours.
4. **Timer2** generates interrupts to increment time.
5. The **LCD** provides instructions and feedback to the user.

## How to Use
1. Power on the system.
2. Press the **"C" key** on the keypad to enter time-setting mode.
3. Enter hours (two digits) using the keypad.
4. Enter minutes (two digits) using the keypad.
5. The clock starts automatically after setting the time.
6. The seven-segment display continuously updates time.

## Future Improvements
- Implement **AM/PM mode**.
- Add an **alarm feature**.
- Improve **power efficiency**.
- Include **external EEPROM** for time retention during power loss.

## Author
Ahmed Hussien


