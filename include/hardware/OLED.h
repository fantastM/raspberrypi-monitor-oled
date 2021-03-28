/**
 * File              : OLED.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 23.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __OLED_H_
#define __OLED_H_

#include <stdbool.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

bool oled_turn_on(void);

bool oled_display(void);

void oled_turn_off(void);

#endif
