#include <string.h>
#include <stdlib.h>
#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "esp01.h"


extern char buff[350];
extern unsigned short int i;
extern u8 rsp;

void esp01_connectAP(void)
{
        Write_CMD_LCD(0x01);     //clear LCD
        Write_CMD_LCD(0x80);     // move cursor to final line
        Write_str_LCD("AT");      //display AT command on LCD
        delay_ms(1000);
        UART0_Str("AT\r\n");       //send AT command to ESP01
        i=0;
        memset(buff,'\0',350);     //clear response buffer    
        while(i<4);                 //wait ffor response
        delay_ms(500);             
        buff[i] = '\0';             //NUll -terminate received string
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);         //display ESP response
        delay_ms(2000);
        //check if ESP responded with ok
if(strstr(buff,"OK"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;
        }
        //disable command echo
         Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("ATE0");
        delay_ms(1000);
        UART0_Str("ATE0\r\n");
        i=0;memset(buff,'\0',350);
        while(i<4);
        delay_ms(500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);
        delay_ms(2000);
        //check response for ATEO command 
if(strstr(buff,"OK"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;
        }
        //set single connection mode
          Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CIPMUX");
        delay_ms(1000);
        UART0_Str("AT+CIPMUX=0\r\n");
        i=0;memset(buff,'\0',350);
        while(i<4);
        delay_ms(500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);
        delay_ms(2000);
if(strstr(buff,"OK"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;
        }
        //disconnect from any previously connected wi-fi network
          Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CWQAP");
        delay_ms(1000);
        UART0_Str("AT+CWQAP\r\n");
        i=0;
        memset(buff,'\0',350);
        while(i<4);
        delay_ms(1500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);
        delay_ms(2000);
if(strstr(buff,"OK"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;
        }
        //connect to Wi-Fi access point
         Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CWJAP");
        delay_ms(1000);
        //need to change the wifi network name and password
        UART0_Str("AT+CWJAP=\"vivo T2 5G\",\"sai@0907\"\r\n");
        i=0;memset(buff,'\0',350);
        while(i<4);
        delay_ms(2500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);
        delay_ms(2000);
        //check if wi-fi connection was successfull
 if(strstr(buff,"WIFI CONNECTED"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;
        }

}
void esp01_sendToThingspeak(char val,char n)
{
        //start TCP connection with thingspeak server
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CIPSTART");
        delay_ms(1000);
        UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
        i=0;memset(buff,'\0',350);
        while(i<5);
        delay_ms(2500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
Write_str_LCD(buff);
        delay_ms(2000);
        //check if TCP connection is established
        if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);

                Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);
                Write_str_LCD("AT+CIPSEND");
                delay_ms(1000);
                UART0_Str("AT+CIPSEND=49\r\n");
                i=0;memset(buff,'\0',350);
                //while(buff[i] != '>');
                delay_ms(500);
                //send HTTP GET request to update field1
                if(n==1)
                {
                //need to change the thingspeak write API key accordind to your channel
                UART0_Str("GET /update?api_key=HCIPRXE9DS0L30TW&field1=");
                }
 UART0_Int(val);     //send sensor value
                UART0_Str("\r\n\r\n");  //End HTTP request
                delay_ms(5000);
                delay_ms(5000);
                buff[i] = '\0';
                Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);
                Write_str_LCD(buff);
                delay_ms(2000);
                //check if data was sent successfully
                if(strstr(buff,"SEND OK"))
                {
                        Write_CMD_LCD(0x01);
                        Write_str_LCD("DATA UPDATED");
                        delay_ms(1000);
                }
                else
                {
                        Write_CMD_LCD(0x01);
                        Write_str_LCD("DATA NOT UPDATED");
                        delay_ms(1000);
                }

        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;
 }


}
void espo1_ReadfromThingspeak(void)
{
        u8 arr[350];        //Temporary buffer for received data
        //start TCP connection with thingspeak
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CIPSTART");
        delay_ms(1000);
        UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
        i=0;memset(buff,'\0',350);
        while(i<5);
        delay_ms(2500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);
        delay_ms(2000);
        Write_CMD_LCD(0x01);
        //check TCP connection
 if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);

                Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);
                Write_str_LCD("AT+CIPSEND");
                delay_ms(1000);
                UART0_Str("AT+CIPSEND=72\r\n");
                i=0;memset(buff,'\0',350);
                //while(buff[i] != '>');
                delay_ms(500);
                //need to change the thingspeak write API key accordind to your channel
                UART0_Str("GET /channels/3380085/fields/1.json?api_key=2AUGIDG19FMFFZJI&results=1");
                //UART0_Int(val);
                UART0_Str("\r\n");
                delay_ms(5000);
                delay_ms(5000);
                buff[i] = '\0';
                 Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);
                Write_str_LCD(buff);
                delay_ms(2000);
                strcpy((char *)arr,buff);    //copy received data
                //check if data was received successfully    
 if(strstr(buff,"SEND OK"))                                                                                                                                  {
                        Write_CMD_LCD(0x01);
                        Write_str_LCD("DATA UPDATED");
                        delay_ms(1000);
                        extract_sp(arr);
                        Write_CMD_LCD(0x01);
                }
                else
                {
                        Write_CMD_LCD(0x01);
                        Write_str_LCD("DATA NOT UPDATED");
                        delay_ms(1000);
                        Write_CMD_LCD(0x01);
                }

        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                Write_CMD_LCD(0x01);
                return;
        }
}
void extract_sp(u8 *p)
{
        u8 cnt=0,r[5],l=0;
        char *q;
        q=(char *)p;
        //find the first occurance of "field1"
        q=strstr((const char *)q,"field1");
        //while(q=(strstr(q,"field1")))
        while(q)
        {
                cnt++;
                //process the second occurance of "field1"
                if(cnt==2)
                {
                        //cnt+=7;
                        //find':' character after field1
                        q=strchr((const char *)q,':');
                        //if(q=strchr((const char *)q,':'))
                        if(q)
                        {
                                q=q+2; //move to the actual value
                        /*      Write_CMD_LCD(0x01);
                                Write_str_LCD("extract2:");
                                delay_ms(2000);
                                Write_CMD_LCD(0x01);
                                Write_str_LCD((char *)q);
                                delay_ms(5000);*/
//copy characters until closing quote
                                for(;*q!='"';q++)
                                {
                                        r[l++]=*q;
                                }
                                r[l]='\0';   //null-terminate extracted string
                        }
                        break;
                }
                q++;
                q=strstr((const char *)q,"field1");
        }
        //convert extracted string to integer
         rsp=atoi((const char *)r);
         //display extracted value on LCD
        Write_CMD_LCD(0x01);
        Write_str_LCD("Remote sp: ");
        Write_int_LCD(rsp);
        delay_ms(3000);
        Write_CMD_LCD(0x01);
}

