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

u8 rt,rsp,smoke;
extern u8 i_flag;
u8 temp,k=0,min;
f32 eAR;
main()
{
        InitUART0();
        LCD_Init();
        init_i2c();
        initkpm();
        Enable_EINT0();
        RTC_Init();
        RTCSetTime(16,15,0);
        Write_str_LCD("ESP01 CONNECT");
        delay_ms(1000);
        esp01_connectAP();
        Init_ADC();
        i2c_eeprom_write(0x50,0x00,45);
        rt=i2c_eeprom_read(0x50,0x00);
        Write_CMD_LCD(0x01);
        delay_ms(2000);
        min=MIN;
        while(1)
        {
                 k=0;
                do
                {
                                eAR=Read_ADC(1);
                                temp=eAR*100;
                                Write_CMD_LCD(0x80);
                                Write_str_LCD("T: ");
                                Write_int_LCD(temp);
                                Write_DAT_LCD(223);
                                Write_str_LCD("C");
                                Write_CMD_LCD(0x80+10);
                                Write_str_LCD("SP: ");
                                Write_int_LCD(rt);
                                delay_ms(2000);
                                if(k==0)
                                {
                                        if(temp>rt)
                                        {
                                                esp01_sendToThingspeak(temp,1);
                                                delay_ms(1000);
                                                k++;
                                        }
                                }
                                if((k>=1)&&(k<=30))
                                {
                                        k++;
                                }
                                else
                                        k=0;
                                if(min==MIN)
                                {
                                        min+=2;
                                        espo1_ReadfromThingspeak();
                                        if(rt!=rsp)
                                        {
                                                i2c_eeprom_write(0x50,0x00,rsp);
                                                rt=i2c_eeprom_read(0x50,0x00);
                                        }
                                }
                                 }
                                if(MIN==59)
                                        min=0;
                }while(i_flag==0);
                temp=0;
                Write_CMD_LCD(0x01);
                Write_str_LCD("Enter the setpoint");
                temp=Readnum();
                i2c_eeprom_write(0x50,0x00,temp);
                temp=0;
                rt=i2c_eeprom_read(0x50,0x00);
                Write_CMD_LCD(0x01);
                i_flag=0;
        }
}
