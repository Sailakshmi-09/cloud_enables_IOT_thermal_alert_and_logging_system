                  /* defines.h */
#ifndef __DEFINES_H__   // Prevents multiple inclusion of this header file
#define __DEFINES_H__

// ---------------- Bit Manipulation Macros ----------------

// Set a specific bit in WORD
// Example: SETBIT(PORT, 3) sets bit 3 to 1
#define SETBIT(WORD,BITPOS)            (WORD |= (1 << BITPOS))

// Clear a specific bit in WORD
// Example: CLRBIT(PORT, 3) clears bit 3 to 0
#define CLRBIT(WORD,BITPOS)            (WORD &= ~(1 << BITPOS))

// Toggle (complement) a specific bit in WORD
// Example: CPLBIT(PORT, 3) changes bit 3 from 0 to 1 or 1 to 0
#define CPLBIT(WORD,BITPOS)            (WORD ^= (1 << BITPOS))

// Write a bit value (0 or 1) to a specific bit position
// If BIT is 1, set the bit; otherwise clear the bit
#define WRITEBIT(WORD,BITPOS,BIT)      (BIT ? SETBIT(WORD,BITPOS) : CLRBIT(WORD,BITPOS))

// Read the value of a specific bit
// Returns 0 if bit is cleared, 1 if bit is set
#define READBIT(WORD,BITPOS)           ((WORD >> BITPOS) & 1)

// Copy the value of bit RBIT to bit WBIT within the same WORD
#define READWRITEBIT(WORD,WBIT,RBIT)   (WORD = ((WORD & ~(1 << WBIT)) | (((WORD >> RBIT) & 1) << WBIT)))

// ---------------- Nibble Manipulation Macros ----------------
// Write a 4-bit nibble at the specified bit position
// BYTE should contain a valid 4-bit value
#define WRITENIBBLE(WORD,BITPOS,BYTE)  (WORD = (WORD & ~(0x0000000F << BITPOS)) | (BYTE << BITPOS))

// Write only the lower 4 bits of BYTE at the specified bit position
#define WRITELNIBBLE(WORD,BITPOS,BYTE) (WORD = (WORD & ~(0x0000000F << BITPOS)) | ((BYTE & 0x0F) << BITPOS))

// Read a 4-bit nibble from the specified bit position
#define READNIBBLE(WORD,BITPOS)        ((WORD >> BITPOS) & 0x0000000F)

// ---------------- Byte Manipulation Macros ----------------

// Write an 8-bit byte at the specified bit position
#define WRITEBYTE(WORD,BITPOS,BYTE)    (WORD = (WORD & ~(0x000000FF << BITPOS)) | (BYTE << BITPOS))

// Read an 8-bit byte from the specified bit position
#define READBYTE(WORD,BITPOS)          ((WORD >> BITPOS) & 0x000000FF)

// ---------------- Special Macros ----------------

// Set WORD to have only the specified bit set
// Example: SSETBIT(PORT, 3) makes PORT = 0x08
#define SSETBIT(WORD,BITPOS)           WORD = 1 << BITPOS

// Alias for SSETBIT (same functionality)
#define SCLRBIT SSETBIT

#endif
