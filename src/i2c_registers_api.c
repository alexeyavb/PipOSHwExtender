#include "i2c_registers_api.h"

extern reg_t g_i2c_reg_data[];
// init register defaults values
void reset_registers_data(void) {
	for (int idx = 1; idx < REGISTER_NUM - 1; idx++) {
		reg_idx_t reg_idx = idx;
		switch (g_i2c_reg_data[reg_idx].value_type) {
		case UNDEFINED:
			break;
		case BOOL:
			g_i2c_reg_data[reg_idx].value.bool_val =
					g_i2c_reg_data[reg_idx].def_val.bool_val;
			break;
		case UINT16:
			g_i2c_reg_data[reg_idx].value.uint16_val =
					g_i2c_reg_data[reg_idx].def_val.uint16_val;
			break;
		case INT16:
			g_i2c_reg_data[reg_idx].value.int16_val =
					g_i2c_reg_data[reg_idx].def_val.int16_val;
			break;
        case UINT32:
			g_i2c_reg_data[reg_idx].value.uint32_val =
					g_i2c_reg_data[reg_idx].def_val.uint32_val;
			break;
		case INT32:
			g_i2c_reg_data[reg_idx].value.int32_val =
					g_i2c_reg_data[reg_idx].def_val.int32_val;
			break;
		case CHAR:
			g_i2c_reg_data[reg_idx].value.char_val =
					g_i2c_reg_data[reg_idx].def_val.char_val;
			break;
		default:
			break;
		}
    }
}

// Get global register address cell number by index
reg_idx_t reg_get_idx(uint8_t address){
	for(int i = 1; i < REGISTER_NUM; i++){
		if (g_i2c_reg_data[i].reg_addr == address){
			return i;
		}
	}
	return NONE;
}

uint8_t reg_get_len(reg_idx_t idx){
	uint8_t data_len = 0;
	switch (g_i2c_reg_data[idx].value_type){
	case BOOL:
	case CHAR:
		data_len = 1;
		break;
	case UINT16:
	case INT16:
		data_len = 2;
		break;
    case UINT32:
    case INT32:
        data_len = 4;
        break;    
	default:
		break;
	}
	return data_len;
}

void reg_ctrl_process_data(reg_idx_t idx){
    switch (idx){
    case UINT16_RW:        
        break;
    case INT16_RW:        
        break;
    default:
        break;
    }
}
