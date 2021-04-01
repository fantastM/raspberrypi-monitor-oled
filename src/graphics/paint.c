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
                     const struct font *font, const char *data,
                     const uint16_t data_bytes) {
  // init image
  struct image *img = (struct image *)malloc(sizeof(struct image));
  img->width_px = width_px;
  img->height_px = height_px;
  const uint16_t area_px = img->width_px * img->height_px;
  const uint16_t area_bytes = area_px / 8;
  img->buf = (uint8_t *)calloc(area_bytes, sizeof(uint8_t));

  // fill image buffer
  if (font->width_px <= 0 || font->height_px <= 0) { // non-text content
    const uint16_t data_newbytes =
        (data_bytes < area_bytes) ? data_bytes : area_bytes;
    memcpy(img->buf, (uint8_t *)data, data_newbytes);
    memset(img->buf + data_bytes, 0x00, area_bytes - data_newbytes);
  } else { // text content
    const uint16_t area_fonts = area_bytes / font->height_px;
    const uint16_t text_fonts =
        (data_bytes < area_fonts) ? data_bytes : area_fonts;
    uint8_t *imgbuf = img->buf;
    for (int i = 0; i < text_fonts; i++) {
      fontbuf buf = char_to_fontbuf('c');
      buf = rotate_fontbuf(buf);
      // 'A' bitmap
      uint8_t a[] = {0x00, 0x00, 0x7C, 0x7E, 0x13, 0x13, 0x7E, 0x7C};
      memcpy(imgbuf, a, font->height_px);
      imgbuf += font->height_px;
    }
    memset(imgbuf, 0x00, area_fonts - text_fonts);
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
