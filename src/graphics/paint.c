/**
 * File              : paint.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 29.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/paint.h"

#include <stdlib.h>

struct image *newimg(const uint8_t width, const uint8_t height) {
  struct image *img;
  img->width = width;
  img->height = height;
  uint16_t area_size = width * height;
  img->buf = calloc(area_size, sizeof(uint8_t));
  return img;
}

void freeimg(struct image *img) { free(img->buf); }

screen img_crop(struct image *img, const uint8_t begin) {
  screen newbuf = NULL;
  uint16_t skip = begin * img->width;
  for (int i = 0; i < skip; i++) {
    img->buf++;
  }
  newbuf = img->buf;
  return newbuf;
}
