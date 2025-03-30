#ifndef __RTC_CLOCK_H_
#define __RTC_CLOCK_H_
#include <stm32f4xx_hal_conf.h>

typedef union rtc_timestamp_t{
    RTC_DateTypeDef Date;
    RTC_TimeTypeDef Time;    
}_rtc_timestamp_t;

// #define T_STR_S    "Date %d-%d-20%d, Time %d:%d:%d\r\n"
// #define T_STR_SZ    36
extern _rtc_timestamp_t GetFullTimestamp_BIN(void);
extern _rtc_timestamp_t GetFullTimestamp_BCD(void);

#endif