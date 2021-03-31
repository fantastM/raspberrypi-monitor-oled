/**
 * File              : font.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 31.03.2021
 * Last Modified Date: 31.03.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/font.h"
#include "support/logger.h"
#include <font8x8_basic.h>
#include <signal.h>

font char_to_font(char c) {
  if (c < 0 || c > 0x7F) {
    log_error("Font unsupport char: '%c'\n", c);
    raise(SIGTERM);
  }
  return (font)font8x8_basic[c];
}

void font_to_buf(const uint8_t *buf, const font f) {}
