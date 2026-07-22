#ifndef _ADC_DEFINES_H_   // Prevents multiple inclusion of this header file
#define _ADC_DEFINES_H_

// ---------------- ADC Channel Selection Bits ----------------
// These bits are used in AD0CR to select ADC input channels

#define CH0                0x01   // Select ADC channel 0 (AD0.0)
#define CH1                0x02   // Select ADC channel 1 (AD0.1)
#define CH2                0x04   // Select ADC channel 2 (AD0.2)
#define CH3                0x08   // Select ADC channel 3 (AD0.3)

// Default ADC channel selected for conversion
#define CHANNEL_SEL        CH1    // Selects channel 1 by default

// ---------------- Clock Definitions ----------------

// Main oscillator frequency (12 MHz crystal)
#define FOSC               12000000

// CPU clock frequency (CCLK = 5 × FOSC = 60 MHz)
#define CCLK               (5 * FOSC)

// Peripheral clock frequency (PCLK = CCLK / 4 = 15 MHz)
#define PCLK               CCLK/4

// Desired ADC clock frequency (maximum recommended is 4.5 MHz)
#define ADCLK              3000000
// ADC clock divider value
// Formula: CLKDIV = ((PCLK / ADCLK) - 1) << 8
// This value is written into bits 15:8 of AD0CR
#define CLKDIV             (((PCLK/ADCLK)-1)<<8)

// ---------------- ADC Control Register (AD0CR) ----------------

// Power Down bit (bit 21)
// Setting this bit powers up the ADC
#define PDN_BIT            (1<<21)

// ADC Start Conversion bit position (bit 24)
#define ADC_START_BIT      24

// ---------------- ADC Data Register (AD0GDR) ----------------

// DONE bit position (bit 31)
// This bit becomes 1 when ADC conversion is complete
#define DONE_BIT           31

#endif
