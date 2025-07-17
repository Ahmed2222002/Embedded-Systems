# ATMega32 I2C Module Test Project

## Overview
This project implements and tests the Inter-Integrated Circuit (I2C) module on the ATMega32 microcontroller. The code provides a driver for I2C communication, supporting both master and slave modes. It includes functions for initializing the I2C module, sending and receiving data, and handling start/stop conditions. The driver is designed to facilitate communication between the ATMega32 (as master or slave) and other I2C-compatible devices, with LCD output for debugging or display purposes.

## Image
![ATMega32 I2C Setup](https://github.com/Ahmed2222002/Embedded-Systems/blob/I2C_Driver/image.png)

## Project Structure
The project consists of the following files:
- **i2c_driver.c**: Implementation of I2C functions for master and slave operations.
- **i2c_driver.h**: Header file declaring I2C function prototypes.
- **DIO_Module.c**: Implementation of Digital Input/Output (DIO) functions for pin and port control (assumed, based on inclusion).
- **DIO_Module.h**: Header file for DIO module (assumed, based on inclusion).
- **LCD.h**: Header file for LCD display functions (assumed, based on inclusion).
- **macros.h**: Utility macros for bit manipulation (assumed, based on inclusion).

## Hardware Requirements
- ATMega32 microcontroller
- I2C-compatible slave device (e.g., EEPROM, sensor, or another microcontroller)
- Pull-up resistors (4.7kΩ recommended) on SDA (Port C, Pin 1) and SCL (Port C, Pin 0)
- 16x2 LCD display (optional, for debugging or displaying I2C data)
- Power supply and necessary connections for the ATMega32
- Crystal oscillator (8 MHz, as defined by `F_CPU 8000000UL`)

## Software Requirements
- AVR-GCC compiler
- AVR Libc library
- Programming tool (e.g., AVRISP mkII or USBasp) for uploading code to the ATMega32

## Setup and Configuration
1. **Connect Hardware**:
   - Connect the I2C slave device to the ATMega32:
     - SDA (data line) to Port C, Pin 1 (PC1).
     - SCL (clock line) to Port C, Pin 0 (PC0).
   - Add pull-up resistors (4.7kΩ) from SDA and SCL to VCC (typically 5V).
   - Connect an LCD display to the microcontroller (if used, as defined in `LCD.h`).
   - Ensure the ATMega32 is powered and connected to the programming tool.

2. **Compile and Upload**:
   - Compile the code using AVR-GCC.
   - Upload the compiled binary to the ATMega32 using a compatible programmer.

3. **I2C Configuration**:
   - The I2C module is initialized with a specified SCL clock frequency using `I2C_master_init()`.
   - The default prescaler is 1, and the bit rate is calculated as `TWBR = ((F_CPU / scl) - 16) / (2 * prescaler)`.
   - The driver supports master operations (start, stop, send/receive data) and slave operations (set address, transmit/receive data).
   - Status codes in `TWSR` are checked to ensure successful I2C transactions.

4. **Program Behavior**:
   - **Master Mode**: Initialize with `I2C_master_init()`, send start/repeated start conditions, address slaves (read/write), and send/receive data.
   - **Slave Mode**: Set the device address with `set_device_address()`, receive data with `read_slave_content()`, or transmit data with `slave_transmite_its_content()`.
   - The LCD can be used to display received data or status messages (via `LCD.h` functions).

## Usage
- **Master Mode**:
  - Initialize the I2C module with a desired SCL frequency (e.g., `I2C_master_init(100000)` for 100 kHz).
  - Use `I2C_start_condition()` to begin communication, followed by `I2C_send_SLA_W()` or `I2C_send_SLA_R()` to address the slave.
  - Send data with `I2C_master_send_data()` or receive data with `I2C_master_Receive_slave_content()` or `I2C_master_Receive_data_with_NACK()`.
  - End communication with `I2C_stop_condition()`.
- **Slave Mode**:
  - Set the slave address with `set_device_address()`.
  - Use `read_slave_content()` to receive data from the master or `slave_transmite_its_content()` to send data to the master.
- The LCD can display data received from the slave or status messages for debugging.

## Code Example
```c
int main(void)
{
    LCD_Initialization(); // Initialize LCD (if used)
    I2C_master_init(100000); // Initialize I2C with 100 kHz SCL
    while (1)
    {
        I2C_start_condition(); // Send start condition
        I2C_send_SLA_W(0xA0); // Address slave (e.g., EEPROM) for writing
        I2C_master_send_data('A'); // Send data to slave
        I2C_stop_condition(); // Send stop condition
        _delay_ms(100);
        
        I2C_start_condition(); // Send start condition
        I2C_send_SLA_R(0xA1); // Address slave for reading
        unsigned char data = I2C_master_Receive_data_with_NACK(); // Receive data
        I2C_stop_condition(); // Send stop condition
        LCD_printCharacter(data); // Display received data on LCD
        _delay_ms(100);
    }
}
```

## Notes
- The I2C driver assumes a clock frequency of 8 MHz (`F_CPU 8000000UL`). Ensure the ATMega32 is configured accordingly.
- The SCL frequency must be chosen carefully to match the slave device’s specifications (typically 100 kHz or 400 kHz).
- The driver checks TWI status codes (`TWSR`) to ensure proper communication. Refer to the ATMega32 datasheet for status code details.
- Pull-up resistors on SDA and SCL are critical for reliable I2C communication.
- The `slave_transmite_its_content()` function includes a hardcoded test value (`'1'`). Modify this for actual slave data transmission.
- The LCD is optional but useful for debugging or displaying I2C data.


## License
This project is licensed under the MIT License.
