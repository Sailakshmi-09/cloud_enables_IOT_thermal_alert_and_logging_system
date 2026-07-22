// Function declaration to send a command to the LCD
// Commands control LCD operations such as clearing the display,
// moving the cursor, turning the display ON/OFF, etc.
void Write_CMD_LCD(char);

// Function declaration to send a single character (data) to the LCD
// The character will be displayed at the current cursor position
void Write_DAT_LCD(char);

// Common low-level function to send a byte to the LCD
// Used internally by both command and data functions
void Write_LCD(char);

// Function declaration to initialize the LCD
// Configures the LCD in 8-bit mode and prepares it for display
void LCD_Init(void);

// Function declaration to display a string on the LCD
// Parameter:
//   char * - Pointer to the string to be displayed
void Write_str_LCD(char *);

// Function declaration to display a signed integer on the LCD
// Parameter:
//   signed int - Integer value to display
// Range of signed int (2 bytes): -32768 to 32767
void Write_int_LCD(signed int);

// Function declaration to display a floating-point number on the LCD
// Parameters:
//   float f - Floating-point number to display
//   char  - Number of digits to display after the decimal point
void Write_float_LCD(float f, char);
