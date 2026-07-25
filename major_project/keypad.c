#include <lpc21xx.h>      // LPC214x register definitions
#include <stdlib.h>       // Standard library for atoi()
#include "types.h"        // User-defined data types (u8, u32, etc.)
#include "delay.h"        // Delay functions
#include "defines.h"      // Bit and nibble manipulation macros
#include "lcd.h"          // LCD display functions
#include "keypad_defines.h" // Keypad row and column pin definitions

// Lookup table for keypad characters
// Each row and column corresponds to a key in the 4x4 keypad
u8 kpmlut[4][4] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// Row scanning codes
// These values drive one row LOW at a time while keeping others HIGH
u8 codes[4] = {0xe, 0xd, 0xb, 0x7};

u32 num;   // Variable to store the final numeric value

// Function to initialize keypad pins
void initkpm(void)
{
    // Configure ROW0 to ROW3 (P1.16-P1.19) as output pins
    // Value 15 (0xF) sets all 4 row bits as output
    WRITENIBBLE(IODIR1, ROW0, 15);
}

// Function to scan keypad columns
u8 colscan(void)
{
    u32 t;

    // Read the 4 column bits from P1.20-P1.23
    t = READNIBBLE(IOPIN1, COL0);

    // If all columns are HIGH (1111 = 15), no key is pressed
    // If any column is LOW, a key is pressed
    t = (t < 15) ? 0 : 1;

    return t;
}

// Function to identify which row contains the pressed key
u8 Rowcheck(void)
{
    u8 rno, i;

    // Scan each row one by one
    for(i = 0; i < 4; i++)
    {
        // Drive one row LOW and others HIGH
        WRITENIBBLE(IOPIN1, ROW0, codes[i]);

        // Check if any column becomes LOW
        if(!colscan())
        {
            rno = i;   // Store row number
            break;
        }
    }

    // Reset all rows to LOW after scanning
    WRITENIBBLE(IOPIN1, ROW0, 0);

    return rno;
}

// Function to identify which column contains the pressed key
u8 colcheck(void)
{
    u8 cno, i;

    // Compare column input with scanning codes
    for(i = 0; i < 4; i++)
    {
        if(READNIBBLE(IOPIN1, COL0) == codes[i])
        {
            cno = i;   // Store column number
            break;
        }
    }

    return cno;
}

// Function to scan the keypad and return the pressed key
u8 keyscan(void)
{
    u8 rno, cno;

    // Wait until a key is pressed
    while(colscan());

    // Find the row number
    rno = Rowcheck();

    // Find the column number
    cno = colcheck();

    // Return the corresponding character from lookup table
    return kpmlut[rno][cno];
}

// Function to read a multi-digit number from the keypad
u32 Readnum(void)
{
    u32 i = 0;
    u8 arr[20], keyval;

    // Move LCD cursor to second line
    Write_CMD_LCD(0xC0);

    while(1)
    {
        // Read a key from the keypad
        keyval = keyscan();

        // Wait until the key is released
        while(!colscan());

        // Debounce delay
        delay_ms(200);

        // If the key is a numeric digit
        if((keyval >= '0') && (keyval <= '9'))
        {
            arr[i] = keyval;          // Store digit in array
            Write_DAT_LCD(arr[i]);    // Display digit on LCD
            i++;
        }

        // If 'D' is pressed, finish input
        else if(keyval == 'D')
        {
            arr[i] = '\0';   // Null-terminate the string
            break;
        }

        // If 'B' is pressed, perform backspace
        else if(keyval == 'B')
        {
            i--;   // Move back one position

            // Erase the last character from LCD
            Write_CMD_LCD(0xC0 + i);
            Write_DAT_LCD(' ');

            // Move cursor back to erased position
            Write_CMD_LCD(0xC0 + i);
        }
    }

    // Convert the entered string to an integer
    num = atoi((const char *)arr);

    return num;   // Return the numeric value
}
