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
  ssd1306_write_command_stream(command); // Set MUX Ratio

  command[0] = 0x3D;
  command[1] = 0x00;
  ssd1306_write_command_stream(command); // Set Display Offset

  ssd1306_write_single_command(0x40); // Set Display Start Line

  ssd1306_write_single_command(0xA0); // Set Segment re-map

  ssd1306_write_single_command(0xC0); // Set COM Output Scan Direction

  command[0] = 0xDA;
  command[1] = 0x02;
  ssd1306_write_command_stream(command); // Set COM Pins hardware configuration

  command[0] = 0x81;
  command[1] = 0x7F;
  ssd1306_write_command_stream(command); // Set Contrast Control

  ssd1306_write_single_command(0xA4); // Disable Entire Display On

  ssd1306_write_single_command(0xA6); // Disable Entire Display On

  command[0] = 0xD5;
  command[1] = 0x80;
  ssd1306_write_command_stream(command); // Set Osc Frequency

  command[0] = 0x8D;
  command[1] = 0x14;
  ssd1306_write_command_stream(command); // Enable charge pump regulator

  ssd1306_write_single_command(0xAF); // Display On
  return true;
}

bool oled_display() {}

void oled_turn_off() {
  ssd1306_write_single_command(0xAE); // Display OFF
  gpio_i2c_end();
  gpio_close();
}
