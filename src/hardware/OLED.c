/**
 * File              : OLED.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "hardware/OLED.h"
#include "hardware/GPIO.h"
#include "hardware/SSD1306.h"
#include "support/logger.h"
#include <stdbool.h>

bool oled_turn_on() {
  if (!gpio_init()) {
    log_error("OLED failed to turn on.\n");
  }
  if (!gpio_i2c_begin()) {
    log_error("OLED failed to turn on.\n");
  }
  /*ssd1306_write_single_command(0xAE); // set Display OFF*/
  return 1;
}

bool oled_display() {}

void oled_turn_off() {
  ssd1306_write_single_command(0xAE); // set Display OFF
  gpio_i2c_end();
  gpio_close();
}
