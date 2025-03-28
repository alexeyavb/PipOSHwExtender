#include "i2c_register_defs.h"
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
    [UINT32_RW] =   { READ_ONLY,    REG_UINT32_RW_ADDR, UINT32, {.uint32_val    = 0x55443322},  {0} },
    [INT32_RW]  =   { READ_ONLY,    REG_INT32_RW_ADDR,  INT32,  {.int32_val     = 0x44332211},  {0} },
    [BOOL_RO]   =   { READ_ONLY,    REG_BOOL_RO_ADDR,   BOOL,   {.bool_val      = 0x01},    {0} },
    [CHAR_RO]   =   { READ_ONLY,    REG_CHAR_RO_ADDR,   CHAR,   {.char_val      = 0x15},    {0} },
};
