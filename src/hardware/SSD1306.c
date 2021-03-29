/**
 * File              : SSD1306.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 28.03.2021
 * Last Modified Date: 30.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "support/logger.h"
#include <hardware/GPIO.h>
#include <hardware/SSD1306.h>
#include <string.h>

uint8_t ssd1306_write_command_stream(const uint8_t *command,
                                     const uint16_t len) {
  uint8_t buf[len + 1];
  buf[0] = CONTROL_BYTE_WRITE_COMMAND_STREAM;
  memcpy(&buf[1], command, len);

  gpio_i2c_set_slave_address(SLAVE_ADDRESS);
  uint8_t result = gpio_i2c_write(buf, len + 1);
  return result;
}

uint8_t ssd1306_write_data_stream(const uint8_t *data, const uint16_t len) {
  uint8_t buf[len + 1];
  buf[0] = CONTROL_BYTE_WRITE_DATA_STREAM;
  memcpy(&buf[1], data, len);

  gpio_i2c_set_slave_address(SLAVE_ADDRESS);
  uint8_t result = gpio_i2c_write(buf, len + 1);
  return result;
}

uint8_t ssd1306_write_single_command(const uint8_t command) {
  uint8_t buf[2];
  buf[0] = CONTROL_BYTE_WRITE_SINGLE_COMMAND;
  buf[1] = command;

  gpio_i2c_set_slave_address(SLAVE_ADDRESS);
  uint8_t result = gpio_i2c_write(buf, 2);
  return result;
}

uint8_t ssd1306_write_single_data(const uint8_t data) {
  uint8_t buf[2];
  buf[0] = CONTROL_BYTE_WRITE_SINGLE_DATA;
  buf[1] = data;

  gpio_i2c_set_slave_address(SLAVE_ADDRESS);
  uint8_t result = gpio_i2c_write(buf, 2);
  return result;
}
