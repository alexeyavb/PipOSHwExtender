#ifndef __RTC_CLOCK_H_
#define __RTC_CLOCK_H_
#include <stm32f4xx_hal_conf.h>
typedef struct rtc_timestamp_t rtc_timestamp_t;
typedef struct rtc_timestamp_t{
    RTC_DateTypeDef Date;
    RTC_TimeTypeDef Time;    
}rtc_timestamp_t;

// #define T_STR_S    "Date %d-%d-20%d, Time %d:%d:%d\r\n"
// #define T_STR_SZ    36
extern rtc_timestamp_t* GetFullTimestamp_BIN(void);
extern rtc_timestamp_t* GetFullTimestamp_BCD(void);
extern uint32_t GetHRTC_CurrentControlRegisterFlag(void);
extern void SendCurrentTimestamp_to_I2C_Register(void);
extern void SendStartHandshakeCmd(void);
extern rtc_timestamp_t* ReadCurrentTimestamp_from_I2C_Register(void);



/// @brief Пример установки даты/времени
///
/*
void inline incl_SetInitialDateTime(void) {
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef DateToUpdate = {0};

    // Initialize RTC and set the Time and Date
    DateToUpdate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
    DateToUpdate.Month = RTC_MONTH_FEBRUARY;
    DateToUpdate.Date = 20;
    DateToUpdate.Year = 19;
    if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
    {
        // Error_Handler();
    }
    // Time setup
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;

    sTime.Hours = 10;
    sTime.Minutes = 34;
    sTime.Seconds = 0;

    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        // Error_Handler();
    }
}
*/


#endif