#include<lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "defines.h"
#include "keypad.h"
#include "uart0.h"
#include "i2c.h"
#include "esp01.h"
#include "lcd.h"
#include "i2c_defines.h"
#include "i2c_eeprom.h"
#include "extint.h"
#include "adc.h"

u8 rt, rsp, smoke;      // rt = stored setpoint, rsp = remote setpoint, smoke = smoke sensor value
extern u8 i_flag;       // External interrupt flag from EINT0
u8 temp, k = 0, min;    // temp = current temperature, k = counter, min = RTC minute
f32 eAR;                // Analog voltage value from ADC

main()
{
    // Initialize UART0 for ESP01 communication
    InitUART0();

    // Initialize LCD display
    LCD_Init();

    // Initialize I2C peripheral
    init_i2c();

    // Initialize keypad module
    initkpm();

    // Enable external interrupt EINT0
    Enable_EINT0();

    // Initialize RTC (Real Time Clock)
    RTC_Init();

    // Set RTC time to 16:15:00
    RTCSetTime(16, 15, 0);

    // Display ESP01 connection message
    Write_str_LCD("ESP01 CONNECT");
    delay_ms(1000);

    // Connect ESP01 to Wi-Fi Access Point
    esp01_connectAP();

    // Initialize ADC for temperature sensor reading
    Init_ADC();

    // Store default setpoint value (45°C) in EEPROM address 0x00
    i2c_eeprom_write(0x50, 0x00, 45);

    // Read setpoint value from EEPROM
    rt = i2c_eeprom_read(0x50, 0x00);

    // Clear LCD
    Write_CMD_LCD(0x01);
    delay_ms(2000);

    // Store current RTC minute value
    min = MIN;

    // Main infinite loop
    while(1)
    {
        k = 0;

        // Repeat until external interrupt occurs
        do
        {
            // Read ADC channel 1 (LM35 temperature sensor)
            eAR = Read_ADC(1);

            // Convert voltage to temperature in Celsius
            // LM35 gives 10 mV per °C, so temperature = voltage × 100
            temp = eAR * 100;

            // Display temperature on LCD
            Write_CMD_LCD(0x80);
            Write_str_LCD("T: ");
            Write_int_LCD(temp);
            Write_DAT_LCD(223);   // Degree symbol
            Write_str_LCD("C");

            // Display setpoint on LCD
            Write_CMD_LCD(0x80 + 10);
            Write_str_LCD("SP: ");
            Write_int_LCD(rt);

            delay_ms(2000);

            // If temperature exceeds setpoint and data has not been sent yet
            if(k == 0)
            {
                if(temp > rt)
                {
                    // Send temperature value to ThingSpeak field1
                    esp01_sendToThingspeak(temp, 1);

                    delay_ms(1000);

                    k++;   // Prevent immediate repeated sending
                }
            }

            // Counter logic to limit repeated data transmission
            if((k >= 1) && (k <= 30))
            {
                k++;
            }
            else
            {
                k = 0;
            }

            // Every 2 minutes, read remote setpoint from ThingSpeak
            if(min == MIN)
            {
                min += 2;

                // Read latest setpoint from ThingSpeak
                espo1_ReadfromThingspeak();

                // If remote setpoint differs from stored setpoint
                if(rt != rsp)
                {
                    // Update EEPROM with new setpoint
                    i2c_eeprom_write(0x50, 0x00, rsp);

                    // Read updated setpoint from EEPROM
                    rt = i2c_eeprom_read(0x50, 0x00);
                }
            }

            // Reset minute counter when RTC reaches 59
            if(MIN == 59)
                min = 0;

        } while(i_flag == 0);   // Exit loop when external interrupt occurs

        // Reset temporary variable
        temp = 0;

        // Prompt user to enter new setpoint
        Write_CMD_LCD(0x01);
        Write_str_LCD("Enter the setpoint");

        // Read setpoint from keypad
        temp = Readnum();

        // Store new setpoint in EEPROM
        i2c_eeprom_write(0x50, 0x00, temp);

        // Clear temporary variable
        temp = 0;

        // Read updated setpoint from EEPROM
        rt = i2c_eeprom_read(0x50, 0x00);

        // Clear LCD
        Write_CMD_LCD(0x01);

        // Clear interrupt flag and return to monitoring loop
        i_flag = 0;
    }
}
