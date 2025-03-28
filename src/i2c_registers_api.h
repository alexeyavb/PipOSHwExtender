#ifndef __I2C_REGISTERS_API_H_
#define __I2C_REGISTERS_API_H_
#include <stdint.h>
#include "i2c_register_defs.h"

extern void reset_registers_data(void);
extern reg_idx_t reg_get_idx(uint8_t address);
extern uint8_t reg_get_len(reg_idx_t idx);
extern void reg_ctrl_process_data(reg_idx_t idx);

#endif