#include <lpc21xx.h>       // LPC214x register definitions
#include "uart0.h"         // UART0 functions (included for project use)
#include "types.h"         // User-defined data types (u8, u32, etc.)
#include "rtc_defines.h"   // RTC macro definitions

// Function to initialize the Real Time Clock (RTC)
void RTC_Init(void)
{
    // Reset the RTC counters and prescaler
    // Setting RTC_CTC_RESET clears the RTC time counters
    CCR = RTC_CTC_RESET;

    // Set the integer part of the RTC prescaler
    // PREINT divides the peripheral clock to generate a 32.768 kHz clock
    PREINT = PREINT_VAL;

    // Set the fractional part of the RTC prescaler
    // PREFRAC compensates for the remainder after integer division
    PREFRAC = PREFRAC_VAL;

    /*
    // Enable the RTC for LPC2129
    // This uses the internal peripheral clock as RTC clock source
    CCR = RTC_CCR_EN;
    */

    // Enable the RTC for LPC2148 with external 32.768 kHz clock source
    // RTC_CCR_EN   -> Starts the RTC
    // RTC_CLKSRC  -> Selects the external RTC clock source
    CCR = RTC_CCR_EN | RTC_CLKSRC;
}

// Function to set the RTC time
void RTCSetTime(u32 hr, u32 mi, u32 se)
{
    // Set the hour value (0-23)
    HOUR = hr;

    // Set the minute value (0-59)
    MIN = mi;

    // Set the second value (0-59)
    SEC = se;
}
