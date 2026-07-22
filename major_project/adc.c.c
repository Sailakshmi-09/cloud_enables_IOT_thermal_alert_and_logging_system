#include <LPC214x.h>        // LPC214x register definitions

#include "types.h"           // User-defined data types (u8, u16, f32, etc.)
#include "defines.h"         // General macro definitions
#include "adc_defines.h"     // ADC-related macro definitions
#include "delay.h"           // Delay function declarations

#define ADC_FUNC 0x01        // Function code for selecting ADC function on pin

// Function to initialize ADC0
void Init_ADC(void)
{
    // Configure P0.28 as ADC input pin (AD0.1)
    // In PINSEL1, bits 25:24 correspond to P0.28
    PINSEL1 |= (ADC_FUNC << 24);

    // Enable ADC power (PDN_BIT) and set ADC clock divider (CLKDIV)
    AD0CR = PDN_BIT | CLKDIV;
}

// Function to read ADC value from the selected channel
f32 Read_ADC(u8 chNo)
{
    u16 adcVal = 0;   // Variable to store 10-bit ADC result
    f32 eAR;          // Variable to store converted analog voltage

    // Clear channel selection bits (bits 0-7) in AD0CR
    AD0CR &= 0xFFFFFF00;
// Select the required ADC channel and start conversion
    AD0CR |= (1 << ADC_START_BIT) | (1 << chNo);

    // Small delay to allow ADC conversion to begin
    delay_us(3);

    // Wait until conversion is complete
    // DONE_BIT in AD0GDR becomes 1 when conversion finishes
    while (((AD0GDR >> DONE_BIT) & 1) == 0);

    // Stop ADC conversion by clearing START bit
    AD0CR &= ~(1 << ADC_START_BIT);

    // Extract 10-bit ADC result from AD0GDR
    // ADC result is stored in bits 15:6
    adcVal = (AD0GDR >> 6) & 0x3FF;

    // Convert ADC digital value to analog voltage
    // Formula: Voltage = (ADC value × Vref) / 1023
    // Assuming Vref = 3.3V
    eAR = ((adcVal * 3.3) / 1023);

    // Return the analog voltage
    return eAR;
}
