#ifndef _ESP01_H_          // Prevents multiple inclusion of this header file
#define _ESP01_H_

// Function declaration to connect ESP01 module to a Wi-Fi Access Point
// This function sends AT commands to initialize ESP01 and join a Wi-Fi network
void esp01_connectAP(void);

// Function declaration to send data to ThingSpeak
// Parameters:
//   char val - Sensor value to be sent
//   char n   - Field number selection (e.g., field1, field2)
void esp01_sendToThingspeak(char val, char n);

// Function declaration to extract the setpoint value from received JSON data
// Parameter:
//   u8 * - Pointer to the received data buffer
void extract_sp(u8 *);

// Function declaration to read data from ThingSpeak
// This function retrieves the latest value from a specified ThingSpeak channel
void espo1_ReadfromThingspeak(void);

#endif
