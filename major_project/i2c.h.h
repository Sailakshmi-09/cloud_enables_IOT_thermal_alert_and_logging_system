#ifndef __I2C_H__      // Prevents multiple inclusion of this header file
#define __I2C_H__

#include "types.h"      // Includes user-defined data types such as u8

// Function declaration to initialize the I2C peripheral
// Configures I2C pins, clock speed, and enables I2C communication
void init_i2c(void);

// Function declaration to generate an I2C START condition
// Used to begin communication with an I2C slave device
void i2c_start(void);

// Function declaration to generate an I2C STOP condition
// Used to end communication with an I2C slave device
void i2c_stop(void);

// Function declaration to generate an I2C REPEATED START condition
// Used when switching from write mode to read mode without releasing the bus
void i2c_restart(void);

// Function declaration to write one byte of data on the I2C bus
// Parameter:
//   u8 - Data byte to transmit
void i2c_write(u8);

// Function declaration to read one byte of data from the I2C bus
// Returns:
//   u8 - Data byte received from the slave device
u8 i2c_read(void);

// Function declaration to read one byte and send ACK
// ACK tells the slave that more data bytes are expected
// Returns:
//   u8 - Data byte received from the slave device
u8 i2c_ack(void);

// Function declaration to read one byte and send NACK
// NACK tells the slave that no more data bytes are needed
// Returns:
//   u8 - Data byte received from the slave device
u8 i2c_nack(void);

// Function declaration to read one byte and send ACK from the master
// Commonly used during sequential reads when more bytes are expected
// Returns:
//   u8 - Data byte received from the slave device
u8 i2c_masterack(void);

#endif
