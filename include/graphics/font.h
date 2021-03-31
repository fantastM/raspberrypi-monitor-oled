/**
 * File              : font.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 31.03.2021
 * Last Modified Date: 01.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __FONT_H_
#define __FONT_H_

#include <stdint.h>

typedef uint8_t *fontbuf;

struct font {
  uint8_t width_px;
  uint8_t height_px;
};

fontbuf char_to_fontbuf(const char c);

uint8_t rotate_fontbuf(const fontbuf fontbuf);

#endif
