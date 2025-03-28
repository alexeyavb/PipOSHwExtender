#include "extender.h"
#include <bsp/board_api.h>
#include <stm32f4xx_hal.h>
void Error_Handler(void)
 {
   __disable_irq();
   while (1)
   {
   }
 }
 