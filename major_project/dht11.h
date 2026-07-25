#ifndef _DHT11_H_      // Prevents multiple inclusion of this header file
#define _DHT11_H_

// Function declaration to send a start request signal to the DHT11 sensor
// The microcontroller pulls the data line LOW for at least 18 ms
void dht11_request(void);

// Function declaration to wait for and detect the DHT11 response signal
// The sensor responds with a specific LOW-HIGH pulse sequence
void dht11_response(void);

// Function declaration to read one byte (8 bits) of data from the DHT11 sensor
// Returns: an unsigned char containing the received data byte
unsigned char dht11_data(void);

#endif
