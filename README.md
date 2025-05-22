```markdown
# Input Capture Unit with ATmega32 and LCD

This project implements an **Input Capture Unit (ICU)** using the **ATmega32** microcontroller to measure the frequency and duty cycle of an input signal. The results are displayed on a **16x2 LCD** in 4-bit mode. The project includes a hardware abstraction layer for LCD interfacing and a digital I/O module for flexible pin configuration. The simulation is designed and tested using **Proteus**, as shown in the provided design image.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [File Structure](#file-structure)
- [Setup Instructions](#setup-instructions)
- [How It Works](#how-it-works)
- [Proteus Simulation](#proteus-simulation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

---

## Project Overview

The project uses the **ATmega32's Timer1 Input Capture Unit** to measure the period and high time of an input signal, calculating its frequency and duty cycle. The results are displayed on an LCD configured in **4-bit mode**, connected to the microcontroller's **PORTA (high pins: D4-D7)**.

The code is modular, with separate modules for:
- LCD interfacing
- Digital I/O operations
- Macro utilities

---

## Features

- Measures frequency and duty cycle of an input signal using **Timer1's ICU**
- Displays results on a **16x2 LCD in 4-bit mode**
- Configurable LCD pin connections via `LCD_Hardware_Interface.h`
- Modular code with reusable **DIO (Digital Input/Output)** and **LCD modules**
- Supports both **4-bit and 8-bit LCD modes** (configurable in header file)
- Error handling for out-of-range measurements

---

## Hardware Requirements

- **Microcontroller:** ATmega32
- **LCD:** 16x2 LCD (e.g., HD44780-compatible)
- **Signal Source:** PWM or square wave signal for input capture
- **Crystal Oscillator:** 8 MHz (defined as `F_CPU` in the code)
- **Other Components:** Resistors, capacitors, and connections as per the Proteus schematic

---

## Software Requirements

- **Compiler:** AVR-GCC
- **IDE:** AVR Studio, Atmel Studio, or any AVR-compatible IDE
- **Simulation Tool:** Proteus (for testing the design)
- **Programmer:** AVRISP, USBasp, or any compatible programmer for flashing the ATmega32

---

## File Structure

```
├── DIO_Module.c                # Digital I/O module for pin manipulation
├── DIO_Module.h                # Header for DIO module
├── LCD.c                       # LCD driver implementation
├── LCD_Hardware_Interface.h    # LCD pin configuration
├── main.c                      # Main program for ICU and LCD display
├── macros.h                    # Utility macros for bit manipulation
└── image.png                   # Proteus simulation schematic
```

---

## Setup Instructions

### Clone the Repository

```bash
git clone https://github.com/Ahmed2222002/Embedded-Systems.git
cd Embedded-Systems/Input_Capture_Uint/
```

### Configure Hardware

- Connect the LCD to the ATmega32 as specified in `LCD_Hardware_Interface.h`:
  - Data pins (**D4-D7**) to **PORTA pins 4-7** (high pins, since `IS_CONNECTED_TO_HIGH_PINS` is set to `1`)
  - Register Select (**RS**) to **PORTB pin 1**
  - Enable (**E**) to **PORTB pin 0**

- Connect the input signal to the **ICP1 pin (PD6)** of the ATmega32 for input capture
- Ensure an **8 MHz crystal oscillator** is connected

### Compile the Code

```bash
avr-gcc -mmcu=atmega32 -O1 -o main.elf main.c LCD.c DIO_Module.c
```

### Convert the ELF file to HEX

```bash
avr-objcopy -O ihex main.elf main.hex
```

### Flash the Microcontroller

```bash
avrdude -c usbasp -p m32 -U flash:w:main.hex
```

### Simulate in Proteus (optional)

- Open the Proteus design file (refer to `image.png` for the schematic)
- Load the compiled `main.hex` into the ATmega32 in Proteus
- Simulate to verify the LCD output and signal measurements

---

## How It Works

### Initialization

- The LCD is initialized in **4-bit mode** using the settings in `LCD_Hardware_Interface.h`
- **Timer1** is configured for input capture with **no prescaler** and **noise canceler enabled**

### Signal Measurement

The ICU captures three timestamps:

1. **a**: First rising edge
2. **b**: Falling edge
3. **c**: Second rising edge

- **High time** = b - a
- **Period** = c - a
- **Frequency** = `F_CPU / period` (Hz)
- **Duty cycle** = `(high / period) * 100 (%)`

### Display

- LCD displays:
  - First row: Duty cycle (e.g., `"duty:75%"`)
  - Second row: Frequency (e.g., `"freq:1000HZ"`)

If the signal is invalid (e.g., `a >= b` or `b >= c`), the LCD shows `"out of range"`

---

## Proteus Simulation

The Proteus schematic for this project is available in the repository under `image.png`. It shows the **ATmega32** connected to the **LCD** and the **input signal source** for testing.

---

## Usage

1. Power on the circuit with the ATmega32 and LCD connected
2. Apply a **PWM or square wave signal** to the **ICP1 pin (PD6)**
3. The LCD will display:
   - **First row:** Duty cycle (e.g., `"duty:75%"`)
   - **Second row:** Frequency (e.g., `"freq:1000HZ"`)

If the signal is invalid, the LCD will show `"out of range"`

---

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a new branch (`git checkout -b feature-branch`)
3. Make your changes and commit (`git commit -m "Add feature"`)
4. Push to the branch (`git push origin feature-branch`)
5. Open a pull request

---

## License

This project is licensed under the **MIT License**. See the `LICENSE` file for details.
```
