/**
 * File              : GPIO.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 27.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "hardware/GPIO.h"
#include "support/logger.h"
#include "support/signal_handler.h"
#include <bcm2835.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int gpio_init() {
  log_debug("GPIO init");
  int r;
  if (!(r = bcm2835_init())) {
    log_error("GPIO init failed. Are you running as root?");
    quit(SIGTERM);
  }
  return r;
}

int gpio_close() {
  log_debug("GPIO close");
  int r;
  if (!(r = bcm2835_close())) {
    log_error("GPIO close failed.");
    quit(SIGTERM);
  }
  return r;
}

int gpio_i2c_begin() {
  log_debug("GPIO I2C begin");
  int r;
  if (!(r = bcm2835_i2c_begin())) {
    log_error("GPIO I2C begin failed. Are you running as root?");
    quit(SIGTERM);
  }
  return r;
}

void gpio_i2c_end() {
  log_debug("GPIO I2C end");
  bcm2835_i2c_end();
}

void gpio_i2c_set_slave_address(uint8_t addr) {
  log_debug("GPIO I2C set salve address");
  bcm2835_i2c_setSlaveAddress(addr);
}

void gpio_i2c_set_clock_divider(uint16_t divider) {
  log_debug("GPIO I2C set clock divider");
  bcm2835_i2c_setClockDivider(divider);
}

void gpio_i2c_set_baudrate(uint16_t baudrate) {
  log_debug("GPIO I2C set baudrate");
  bcm2835_i2c_set_baudrate(baudrate);
}

uint8_t gpio_i2c_write(const char *buf, uint16_t len) {
  log_debug("GPIO I2C write");
  return bcm2835_i2c_write(buf, len);
}

uint8_t gpio_i2c_read(char *buf, uint16_t len) {
  log_debug("GPIO I2C read");
  return bcm2835_i2c_read(buf, len);
}
