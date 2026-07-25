#ifndef __RTC_H__      // Prevents multiple inclusion of this header file
#define __RTC_H__

// Function declaration to initialize the Real Time Clock (RTC)
// This function configures the RTC prescaler and enables the RTC
void RTC_Init(void);

// Function declaration to set the RTC time
// Parameters:
//   u32 - Hour value (0 to 23)
//   u32 - Minute value (0 to 59)
//   u32 - Second value (0 to 59)
void RTCSetTime(u32, u32, u32);

#endif
