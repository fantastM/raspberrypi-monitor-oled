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

  uint8_t command[2];
  command[0] = 0xA8;
  command[1] = 0x3F;
  log_debug("OLED -- Set MUX Ratio\n");
  ssd1306_write_command_stream(command, 2);

  command[0] = 0xD3;
  command[1] = 0x00;
  log_debug("OLED -- Set Display Offset\n");
  ssd1306_write_command_stream(command, 2);

  log_debug("OLED -- Set Display Start Line\n");
  ssd1306_write_single_command(0x40);

  log_debug("OLED -- Set Segment re-map\n");
  ssd1306_write_single_command(0xA1);

  log_debug("OLED -- Set COM Output Scan Direction\n");
  ssd1306_write_single_command(0xC8);

  command[0] = 0xDA;
  command[1] = 0x02;
  log_debug("OLED -- Set COM Pins hardware configuration\n");
  ssd1306_write_command_stream(command, 2);

  command[0] = 0x81;
  command[1] = 0x7F;
  log_debug("OLED -- Set Contrast Control\n");
  ssd1306_write_command_stream(command, 2);

  log_debug("OLED -- Disable Entire Display On\n");
  ssd1306_write_single_command(0xA4);

  log_debug("OLED -- Set Normal Display\n");
  ssd1306_write_single_command(0xA6);

  command[0] = 0xD5;
  command[1] = 0x80;
  log_debug("OLED -- Set Osc Frequency\n");
  ssd1306_write_command_stream(command, 2);

  command[0] = 0x8D;
  command[1] = 0x14;
  log_debug("OLED -- Enable charge pump regulator\n");
  ssd1306_write_command_stream(command, 2);

  log_debug("OLED -- Display On\n");
  ssd1306_write_single_command(0xAF);
  return true;
}

bool oled_display(screen screen) {
  log_info("OLED -- Rendering sreen\n");
  ssd1306_write_single_command(0x00);
  ssd1306_write_single_command(0x10);
  ssd1306_write_data_stream(screen, 128 * 32);
  return true;
}

void oled_turn_off() {
  ssd1306_write_single_command(0xAE); // Display OFF
  gpio_i2c_end();
  gpio_close();
}
