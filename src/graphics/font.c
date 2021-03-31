/**
 * File              : font.c
 * License           : GNU GENERAL PUBLIC LICENSE v3.0
 * Author            : fantasticmao <maomao8017@gmail.com>
 * Date              : 31.03.2021
 * Last Modified Date: 01.04.2021
 * Last Modified By  : fantasticmao <maomao8017@gmail.com>
 */
#include "graphics/font.h"
#include "support/logger.h"
#include <font8x8_basic.h>
#include <signal.h>

fontbuf char_to_fontbuf(const char c) {
  if (c < 0 || c > 0x7F) {
    log_error("Font unsupport char: '%c'\n", c);
    raise(SIGTERM);
  }
  return (fontbuf)font8x8_basic[c];
}

uint8_t rotate_fontbuf(const fontbuf fontbuf) { return NULL; }
