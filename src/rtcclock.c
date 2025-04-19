#include <bsp/board_api.h>
#include <stm32f4xx_hal_conf.h>
#include "i2c_register_defs.h"
#include "i2c_registers_api.h"
#include "rtcclock.h"

extern RTC_HandleTypeDef RTCHandle;
extern I2C_HandleTypeDef I2CHandle;
static rtc_timestamp_t ts = {0};
static rtc_timestamp_t _ts_out = {0};

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

// Установка ввнутренних часов (бинарный формат)
bool SetFullTimestamp_BIN(rtc_timestamp_t* timestamp){
  UNUSED(timestamp);
  return true;
}

// Установка ввнутренних часов (бинарный формат)
bool SetFullTimestamp_BCD(rtc_timestamp_t* timestamp){
  UNUSED(timestamp);
  return true;
}

reg_t* GetI2CRegisterRowByIdx( int RegisterAddress ){
  return &g_i2c_rtc_registers[reg_rtc_get_idx(RegisterAddress)];
}

// Отправляем данные о времени в регистр
void SendCurrentTimestamp_to_I2C_Register(void){
    rtc_timestamp_t *_ts_local = GetFullTimestamp_BCD();
    GetI2CRegisterRowByIdx(HW_RTC_YEAR_ADDR)->value.uint32_val = _ts_local->Date.Year;
    GetI2CRegisterRowByIdx(HW_RTC_MONTH_ADDR)->value.uint32_val = _ts_local->Date.Month;
    GetI2CRegisterRowByIdx(HW_RTC_DAY_ADDR)->value.uint32_val = _ts_local->Date.Date;    
    GetI2CRegisterRowByIdx(HW_RTC_HOURS_ADDR)->value.uint32_val = _ts_local->Time.Hours;
    GetI2CRegisterRowByIdx(HW_RTC_MINUTES_ADDR)->value.uint32_val = _ts_local->Time.Minutes;
    GetI2CRegisterRowByIdx(HW_RTC_SECONDS_ADDR)->value.uint32_val = _ts_local->Time.Seconds;
    GetI2CRegisterRowByIdx(HW_RTC_SUBSECS_ADDR)->value.uint32_val = _ts_local->Time.SubSeconds;
}

// RTC_API IMPLEMENTATION

// Отправка рукопожатия материнской плате
void SendStartHandshakeCmd(void){
  GetI2CRegisterRowByIdx(HW_RTC_CONTROL_ADDR)->value.uint32_val = 0xAA;
  return;
}

// отправка ответа о том, что синхронизация часов прошла успешно
void SendSetTimestampInfo(void){
  GetI2CRegisterRowByIdx(HW_RTC_CONTROL_ADDR)->value.uint32_val = 0xCC;
  return;
}

// проверка, что материнка приняла рукопожатие и отправила ответ
bool GetHostHandShakeRcvd(void){
  return (GetI2CRegisterRowByIdx(HW_RTC_CONTROL_ADDR)->value.uint32_val == 0xBB);
}

// проверка, что мы отправили хэндшейк
bool GetBoardHandshakeSend(void){
  return (GetI2CRegisterRowByIdx(HW_RTC_CONTROL_ADDR)->value.uint32_val == 0xAA);
}

// считывание ответа о том, что синхронизация часов прошла успешно
bool GetHRTCSetUpOk(void){
  return (GetI2CRegisterRowByIdx(HW_RTC_CONTROL_ADDR)->value.uint32_val == 0xCC);
}

uint32_t GetHRTC_CurrentControlRegisterFlag(void){
  return (GetI2CRegisterRowByIdx(HW_RTC_CONTROL_ADDR)->value.uint32_val);
}
// считываем данные полученные от материнской платы
rtc_timestamp_t* ReadCurrentTimestamp_from_I2C_Register(void){
  
  _ts_out.Date.Year = GetI2CRegisterRowByIdx(HW_RTC_YEAR_ADDR)->value.uint32_val;
  _ts_out.Date.Month = GetI2CRegisterRowByIdx(HW_RTC_MONTH_ADDR)->value.uint32_val;
  _ts_out.Date.Date = GetI2CRegisterRowByIdx(HW_RTC_DAY_ADDR)->value.uint32_val;    
  _ts_out.Time.Hours = GetI2CRegisterRowByIdx(HW_RTC_HOURS_ADDR)->value.uint32_val;
  _ts_out.Time.Minutes = GetI2CRegisterRowByIdx(HW_RTC_MINUTES_ADDR)->value.uint32_val;
  _ts_out.Time.Seconds = GetI2CRegisterRowByIdx(HW_RTC_SECONDS_ADDR)->value.uint32_val;
  _ts_out.Time.SubSeconds = GetI2CRegisterRowByIdx(HW_RTC_SUBSECS_ADDR)->value.uint32_val;

  return &_ts_out;
}

HAL_StatusTypeDef SetMCUTime(RTC_TimeTypeDef* sTime){
  sTime->DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime->StoreOperation = RTC_STOREOPERATION_RESET;
  return HAL_RTC_SetTime(&RTCHandle, sTime, RTC_FORMAT_BIN);
}

HAL_StatusTypeDef SetMCUDate(RTC_DateTypeDef* sDate){
  // sDate->WeekDay = RTC_WEEKDAY_WEDNESDAY;
  // sDate->Month = RTC_MONTH_FEBRUARY;
  return HAL_RTC_SetDate(&RTCHandle, sDate, RTC_FORMAT_BIN);
}