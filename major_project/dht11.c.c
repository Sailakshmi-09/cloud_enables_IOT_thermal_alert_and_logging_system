#define input 0       // Macro to configure a pin as input
#define output 1      // Macro to configure a pin as output

#define DHT11 4       // DHT11 data pin connected to P0.4

// Function to send a start request signal to the DHT11 sensor
void dht11_request(void)
{
    // Configure DHT11 pin as output
    WRITEBIT(IODIR0, DHT11, output);

    // Pull the data line LOW for at least 18 ms
    // This signals the DHT11 to start communication
    WRITEBIT(IOPIN0, DHT11, 0);

    // Keep the line LOW for 20 ms
    delay_ms(20);

    // Pull the data line HIGH
    // The DHT11 will respond after this
    WRITEBIT(IOPIN0, DHT11, 1);
}

// Function to wait for the DHT11 response signal
void dht11_response(void)
{
    // Configure DHT11 pin as input to receive data
    WRITEBIT(IODIR0, DHT11, input);
// Wait until the DHT11 pulls the line LOW
    while(READBIT(IOPIN0, DHT11) == 1);

    // Wait until the DHT11 pulls the line HIGH
    while(READBIT(IOPIN0, DHT11) == 0);

    // Wait until the DHT11 completes its response signal
    while(READBIT(IOPIN0, DHT11) == 1);
}

// Function to read one byte (8 bits) of data from the DHT11
unsigned char dht11_data(void)
{
    unsigned char count;
    unsigned char data = 0;   // Variable to store received byte

    // Loop to read 8 bits
    for(count = 0; count < 8; count++)
    {
        // Wait until the line goes HIGH (start of bit transmission)
        while(READBIT(IOPIN0, DHT11) == 0);

        // Wait for 30 microseconds
        // DHT11 sends:
        //   ~26-28 us HIGH for bit 0
        //   ~70 us HIGH for bit 1
        delay_us(30);
// Read the pin state after 30 us
        if (READBIT(IOPIN0, DHT11))
        {
            // If still HIGH, it is a bit '1'
            data = ((data << 1) | 0x01);
        }
        else
        {
            // If LOW, it is a bit '0'
            data = (data << 1);
        }

        // Wait until the HIGH signal ends before reading next bit
        while(READBIT(IOPIN0, DHT11));
    }

    // Return the complete 8-bit data byte
    return data;
}
