/**
 * File              : font.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 31.03.2021
 * Last Modified Date: 31.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __FONT_H_
#define __FONT_H_

#include <stdint.h>

#define FONT_WIDTH_PX 8
#define FONT_HEIGHT_PX 8

typedef uint8_t *font;

font char_to_font(char c);

void font_to_buf(const uint8_t *buf, const font f);

#endif
