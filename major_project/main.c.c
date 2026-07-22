#include "uart0.h"   // UART0 communication functions
#include "delay.h"   // Delay functions
#include "lcd.h"     // LCD display functions
#include "esp01.h"   // ESP01 Wi-Fi module functions

// External variables declared in another source file
extern char buff[100], dummy;
extern unsigned char i, ch, r_flag;

// Array of strings to be sent to ThingSpeak
char arr[][4] = {"985", "467", "645"};

int main()
{
    char i;

    // Initialize UART0 for serial communication with ESP01
    InitUART0();

    // Initialize the LCD
    LCD_Init();

    // Move cursor to first line, first position
    Write_CMD_LCD(0x80);

    // Display startup message
    Write_str_LCD("ESP01 Interface");

    // Wait for 1 second
    delay_ms(1000);

    // Infinite loop
    while(1)
    {
        // Connect ESP01 module to Wi-Fi Access Point
        esp01_connectAP();

        // Send all values in the array to ThingSpeak
        for(i = 0; i < 3; i++)
        {
            // Send one value to ThingSpeak
            esp01_sendToThingspeak(arr[i]);

            // Wait for 5 seconds before sending next value
            delay_ms(5000);
        }

        // Stop execution here after sending all values
        while(1);
    }
}
