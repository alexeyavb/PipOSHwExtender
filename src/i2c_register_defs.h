#ifndef __I2C_REGISTERS_H_
#define __I2C_REGISTERS_H_
#include <stdint.h>

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
typedef struct reg_t reg_t;
typedef struct char32_array char32_array;
typedef union var_t var_t;
typedef enum val_type_t val_type_t;

//Type for register values
typedef union var_t {
    uint8_t     bool_val;
    uint16_t    uint16_val;
    int16_t     int16_val;
    uint32_t    uint32_val;
    int32_t     int32_val;
    char     char_val;
} var_t;

//Register value types
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

struct reg_t {
    uint8_t     access;         //Access
    uint8_t     reg_addr;       //Address
    val_type_t  value_type;     //Value type
    const var_t def_val;        //Default values
    var_t       value;          //Current values
};

//Access table to registers
typedef enum reg_mode_t {
    RESERVED = 0,
    READ_ONLY,
    FULL_ACCESS
} reg_mode_t;

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

/////////////////////////////////
/// @brief i2c register read/write struct
/////////////////////////////////
typedef struct i2c_s {
    reg_idx_t   curr_idx;
    uint8_t     reg_addr_rcvd;
    uint8_t     reg_address;
} i2c_t;

typedef struct char32_array{
    const uint32_t array_sz;
    char f_char32_array[I2C_CHAR_ARRAY_SZ];
}char_array;

// Описатель регистра RTC
#define HW_EXTEDNER_I2C_REG_BASE 0x11


// Начальное смещение
#define HW_STD_OFFSET (0x05)
#define HW_EXTENDER_RTC_REG_OFFSET  (HW_EXTEDNER_I2C_REG_BASE + HW_STD_OFFSET)
#define HW_RTC_BASE (HW_EXTENDER_RTC_REG_OFFSET)

// Адреса функций
#define HW_RTC_SECONDS_ADDR  HW_RTC_BASE
#define HW_RTC_MINUTES_ADDR  (HW_RTC_BASE + 0x01)
#define HW_RTC_HOURS_ADDR    (HW_RTC_BASE + 0x02)
#define HW_RTC_DAY_ADDR      (HW_RTC_BASE + 0x03)
#define HW_RTC_DATE_ADDR     (HW_RTC_BASE + 0x04)
#define HW_RTC_MONTH_ADDR    (HW_RTC_BASE + 0x05)
#define HW_RTC_YEAR_ADDR     (HW_RTC_BASE + 0x06)
#define HW_RTC_CONTROL_ADDR  (HW_RTC_BASE + 0x07)
#define HW_RTC_RAM00_ADDR    (HW_RTC_BASE + 0x08)
#define HW_RTC_RAM01_ADDR    (HW_RTC_BASE + 0x09)
#define HW_RTC_RAM02_ADDR    (HW_RTC_BASE + 0x0A)
#define HW_RTC_RAM03_ADDR    (HW_RTC_BASE + 0x0B)
#define HW_RTC_RAM04_ADDR    (HW_RTC_BASE + 0x0C)
#define HW_RTC_RAM05_ADDR    (HW_RTC_BASE + 0x0D)
#define HW_RTC_RAM06_ADDR    (HW_RTC_BASE + 0x0E)
#define HW_RTC_RAM07_ADDR    (HW_RTC_BASE + 0x0F)
#define HW_RTC_RAM08_ADDR    (HW_RTC_BASE + 0x10)
#define HW_RTC_RAM09_ADDR    (HW_RTC_BASE + 0x11)
#define HW_RTC_RAM0A_ADDR    (HW_RTC_BASE + 0x12)
#define HW_RTC_RAM0B_ADDR    (HW_RTC_BASE + 0x13)
#define HW_RTC_RAM0C_ADDR    (HW_RTC_BASE + 0x14)
#define HW_RTC_RAM0D_ADDR    (HW_RTC_BASE + 0x15)
#define HW_RTC_RAM0E_ADDR    (HW_RTC_BASE + 0x16)
#define HW_RTC_RAM0F_ADDR    (HW_RTC_BASE + 0x17)
#define HW_RTC_VERSION_ADDR  (HW_RTC_BASE + 0x18)
#define HW_RTC_NUM_ID_ADDR   (HW_RTC_BASE + 0x19)


#endif