#include <lpc21xx.h>               // LPC214x register definitions
#include "pin_function_defines.h"    // Pin function configuration macros
#include "defines.h"                 // Bit manipulation macros
#include "types.h"                   // User-defined data types (u8, etc.)

u8 i_flag = 0;                       // Global flag variable, set when interrupt occurs

// EINT0 Interrupt Service Routine (ISR)
// This function executes automatically when EINT0 interrupt occurs
void eint0_isr(void) __irq
{
    i_flag = 1;                      // Set interrupt flag to indicate EINT0 occurred

    SCLRBIT(EXTINT, 0);              // Clear EINT0 interrupt flag in EXTINT register

    VICVectAddr = 0;                 // Dummy write to VICVectAddr
                                        // Signals end of interrupt to the VIC
}

// Function to enable and configure EINT0
void Enable_EINT0(void)
{
    // Configure P0.16 as EINT0 function
    // PINSEL1 bits 1:0 correspond to P0.16
    CFGPIN(PINSEL1, 0, FUNC2);
// Enable EINT0 interrupt in VIC
    // Interrupt number 14 corresponds to EINT0
    SETBIT(VICIntEnable, 14);

    // Configure VIC vector control slot 1
    // 0x20 enables the vector slot, 14 selects EINT0 interrupt
    VICVectCntl1 = 0x20 | 14;

    // Assign the ISR address to vector slot 1
    VICVectAddr1 = (unsigned)eint0_isr;

    // Enable EINT0
    // (By default, EINT0 is enabled after configuration)

    // Configure EINT0 as edge-triggered interrupt
    // 1 = Edge-triggered, 0 = Level-triggered
    SETBIT(EXTMODE, 0);

    // Configure EINT0 as falling-edge triggered
    // 0 = Falling edge, 1 = Rising edge
    // Since this line is commented, default is falling edge
    // SETBIT(EXTPOLAR, 0);
}
