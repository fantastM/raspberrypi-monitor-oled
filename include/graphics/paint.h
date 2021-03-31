/**
 * File              : paint.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 01.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __PAINT_H_
#define __PAINT_H_

#include "font.h"
#include <stdint.h>

typedef uint8_t *screen;

struct image {
  uint8_t width_px;
  uint8_t height_px;
  uint8_t *buf;
};

struct image *newimg(const uint8_t width_px, const uint8_t height_px,
                     const struct font *font, const uint8_t text[],
                     const uint16_t text_bytes);

void freeimg(struct image *img);

/**
 * |        |
 * |   ^^   |
 * |   ||   |
 * |   ||   |
 * +--------+
 * |        |
 * | screen |
 * |        |
 * +--------+
 * |   ||   |
 * |   ||   |
 * |   vv   |
 * |        |
 */
screen cropimg(const struct image *img, const uint8_t start_page);

#endif
