/**
 * File              : paint.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 31.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/paint.h"
#include "hardware/SSD1306.h"
#include <stdlib.h>

struct image *newimg(const uint8_t width_px, const uint8_t height_px) {
  struct image *img = malloc(sizeof(struct image));
  img->width_px = width_px;
  img->height_px = height_px;
  img->buf = calloc(img->width_px * img->height_px, sizeof(uint8_t));
  return img;
}

void freeimg(struct image *img) {
  free(img->buf);
  free(img);
}

screen img_crop(struct image *img, const uint8_t start_page) {
  uint16_t skip = start_page * img->width_px;
  return img->buf + skip;
}
