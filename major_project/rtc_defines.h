#ifndef _RTC_DEFINES_H      // Prevents multiple inclusion of this header file
#define _RTC_DEFINES_H__

// ---------------- System Clock and Peripheral Clock Macros ----------------

// Main oscillator frequency (12 MHz crystal)
//#define FOSC  12000000

// CPU clock frequency (CCLK = 5 × FOSC = 60 MHz)
//#define CCLK  (5*FOSC)

// Peripheral clock frequency (PCLK = CCLK / 4 = 15 MHz)
//#define PCLK  (CCLK/4)

// ---------------- RTC Prescaler Macros ----------------

// PREINT value for RTC prescaler
// This divides the peripheral clock (PCLK) to generate a 32.768 kHz clock
// Formula: (PCLK / 32768) - 1
#define PREINT_VAL  (int)((PCLK / 32768) - 1)

// PREFRAC value for RTC fractional divider
// This compensates for the remainder after integer division
// Formula: PCLK - ((PREINT + 1) × 32768)
#define PREFRAC_VAL (PCLK - ((PREINT + 1) * 32768))

// ---------------- RTC Clock Control Register (CCR) Macros ----------------

// RTC Enable bit (bit 0)
// Setting this bit starts the RTC
#define RTC_CCR_EN                      (1<<0)

// RTC Counter Reset bit (bit 1)
// Setting this bit resets the RTC counters
#define RTC_CTC_RESET                   (1<<1)

// RTC Clock Source bit (bit 4)
// Used to select the RTC clock source
#define RTC_CLKSRC                      (1<<4)

#endif
