#include "i2c_registers_api.h"

rtc_reg_idx_t reg_rtc_get_idx(uint8_t address){
	for(int i = RTC_REGISTER_VERSION; i < RTC_REGISTER_SZ; i++){
		if (g_i2c_rtc_registers[i].reg_addr == address){
			return i;
		}
	}
	return RTC_NONE;
}

uint8_t reg_rtc_get_len(rtc_reg_idx_t idx){
	uint8_t data_len = 0;
	switch (g_i2c_rtc_registers[idx].value_type){
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

void reg_rtc_ctrl_process_data(rtc_reg_idx_t idx){
    switch (idx){
    case RTC_CONTROL:
		break;
	case RTC_RAM00:
	case RTC_RAM01:
	case RTC_RAM02:
	case RTC_RAM03:
	case RTC_RAM04:
	case RTC_RAM05:
	case RTC_RAM06:
	case RTC_RAM07:
	case RTC_RAM08:
	case RTC_RAM09:
	case RTC_RAM0A:
	case RTC_RAM0B:
	case RTC_RAM0C:
	case RTC_RAM0D:
	case RTC_RAM0E:
	case RTC_RAM0F:
		break;
	default:
		break;
	}
}

#ifdef __USE_TEST_REGISTERS
/////////////////////////////////////////////////////////
/// @brief tet register
/////

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
    case UINT32_RW:        
        break;
    case INT32_RW:
        break;
    default:
        break;
    }
}
#endif