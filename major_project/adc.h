#ifndef _ADC_H_        // Prevents multiple inclusion of this header file
#define _ADC_H_

#include "types.h"       // Includes user-defined data types such as u8 and f32

// Function declaration to initialize the ADC peripheral
// This function configures the ADC and prepares it for conversion
void Init_ADC(void);

// Function declaration to read ADC value from a specified channel
// Parameter: chNo - ADC channel number to read
// Returns: Analog voltage as a floating-point value (f32)
f32 Read_ADC(u8 chNo);

#endif
