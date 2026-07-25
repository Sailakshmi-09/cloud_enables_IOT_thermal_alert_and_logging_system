#include<LPC21xx.h>

#include "delay.h"
#include "lcd.h"
#include "defines.h"
#define LCD_DAT 8   // LCD data bus connected to P0.8 - P0.15
#define RS 17       // Register Select pin connected to P0.17
#define RW 19       // Read/Write pin connected to P0.19
#define EN 18       // Enable pin connected to P0.18

// Function to initialize the LCD
void LCD_Init(void)
{
    // Configure LCD data pins (P0.8 - P0.15) as output
    WRITEBYTE(IODIR0, LCD_DAT, 0xFF);

    // Configure control pins as output
    WRITEBIT(IODIR0, RS, 1);
    WRITEBIT(IODIR0, RW, 1);
    WRITEBIT(IODIR0, EN, 1);

    // Wait for LCD power stabilization
    delay_ms(16);

    // Initialization sequence for 8-bit LCD mode
    Write_CMD_LCD(0x30);
    delay_ms(6);

    Write_CMD_LCD(0x30);
    delay_ms(1);

    Write_CMD_LCD(0x30);
    delay_ms(1);

    // Function set: 8-bit mode, 2 lines, 5x7 font
    Write_CMD_LCD(0x38);

    // Display OFF
    Write_CMD_LCD(0x10);

    // Clear display
    Write_CMD_LCD(0x01);

    // Entry mode: cursor moves right after each character
    Write_CMD_LCD(0x06);

    // Display ON, cursor ON, blinking cursor ON
    Write_CMD_LCD(0x0F);
}

// Function to send a command to the LCD
void Write_CMD_LCD(char cmd)
{
    // RS = 0 selects command register
    WRITEBIT(IOCLR0, RS, 1);

    // Send command byte to LCD
    Write_LCD(cmd);
}

// Function to send data (character) to the LCD
void Write_DAT_LCD(char dat)
{
    // RS = 1 selects data register
    WRITEBIT(IOSET0, RS, 1);

    // Send data byte to LCD
    Write_LCD(dat);
}

// Common function to write a byte to the LCD
void Write_LCD(char ch)
{
    // RW = 0 selects write operation
    WRITEBIT(IOCLR0, RW, 1);

    // Place the byte on LCD data bus
    WRITEBYTE(IOPIN0, LCD_DAT, ch);

    // Generate Enable pulse
    WRITEBIT(IOSET0, EN, 1);   // EN = 1
    WRITEBIT(IOCLR0, EN, 1);   // EN = 0

    // Wait for LCD to process the data
    delay_ms(2);
}

// Function to display a string on the LCD
void Write_str_LCD(char *p)
{
    // Send each character until null character is reached
    while(*p)
        Write_DAT_LCD(*p++);
}

// Function to display an integer number on the LCD
void Write_int_LCD(signed int n)
{
    char a[10], i = 0;

    // Handle negative numbers
    if(n < 0)
    {
        Write_DAT_LCD('-');
        n = -n;
    }

    // Convert integer to ASCII digits
    do
    {
        a[i++] = n % 10 + 48;  // 48 is ASCII value of '0'
        n = n / 10;
    } while(n);

    // Display digits in correct order
    for(; i > 0; i--)
        Write_DAT_LCD(a[i-1]);
}

// Function to display a floating-point number on the LCD
// f = float number to display
// i = number of digits after decimal point
void Write_float_LCD(float f, char i)
{
    unsigned long int n = f;

    // Display integer part
    Write_int_LCD(n);

    // Display decimal point
    Write_DAT_LCD('.');

    // Display fractional part
    for(; i > 0; i--)
    {
        f = f * 10;
        n = f;
        Write_DAT_LCD(n % 10 + 48);
    }
}
