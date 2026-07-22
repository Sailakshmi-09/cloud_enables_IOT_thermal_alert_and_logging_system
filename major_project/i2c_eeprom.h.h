                                       /* i2c_eeprom.h */
#ifndef __I2C_EEPROM_H__   // Prevents multiple inclusion of this header file
#define __I2C_EEPROM_H__

#include "types.h"             // Includes user-defined data types (u8, u16, etc.)

// Function declaration to write a single byte to EEPROM
// Parameters:
//   u8  - EEPROM slave address
//   u16 - EEPROM memory address where data will be written
//   u8  - Data byte to write
void i2c_eeprom_write(u8, u16, u8);

// Function declaration to read a single byte from EEPROM
// Parameters:
//   u8  - EEPROM slave address
//   u16 - EEPROM memory address to read from
// Returns:
//   u8  - Data byte read from EEPROM
u8 i2c_eeprom_read(u8, u16);

// Function declaration to write multiple bytes (page write) to EEPROM
// Parameters:
//   slaveAddr      - EEPROM slave address
//   wBuffStartAddr - Starting EEPROM memory address for writing
//   p              - Pointer to the data buffer containing bytes to write
//   nBytes         - Number of bytes to write
void i2c_eeprom_page_write(u8 slaveAddr,
                           u8 wBuffStartAddr,
                           u8 *p,
                           u8 nBytes);

// Function declaration to read multiple bytes sequentially from EEPROM
// Parameters:
//   slaveAddr      - EEPROM slave address
//   rBuffStartAddr - Starting EEPROM memory address for reading
//   p              - Pointer to the buffer where received data will be stored
//   nBytes         - Number of bytes to read
void i2c_eeprom_seq_read(u8 slaveAddr,
                         u8 rBuffStartAddr,
                         u8 *p,
                         u8 nBytes);

#endif
