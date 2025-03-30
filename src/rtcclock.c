#include <bsp/board_api.h>
#include <stm32f4xx_hal_conf.h>
#include "i2c_register_defs.h"
#include "i2c_registers_api.h"
#include "rtcclock.h"

extern RTC_HandleTypeDef RTCHandle;
extern I2C_HandleTypeDef I2CHandle;
static rtc_timestamp_t ts = {0,};


typedef struct rtc_timestamp_t rtc_timestamp_t, *PTIMESTAMP_T, **LPTIMESTAMP_T;
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


rtc_timestamp_t* GetFullTimestamp_BIN(void){
    
    HAL_RTC_GetTime(&RTCHandle, &ts.Time, RTC_FORMAT_BIN); // RTC_FORMAT_BCD;
    HAL_RTC_GetDate(&RTCHandle, &ts.Date, RTC_FORMAT_BIN); // RTC_FORMAT_BCD;      

    return &ts;
}

rtc_timestamp_t* GetFullTimestamp_BCD(void){    

    HAL_RTC_GetTime(&RTCHandle, &ts.Time, RTC_FORMAT_BCD); 
    HAL_RTC_GetDate(&RTCHandle, &ts.Date, RTC_FORMAT_BCD);      

    return &ts;
}

reg_t* GetI2CRegisterRowByIdx( int RegisterAddress ){
  return &g_i2c_rtc_registers[reg_rtc_get_idx(RegisterAddress)];
}
void SendCurrentTimestamp_to_I2C_Register(void){
    rtc_timestamp_t *_ts = GetFullTimestamp_BCD();
    GetI2CRegisterRowByIdx(HW_RTC_YEAR_ADDR)->value.uint32_val = _ts->Date.Year;
    GetI2CRegisterRowByIdx(HW_RTC_MONTH_ADDR)->value.uint32_val = _ts->Date.Month;
    GetI2CRegisterRowByIdx(HW_RTC_DAY_ADDR)->value.uint32_val = _ts->Date.Date;    
    GetI2CRegisterRowByIdx(HW_RTC_HOURS_ADDR)->value.uint32_val = _ts->Time.Hours;
    GetI2CRegisterRowByIdx(HW_RTC_MINUTES_ADDR)->value.uint32_val = _ts->Time.Minutes;
    GetI2CRegisterRowByIdx(HW_RTC_SECONDS_ADDR)->value.uint32_val = _ts->Time.Seconds;
    GetI2CRegisterRowByIdx(HW_RTC_SUBSECS_ADDR)->value.uint32_val = _ts->Time.SubSeconds;
    // I2CHandle.pBuffPtr = 0x00;
}
