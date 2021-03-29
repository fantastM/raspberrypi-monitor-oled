/**
 * File              : SSD1306.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef _SSD1306_H_
#define _SSD1306_H_

#include <stdint.h>

// SSD1306 datasheet #8.1 and #8.1.5 section
// MCU I2C Interface
#define SLAVE_ADDRESS 0x3C
#define CONTROL_BYTE_WRITE_COMMAND_STREAM 0x00
#define CONTROL_BYTE_WRITE_DATA_STREAM 0x40
#define CONTROL_BYTE_WRITE_SINGLE_COMMAND 0x80
#define CONTROL_BYTE_WRITE_SINGLE_DATA 0xC0

// SSD1306 datasheet #8.7 section
// Graphic Display Data RAM (GDDRAM)
#define PAGE_HEIGHT 8

uint8_t ssd1306_write_command_stream(uint8_t command[], uint16_t len);

uint8_t ssd1306_write_data_stream(uint8_t data[], uint16_t len);

uint8_t ssd1306_write_single_command(uint8_t command);

uint8_t ssd1306_write_signle_data(uint8_t data);

#endif
