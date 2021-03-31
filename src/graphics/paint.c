/**
 * File              : paint.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 01.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/paint.h"
#include <stdlib.h>
#include <string.h>

struct image *newimg(const uint8_t width_px, const uint8_t height_px,
                     const struct font *font, const uint8_t *text,
                     const uint16_t text_bytes) {
  // init image
  struct image *img = (struct image *)malloc(sizeof(struct image));
  img->width_px = width_px;
  img->height_px = height_px;
  uint16_t area_px = img->width_px * img->height_px;
  uint16_t area_bytes = area_px / sizeof(uint8_t);
  img->buf = (uint8_t *)calloc(area_bytes, sizeof(uint8_t));

  // fill image buffer
  if (font->width_px <= 0 || font->height_px <= 0) { // non-text content
    if (text_bytes < area_bytes) {
      memcpy(img->buf, text, text_bytes);
      memset(img->buf + text_bytes, 0x00, area_bytes - text_bytes);
    } else {
      memcpy(img->buf, text, area_bytes);
    }
  } else { // text content
    uint16_t img_char_num =
        (img->width_px / font->width_px) * (img->height_px / font->height_px);
    // TODO
  }
  return img;
}

void freeimg(struct image *img) {
  free(img->buf);
  free(img);
}

screen cropimg(const struct image *img, const uint8_t start_page) {
  uint16_t skip = start_page * img->width_px;
  return img->buf + skip;
}
