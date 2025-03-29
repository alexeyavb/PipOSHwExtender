#ifndef __ROTARY_DEFS_H
#define __ROTARY_DEFS_H
/*
#include <stdint.h>
#define REG_RVERSION_ADDR   0x21
#define REG_RLEFT_RO_ADDR   0x22
#define REG_RLRIGHT_RO_ADDR 0x23
#define REG_R1BPR_RO_ADDR   0x24
#define REG_R1BUP_RO_ADDR   0x25
#define REG_RUP_RO_ADDR     0x26
#define REG_RDOWN_RO_ADDR   0x27
#define REG_R2BPR_RO_ADDR   0x28
#define REG_R2BUP_RO_ADDR   0x29
#define REG_RD_CPLT_ADDR    0x30

typedef struct reg_rotary_t reg_rotary_t;

typedef enum reg_rotary_idx_t {
    R_NONE = -1,
    R_ECHO = 0,
    R_VERSION,
    R_LEFT,
    R_RIGHT,
    R1_BPR,
    R1_BUP,
    R_UP,
    R_DOWN,
    R2_BPR,
    R2_BUP,
    R_RD_CPLT
} reg_rotary_idx_t;

struct reg_rotary_t {
    uint8_t     access;         //Access
    uint8_t     reg_addr;       //Address
    val_type_t  value_type;     //Value type
    const var_t def_val;        //Default values
    var_t       value;          //Current values
};
*/
#endif //__ROTARY_DEFS_H