#include "i2c_register_defs.h"
#ifdef __USE_TEST_REGISTERS
// i2c register descriptor
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
#endif

#ifdef __USE_RTC_REGISTERS
reg_t g_i2c_rtc_registers[] = {
    [RTC_VERSION]   = { READ_ONLY,      HW_RTC_VERSION_ADDR,    CHAR,   {.char_val  = 0x10}, {.char_val = 0x1e} },
    [RTC_SUBSECS]   = { FULL_ACCESS,    HW_RTC_SUBSECS_ADDR,    UINT32, {.uint32_val  = 0x2b2b2b2b}, {.uint32_val = 0x2b2b2b2b} },
    [RTC_SECONDS]   = { FULL_ACCESS,    HW_RTC_SECONDS_ADDR,    CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_MINUTES]   = { FULL_ACCESS,    HW_RTC_MINUTES_ADDR,    CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_HOURS]     = { FULL_ACCESS,    HW_RTC_HOURS_ADDR,      CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_DAY]       = { FULL_ACCESS,    HW_RTC_DAY_ADDR,        CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_DATE]      = { FULL_ACCESS,    HW_RTC_DATE_ADDR,       CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_MONTH]     = { FULL_ACCESS,    HW_RTC_MONTH_ADDR,      CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_YEAR]      = { FULL_ACCESS,    HW_RTC_YEAR_ADDR,       CHAR,   {.char_val  = 0x00},    {0} },
    [RTC_CONTROL]   = { FULL_ACCESS,    HW_RTC_CONTROL_ADDR,    CHAR,   {.char_val  = 0xAA},    {0} },
    [RTC_RAM00]     = { FULL_ACCESS,    HW_RTC_RAM00_ADDR,      CHAR,  {.uint32_val  = 0x00},    {0} },
    [RTC_RAM01]     = { FULL_ACCESS,    HW_RTC_RAM01_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM02]     = { FULL_ACCESS,    HW_RTC_RAM02_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM03]     = { FULL_ACCESS,    HW_RTC_RAM03_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM04]     = { FULL_ACCESS,    HW_RTC_RAM04_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM05]     = { FULL_ACCESS,    HW_RTC_RAM05_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM06]     = { FULL_ACCESS,    HW_RTC_RAM06_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM07]     = { FULL_ACCESS,    HW_RTC_RAM07_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM08]     = { FULL_ACCESS,    HW_RTC_RAM08_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM09]     = { FULL_ACCESS,    HW_RTC_RAM09_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0A]     = { FULL_ACCESS,    HW_RTC_RAM0A_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0B]     = { FULL_ACCESS,    HW_RTC_RAM0B_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0C]     = { FULL_ACCESS,    HW_RTC_RAM0C_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0D]     = { FULL_ACCESS,    HW_RTC_RAM0D_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0E]     = { FULL_ACCESS,    HW_RTC_RAM0E_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} },
    [RTC_RAM0F]     = { FULL_ACCESS,    HW_RTC_RAM0F_ADDR,   UINT32,   {.uint32_val  = 0x00},    {0} }
};

#endif 
