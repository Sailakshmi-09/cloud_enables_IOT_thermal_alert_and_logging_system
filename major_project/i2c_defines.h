  /* i2c_defines.h */
#ifndef __I2C_DEFINES_H__   // Prevents multiple inclusion of this header file
#define __I2C_DEFINES_H__

#include "uart0.h"             // Includes UART0 definitions (used for debugging or communication)

// ---------------- Pin Function Selection ----------------

// Enable SCL (Serial Clock Line) function on the required pin
// This value is used in PINSEL register configuration
#define SCL_EN  0x00000010

// Enable SDA (Serial Data Line) function on the required pin
// This value is used in PINSEL register configuration
#define SDA_EN  0x00000040

// ---------------- I2C Speed Configuration ----------------

// CPU Clock Frequency (CCLK) and Peripheral Clock Frequency (PCLK)
// are assumed to be defined elsewhere, so they are commented out here.

// Desired I2C communication speed
// Standard mode I2C operates at 100 kHz
#define I2C_SPEED 100000    // Hz

// Load value for I2C clock high and low registers (I2SCLH and I2SCLL)
// Formula: (PCLK / I2C_SPEED) / 2
// This divides the peripheral clock to generate the required I2C clock frequency
#define LOADVAL   ((PCLK/I2C_SPEED)/2)

// ---------------- I2C Control Set Register (I2CONSET) Bit Definitions ----------------

// Assert Acknowledge bit position
// Used to send an ACK after receiving a byte
#define AA_BIT 2

// I2C Interrupt Flag bit position
// Set when an I2C operation is completed
#define SI_BIT 3

// STOP condition bit position
// Used to generate a STOP condition on the I2C bus
#define STO_BIT 4

// START condition bit position
// Used to generate a START condition on the I2C bus
#define STA_BIT 5

// I2C Enable bit position
// Used to enable the I2C peripheral
#define I2EN_BIT 6

#endif
