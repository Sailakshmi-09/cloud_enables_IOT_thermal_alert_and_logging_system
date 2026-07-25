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
          Write_CMD_LCD(0x01);              // Clear the LCD display.

          Write_CMD_LCD(0x80);              // Move the cursor to the first row, first column.

          Write_str_LCD("ATE0");            // Display "ATE0" on the LCD to indicate the command being sent.

          delay_ms(1000);                   // Wait for 1 second so the message is visible.

          UART0_Str("ATE0\r\n");            // Send the "ATE0" AT command through UART.
                                  // '\r\n' indicates the end of the command.
                                  // ATE0 disables command echo from the ESP8266/GSM module.

          i = 0;                            // Initialize the receive buffer index.

          memset(buff, '\0', 350);          // Clear the receive buffer by filling it with NULL characters.

          while(i < 4);                     // Wait until at least 4 characters are received.
                                  // The UART interrupt/service routine increments 'i'
                                  // whenever a character is received.

          delay_ms(500);                    // Wait an additional 500 ms to ensure the complete response is received.

           buff[i] = '\0';                   // Append a NULL terminator to make the received data a valid C string.

           Write_CMD_LCD(0x01);              // Clear the LCD before displaying the received response.

           Write_CMD_LCD(0x80);              // Move the cursor to the beginning of the first row.

           Write_str_LCD(buff);              // Display the received response (e.g., "OK") on the LCD.

           delay_ms(2000);                   // Keep the response displayed for 2 seconds.
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
        Write_CMD_LCD(0x01);            // Clear the LCD display.
        Write_CMD_LCD(0x80);              // Move the LCD cursor to the first row, first column.

        Write_str_LCD("AT+CIPMUX");       // Display the AT command name on the LCD.

        delay_ms(1000);                   // Wait for 1 second so the command is visible.

        UART0_Str("AT+CIPMUX=0\r\n");     // Send the "AT+CIPMUX=0" command to the ESP8266.
                                  // CIPMUX=0 configures the ESP8266 for Single Connection Mode.
                                  // '\r\n' marks the end of the AT command.

        i = 0;                            // Reset the receive buffer index.

        memset(buff, '\0', 350);          // Clear the receive buffer by filling it with NULL characters.

        while(i < 4);                     // Wait until at least 4 characters are received.
                                  // The UART receive interrupt updates 'i' as data arrives.

        delay_ms(500);                    // Wait an additional 500 ms to ensure the complete response is received.

        buff[i] = '\0';                   // Append a NULL terminator to make the received data a valid C string.

        Write_CMD_LCD(0x01);              // Clear the LCD before displaying the response.

        Write_CMD_LCD(0x80);              // Move the cursor to the first row, first column.

        Write_str_LCD(buff);              // Display the received response (typically "OK") on the LCD.

        delay_ms(2000);                   // Keep the response displayed for 2 seconds.
        
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
        Write_CMD_LCD(0x01);              // Clear the LCD display.

        Write_CMD_LCD(0x80);              // Move the LCD cursor to the first row, first column.

        Write_str_LCD("AT+CWQAP");        // Display the command name "AT+CWQAP" on the LCD.

        delay_ms(1000);                   // Wait for 1 second so the command is visible.

        UART0_Str("AT+CWQAP\r\n");        // Send the "AT+CWQAP" command to the ESP8266.
                                  // This command disconnects the ESP8266 from the currently connected Wi-Fi Access Point (AP).
                                  // '\r\n' indicates the end of the AT command.

        i = 0;                            // Reset the receive buffer index.

         memset(buff, '\0', 350);          // Clear the receive buffer by filling it with NULL characters.

         while(i < 4);                     // Wait until at least 4 characters are received.
                                  // The UART receive interrupt/service routine increments 'i'
                                  // whenever a character is received.

         delay_ms(1500);                   // Wait an additional 1.5 seconds to ensure the complete response is received.

        buff[i] = '\0';                   // Append a NULL terminator to make the received data a valid C string.

        Write_CMD_LCD(0x01);              // Clear the LCD before displaying the module's response.

        Write_CMD_LCD(0x80);              // Move the LCD cursor to the first row, first column.

        Write_str_LCD(buff);              // Display the received response (e.g., "OK") on the LCD.

        delay_ms(2000);                   // Keep the response displayed for 2 seconds.
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
        Write_str_LCD("AT+CWJAP");//for wifi connection
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
        Write_CMD_LCD(0x01);                  // Clear the LCD display.

        Write_CMD_LCD(0x80);                  // Move the LCD cursor to the first row, first column.

        Write_str_LCD("AT+CIPSTART");         // Display the command name "AT+CIPSTART" on the LCD.

        delay_ms(1000);                       // Wait for 1 second so the command is visible.

        UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
                                      // Send the AT+CIPSTART command to the ESP8266.
                                      // "TCP"                 -> Select TCP protocol.
                                      // "api.thingspeak.com" -> ThingSpeak server address.
                                      // 80                   -> HTTP server port number.
                                      // '\r\n'               -> Marks the end of the AT command.

         i = 0;                                // Reset the receive buffer index.

        memset(buff, '\0', 350);              // Clear the receive buffer by filling it with NULL characters.

        while(i < 5);                         // Wait until at least 5 characters are received.
                                      // The UART receive interrupt/service routine updates 'i'
                                      // as characters are received from the ESP8266.

        delay_ms(2500);                       // Wait an additional 2.5 seconds to allow the
                                      // ESP8266 to establish the TCP connection.

        buff[i] = '\0';                       // Append a NULL terminator to make the received
                                      // data a valid C string.

        Write_CMD_LCD(0x01);                  // Clear the LCD before displaying the response.

        Write_CMD_LCD(0x80);                  // Move the cursor to the first row, first column.

        Write_str_LCD(buff);                  // Display the ESP8266 response on the LCD
                                      // (e.g., "CONNECT", "OK", or an error message).
        delay_ms(2000);
        //check if TCP connection is established
        if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);

                Write_CMD_LCD(0x01);              // Clear the LCD display.

                Write_CMD_LCD(0x80);              // Move the LCD cursor to the first row, first column.

                Write_str_LCD("AT+CIPSEND");      // Display the command name "AT+CIPSEND" on the LCD.

                delay_ms(1000);                   // Wait for 1 second so the command is visible.

                UART0_Str("AT+CIPSEND=49\r\n");   // Send the AT+CIPSEND command to the ESP8266.
                                  // 49 specifies that the next 49 bytes of data
                                  // (e.g., an HTTP GET request) will be transmitted
                                  // over the already established TCP connection.
                                  // '\r\n' marks the end of the AT command.
                i=0;memset(buff,'\0',350);
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
           Write_CMD_LCD(0x01);                  // Clear the LCD display.

           Write_CMD_LCD(0x80);                  // Move the LCD cursor to the first row, first column.

           Write_str_LCD("AT+CIPSTART");         // Display the command name "AT+CIPSTART" on the LCD.

           delay_ms(1000);                       // Wait for 1 second so the command is visible.

           UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
                                      // Send the AT+CIPSTART command to the ESP8266.
                                      // "TCP"                 -> Use TCP protocol.
                                      // "api.thingspeak.com" -> ThingSpeak server address.
                                      // 80                   -> HTTP port number.
                                      // '\r\n'               -> End of the AT command.

           i = 0;                                // Reset the receive buffer index.

           memset(buff, '\0', 350);              // Clear the receive buffer by filling it with NULL characters.

           while(i < 5);                         // Wait until at least 5 characters are received.
                                      // The UART receive interrupt/service routine
                                      // increments 'i' whenever a character is received.

          delay_ms(2500);                       // Wait an additional 2.5 seconds to allow
                                      // the ESP8266 to establish the TCP connection
                                      // and send the complete response.

          buff[i] = '\0';                       // Append a NULL terminator to make the
                                      // received data a valid C string.

          Write_CMD_LCD(0x01);                  // Clear the LCD before displaying the response.

          Write_CMD_LCD(0x80);                  // Move the LCD cursor to the first row, first column.

          Write_str_LCD(buff);                  // Display the response received from the ESP8266
                                      // (e.g., "CONNECT", "OK", or an error message).

           delay_ms(2000);                       // Keep the response displayed on the LCD
                                      // for 2 seconds before continuing.
           Write_CMD_LCD(0x01);
 //check TCP connection
       if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);

                Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);              // Move the LCD cursor to the first row, first column.

                Write_str_LCD("AT+CIPSEND");      // Display the command name "AT+CIPSEND" on the LCD.

                delay_ms(1000);                   // Wait for 1 second so the command is visible.

                UART0_Str("AT+CIPSEND=72\r\n");   // Send the AT+CIPSEND command to the ESP8266.
                                  // 72 specifies that 72 bytes of data will be sent
                                  // over the already established TCP connection.
                                  // '\r\n' indicates the end of the AT command.

                i = 0;                            // Reset the receive buffer index before receiving the response.

                memset(buff, '\0', 350);          // Clear the receive buffer by filling it with NULL characters.
                                  // This removes any previous data before storing
                                  // the new response from the ESP8266.
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
              if(strstr(buff,"SEND OK"))  
              {
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

