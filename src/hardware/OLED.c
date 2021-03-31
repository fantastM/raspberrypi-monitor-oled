/**
 * File              : OLED.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 31.03.2021
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
  ssd1306_write_single_command(0xA0);

  log_debug("OLED -- Set COM Output Scan Direction\n");
  ssd1306_write_single_command(0xC0);

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

bool oled_display(const uint8_t *buf) {
  uint8_t command[3];
  command[0] = 0x20;
  command[1] = 0x00;
  log_debug("OLED -- Set Memory Addressing Mode\n");
  ssd1306_write_command_stream(command, 2);

  command[0] = 0x21;
  command[1] = 0x00;
  command[2] = SCREEN_WIDTH_PX - 1;
  log_debug("OLED -- Set Column Address\n");
  ssd1306_write_command_stream(command, 3);

  command[0] = 0x22;
  command[1] = 0x00;
  command[2] = SCREEN_PAGE_NUM - 1;
  log_debug("OLED -- Set Page Address\n");
  ssd1306_write_command_stream(command, 3);

  log_debug("OLED -- Rendering sreen\n");
  ssd1306_write_data_stream(buf, SCREEN_WIDTH_PX * SCREEN_PAGE_NUM);
  return true;
}

void oled_turn_off() {
  log_debug("OLED -- Display Off\n");
  ssd1306_write_single_command(0xAE);

  gpio_i2c_end();
  gpio_close();
}
