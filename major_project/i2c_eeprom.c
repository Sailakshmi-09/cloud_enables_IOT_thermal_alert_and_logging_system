#include <LPC21xx.h>   // LPC214x register definitions
#include "types.h"      // User-defined data types (u8, u16, etc.)
#include "i2c.h"        // I2C function declarations
#include "delay.h"      // Delay functions

// Function to write a single byte to EEPROM
void i2c_eeprom_write(u8 slaveAddr, u16 wBuffAddr, u8 dat)
{
    i2c_start();                        // Generate I2C START condition

    // Send slave address with write bit (R/W = 0)
    i2c_write(slaveAddr << 1);

    // Send high byte of EEPROM memory address
    i2c_write((wBuffAddr >> 8) & 0xFF);

    // Send low byte of EEPROM memory address
    i2c_write((wBuffAddr & 0xFF));

    // Send data byte to be written
    i2c_write(dat);

    i2c_stop();                         // Generate I2C STOP condition

    // Wait for EEPROM internal write cycle to complete
    delay_ms(10);
}

// Function to read a single byte from EEPROM
u8 i2c_eeprom_read(u8 slaveAddr, u16 rBuffAddr)
{
    u8 dat;

    i2c_start();                        // Generate I2C START condition

    // Send slave address with write bit to set memory address
    i2c_write(slaveAddr << 1);

    // Send high byte of EEPROM memory address
    i2c_write((rBuffAddr >> 8) & 0xFF);

    // Send low byte of EEPROM memory address
    i2c_write((rBuffAddr & 0xFF));

    i2c_restart();                      // Generate repeated START condition

    // Send slave address with read bit (R/W = 1)
    i2c_write((slaveAddr << 1) | 1);

    // Read one byte and send NACK (last byte)
    dat = i2c_nack();

    i2c_stop();                         // Generate I2C STOP condition

    return dat;                         // Return the received data
}

// Function to write multiple bytes (page write) to EEPROM
void i2c_eeprom_page_write(u8 slaveAddr, u8 wBuffStartAddr, u8 *p, u8 nBytes)
{
    u8 i;

    i2c_start();                        // Generate I2C START condition

    // Send slave address with write bit
    i2c_write(slaveAddr << 1);

    // Send starting EEPROM memory address
    i2c_write(wBuffStartAddr);

    // Write multiple bytes sequentially
    for(i = 0; i < nBytes; i++)
    {
        i2c_write(p[i]);                // Write each byte from buffer
    }

    i2c_stop();                         // Generate I2C STOP condition

    // Wait for EEPROM internal page write cycle
    delay_ms(10);
}

// Function to read multiple bytes sequentially from EEPROM
void i2c_eeprom_seq_read(u8 slaveAddr, u8 rBuffStartAddr, u8 *p, u8 nBytes)
{
    u8 i;

    i2c_start();                        // Generate I2C START condition

    // Send slave address with write bit to set start address
    i2c_write(slaveAddr << 1);

    // Send starting EEPROM memory address
    i2c_write(rBuffStartAddr);

    i2c_restart();                      // Generate repeated START condition

    // Send slave address with read bit
    i2c_write((slaveAddr << 1) | 1);

    // Read all bytes except the last one
    // Send ACK after each received byte to request more data
    for(i = 0; i < nBytes - 1; i++)
    {
        p[i] = i2c_masterack();
    }

    // Read the last byte and send NACK to end communication
    p[i] = i2c_nack();

    i2c_stop();                         // Generate I2C STOP condition
}
