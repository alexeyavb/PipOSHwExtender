#include <stm32f4xx_hal.h>
#include "i2c_register_defs.h"
#include "i2c_registers_api.h"
#include "i2c.h"

extern I2C_HandleTypeDef I2CHandle;
extern int board_uart_write(void const *buf, int len);
extern unsigned int strlen(const char* buff);

void I2C1_EV_IRQHandler(void){
   HAL_I2C_EV_IRQHandler(&I2CHandle);
   HAL_I2C_EnableListen_IT(&I2CHandle);
}

void I2C1_ER_IRQHandler(void){
   HAL_I2C_ER_IRQHandler(&I2CHandle);   
   HAL_I2C_EnableListen_IT(&I2CHandle);
} 

#ifdef __USE_RTC_REGISTERS
static rtc_i2c_s temporary_reg = {
	.curr_idx = RTC_NONE,
    .reg_addr_rcvd = 0x00,
    .reg_address = 0x00,
};

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
    
    if(TransferDirection == I2C_DIRECTION_TRANSMIT){
        // Мастер пишет какие то данные
        // Первый запрос всегда 1 байт и содержит адрес регистра
        // Сохраняем в temporary_reg.reg_address
        HAL_I2C_Slave_Sequential_Receive_IT(hi2c, &temporary_reg.reg_address, 1, I2C_FIRST_FRAME); 
    }
    else{
        // Мастер хочет считать данные
        // Возвращаем данные которые лежат в запрошенном регистре (адре сохранен в предыдущем входе)
        temporary_reg.curr_idx = reg_rtc_get_idx(temporary_reg.reg_address);
        if(
                    temporary_reg.curr_idx != RTC_NONE
                    && temporary_reg.curr_idx != RTC_ECHO
        ){
                uint8_t *pData =((uint8_t*)&g_i2c_rtc_registers[temporary_reg.curr_idx].value.uint32_val);
                uint8_t Size = reg_rtc_get_len(temporary_reg.curr_idx);
                HAL_I2C_Slave_Sequential_Transmit_IT(hi2c, pData, Size, I2C_LAST_FRAME);
        }     
    }    
    UNUSED(AddrMatchCode);    
    UNUSED(TransferDirection);
}


void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
    // Мастер хочет писать данные в регистр
    // коллбэк вызывается после основного запроса на запись. в первый раз это будет адрес регистра.
    // в предыдущей функции
    // Второй раз, если это запрос на запись, это будет полезная нагрузка
    if(!temporary_reg.reg_addr_rcvd){
        // master wait for data rcv
        temporary_reg.reg_addr_rcvd = 1;
        temporary_reg.curr_idx = reg_rtc_get_idx(temporary_reg.reg_address);
        // check access
        if(
            (temporary_reg.curr_idx != RTC_NONE && temporary_reg.curr_idx != RTC_ECHO)
                && (g_i2c_rtc_registers[temporary_reg.curr_idx].access != READ_ONLY)
        ){
            uint8_t *pData =((uint8_t*)&g_i2c_rtc_registers[temporary_reg.curr_idx].value.uint32_val);
            uint8_t Size = reg_rtc_get_len(temporary_reg.curr_idx);
            HAL_I2C_Slave_Sequential_Receive_IT(hi2c, pData, Size, I2C_NEXT_FRAME);
        }
    } else
    {
        // callback rerturned after register callback 
        temporary_reg.reg_addr_rcvd = 0;
        reg_rtc_ctrl_process_data(temporary_reg.curr_idx);
        temporary_reg.curr_idx = RTC_NONE;
    }

    HAL_I2C_EnableListen_IT(hi2c);
    UNUSED(hi2c);
}
#endif
/// @brief Test registers all worked
#ifdef __USE_TEST_REGISTERS
static i2c_s temporary_reg = {
	.curr_idx = NONE,
    .reg_addr_rcvd = 0x00,
    .reg_address = 0x00
};

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
    
    if(TransferDirection == I2C_DIRECTION_TRANSMIT){
        // Мастер пишет какие то данные
        // Первый запрос всегда 1 байт и содержит адрес регистра
        // Сохраняем в temporary_reg.reg_address
        HAL_I2C_Slave_Sequential_Receive_IT(hi2c, &temporary_reg.reg_address, 1, I2C_FIRST_FRAME); 
    }
    else{
        // Мастер хочет считать данные
        // Возвращаем данные которые лежат в запрошенном регистре (адре сохранен в предыдущем входе)
        temporary_reg.curr_idx = reg_get_idx(temporary_reg.reg_address);
        if(
                    temporary_reg.curr_idx != NONE
                    && temporary_reg.curr_idx != ECHO
        ){
                uint8_t *pData =((uint8_t*)&g_i2c_reg_data[temporary_reg.curr_idx].value.uint16_val);
                uint8_t Size = reg_get_len(temporary_reg.curr_idx);
                HAL_I2C_Slave_Sequential_Transmit_IT(hi2c, pData, Size, I2C_LAST_FRAME);
        }     
    }    
    UNUSED(AddrMatchCode);    
    UNUSED(TransferDirection);
}


void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
    // Мастер хочет писать данные в регистр
    // коллбэк вызывается после основного запроса на запись. в первый раз это будет адрес регистра.
    // в предыдущей функции
    // Второй раз, если это запрос на запись, это будет полезная нагрузка
    if(!temporary_reg.reg_addr_rcvd){
        // master wait for data rcv
        temporary_reg.reg_addr_rcvd = 1;
        temporary_reg.curr_idx = reg_get_idx(temporary_reg.reg_address);
        // check access
        if(
            (temporary_reg.curr_idx != NONE && temporary_reg.curr_idx != ECHO)
                && (g_i2c_reg_data[temporary_reg.curr_idx].access != READ_ONLY)
        ){
            uint8_t *pData =((uint8_t*)&g_i2c_reg_data[temporary_reg.curr_idx].value.uint16_val);
            uint8_t Size = reg_get_len(temporary_reg.curr_idx);
            HAL_I2C_Slave_Sequential_Receive_IT(hi2c, pData, Size, I2C_NEXT_FRAME);
        }
    } else
    {
        // callback rerturned after register callback 
        temporary_reg.reg_addr_rcvd = 0;
        reg_ctrl_process_data(temporary_reg.curr_idx);
        temporary_reg.curr_idx = NONE;
    }

    HAL_I2C_EnableListen_IT(hi2c);
    UNUSED(hi2c);
}
#endif

void HAL_I2C_ListenCpltCallback (I2C_HandleTypeDef *hi2c){
    HAL_I2C_EnableListen_IT(hi2c);
}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c){    
    temporary_reg.reg_addr_rcvd = 0;
    HAL_I2C_EnableListen_IT(hi2c);
    UNUSED(hi2c);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
        //HAL_I2C_ERROR_NONE       0x00000000U    /*!< No error           */
        //HAL_I2C_ERROR_BERR       0x00000001U    /*!< BERR error         */
        //HAL_I2C_ERROR_ARLO       0x00000002U    /*!< ARLO error         */
        //HAL_I2C_ERROR_AF         0x00000004U    /*!< Ack Failure error  */
        //HAL_I2C_ERROR_OVR        0x00000008U    /*!< OVR error          */
        //HAL_I2C_ERROR_DMA        0x00000010U    /*!< DMA transfer error */
        //HAL_I2C_ERROR_TIMEOUT    0x00000020U    /*!< Timeout Error      */
        uint32_t error_code = HAL_I2C_GetError(hi2c);
        if (error_code != HAL_I2C_ERROR_AF){}
        HAL_I2C_EnableListen_IT(hi2c);
}
