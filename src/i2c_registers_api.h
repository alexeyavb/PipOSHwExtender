#ifndef __I2C_REGISTERS_API_H_
#define __I2C_REGISTERS_API_H_
#include <stdint.h>
#include "tusb_config.h"
#include "i2c_register_defs.h"
// test registers
#ifdef __USE_TEST_REGISTERS
extern void reset_registers_data(void);
extern reg_idx_t reg_get_idx(uint8_t address);
extern uint8_t reg_get_len(reg_idx_t idx);
extern void reg_ctrl_process_data(reg_idx_t idx);
#endif

#ifdef __USE_RTC_REGISTERS
// working register
extern rtc_reg_idx_t reg_rtc_get_idx(uint8_t address);
extern uint8_t reg_rtc_get_len(rtc_reg_idx_t idx);
extern void reg_rtc_ctrl_process_data(rtc_reg_idx_t idx);
#endif 


#endif