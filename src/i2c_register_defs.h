#ifndef __I2C_REGISTERS_H_
#define __I2C_REGISTERS_H_
#include <stdint.h>
#include "tusb_config.h"
#ifdef __USE_TEST_REGISTERS
//Register Addresses
#define REG_VERSION_ADDR                0x00
#define REG_UINT16_RW_ADDR              0x01
#define REG_INT16_RW_ADDR               0x02
#define REG_BOOL_RW_ADDR                0x03
#define REG_CHAR_RW_ADDR                0x04
#define REG_UINT32_RW_ADDR              0x05
#define REG_INT32_RW_ADDR               0x06

#define REG_UINT16_RO_ADDR              0x11
#define REG_INT16_RO_ADDR               0x12
#define REG_BOOL_RO_ADDR                0x13
#define REG_CHAR_RO_ADDR                0x14
#define REG_UINT32_RO_ADDR              0x15
#define REG_INT32_RO_ADDR               0x16

#define I2C_CHAR_ARRAY_SZ               0x16

//Register structure
typedef enum reg_idx_t reg_idx_t;
typedef struct i2c_s i2c_s;
#endif

#ifdef __USE_RTC_REGISTERS
typedef enum rtc_reg_idx_t rtc_reg_idx_t;
typedef struct rtc_i2c_s rtc_i2c_s;
#endif

typedef struct reg_t reg_t;

typedef union var_t var_t;
typedef enum val_type_t val_type_t;
typedef enum reg_mode_t reg_mode_t;
typedef struct char32_array char32_array;

//Register value types
// typedef struct char32_array{
//     const uint32_t array_sz;
//     char f_char32_array[32];
// } _char32_array, *LP_CHAR32_ARRAY;


typedef enum val_type_t {
    EMPTY,
    UNDEFINED,
    BOOL,
    UINT16,
    INT16,
    UINT32,
    INT32,
    CHAR
} val_type_t;
//Type for register values
typedef union var_t {
    uint8_t     bool_val;
    uint16_t    uint16_val;
    int16_t     int16_val;
    uint32_t    uint32_val;
    int32_t     int32_val;
    char     char_val;
} _var_t, *PVAR_T, **LPVAR_T;
//Access table to registers
typedef enum reg_mode_t {
    RESERVED = 0,
    READ_ONLY,
    FULL_ACCESS
}reg_mode_t;

struct reg_t {
    uint8_t     access;         //Access
    uint8_t     reg_addr;       //Address
    val_type_t  value_type;     //Value type
    const var_t def_val;        //Default values
    var_t       value;          //Current values
};

#ifdef __USE_TEST_REGISTERS
// Отладочный регистр
//Register indices
typedef enum reg_idx_t {
    NONE = -1,
    ECHO = 0,
    VERSION,
    UINT16_RW,
    INT16_RW,
    UINT32_RW,
    INT32_RW,
    BOOL_RW,
    CHAR_RW,
    UINT16_RO,
    INT16_RO,
    UINT32_RO,
    INT32_RO,
    BOOL_RO,
    CHAR_RO,
    REGISTER_NUM
} reg_idx_t;

typedef struct i2c_s {
    reg_idx_t   curr_idx;
    uint8_t     reg_addr_rcvd;
    uint8_t     reg_address;
} _i2c_s, *P_I2C_T, **LP_I2C_T;

extern reg_t g_i2c_reg_data[];          // Test example register
#endif

#ifdef __USE_RTC_REGISTERS
/////////////////////////////////
/// @brief i2c register read/write struct
/////////////////////////////////

// Описатель регистра RTC
#define HW_EXTEDNER_I2C_REG_BASE 0x11
#define HW_STD_OFFSET (0x05)

#define HW_EXTENDER_RTC_REG_OFFSET  (HW_EXTEDNER_I2C_REG_BASE + HW_STD_OFFSET)
#define HW_RTC_BASE (HW_EXTENDER_RTC_REG_OFFSET)

// Адреса функций
#define HW_RTC_VERSION_ADDR  HW_RTC_BASE
#define HW_RTC_SUBSECS_ADDR  (HW_RTC_BASE + 0x01)
#define HW_RTC_SECONDS_ADDR  (HW_RTC_BASE + 0x02)
#define HW_RTC_MINUTES_ADDR  (HW_RTC_BASE + 0x03)
#define HW_RTC_HOURS_ADDR    (HW_RTC_BASE + 0x04)
#define HW_RTC_DAY_ADDR      (HW_RTC_BASE + 0x05)
#define HW_RTC_DATE_ADDR     (HW_RTC_BASE + 0x06)
#define HW_RTC_MONTH_ADDR    (HW_RTC_BASE + 0x07)
#define HW_RTC_YEAR_ADDR     (HW_RTC_BASE + 0x08)
#define HW_RTC_CONTROL_ADDR  (HW_RTC_BASE + 0x09)
#define HW_RTC_RAM00_ADDR    (HW_RTC_BASE + 0x0A)
#define HW_RTC_RAM01_ADDR    (HW_RTC_BASE + 0x0B)
#define HW_RTC_RAM02_ADDR    (HW_RTC_BASE + 0x0C)
#define HW_RTC_RAM03_ADDR    (HW_RTC_BASE + 0x0D)
#define HW_RTC_RAM04_ADDR    (HW_RTC_BASE + 0x0E)
#define HW_RTC_RAM05_ADDR    (HW_RTC_BASE + 0x0F)
#define HW_RTC_RAM06_ADDR    (HW_RTC_BASE + 0x10)
#define HW_RTC_RAM07_ADDR    (HW_RTC_BASE + 0x11)
#define HW_RTC_RAM08_ADDR    (HW_RTC_BASE + 0x12)
#define HW_RTC_RAM09_ADDR    (HW_RTC_BASE + 0x13)
#define HW_RTC_RAM0A_ADDR    (HW_RTC_BASE + 0x14)
#define HW_RTC_RAM0B_ADDR    (HW_RTC_BASE + 0x15)
#define HW_RTC_RAM0C_ADDR    (HW_RTC_BASE + 0x16)
#define HW_RTC_RAM0D_ADDR    (HW_RTC_BASE + 0x17)
#define HW_RTC_RAM0E_ADDR    (HW_RTC_BASE + 0x18)
#define HW_RTC_RAM0F_ADDR    (HW_RTC_BASE + 0x19)
#define HW_RTC_NUM_ID_ADDR   (HW_RTC_BASE + 0x1A)

// Описатель комманд
#define HW_RTC_CMD_INITIAL                  0xAA
#define HW_RTC_CMD_INITIAL_HANDSHAKE        0xBB
#define HW_RTC_CMD_TX_MAIN_TIME             HW_RTC_CMD_INITIAL + 0x01   // local board rtc clock values
#define HW_RTC_CMD_RX_REMT_TIME             HW_RTC_CMD_INITIAL + 0x02   // remote board rtc clock values
#define HW_RTC_CMD_WAIT_FOR_LOCAL_SETUP     HW_RTC_CMD_INITIAL + 0x03   // wait flag for setup local board rtc clock
#define HW_RTC_CMD_WAIT_FOR_REMOTE_SETUP    HW_RTC_CMD_INITIAL + 0x04   // wait flag for setup remote board rtc clock
#define HW_RTC_CMD_LOCAL_SETUP_COMPLETE     HW_RTC_CMD_INITIAL + 0x05   // wait flag for setup remote board rtc clock
#define HW_RTC_CMD_REMOTE_SETUP_COMPLETE    HW_RTC_CMD_INITIAL + 0x06   // wait flag for setup remote board rtc clock
/// @brief Описание протокола взаимодействия флагов
// 1. Локальная доска отправляет 0xAA HW_RTC_CMD_INITIAL и ждет от мастера 0xBB HW_RTC_CMD_INITIAL_HANDSHAKE, ни каких действий с регистром не производим
// 2. После получения 0xBB HW_RTC_CMD_INITIAL_HANDSHAKE от мастера, доска отправляет для мастера текущие значения RTC_CLOCK в регистр 
// 2.1. устанавливает HW_RTC_CMD_TX_MAIN_TIME
// 2.2. ждет от мастера HW_RTC_CMD_RX_REMT_TIME больше ни каких действий с регистром не производит
// 2.3. После получения HW_RTC_CMD_RX_REMT_TIME от мастера, считываем значения регистров - данные RTC мастера
// 3. Сравнивает текущее локальное значение локальных RTC со значениями RTC мастера
// 4. Значения равны устанавливаем HW_RTC_CMD_INITIAL, выход из алгоритма
// 5. Если Значение от мастера > текущих локальных то подразумеваем, что мастер обновил часы по интернет 
// 5.1. устанавливаем значение команды HW_RTC_CMD_WAIT_FOR_LOCAL_SETUP
// 5.2. устанавливаем локальные часы по значению из регистра от мастера 
// 5.3. Устанавливаем HW_RTC_CMD_LOCAL_SETUP_COMPLETE
// 5.4. Выход из алгоритма, мастер сам должен проинициализировать синхронизацию
// 6. Если Значение от текущих локальных > часов от мастера, то мастер должен обновить свои часы по нашим, 
// 6.1 устанавливаем флаг HW_RTC_CMD_WAIT_FOR_REMOTE_SETUP, ждем от мастера HW_RTC_CMD_REMOTE_SETUP_COMPLETE или таймаут
// 6.2. По таймауту или флагу пишем в регистр HW_RTC_CMD_INITIAL 
// 6.3. Выход из алгоритма
///

// Описатель функций
typedef enum rtc_reg_idx_t{
    RTC_NONE    = - 2,
    RTC_ECHO    = - 1,
    RTC_REGISTER_VERSION = 0,
    RTC_SUBSECS,
    RTC_SECONDS,
    RTC_MINUTES,
    RTC_HOURS,
    RTC_DAY,
    RTC_DATE,
    RTC_MONTH,
    RTC_YEAR,
    RTC_CONTROL,
    RTC_RAM00,
    RTC_RAM01,
    RTC_RAM02,
    RTC_RAM03,
    RTC_RAM04,
    RTC_RAM05,
    RTC_RAM06,
    RTC_RAM07,
    RTC_RAM08,
    RTC_RAM09,
    RTC_RAM0A,
    RTC_RAM0B,
    RTC_RAM0C,
    RTC_RAM0D,
    RTC_RAM0E,
    RTC_RAM0F,
    RTC_REGISTER_SZ
} _rtc_reg_idx_t;

typedef struct rtc_i2c_s {
    rtc_reg_idx_t   curr_idx;
    uint8_t     reg_addr_rcvd;
    uint8_t     reg_address;
} _rtc_i2c_s, *PRTC_I2C_T, **LPRTC_I2C_T;

extern reg_t g_i2c_rtc_registers[];     // working i2c date time register
#endif

#endif