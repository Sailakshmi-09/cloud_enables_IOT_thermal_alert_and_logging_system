#ifndef _UART0_H_        // Prevents multiple inclusion of this header file
#define _UART0_H_

// ---------------- UART Interrupt Configuration ----------------

// Set to 1 to enable UART0 interrupts
// Set to 0 to disable UART0 interrupts
#define UART_INT_ENABLE 1

// ---------------- Baud Rate Calculation ----------------

// Main oscillator frequency (12 MHz crystal)
#define FOSC      12000000   // Hz

// CPU clock frequency (CCLK = 5 × FOSC = 60 MHz)
#define CCLK      5*FOSC

// Peripheral clock frequency (PCLK = CCLK / 4 = 15 MHz)
#define PCLK      CCLK/4

// Desired UART baud rate
#define BAUD      9600

// UART divisor calculation
// Formula: Divisor = PCLK / (16 × BAUD)
// This value is loaded into U0DLL and U0DLM registers
#define DIVISOR   (PCLK/(16 * BAUD))

// ---------------- UART Function Declarations ----------------

// Function to initialize UART0
// Configures UART pins, baud rate, data format, and interrupts
void InitUART0(void);

// Function to transmit a single character through UART0
// Parameter:
//   char ch - Character to transmit
void UART0_Tx(char ch);

// Function to receive a single character from UART0
// Returns:
//   char - Received character
char UART0_Rx(void);

// Function to transmit a string through UART0
// Parameter:
//   char * - Pointer to the string to transmit
void UART0_Str(char *);

// Function to transmit an unsigned integer through UART0
// Parameter:
//   unsigned int - Integer value to transmit
void UART0_Int(unsigned int);

// Function to transmit a floating-point number through UART0
// Parameter:
//   float - Floating-point value to transmit
void UART0_Float(float);

#endif
