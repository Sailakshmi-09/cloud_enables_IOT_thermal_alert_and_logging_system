                /* delay.h */
#ifndef __DELAY_H__   // Prevents multiple inclusion of this header file
#define __DELAY_H__

#include "types.h"       // Includes user-defined data types such as u32

// Function declaration for millisecond delay
// Parameter: dlyMS - delay duration in milliseconds
void delay_ms(u32 dlyMS);

// Function declaration for microsecond delay
// Parameter: dlyUS - delay duration in microseconds
void delay_us(u32 dlyUS);

#endif
