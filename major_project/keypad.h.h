#ifndef __KEYPAD_H__     // Prevents multiple inclusion of this header file
#define __KEYPAD_H__

// Function declaration to initialize the keypad module
// Configures keypad row pins as outputs and prepares the keypad for scanning
void initkpm(void);

// Function declaration to identify which row contains the pressed key
// Returns: row number (0 to 3)
u8 Rowcheck(void);

// Function declaration to identify which column contains the pressed key
// Returns: column number (0 to 3)
u8 colcheck(void);

// Function declaration to scan the keypad columns
// Returns: 0 if a key is pressed, 1 if no key is pressed
u8 colscan(void);

// Function declaration to scan the keypad and return the pressed key
// Returns: ASCII character corresponding to the pressed key
u8 keyscan(void);

// Function declaration to read a multi-digit number from the keypad
// Returns: the entered number as an unsigned 32-bit integer
u32 Readnum(void);

// Function declaration for password handling
// Parameter:
//   u8 * - Pointer to the password buffer
void password(u8 *);

#endif
