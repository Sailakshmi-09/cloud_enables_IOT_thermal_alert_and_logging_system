#include <lpc214x.h>
#include "delay.h"      // Delay functions
#include "defines.h"    // Bit manipulation macros
#include "lcd.h"        // LCD function declarations
#include "dht11.h"      // DHT11 sensor function declarations

int main (void)
{
    // Variables to store humidity, temperature, and checksum data
    unsigned char humidity_integer, humidity_decimal;
    unsigned char temp_integer, temp_decimal;
    unsigned char checksum;

    // Initialize the LCD display
    LCD_Init();

    // Infinite loop to continuously read sensor data
    while(1)
    {
        // Send start signal to DHT11 sensor
        dht11_request();

        // Wait for DHT11 response signal
        dht11_response();

        // Read humidity integer part
        humidity_integer = dht11_data();

        // Read humidity decimal part
        humidity_decimal = dht11_data();
// Read temperature integer part
        temp_integer = dht11_data();

        // Read temperature decimal part
        temp_decimal = dht11_data();

        // Read checksum byte
        checksum = dht11_data();

        // Verify checksum
        // Checksum should equal the sum of the first four bytes
        if( (humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )
        {
            // Display checksum error message if data is corrupted
            Write_str_LCD("Checksum Error\r\n");
        }
        else
        {
            // ---------------- Display Humidity ----------------

            // Move cursor to first line, first position
            Write_CMD_LCD(0x80);

            // Display humidity label
            Write_str_LCD("H : ");
// Display humidity integer part
            Write_int_LCD(humidity_integer);

            // Display decimal point
            Write_DAT_LCD('.');

            // Display humidity decimal part
            Write_int_LCD(humidity_decimal);

            // Display humidity unit
            Write_str_LCD(" % RH ");

            // ---------------- Display Temperature ----------------

            // Move cursor to second line, first position
            Write_CMD_LCD(0xC0);

            // Display temperature label
            Write_str_LCD("T : ");

            // Display temperature integer part
            Write_int_LCD(temp_integer);

            // Display decimal point
            Write_DAT_LCD('.');
// Display temperature decimal part
            Write_int_LCD(temp_decimal);

            // Display degree symbol (ASCII 223 for many LCDs)
            Write_DAT_LCD(223);

            // Display Celsius unit
            Write_str_LCD("C");

            // ---------------- Display Checksum ----------------

            // Move cursor to fourth line, fifth position
            Write_CMD_LCD(0xD4);

            // Display checksum label
            Write_str_LCD("Checksum : ");

            // Display checksum value
            Write_int_LCD(checksum);

            // Wait for 3 seconds before updating data
            delay_ms(3000);

            // Clear the LCD display
            Write_CMD_LCD(0x01);
        }
    }
}
