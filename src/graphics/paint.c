/**
 * File              : paint.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 24.03.2021
 * Last Modified Date: 02.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/paint.h"

#include <stdlib.h>
#include <string.h>

struct image *newimg_buffer(const uint8_t width_px, const uint8_t height_px,
                            const char *data, const uint16_t data_bytes) {
  // init image
  struct image *img = (struct image *)malloc(sizeof(struct image));
  img->width_px = width_px;
  img->height_px = height_px;
  const uint16_t area_px = img->width_px * img->height_px;
  const uint16_t area_bytes = area_px / 8;
  img->buf = (uint8_t *)calloc(area_bytes, sizeof(uint8_t));

  // fill image buffer
  const uint16_t data_newbytes =
      (data_bytes < area_bytes) ? data_bytes : area_bytes;
  memcpy(img->buf, (uint8_t *)data, data_newbytes);
  memset(img->buf + data_bytes, 0x00, area_bytes - data_newbytes);
  return img;
}

struct image *newimg_text(const uint8_t width_px, const uint8_t height_px,
                          const char *text[], const uint8_t text_lines,
                          const struct font *font) {
  // init image
  struct image *img = (struct image *)malloc(sizeof(struct image));
  img->width_px = width_px;
  img->height_px = height_px;
  const uint16_t area_px = img->width_px * img->height_px;
  const uint16_t area_bytes = area_px / 8;
  img->buf = (uint8_t *)calloc(area_bytes, sizeof(uint8_t));

  // fill image text
  uint8_t *imgbuf = img->buf;
  const uint8_t line_fonts = img->width_px / font->width_px;
  for (int i = 0; i < text_lines; i++) {
    uint8_t j = 0, k = 0;
    for (; text[i][j] != '\0' && j < line_fonts; j++, k += font->width_px) {
      fontbuf buf = char_to_fontbuf(text[i][j]);
      memcpy(imgbuf, buf, font->width_px);
      imgbuf += font->width_px;
    }
    if (k < img->width_px) {
      memset(imgbuf, 0x00, img->width_px - k);
      imgbuf += img->width_px - k;
    }
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
