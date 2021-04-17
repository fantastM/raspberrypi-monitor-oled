/**
 * File              : paint.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 17.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __PAINT_H_
#define __PAINT_H_

#include <stdint.h>

#include "font.h"

typedef uint8_t *screen;

struct image {
  uint8_t width_px;
  uint8_t height_px;
  uint8_t *buf;
};

struct image *newimg(const uint8_t width_px, const uint8_t height_px);

void fillimg_buffer(struct image *img, const char data[], uint16_t data_bytes);

void fillimg_text(struct image *img, const char *text[], uint8_t text_lines,
                  const struct font *font);

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
screen cropimg(const struct image *img, uint8_t start_page);

#endif
