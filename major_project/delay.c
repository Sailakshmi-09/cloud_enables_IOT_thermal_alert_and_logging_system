 #include "types.h"   // Includes user-defined data types such as u32

// Function to generate delay in milliseconds
void delay_ms(u32 dlyMS)
{
    // Convert milliseconds into loop count
    // Assuming CPU clock is 12 MHz, approximately 12000 iterations = 1 ms
    dlyMS *= 12000;

    // Decrement the counter until it reaches zero
    // This creates a blocking delay
    while(dlyMS--);
}
// Function to generate delay in microseconds
void delay_us(u32 dlyUS)
{
    // Convert microseconds into loop count
    // Assuming CPU clock is 12 MHz, approximately 12 iterations = 1 us
    dlyUS *= 12;

    // Decrement the counter until it reaches zero
    // This creates a blocking delay
    while(dlyUS--);
}
// Function to generate delay in seconds
void delay_s(u32 dlyS)
{
    // Convert seconds into loop count
    // Assuming CPU clock is 12 MHz, approximately 12,000,000 iterations = 1 s
    dlyS *= 12000000;
         // Decrement the counter until it reaches zero
    // This creates a blocking delay
    while(dlyS--);
}
