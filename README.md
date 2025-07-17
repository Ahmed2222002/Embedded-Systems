

# ATMega32 ADC Module Test Project

## Overview
This project demonstrates the implementation and testing of the Analog-to-Digital Converter (ADC) module on the ATMega32 microcontroller. The code provides a driver for the ADC and Digital Input/Output (DIO) modules, enabling the reading of analog signals from a specified pin and outputting the digital result to a port.


## Image
![ATMega32 ADC Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/ADC_Driver/image.png)

## Project Structure
The project consists of the following files:
- **main.c**: Main application file that initializes the ADC and DIO modules and continuously reads ADC values to output on Port D.
- **ADC_driver.c**: Implementation of ADC initialization and reading functions.
- **ADC_driver.h**: Header file for the ADC driver, declaring function prototypes.
- **DIO_Module.c**: Implementation of DIO functions for configuring and controlling ATMega32 ports and pins.
- **DIO_Module.h**: Header file for the DIO module, declaring function prototypes.
- **macros.h**: Utility macros for bit manipulation operations.

## Hardware Requirements
- ATMega32 microcontroller
- Analog input source (e.g., potentiometer or sensor) connected to Port A, Pin 0
- Output device (e.g., LEDs or display) connected to Port D
- Power supply and necessary connections for the ATMega32

## Software Requirements
- AVR-GCC compiler
- AVR Libc library
- Programming tool (e.g., AVRISP mkII or USBasp) for uploading code to the ATMega32

## Setup and Configuration
1. **Connect Hardware**:
   - Connect an analog input source to Port A, Pin 0 (PA0).
   - Connect output devices (e.g., LEDs) to Port D to observe the ADC output.
   - Ensure the ATMega32 is powered and properly connected to the programming tool.

2. **Compile and Upload** essentials:
   - Compile the code using AVR-GCC.
   - Upload the compiled binary to the ATMega32 using a compatible programmer.

3. **ADC Configuration**:
   - The ADC is initialized with a prescaler of 64 and uses AVCC as the voltage reference.
   - The analog input is read from PA0 (default pin).
   - The ADC result is right-adjusted (default setting).

4. **DIO Configuration**:
   - Port A, Pin 0 is set as input for the ADC.
   - Port D is set as output to display the ADC value.

## Usage
- The program continuously reads the analog input from PA0 using the ADC.
- The ADC value (10-bit) is written to Port D, where it can be observed (e.g., via LEDs or a display).
- Modify the `ADC_initialization` parameters in `main.c` to change the input pin or prescaler if needed.

## Code Example
```c
int main(void)
{
    setBitDirection('A', 0, '0'); // Set PA0 as input
    ADC_initialization('0', '64'); // Initialize ADC on PA0 with prescaler 64
    setBortDirection('D', '1');   // Set Port D as output
    while (1)
    {
        unsigned short adc_val = readADC(); // Read ADC value
        writePort('D', adc_val);            // Output ADC value to Port D
    }
}
```

## Notes
- The ADC result is right-adjusted by default. To use left-adjusted results, modify the `lift_adjust` macro in `ADC_driver.c` to `1`.
- Ensure the analog input voltage does not exceed the reference voltage (AVCC, typically 5V).
- The prescaler value can be adjusted in `ADC_initialization` to change the ADC conversion speed.


