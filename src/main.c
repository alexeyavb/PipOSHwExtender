/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <bsp/board_api.h>
#include <stm32f4xx_hal.h>

#include "rtcclock.h"

/* Blink pattern
 * - 250 ms  : button is not pressed
 * - 1000 ms : button is pressed (and hold)
 */
enum blink_intervals{
  BLINK_PROCESS = 25,
  BLINK_ERROR = 100,
  BLINK_PRESSED = 250,
  BLINK_UNPRESSED = 1000
};

enum sync_time_interval{
  NO_SYNC = -1,
  FIRST_SYNC = 100,
  NEXT_SYNC = 1000,
  NORMAL_SYNC = 5000
};

static uint32_t interval_ms = 0;
static uint32_t board_ms = 0;

//timesynchronization variables
// {
static uint32_t synct_interval_ms = 0;
static bool first_sync = true;
// }

#define HELLO_STR   "Hello from TinyUSB\r\n\0"
int main(void) {

  board_init();
  board_led_write(true);

  board_uart_write(HELLO_STR, strlen(HELLO_STR));

  uint32_t start_ms = 0;
  bool led_state = false;

  uint32_t start_tsync_ms = 0;

  while (1) {
    // shared
    interval_ms = board_button_read() ? BLINK_PRESSED : BLINK_UNPRESSED;
    
    // timesync
    synct_interval_ms = first_sync ? FIRST_SYNC : NORMAL_SYNC;
    first_sync = true;

    // Blink and print every interval ms
    board_ms = board_millis() ; // blinc calculation
    if (!(board_ms - start_ms < interval_ms)) {
      start_ms = board_ms;
      board_led_write(led_state);
      led_state = 1 - led_state; // toggle
    }
    
    board_ms = board_millis() ; // tymesync calculation
    if(!(board_ms - start_tsync_ms < synct_interval_ms)) {
      start_tsync_ms = board_ms;
      // Read current fag in i2c register
      uint32_t ts_current_flag = GetHRTC_CurrentControlRegisterFlag();
      if(!(ts_current_flag == 0xAA || ts_current_flag == 0xBB || ts_current_flag == 0xDD)){
        // no stop update flags, trying send timestamp to registers
        SendStartHandshakeCmd();
        SendCurrentTimestamp_to_I2C_Register();
      }

      // Received handshake ok from board
      if(ts_current_flag == 0xBB){
        rtc_timestamp_t* tss;
        tss = ReadCurrentTimestamp_from_I2C_Register();        
        UNUSED(tss);
      }

      // Received timesync ok from board
      if(ts_current_flag == 0xCC){
        
      }

      // Received timestamp from board to mcu
      if(ts_current_flag == 0xDD){

      }

      // Send datetimesync from board to mcu
      if(ts_current_flag == 0xEE){

      }


    }
    // // echo
    // uint8_t ch;
    // if (board_uart_read(&ch, 1) > 0) {
    //   board_uart_write(&ch, 1);
    // }
  }
}

#if TUSB_MCU_VENDOR_ESPRESSIF
void app_main(void) {
  main();
}
#endif
