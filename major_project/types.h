                     /* types.h */
#ifndef __TYPES_H__      // Prevents multiple inclusion of this header file
#define __TYPES_H__

// ---------------- 8-bit Data Types ----------------

// Unsigned 8-bit integer (0 to 255)
typedef unsigned char u8;

// Signed 8-bit integer (-128 to 127)
typedef signed char s8;

// ---------------- 16-bit Data Types ----------------

// Unsigned 16-bit integer (0 to 65535)
typedef unsigned short int u16;

// Signed 16-bit integer (-32768 to 32767)
typedef signed short int s16;

// ---------------- 32-bit Data Types ----------------

// Unsigned 32-bit integer (0 to 4,294,967,295)
typedef unsigned int u32;

// Signed 32-bit integer (-2,147,483,648 to 2,147,483,647)
typedef signed int s32;

// ---------------- Floating Point Data Types ----------------

// 32-bit floating-point number
typedef float f32;

// 64-bit floating-point number (double precision)
typedef double f64;

#endif
