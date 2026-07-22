#include <LPC21xx.H>   /* LPC214x register definitions */

#include "uart0.h"       // UART0 function declarations and macros

// Global variables for UART communication
char buff[350] = "hello", dummy;   // Buffer to store received data and dummy variable
unsigned char ch, r_flag;          // ch = received character, r_flag = receive flag
unsigned short int i = 0;          // Index for buffer storage

// UART0 Interrupt Service Routine (ISR)
void UART0_isr(void) __irq
{
    // Check if the interrupt is a receive interrupt
    if((U0IIR & 0x04))
    {
        // Read received character from UART Receive Buffer Register
        // Reading U0RBR clears the receive interrupt
        ch = U0RBR;

        // Store character in buffer if buffer is not full
        if(i < 350)
            buff[i++] = ch;
    }
    else
    {
        // Read U0IIR to clear transmit interrupt
        dummy = U0IIR;
    }

    // Dummy write to VICVectAddr signals end of interrupt processing
    VICVectAddr = 0;
}

// Function to initialize UART0
void InitUART0(void)
{
    // Configure P0.0 as TxD0 and P0.1 as RxD0
    PINSEL0 |= 0x00000005;

    // Configure UART:
    // 8 data bits, no parity, 1 stop bit, DLAB = 1
    U0LCR = 0x83;

    // Set baud rate divisor for 9600 baud rate
    // Assuming PCLK = CCLK/4
    U0DLL = DIVISOR;           // Lower byte of divisor
    U0DLM = DIVISOR >> 8;      // Upper byte of divisor

    // Clear DLAB bit to access normal UART registers
    U0LCR = 0x03;

#if UART_INT_ENABLE > 0

    // Configure UART0 interrupt as IRQ
    VICIntSelect = 0x00000000;

    // Set ISR address in vector slot 0
    VICVectAddr0 = (unsigned)UART0_isr;

    // Enable vector slot 0 for UART0 interrupt (interrupt number 6)
    VICVectCntl0 = 0x20 | 6;

    // Enable UART0 interrupt in VIC
    VICIntEnable = 1 << 6;

    // Enable UART0 receive and THRE (transmit holding register empty) interrupts
    U0IER = 0x03;

#endif
}

// Function to transmit a single character through UART0
void UART0_Tx(char ch)
{
    // Wait until Transmit Holding Register is empty
    while (!(U0LSR & 0x20));

    // Load character into Transmit Holding Register
    U0THR = ch;
}

// Function to receive a single character from UART0
char UART0_Rx(void)
{
    // Wait until data is available in Receive Buffer Register
    while (!(U0LSR & 0x01));

    // Return received character
    return (U0RBR);
}

// Function to transmit a string through UART0
void UART0_Str(char *s)
{
    // Send characters one by one until null character is reached
    while(*s)
        UART0_Tx(*s++);
}

// Function to transmit an unsigned integer through UART0
void UART0_Int(unsigned int n)
{
    unsigned char a[10] = {0,0,0,0,0,0,0,0,0,0};   // Array to store digits
    int i = 0;

    // Handle zero separately
    if(n == 0)
    {
        UART0_Tx('0');
        return;
    }
    else
    {
        // Convert integer to ASCII digits in reverse order
        while(n > 0)
        {
            a[i++] = (n % 10) + 48;   // 48 is ASCII value of '0'
            n = n / 10;
        }

        // Send digits in correct order
        --i;
        for(; i >= 0; i--)
        {
            UART0_Tx(a[i]);
        }
    }
}

// Function to transmit a floating-point number through UART0
void UART0_Float(float f)
{
    int x;
    float temp;

    // Extract integer part
    x = f;

    // Send integer part
    UART0_Int(x);

    // Send decimal point
    UART0_Tx('.');

    // Extract two digits after decimal point
    temp = (f - x) * 100;
    x = temp;

    // Send fractional part
    UART0_Int(x);
}
