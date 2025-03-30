#include <bsp/board_api.h>
#include "i2c_register_defs.h"
#include "i2c_registers_api.h"
#include "rtcclock.h"

extern RTC_HandleTypeDef RTCHandle;

typedef union rtc_timestamp_t _rtc_timestamp_t, *PTIMESTAMP_T, **LPTIMESTAMP_T;
void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(rtcHandle->Instance==RTC)
  {
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
//      Error_Handler();
    }
    __HAL_RCC_RTC_ENABLE();
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{
  if(rtcHandle->Instance==RTC)
  {
    __HAL_RCC_RTC_DISABLE();
  }
}

_rtc_timestamp_t GetFullTimestamp_BIN(void){
    _rtc_timestamp_t ts = {0,};
    HAL_RTC_GetTime(&RTCHandle, &ts.Time, RTC_FORMAT_BIN); // RTC_FORMAT_BCD;
    HAL_RTC_GetDate(&RTCHandle, &ts.Date, RTC_FORMAT_BIN); // RTC_FORMAT_BCD;      

    return ts;
}

_rtc_timestamp_t GetFullTimestamp_BCD(void){
    _rtc_timestamp_t ts = {0,};
    HAL_RTC_GetTime(&RTCHandle, &ts.Time, RTC_FORMAT_BCD); 
    HAL_RTC_GetDate(&RTCHandle, &ts.Date, RTC_FORMAT_BCD);      

    return ts;
}

void SendCurrentTimestamp_to_I2C_Register(void){
    _rtc_timestamp_t ts = GetFullTimestamp_BCD();
    rtc_reg_idx_t idx = {0, };
    idx = reg_rtc_get_idx(HW_RTC_YEAR_ADDR);    
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Date.Year;
    
    idx = reg_rtc_get_idx(HW_RTC_MONTH_ADDR);
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Date.Month;
    
    idx = reg_rtc_get_idx(HW_RTC_DAY_ADDR);
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Date.Date;
    
    idx = reg_rtc_get_idx(HW_RTC_HOURS_ADDR);
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Time.Hours;

    idx = reg_rtc_get_idx(HW_RTC_MINUTES_ADDR);
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Time.Minutes;

    idx = reg_rtc_get_idx(HW_RTC_SECONDS_ADDR);
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Time.Seconds;

    idx = reg_rtc_get_idx(HW_RTC_SUBSECS_ADDR);
    g_i2c_rtc_registers[idx].value.uint16_val = ts.Time.SubSeconds;
}
