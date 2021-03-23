/**
 * File              : GPIO.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 24.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __GPIO_H_
#define __GPIO_H_

#include "support.h"
#include <signal.h>

/**
 * GPIO init
 *
 * Initialise the library by opening /dev/mem (if you are root) or /dev/gpiomem
 * (if you are not) and getting pointers to the internal memory for BCM 2835
 * device registers.
 */
int gpio_init(void);

/**
 * GPIO close
 */
int gpio_close(void);

/**
 * Start I2C operations.
 */
int gpio_i2c_begin(void);

/**
 * Complete I2C operations.
 */
void gpio_i2c_end(void);

/**
 * Sets the I2C slave address.
 */
void gpio_i2c_set_slave_address(UBYTE addr);

/**
 * Sets the I2C clock divider and therefore the I2C clock speed.
 */
void gpio_i2c_set_clock_divider(UWORD divider);

/**
 * Sets the I2C clock divider by converting the baudrate parameter to the
 * equivalent I1C clock divider.
 */
void gpio_i2c_set_baudrate(UWORD baudrate);

/**
 * Transfers any number of bytes to the currently selected I2C slave. (as
 * previously set by
 */
UBYTE gpio_i2c_write(const char *buf, UWORD len);

/**
 * Transfers any number of bytes from the currently selected I2C slave. (as
 * previously set by
 */
UBYTE gpio_i2c_read(char *buf, UWORD len);

#endif
