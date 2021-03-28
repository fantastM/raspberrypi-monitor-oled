/**
 * File              : GPIO.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "hardware/GPIO.h"
#include "support/logger.h"
#include "support/signal_handler.h"
#include <bcm2835.h>
#include <signal.h>
#include <stdint.h>

int gpio_init() {
  log_debug("GPIO init\n");
  int r;
  if (!(r = bcm2835_init())) {
    log_error("GPIO init failed. Are you running as root?\n");
    quit(SIGTERM);
  }
  return r;
}

int gpio_close() {
  log_debug("GPIO close\n");
  int r;
  if (!(r = bcm2835_close())) {
    log_error("GPIO close failed.\n");
    quit(SIGTERM);
  }
  return r;
}

int gpio_i2c_begin() {
  log_debug("GPIO I2C begin\n");
  int r;
  if (!(r = bcm2835_i2c_begin())) {
    log_error("GPIO I2C begin failed. Are you running as root?\n");
    quit(SIGTERM);
  }
  return r;
}

void gpio_i2c_end() {
  log_debug("GPIO I2C end\n");
  bcm2835_i2c_end();
}

void gpio_i2c_set_slave_address(uint8_t addr) {
  log_debug("GPIO I2C set salve address: 0x%X\n", addr);
  bcm2835_i2c_setSlaveAddress(addr);
}

void gpio_i2c_set_clock_divider(uint16_t divider) {
  log_debug("GPIO I2C set clock divider\n");
  bcm2835_i2c_setClockDivider(divider);
}

void gpio_i2c_set_baudrate(uint16_t baudrate) {
  log_debug("GPIO I2C set baudrate\n");
  bcm2835_i2c_set_baudrate(baudrate);
}

bool gpio_i2c_write(const char *buf, uint32_t len) {
  log_debug("GPIO I2C write sth, len: %d\n", len);
  bcm2835I2CReasonCodes code = bcm2835_i2c_write(buf, len);
  if (code != BCM2835_I2C_REASON_OK) {
    log_error("GPIO I2C write error, bcm2835I2CReasonCodes: %d. Read the "
              "bcm2835 document for more details: \n\t%s\n",
              code, BCM2835_CONSTANTS_URL);
    return false;
  }
  return true;
}

bool gpio_i2c_read(char *buf, uint32_t len) {
  log_debug("GPIO I2C rea\n");
  bcm2835I2CReasonCodes code = bcm2835_i2c_read(buf, len);
  if (code != BCM2835_I2C_REASON_OK) {
    log_error("GPIO I2C read error, bcm2835I2CReasonCodes: %d. Read the "
              "bcm2835 document for more details: \n\t%s\n",
              code, BCM2835_CONSTANTS_URL);
    return false;
  }
  return true;
}
