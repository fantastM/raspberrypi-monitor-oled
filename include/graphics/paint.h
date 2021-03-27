/**
 * File              : paint.h
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 26.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#ifndef __PAINT_H_
#define __PAINT_H_

#include <stdint.h>

struct image {
  uint8_t *buf;
  uint8_t width;
  uint8_t height;
  uint8_t fg_color;
  uint8_t bg_color;
} image;

struct image *new_image(const uint8_t width, const uint8_t height);

/**
 *-------+-------+-------
 *       |       |
 * <=====| image |=====>
 *       |       |
 *-------+-------+-------
 */
struct image *image_crop_horizontal(const struct image *source,
                                    const uint8_t begin, const uint8_t width);

/**
 * |       |
 * |  ^^   |
 * |  ||   |
 * |  ||   |
 * +-------+
 * |       |
 * | image |
 * |       |
 * +-------+
 * |  ||   |
 * |  ||   |
 * |  vv   |
 * |       |
 */
struct image *image_crop_vertical(const struct image *source,
                                  const uint8_t begin, const uint8_t height);

#endif
