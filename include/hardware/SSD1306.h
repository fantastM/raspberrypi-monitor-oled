/**
 * File              : SSD1306.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 24.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef _SSD1306_H_
#define _SSD1306_H_

#include <stdbool.h>

// SSD1306 datasheet #8.1 and #8.1.5 section
#define SSD1306_SLAVE_ADDRESS_1 0x3C
#define SSD1306_SLAVE_ADDRESS_2 0x3D

// SSD1306 datasheet #8.7 section
#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define PAGE_HEIGHT 8
#define PAGE_LEN (SCREEN_HEIGHT / PAGE_HEIGHT)

bool ssd1306_start_condition();

#endif
