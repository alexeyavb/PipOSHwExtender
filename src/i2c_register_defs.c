#include "i2c_register_defs.h"
// i2c register descriptor
// Отладочный регистр
reg_t g_i2c_reg_data[] =
{
    [VERSION]   =   { READ_ONLY,    REG_VERSION_ADDR,   CHAR,   {.char_val      = 0x1a},    {0} },
    [UINT16_RW] =   { FULL_ACCESS,  REG_UINT16_RW_ADDR, UINT16, {.uint16_val    = 0x00},    {0} },
    [INT16_RW]  =   { FULL_ACCESS,  REG_INT16_RW_ADDR,  INT16,  {.int16_val     = 0x00},    {0} },
    [BOOL_RW]   =   { FULL_ACCESS,  REG_BOOL_RW_ADDR,   BOOL,   {.bool_val      = 0x00},    {0} },
    [CHAR_RW]   =   { FULL_ACCESS,  REG_CHAR_RW_ADDR,   CHAR,   {.char_val      = 0x00},    {0} },
    [UINT16_RO] =   { READ_ONLY,    REG_UINT16_RO_ADDR, UINT16, {.uint16_val    = 0x5544},  {0} },
    [INT16_RO]  =   { READ_ONLY,    REG_INT16_RO_ADDR,  INT16,  {.int16_val     = 0x4433},  {0} },
    [UINT32_RO] =   { READ_ONLY,    REG_UINT32_RO_ADDR, UINT32, {.uint32_val    = 0x99887766},  {0} },
    [INT32_RO]  =   { READ_ONLY,    REG_INT32_RO_ADDR,  INT32,  {.int32_val     = 0x55443322},  {0} },
    [UINT32_RW] =   { FULL_ACCESS,  REG_UINT32_RW_ADDR, UINT32, {.uint32_val    = 0x55443322},  {0} },
    [INT32_RW]  =   { FULL_ACCESS,  REG_INT32_RW_ADDR,  INT32,  {.int32_val     = 0x44332211},  {0} },
    [BOOL_RO]   =   { READ_ONLY,    REG_BOOL_RO_ADDR,   BOOL,   {.bool_val      = 0x01},    {0} },
    [CHAR_RO]   =   { READ_ONLY,    REG_CHAR_RO_ADDR,   CHAR,   {.char_val      = 0x15},    {0} },
}, *LP_I2C_REG_DATA;

// Описатель функций
typedef enum rtc_reg_idx_t{
    RTC_NONE    = HW_RTC_BASE - 0x03,
    RTC_ECHO    = HW_RTC_BASE - 0x02,
    RTC_VERSION = HW_RTC_BASE - 0x01,
    RTC_SECONDS = HW_RTC_BASE,
    RTC_MINUTES = HW_RTC_BASE + 0x01,
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
} rtc_reg_idx_t;

reg_t g_i2c_rtc_registers[] = {
    [RTC_VERSION]   = { READ_ONLY,      REG_VERSION_ADDR,   CHAR,     {.char_val    = 0x1a},    {0} },
    [RTC_SECONDS]   = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_MINUTES]   = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_HOURS]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_DAY]       = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_DATE]      = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_MONTH]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_YEAR]      = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_CONTROL]   = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM00]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM01]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM02]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM03]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM04]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM05]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM06]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM07]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM08]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM09]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0A]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0B]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0C]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0D]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0E]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0F]     = { FULL_ACCESS,    REG_VERSION_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} }
} , *LP_I2C_REGISTERS;

