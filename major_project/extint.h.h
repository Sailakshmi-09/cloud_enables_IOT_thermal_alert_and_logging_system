#ifndef _EXTINT_H_        // Prevents multiple inclusion of this header file
#define _EXTINT_H_

// Function declaration for the EINT0 Interrupt Service Routine (ISR)
// The '__irq' keyword tells the compiler that this function is an interrupt handler
// It is executed automatically when the EINT0 external interrupt occurs
void eint0_isr(void) __irq;

// Function declaration to configure and enable EINT0
// This function sets up the external interrupt pin, VIC, and trigger mode
void Enable_EINT0(void);

#endif
